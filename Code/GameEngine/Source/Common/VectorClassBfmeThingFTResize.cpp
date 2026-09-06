// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// FUZZY-TWIN of Code/Libraries/Source/WWVegas/WW3D2/VectorClassProxyResizeThunk.cpp
// (?Resize@?$VectorClass@VProxyClass@@@@UAE_NHPBVProxyClass@@@Z, 0x00934630,
// 324B): same VectorClass<T>::Resize control flow, but T is BfmeThingFT
// (already matched, sizeof 0x24 -- see Code/GameEngine/Source/Common/
// BfmeOneHundredNinetyEight.cpp), and the per-element copy in the middle loop
// calls the already-matched `bfmeTakeFT(const BfmeThingFT *)` (retail
// 0x0093D9B0, argument passed by POINTER: `lea ecx,[edi+ebx]` / push the
// source address) instead of an `operator=(const T &)` (argument by
// reference). That is why this is a hand-written specialisation rather than
// the shared template body the twin instantiates: the generic
// `newptr[index] = Vector[index]` line calls whatever operator= the element
// type defines, and BfmeThingFT does not define one -- it defines bfmeTakeFT
// instead. The array-construct/destruct-with-cleanup thunks (??_L / ??_M)
// and the stride (0x24 vs the twin's 0x74) follow directly from sizeof
// BfmeThingFT.

#include <new.h>

extern void *__cdecl operator new[](size_t size);
extern void __cdecl operator delete[](void *p);

class BfmeItemFT;

// upstream layout: Code/GameEngine/Source/Common/BfmeOneHundredNinetyEight.cpp
class BfmeThingFT
{
public:
	BfmeThingFT() {}
	~BfmeThingFT() {}

	BfmeThingFT &bfmeTakeFT(const BfmeThingFT *from);

private:
	BfmeItemFT *m_bfmeItem;			// 0x00
	int m_bfmeFirst;			// 0x04
	int m_bfmeSecond;			// 0x08
	int m_bfmeThird;			// 0x0c
	int m_bfmeFourth;			// 0x10
	int m_bfmeFifth;			// 0x14
	int m_bfmeSixth;			// 0x18
	int m_bfmeSeventh;			// 0x1c
	int m_bfmeEighth;			// 0x20
};

// ?bfmeTakeFT@BfmeThingFT@@QAEAAV1@PBV1@@Z -- declared (above) but not
// defined here, so calls bind to the already-matched retail body at
// 0x0093D9B0 instead of a locally emitted one.

// upstream layout: Code/Libraries/Source/WWVegas/WWLib/vector.h
class VectorClassBfmeThingFT
{
public:
	VectorClassBfmeThingFT(int size = 0, BfmeThingFT const *array = 0);
	virtual ~VectorClassBfmeThingFT(void);							///< vtable +0x00
	virtual bool operator==(const VectorClassBfmeThingFT &) const;	///< vtable +0x04
	virtual bool Resize(int newsize, BfmeThingFT const *array = 0);	///< vtable +0x08
	virtual void Clear(void);											///< vtable +0x0C
	virtual int ID(BfmeThingFT const *ptr);							///< vtable +0x10
	virtual int ID(BfmeThingFT const &ptr);							///< vtable +0x14

protected:
	BfmeThingFT *Vector;			///< retail this+0x04
	int VectorMax;					///< retail this+0x08
	bool IsValid;					///< retail this+0x0C
	bool IsAllocated;				///< retail this+0x0D
	bool VectorClassPad[2];
};

VectorClassBfmeThingFT::VectorClassBfmeThingFT(int size, BfmeThingFT const *array) :
	Vector(0), VectorMax(size), IsValid(true), IsAllocated(false)
{
	if (size) {
		if (array) {
			Vector = new ((void *)array) BfmeThingFT[size];
		} else {
			Vector = new BfmeThingFT[size];
			IsAllocated = true;
		}
	}
}

// ?Resize@VectorClassBfmeThingFT@@UAE_NHPBVBfmeThingFT@@@Z
bool VectorClassBfmeThingFT::Resize(int newsize, BfmeThingFT const *array)
{
	if (newsize) {

		BfmeThingFT *newptr;

		IsValid = false;
		if (!array) {
			newptr = new BfmeThingFT[newsize];
		} else {
			newptr = new ((void *)array) BfmeThingFT[newsize];
		}
		IsValid = true;
		if (!newptr) {
			return (false);
		}

		if (Vector != 0) {

			int copycount = (newsize < VectorMax) ? newsize : VectorMax;
			for (int index = 0; index < copycount; index++) {
				newptr[index].bfmeTakeFT(&Vector[index]);
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
void rva0093e1f0ForceEmit()
{
	VectorClassBfmeThingFT v;
	v.Resize(1);
}
