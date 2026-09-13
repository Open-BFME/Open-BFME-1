// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the HAnimComboClass::Reset naked dump to clean C++.
//
// Zero Hour's hanim.cpp body. The loop is ZH's verbatim; what retail expands is
// the `delete data`, which inlines the element destructor and then frees the
// block back to a static memory pool rather than calling operator delete out of
// line.
//
// The two releases inside that destructor have different shapes and that is the
// layout evidence. The motion at data+0x00 is released with no pointer
// adjustment, so its reference-count base sits at offset zero. The pivot map at
// data+0x0C is released through `lea ecx,[eax+0x18]`, so its reference-count
// base is 0x18 bytes into the object -- multiple inheritance with the counted
// base second. Release_Ref itself inlines to `--NumRefs; if (NumRefs == 0)
// Delete_This();` with the count at +0x04 and Delete_This as vtable slot 0.
//
// Retail does not null the members after releasing them, so the destructor
// releases without clearing -- ZH's REF_PTR_RELEASE macro would have stored
// zeroes that are not in the bytes.
//
// Retail pins the layout: the vector is the whole object, so its element
// pointer is at this+0x04 and its active count at this+0x10, and the shared
// flag is the byte at data+0x10.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	void Release_Ref(void)
	{
		NumRefs--;
		if (NumRefs == 0)
		{
			Delete_This();
		}
	}

protected:
	virtual void Delete_This(void);						///< vtable +0x00

	Int NumRefs;										///< retail this+0x04
};

class HAnimClass : public RefCountClass {};

// 0x18 bytes ahead of the counted base, which is what makes the release site
// adjust the pointer before touching the count.
class PivotMapBase
{
public:
	// this base must be polymorphic too: MSVC lays a polymorphic base out at
	// offset zero, so a plain byte-array base would put RefCountClass at +0x00
	// and the release site would lose its pointer adjustment
	virtual void unused00();

private:
	unsigned char m_unreconstructed_04[0x18 - 4];
};

class PivotMapClass : public PivotMapBase, public RefCountClass {};

class HAnimComboDataClass;

// The free at 0x00973E90 is already pinned under several
// ObjectPoolClass<T,256>::Free_Object_Memory names -- ICF folds every
// instantiation onto one body -- so the pool is an object pool rather than a
// generic allocator, and 256 is the block count its mangling encodes.
template <class T, int NUM> class ObjectPoolClass
{
public:
	void Free_Object_Memory(T *object);
};

extern ObjectPoolClass<HAnimComboDataClass, 256> TheHAnimComboDataPool;	///< retail [0x0134BC4C]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hanim.h
class HAnimComboDataClass
{
public:
	bool Is_Shared(void) const { return IsShared; }

	~HAnimComboDataClass(void)
	{
		if (Motion)
			Motion->Release_Ref();
		if (PivotMap)
			PivotMap->Release_Ref();
	}

	void operator delete(void *block)
	{
		TheHAnimComboDataPool.Free_Object_Memory((HAnimComboDataClass *)block);
	}

private:
	HAnimClass *Motion;									///< retail this+0x00
	unsigned char m_unreconstructed_04[8];
	PivotMapClass *PivotMap;							///< retail this+0x0C
	bool IsShared;										///< retail this+0x10
};

class HAnimComboDataVector
{
public:
	Int Count(void) const { return ActiveCount; }
	HAnimComboDataClass *operator[](Int index) const { return Vector[index]; }
	void Reset_Active(void) { ActiveCount = 0; }

private:
	unsigned char m_unreconstructed_00[4];				///< the vector's own vtable pointer
	HAnimComboDataClass **Vector;						///< retail this+0x04
	unsigned char m_unreconstructed_08[8];
	Int ActiveCount;									///< retail this+0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hanim.h
class HAnimComboClass
{
public:
	void Reset(void);

protected:
	HAnimComboDataVector HAnimComboData;				///< retail this+0x00
};

// ?Reset@HAnimComboClass@@QAEXXZ
void	HAnimComboClass::Reset( void )
{
	int numAnimations = HAnimComboData.Count();
	while ( numAnimations-- ) {
		HAnimComboDataClass *data = HAnimComboData[numAnimations];
		if(data && (! data->Is_Shared())) {
			delete data;
		}
	}
	HAnimComboData.Reset_Active();
}
