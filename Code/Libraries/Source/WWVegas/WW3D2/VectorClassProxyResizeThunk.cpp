// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Lift the VectorClass<ProxyClass>::Resize raw machine-code dump to clean C++
// (packet 00934630).
//
// The reference body (WW3D2/collect.cpp, class ProxyClass in proxy.h) is
// structurally exact: this repo's own vector.h + proxy.h reproduce the whole
// control flow byte for byte EXCEPT for one literal, 0x74 (116), used for the
// per-element size passed to operator new[]/delete[], the array
// constructor/destructor iterators (??_L / ??_M), and the element pointer
// stride. This tree's proxy.h defines ProxyClass as StringClass (4 bytes,
// pointer handle) + Matrix3D (48 bytes) = 0x34 (52) bytes -- the same
// structural-boilerplate gap already diagnosed on sibling packets in this
// sweep (VehicleCurveClass::_ArcInfoStruct at 0x34 vs retail's second copy at
// 0x74; MixFileCreator::FileInfoStruct likewise). The call at the copy site
// resolves to ??4ProxyClass@@QAEAAV0@ABV0@@Z at 0x00933C60 (packet-pinned),
// which independently confirms this is ProxyClass and not a different class
// sharing the VectorClass<T> boilerplate shape.
//
// Rather than touching the shared proxy.h (which the other matched
// ProxyClass-adjacent rows in collect.cpp depend on), this is an isolated
// local replica carrying the extra 0x40 bytes as unreconstructed padding, so
// the pointer arithmetic (stride 0x74) and the out-of-line calls to the
// *pinned* retail helpers all land correctly. C++ name mangling does not
// encode member layout, only the identifier, so the mangled symbol produced
// here is identical to the real ?Resize@?$VectorClass@VProxyClass@@@@... .
//
// Retail pins the layout: Vector at this+0x04, VectorMax at this+0x08,
// IsValid/IsAllocated at this+0x0C/0x0D -- the standard VectorClass layout
// from WWLib's vector.h, unchanged here.

#include <new.h>

// Declaring operator new[]/delete[] in this TU is required: MSVC 7.1 folds
// `new T[n]` / `delete[]` for a T that only ever needs scalar `operator new`
// (??2) down to the scalar overload unless the array forms are declared
// somewhere the compiler can see, per this repo's own WWLib/always.h (whose
// global declarations are what makes the real vector.h route through ??_U /
// ??_V instead).
extern void *__cdecl operator new[](size_t size);
extern void __cdecl operator delete[](void *p);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/wwstring.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/proxy.h
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

// ??4ProxyClass@@QAEAAV0@ABV0@@Z -- declared (above, in-class) but not
// defined here, so this TU's Resize call site binds to the pinned retail
// address (0x00933C60) instead of a locally emitted body.

template <class T> class VectorClass
{
public:
	VectorClass(int size = 0, T const *array = 0);
	virtual ~VectorClass(void);								///< vtable +0x00
	virtual bool operator==(const VectorClass<T> &) const;	///< vtable +0x04
	virtual bool Resize(int newsize, T const *array = 0);		///< vtable +0x08
	virtual void Clear(void);									///< vtable +0x0C
	virtual int ID(T const *ptr);								///< vtable +0x10
	virtual int ID(T const &ptr);								///< vtable +0x14

protected:
	T *Vector;						///< retail this+0x04
	int VectorMax;					///< retail this+0x08
	bool IsValid;					///< retail this+0x0C
	bool IsAllocated;				///< retail this+0x0D
	bool VectorClassPad[2];
};

// ?Resize@?$VectorClass@VProxyClass@@@@UAE_NHPBVProxyClass@@@Z
template <class T>
bool VectorClass<T>::Resize(int newsize, T const *array)
{
	if (newsize) {

		T *newptr;

		IsValid = false;
		if (!array) {
			newptr = new T[newsize];
		} else {
			newptr = new ((void *)array) T[newsize];
		}
		IsValid = true;
		if (!newptr) {
			return (false);
		}

		if (Vector != 0) {

			int copycount = (newsize < VectorMax) ? newsize : VectorMax;
			for (int index = 0; index < copycount; index++) {
				newptr[index] = Vector[index];
			}

			if (IsAllocated) {
				delete[] Vector;
				Vector = 0;
			}
		}

		Vector = newptr;
		VectorMax = newsize;
		IsAllocated = (Vector && !array);

	} else {
		Clear();
	}
	return (true);
}

// Force emission of the Resize instantiation even though nothing else in
// this isolated TU calls it.
template bool VectorClass<ProxyClass>::Resize(int, ProxyClass const *);
