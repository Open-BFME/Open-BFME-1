// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// VectorClass<ProxyClass>::ID(const ProxyClass &) at retail 0x00933DF0
// (slot +0x14 of vtable 0x0113C894, whose other slots are the landed Proxy
// vector members ??_G, operator==, Resize, Clear): pointer-difference ID
// over the 0x74-byte element -- the same isolated ProxyClass replica
// (StringClass + Matrix3D + trailing pad) as the landed Resize thunk,
// because the shared proxy.h declares 0x34 and cannot produce retail's
// 0x8D3DCB09/shr-6 divide (2^38/0x8D3DCB09 = 116 = 0x74). C++ name mangling
// does not encode member layout, so the mangled symbol here is identical
// to the real ?ID@?$VectorClass@VProxyClass@@@@... .

#include <new.h>

// Declaring operator new[]/delete[] in this TU is required: MSVC 7.1 folds
// `new T[n]` / `delete[]` for a T that only ever needs scalar `operator new`
// (??2) down to the scalar overload unless the array forms are declared
// somewhere the compiler can see (same note as the Resize thunk).
extern void *__cdecl operator new[](size_t size);
extern void __cdecl operator delete[](void *p);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/proxy.h
class StringClass
{
public:
	StringClass() : m_Buffer(0) {}
	~StringClass() {}
	char *m_Buffer;
};

class Matrix3D
{
public:
	float Row[3][4];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/proxy.h
class ProxyClass
{
public:
	ProxyClass(void) {}

	StringClass	Name;
	Matrix3D	Transform;

	// BFME's build of this class carries additional trailing bytes that
	// ZH's proxy.h does not declare -- unreconstructed, only their combined
	// size (making sizeof(ProxyClass) == 0x74) matters here.
	unsigned char m_unreconstructed_tail[0x74 - 0x34];

	ProxyClass &operator=(const ProxyClass &that);
};

template <class T> class VectorClass
{
public:
	VectorClass(int size = 0, T const *array = 0);
	virtual ~VectorClass(void);
	virtual bool operator==(const VectorClass<T> &) const;
	virtual bool Resize(int newsize, T const *array = 0);
	virtual void Clear(void);
	virtual int ID(T const *ptr);
	virtual int ID(T const &ptr);

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

// ?ID@?$VectorClass@VProxyClass@@@@UAEHAABVProxyClass@@@Z
template <class T>
int VectorClass<T>::ID(T const &ptr)
{
	if (!IsValid)
		return 0;
	return ((char *)&ptr - (char *)Vector) / sizeof(T);
}

// Force emission of the ID instantiation.
template int VectorClass<ProxyClass>::ID(ProxyClass const &);
