#include <iostream>
#include <memory>
#include <cstddef>
#include <cstring>

using unique_ptr_voidType = std::unique_ptr<void, void (*)(const void *p)>;
using unique_ptr_const_voidType
    = std::unique_ptr<const void, void (*)(const void *p)>;

// NOTE: these UPVoid structs will call new with std::nothrow ...
// usage: UPVoid<Object>::createPtr(args to constructor) === new Object(args to
// constructor)
template <typename T>
struct UPVoid {
	template <typename... Args>
	static unique_ptr_voidType createPtr(Args &&...args);

	// this function will allocate and memset it to 0 using sizeof(T), which
	// does not accept T as a pointer type as its most likely a mistake/typo
	// in most cases if you want to put a pointer value on the heap, maybe
	// make a new function for it, as it's not common to do so
	static unique_ptr_voidType createZeroedPtr();
};

// const overload/specialization
// usage: UPVoid<const Object>::createPtr(args to constructor) === new const
// Object(args to constructor)
template <typename T>
struct UPVoid<const T> {
	template <typename... Args>
	static unique_ptr_const_voidType createPtr(Args &&...args);

	// we will not provide a createZeroedPtr() for const T, as it really
	// depends on the type of T (and its default constructor) by the
	// standard, `new T()` will perform value initialization, which can mean
	// different things depending on if T is a class, an array, or
	// otherwise; if its a class, it depends on if t here is a default
	// constructor or the default constructor is provided by the user or
	// automatically created by the compiler We will not list them out here,
	// and we will not put any assumption on the type T, please refer to
	// https://en.cppreference.com/w/cpp/language/value_initialization
};

// specialization for unbounded arrays
// usage: UPVoid<unsigned char[]>::createPtr(srcSize) === new unsigned
// char[srcSize]
template <typename T>
struct UPVoid<T[]> {
	static unique_ptr_voidType createPtr(const size_t size);

	// same idea, but allow T to be a pointer
	static unique_ptr_voidType createZeroedPtr(const size_t size);
};

// specialization for bounded arrays where size is known at compile time (just
// for easier syntax) usage: UPVoid<unsigned char[N]>::createPtr() === new
// unsigned char[N]
template <typename T, size_t N>
struct UPVoid<T[N]> {
	static unique_ptr_voidType createPtr();
	// same as the UpVoid<T[]> case, except the size is implicit
	static unique_ptr_voidType createZeroedPtr();
};

template <typename T>
template <typename... Args>
unique_ptr_voidType UPVoid<T>::createPtr(Args &&...args)
{
	return unique_ptr_voidType{
	    new (std::nothrow) T(std::forward<Args>(args)...),
	    [](const void *ip) {
		    const T *p = static_cast<const T *>(ip);
		    delete p;
	    }};
}
template <typename T>
unique_ptr_voidType UPVoid<T>::createZeroedPtr()
{
	static_assert(
	    !std::is_pointer<T>::value,
	    "You probably have a typo or using this function wrong! It will memset with sizeof(T), where T is a pointer! If you want to allocate a pointer on the heap, maybe create a new funct ion for this");
	auto ret
	    = createPtr(); // invoke default constructor, based on whatever T is
	memset(ret.get(), 0,
	       sizeof(T)); // zero the bits based on the size of the type
	return ret;
}

template <typename T>
template <typename... Args>
unique_ptr_const_voidType UPVoid<const T>::createPtr(Args &&...args)
{
	return unique_ptr_const_voidType{
	    new (std::nothrow) T(std::forward<Args>(args)...),
	    [](const void *ip) {
		    const T *p = static_cast<const T *>(ip);
		    delete p;
	    }};
}

template <typename T>
unique_ptr_voidType UPVoid<T[]>::createPtr(const size_t size)
{
	return unique_ptr_voidType{
	    new (std::nothrow) T[size], [](const void *ip) {
		    const T *p = static_cast<const T *>(ip);
		    delete[] p;
	    }};
}
template <typename T>
unique_ptr_voidType UPVoid<T[]>::createZeroedPtr(const size_t size)
{
	auto ret = createPtr(
	    size); // invoke default constructor, based on whatever T is
	memset(ret.get(), 0,
	       sizeof(T) * size); // zero the bits based on the size of the type
	return ret;
}

template <typename T, size_t N>
unique_ptr_voidType UPVoid<T[N]>::createPtr()
{
	return unique_ptr_voidType{new (std::nothrow) T[N], [](const void *ip) {
					   const T *p
					       = static_cast<const T *>(ip);
					   delete[] p;
				   }};
}
template <typename T, size_t N>
unique_ptr_voidType UPVoid<T[N]>::createZeroedPtr()
{
	auto ret
	    = createPtr(); // invoke default constructor, based on whatever T is
	memset(ret.get(), 0,
	       sizeof(T) * N); // zero the bits based on the size of the type
	return ret;
}

int main()
{
	auto t1 = UPVoid<unsigned char[]>::createZeroedPtr(69);
    std::cout<<"t1[0] = '" <<((unsigned char*)t1.get())[0]<<"'\n";
	auto t2 = UPVoid<unsigned char[420]>::createZeroedPtr();
    std::cout<<"t2[0] = '" <<((unsigned char*)t2.get())[0]<<"'\n";
}
