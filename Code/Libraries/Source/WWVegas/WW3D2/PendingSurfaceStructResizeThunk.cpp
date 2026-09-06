// cl: /DNDEBUG /MD /EHsc

// Render2DSentenceClass::PendingSurfaceStruct's VectorClass<T>::Resize,
// retail 0x00940450 (382 B), vtable 0x0113CE74 slot 2 (see
// tools/vtable_lookup.py --vt 0x0113CE74; slot 0 is the scalar deleting dtor
// at 0x00940940, slot 3 is Clear at 0x009405D0, all in render2dsentence.cpp).
//
// PendingSurfaceStruct's already-matched ctor (0x0093F3F0,
// PendingSurfaceStructCtor.cpp) and dtor (0x0005F5E0,
// Render2DSentenceClass_PendingSurfaceStruct_dtor.cpp) agree on a
// W3DRadarResetSurface base (a single ref-counted surface handle at +0x0)
// followed by a DynamicVectorClass-shaped Renderers member at +0x4. The
// element size this body multiplies newsize by is 0x1C (imul eax,eax,0x1C):
// 4 (Surface) + 0x18 (DynamicVectorClass<Render2DClass *>: vtable-less
// VectorClass base 0x10 + ActiveCount/GrowthStep 8) = 0x1C. That matches.
//
// The per-element copy in the Resize loop reproduces
// WWLib/refcount.h's REF_PTR_SET macro inline: if (that.Surface) AddRef it,
// if (this.Surface) Release it, then copy the pointer -- both calls go
// through the surface object's OWN vtable (slot 1 = AddRef at [ecx+4], slot 2
// = Release at [edx+8]), exactly the slot 2 release already proven by
// W3DRadarResetSurface_destructor.cpp and the slot 1 addRef already proven by
// W3DDisplayDrawImage.cpp's copy constructor. Renderers is then assigned as a
// whole (call to the already-matched trivial VectorClass<T>::operator= at
// 0x0093CEA0 -- VectorClassTrivialAssignment.cpp/dup_0093cea0 -- folded
// because its element type, like VectorClass<int>, is a plain 4-byte
// pointer), followed by the compiler's own memberwise copy of the two
// derived-only ints (ActiveCount at +0x10, GrowthStep at +0x14 relative to
// Renderers) that DynamicVectorClass does not redeclare operator= for.

#include <new.h>

extern void *__cdecl operator new[](size_t size);
extern void __cdecl operator delete[](void *pointer);

// Reachable through the surface's own vtable: slot 1 (+4) is the AddRef seen
// in W3DDisplayDrawImage.cpp's SurfaceResource::addRef, slot 2 (+8) is the
// Release seen in W3DRadarResetSurface_destructor.cpp.
class SurfaceResource
{
public:
	virtual void unused00();
	virtual unsigned long __stdcall addRef();
	virtual unsigned long __stdcall release();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
class W3DRadarResetSurface
{
public:
	W3DRadarResetSurface(void) : m_surface(0) {}
	~W3DRadarResetSurface();		// retail 0x008FC5B0, matched

	W3DRadarResetSurface &operator=(const W3DRadarResetSurface &that);

protected:
	SurfaceResource *m_surface;
};

W3DRadarResetSurface &W3DRadarResetSurface::operator=(const W3DRadarResetSurface &that)
{
	if (that.m_surface)
		that.m_surface->addRef();
	if (m_surface)
		m_surface->release();
	m_surface = that.m_surface;
	return *this;
}

class VectorClassDummy
{
public:
	VectorClassDummy(int size = 0, void *const *array = 0);
	virtual ~VectorClassDummy(void);
	virtual bool operator==(VectorClassDummy const &) const;
	virtual bool Resize(int newsize, void *const *array = 0);
	virtual void Clear(void);
	virtual int ID(void *const *ptr);
	virtual int ID(void *const &ptr);

	VectorClassDummy &operator=(const VectorClassDummy &that);

	void **Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

inline VectorClassDummy::VectorClassDummy(int size, void *const *array) :
	Vector(0), VectorMax(size), IsValid(true), IsAllocated(false)
{
	(void)array;
	if (size)
	{
		if (array)
			Vector = (void **)array;
		else
		{
			Vector = new void *[size];
			IsAllocated = true;
		}
	}
}

VectorClassDummy &VectorClassDummy::operator=(const VectorClassDummy &that)
{
	if (this != &that)
	{
		Clear();
		IsValid = false;
		VectorMax = that.VectorMax;
		if (VectorMax)
		{
			Vector = new void *[VectorMax];
			if (Vector)
			{
				IsAllocated = true;
				IsValid = true;
				for (int index = 0; index < VectorMax; ++index)
					Vector[index] = that.Vector[index];
			}
		}
		else
		{
			Vector = 0;
			IsAllocated = false;
			IsValid = true;
		}
	}
	return *this;
}

class DynamicVectorDummy : public VectorClassDummy
{
public:
	DynamicVectorDummy(int size = 0, void *const *array = 0);

	int ActiveCount;
	int GrowthStep;
};

inline DynamicVectorDummy::DynamicVectorDummy(int size, void *const *array)
	: VectorClassDummy(size, array)
{
	GrowthStep = 10;
	ActiveCount = 0;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
class Render2DSentenceClass
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
	struct PendingSurfaceStruct : public W3DRadarResetSurface
	{
		PendingSurfaceStruct(void);	// retail 0x0093F3F0, matched
		~PendingSurfaceStruct(void);	// retail 0x0005F5E0, matched

		DynamicVectorDummy Renderers;
	};
};

typedef Render2DSentenceClass::PendingSurfaceStruct PendingSurfaceStruct;

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

template <class T>
VectorClass<T>::VectorClass(int size, T const *array) :
	Vector(0), VectorMax(size), IsValid(true), IsAllocated(false)
{
	if (size)
	{
		if (array)
			Vector = new ((void *)array) T[size];
		else
		{
			Vector = new T[size];
			IsAllocated = true;
		}
	}
}

// ?Resize@?$VectorClass@UPendingSurfaceStruct@Render2DSentenceClass@@@@UAE_NHPBUPendingSurfaceStruct@Render2DSentenceClass@@@Z
template <class T>
bool VectorClass<T>::Resize(int newsize, T const *array)
{
	if (newsize)
	{
		T *newptr;

		IsValid = false;
		if (!array)
			newptr = new T[newsize];
		else
			newptr = new ((void *)array) T[newsize];
		IsValid = true;
		if (!newptr)
			return (false);

		if (Vector != 0)
		{
			int copycount = (newsize < VectorMax) ? newsize : VectorMax;
			for (int index = 0; index < copycount; index++)
				newptr[index] = Vector[index];

			if (IsAllocated)
			{
				delete[] Vector;
				Vector = 0;
			}
		}

		Vector = newptr;
		VectorMax = newsize;
		IsAllocated = (Vector && !array);
	}
	else
	{
		Clear();
	}
	return (true);
}

// Force emission of the Resize instantiation even though nothing else in
// this isolated TU calls it.
template VectorClass<PendingSurfaceStruct>::VectorClass(int, PendingSurfaceStruct const *);
template bool VectorClass<PendingSurfaceStruct>::Resize(int, PendingSurfaceStruct const *);
