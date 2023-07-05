#include <bits/stdc++.h>
#include <regex.h>

#define MAX_GROUPING 10
#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

//static const char *const str =
//       "1) John Driverhacker;\n2) John Doe;\n3) John Foo;\n";

//static const char *const str =
//       "3) John Foo";
//static const char *const re = "John.*o";

//static const char *const str = "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
//static const char *const str = "-fff.ffffffffffffffffffffffffffffffffffffffffffffffffffffffff3";
//static const char *const str = "fff.fffff\nfffffffffffffffffffffffffffffffffffffffffffffffffff3";
//static const char *const str = "1.2.23.4";

static const char *const str = "999";
//static const char *const str = "mymail.somecollege.edu";
//static const char *const str = "NONE";
//static const char *const str = "";
//static const char *const str = "1.23-3.1-34_4.a2.";
//static const char *const str = "1.2-33.1344.a2.";
//static const char *const str = "1.23-3.1-344.a2.";

//static const char *const re = "^(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9_-]{0,61}[a-zA-Z0-9])\\.)*([a-zA-Z]|[a-zA-Z][a-zA-Z0-9_-]{0,61}[a-zA-Z0-9])(\\.)?$";

//static const char *const re = "[0-9]+\\000";
//static const char *const re = "[0-9]+\\x00";
static const char *const re = "[0-9]+\\x00";

/*
hand generated:
^(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9_-]{0,61}[a-zA-Z0-9])\\.)*([a-zA-Z]|[a-zA-Z][a-zA-Z0-9_-]{0,61}[a-zA-Z0-9])(\\.)?$

macro generated:
^(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9_-]{0,61}[a-zA-Z0-9])\\.)*([a-zA-Z]|[a-zA-Z][a-zA-Z0-9_-]{0,61}[a-zA-Z0-9])(\\.)?$
*/



//static const char *const re = "(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\\-\\_]{0,61}[a-zA-Z0-9])\\.)*([a-zA-Z]|[a-zA-Z][a-zA-Z0-9\\-\\_]{0,61}[a-zA-Z0-9])(\\.)?";

//static const char *const re = "(?=^.{4,253}$)(^((?!-)[a-zA-Z0-9-]{0,62}[a-zA-Z0-9]\\.)+[a-zA-Z]{2,63}$)";
//static const char *const re = "^((.{1,63}\\.){1,127}[a-z0-9-]+\\.?)$";

/*
1) John Driverhacker;\2) John Doe;\3) John Foo;\;

3) John Foo
*/

int main(void)
{
   static const char *s = str;
   regex_t     regex;
   regmatch_t  pmatch[MAX_GROUPING];
   regoff_t    off, len;

   if (regcomp(&regex, re, REG_EXTENDED))
       exit(EXIT_FAILURE);

   printf("String = \"%s\"\n", str);
   printf("Matches:\n");

   for (unsigned int i = 0; ; i++) {
       if (regexec(&regex, s, ARRAY_SIZE(pmatch), pmatch, 0)){
            printf("regexec failed!\n");
           break;
        }

       off = pmatch[0].rm_so + (s - str);
       len = pmatch[0].rm_eo - pmatch[0].rm_so;
       printf("#%zu:\n", i);
       printf("offset = %jd; length = %jd, so=%d, eo=%d\n", (intmax_t) off,
               (intmax_t) len, pmatch[0].rm_so,pmatch[0].rm_eo);
       printf("substring = \"%.*s\"\n", len, s + pmatch[0].rm_so);

       printf("groupings:\n");
       for (int j=1;j<MAX_GROUPING;++j){
            if (pmatch[j].rm_eo == -1) break;
            const int glen = pmatch[j].rm_eo - pmatch[j].rm_so;
            printf("grouping %d = \"%.*s\"\n", j, glen, s + pmatch[j].rm_so);
        }

       s += pmatch[0].rm_eo;
   }

   exit(EXIT_SUCCESS);
}


