#include <err.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/x509.h>

#define PREFIX_PATH "./"

#define CACERT_FILE PREFIX_PATH"cacert.pem"

#define SERVER_CERT_FILE PREFIX_PATH"lis.cert"
//#define CACERT_FILE SERVER_CERT_FILE

#define MAX_BUFSIZE 4096

void bioToString(BIO* b, const char* fileName){
    char buf [MAX_BUFSIZE] = {0};
    const int ret = BIO_read(b, buf, MAX_BUFSIZE - 1);
    if (ret == 0 || ret == -1) printf("%s: error returned by 0 or 1\n", fileName);
    else if (ret == -2) printf("%s: this read operation is not supported...\n", fileName);
    else printf("%s: read was successful! String is:\n %s\n", fileName, buf);
}

int main(){
    //read in the bio and X509 structs
   BIO* cacertBio = BIO_new(BIO_s_file());
   if (BIO_read_filename(cacertBio, CACERT_FILE) <= 0) err(1, "can't BIO_read_filename on %s", CACERT_FILE);
   //try reading BIO to string...
   //bioToString(cacertBio, CACERT_FILE);
   X509* cacertx509;
   if (!(cacertx509 = PEM_read_bio_X509(cacertBio, NULL, NULL, NULL))) err(1, "can't PEM_read_bio_X509 on %s", CACERT_FILE);

   BIO* serverCertBio = BIO_new(BIO_s_file());
   if (BIO_read_filename(serverCertBio, SERVER_CERT_FILE) <= 0) err(1, "can't BIO_read_filename on %s", SERVER_CERT_FILE);
   //try reading BIO to string...
   //bioToString(serverCertBio, SERVER_CERT_FILE);
   X509* serverCertx509;
   if (!(serverCertx509 = PEM_read_bio_X509(serverCertBio, NULL, NULL, NULL))) err(1, "can't PEM_read_bio_X509 on %s", SERVER_CERT_FILE);






   //add CA file into context
   X509_STORE* trustedCertStore;
   if (!(trustedCertStore = X509_STORE_new()))  err(1, "can't X509_STORE_new!");
   X509_STORE_CTX* context;
   if (!(context = X509_STORE_CTX_new()))  err(1, "can't X509_STORE_CTX_new!");
   if (X509_STORE_add_cert(trustedCertStore, cacertx509) == 0) err(1, "can't X509_STORE_add_cert trustedCertStore!");
   //set up the context with the trustedCertStore
   if (X509_STORE_CTX_init(context, trustedCertStore, serverCertx509, NULL) == 0) err(1, "can't X509_STORE_CTX_init!");

   //lastly, we verify the cert
   if (X509_verify_cert(context) == 1) printf("certificate successfully verified!\n");
   else  printf("certificate verify FAILED!\n");











   X509_STORE_CTX_free(context);
   X509_STORE_free(trustedCertStore);

   X509_free(cacertx509);
   BIO_free(cacertBio); 

   X509_free(serverCertx509);
   BIO_free(serverCertBio); 
}
