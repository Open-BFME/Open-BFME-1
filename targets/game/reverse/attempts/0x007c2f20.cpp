// ?d_007c2f20@@YAXXZ
// partial score=0.741 date=2026-09-27
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// The matched createShadow factory at RVA 0x007C3260 constructs this owner.
// The owner constructor starts at RVA 0x007C2F20. Its vtable is at VA
// 0x01128738, and its matched destructor is at RVA 0x007C1660.

#define private public
#include <vector>
#undef private

typedef float Real;
typedef bool Bool;

extern "C" double __cdecl tan(double angle);
extern "C" double __cdecl fabs(double value);
extern "C" double __cdecl sqrt(double value);
extern "C" void __cdecl _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static Bool Has_Stencil(void);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_unreconstructed_00[0x64];
	Bool m_useShadowVolumes;
};

extern GlobalData *TheGlobalData;

enum KindOfType { KINDOF_INVALID = 0 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	virtual void v00(void);
	virtual void v01(void);
	virtual void v02(void);
	virtual void v03(void);
	virtual void v04(void);
	virtual void v05(void);
	virtual void v06(void);
	virtual void v07(void);
	virtual void v08(void);
	virtual void v09(void);
	virtual void v10(void);
	virtual void v11(void);
	virtual void v12(void);
	virtual void v13(void);
	virtual void v14(void);
	virtual void v15(void);
	virtual void v16(void);
	virtual void v17(void);
	virtual void v18(void);
	virtual void v19(void);
	virtual void v20(void);
	virtual void v21(void);
	virtual void v22(void);
	virtual void v23(void);
	virtual void v24(void);
	virtual void v25(void);
	virtual void v26(void);
	virtual void v27(void);
	virtual void v28(void);
	virtual void v29(void);
	virtual void v30(void);
	virtual void v31(void);
	virtual void v32(void);
	virtual void v33(void);
	virtual void v34(void);
	virtual void v35(void);
	virtual void v36(void);
	virtual void v37(void);
	virtual void v38(void);
	virtual void v39(void);
	virtual void v40(void);
	virtual void v41(void);
	virtual void v42(void);
	virtual void v43(void);
	virtual void v44(void);
	virtual void v45(void);
	virtual void v46(void);
	virtual void v47(void);
	virtual void v48(void);
	virtual void v49(void);
	virtual void v50(void);
	virtual void v51(void);
	virtual void v52(void);
	virtual void v53(void);
	virtual void v54(void);
	virtual void v55(void);
	virtual void v56(void);
	virtual void v57(void);
	virtual void v58(void);
	virtual void v59(void);
	virtual void v60(void);
	virtual void v61(void);
	virtual void v62(void);
	virtual void v63(void);
	virtual void v64(void);
	virtual void v65(void);
	virtual void v66(void);
	virtual void v67(void);
	virtual void v68(void);
	virtual void v69(void);
	virtual void v70(void);
	virtual void v71(void);
	virtual void v72(void);
	virtual void v73(void);
	virtual void v74(void);
	virtual void v75(void);
	virtual void v76(void);
	virtual void v77(void);
	virtual void v78(void);
	virtual void v79(void);
	virtual void v80(void);
	virtual void v81(void);
	virtual void v82(void);
	virtual void v83(void);
	virtual void v84(void);
	virtual void v85(void);
	virtual void v86(void);
	virtual void v87(void);
	virtual void v88(void);
	virtual void v89(void);
	virtual void v90(void);
	virtual void v91(void);
	virtual void v92(void);
	virtual void v93(void);
	virtual void v94(void);
	virtual void v95(void);
	virtual void v96(void);
	virtual void v97(void);
	virtual void v98(void);
	virtual void v99(void);
	Bool isKindOf(KindOfType kind) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable : public Thing
{
};

class Object
{
public:
	virtual void releaseSelf();
	virtual void s04();
	virtual void s08();
	virtual void s0c();
	virtual void s10();
	virtual void s14();
	virtual const char *s18();
	int m_refCount;
	char m_unreconstructed_008[0xc0];
	void *m_unreconstructed_0c8;

	void releaseRef()
	{
		if (--m_refCount == 0)
			releaseSelf();
	}
};

class MeshModelClass
{
public:
	char m_unreconstructed_00[0x24];
	int m_unreconstructed_24;
	int m_unreconstructed_28;
};

class MeshClass : public Object
{
public:
	MeshModelClass *Get_Model();
};

struct BfmeShadowObjectState
{
	char m_unreconstructed_00[0x18];
	volatile unsigned int m_flags;
};

class Rva007C2E50Node
{
public:
	virtual void releaseSelf();
	virtual void s04();
	virtual void s08();
	virtual void *s0c();
	virtual void s10();
	virtual Object *s14();
	virtual void s18();
	virtual void s1c();
	virtual void s20();
	virtual void s24();
	virtual void s28();
	virtual void s2c();
	virtual void s30();
	virtual void s34();
	virtual void s38();
	virtual void s3c();
	virtual void s40();
	virtual void s44();
	virtual void s48();
	virtual void s4c();
	virtual void s50();
	virtual void s54();
	virtual void s58();
	virtual void s5c();
	virtual void s60();
	virtual void s64();
	virtual void s68();
	virtual int s6c();
	virtual void s70();
	virtual Rva007C2E50Node *s74(int index);
	int m_refCount;
};

class Rva007C2E50Collector
{
public:
	void collect(_STL::vector<Object *> *out, Rva007C2E50Node *node);
};

struct BfmeShadowBounds
{
	float m_values[6];
};

class BfmeShadowResource : public Rva007C2E50Node
{
public:
	virtual void s78();
	virtual void s7c();
	virtual void s80();
	virtual void s84();
	virtual void s88();
	virtual void s8c();
	virtual void s90();
	virtual void s94();
	virtual void s98();
	virtual void s9c();
	virtual void sA0();
	virtual void sA4();
	virtual void sA8();
	virtual void sAC();
	virtual void sB0();
	virtual void sB4();
	virtual void sB8();
	virtual void sBC();
	virtual void sC0();
	virtual void sC4();
	virtual void sC8();
	virtual void sCC();
	virtual void sD0();
	virtual void sD4();
	virtual void sD8();
	virtual void sDC();
	virtual void sE0();
	virtual void sE4();
	virtual void sE8();
	virtual void sEC();
	virtual void sF0();
	virtual void sF4();
	virtual void sF8();
	virtual void sFC();
	virtual void s100();
	virtual void s104();
	virtual void s108();
	virtual void getBounds(BfmeShadowBounds *bounds);
};

struct BfmeShadowBufferEntry
{
	Object *m_object;
	void *m_allocation0;
	void *m_allocation1;
	void *m_allocation2;
	unsigned int m_unreconstructed_10;
	unsigned char m_hasShadow;
	char m_unreconstructed_15[3];
};

namespace Shadow
{
	// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shadow.h
	struct ShadowTypeInfo
	{
		unsigned char m_unreconstructed_00[0x98];
		Real m_sizeX;
	};
}

class Rva007B12F0Base
{
public:
	Rva007B12F0Base();
	~Rva007B12F0Base() { *(unsigned int *)this = 0x011283dc; }
	void *m_vtable;

private:
	char m_padding[0x54];
};

class BfmeVolumetricShadowBufferOwner : public Rva007B12F0Base
{
public:
	BfmeVolumetricShadowBufferOwner(
		BfmeVolumetricShadowBufferOwner **prevLink,
		BfmeShadowResource *resource);

private:
	volatile int m_unreconstructed_058;
	volatile int m_unreconstructed_05c;
	volatile Real m_unreconstructed_060;
	volatile char m_unreconstructed_064;
	BfmeVolumetricShadowBufferOwner **m_prevLink;
	BfmeVolumetricShadowBufferOwner *m_next;
	unsigned int m_unreconstructed_070;
	BfmeShadowResource *volatile m_resource;
	int m_entryCount;
	BfmeShadowBufferEntry *m_entries;
	Real m_unreconstructed_080;
	Real m_unreconstructed_084;

	public:
	volatile Real m_shadowLengthScale;
	volatile Real m_extraExtrusionPadding;
	char m_unreconstructed_090[0x10];
};

BfmeVolumetricShadowBufferOwner::BfmeVolumetricShadowBufferOwner(
	BfmeVolumetricShadowBufferOwner **prevLink, BfmeShadowResource *resource)
{
	m_unreconstructed_058 = 0;
	m_unreconstructed_05c = 0;
	m_unreconstructed_060 = 20.0f;
	m_unreconstructed_064 = 0;
	_ReadWriteBarrier();
	*(unsigned int *)this = 0x01128738;
	m_prevLink = prevLink;
	m_next = *prevLink;
	_ReadWriteBarrier();
	m_resource = resource;
	m_shadowLengthScale = 0.0f;
	m_extraExtrusionPadding = 0.0f;

	if (m_next != 0)
		m_next->m_prevLink = &m_next;
	*m_prevLink = this;
	++resource->m_refCount;

	_STL::vector<Object *> objects;
	(reinterpret_cast<Rva007C2E50Collector *>(this))->collect(&objects, resource);

	int index = 0;
	if (objects.size() > 0)
	{
		unsigned int mask = 0x1000;
		while (index < objects.size())
		{
			MeshClass *mesh = reinterpret_cast<MeshClass *>(objects.begin()[index]);
			BfmeShadowObjectState *state =
				reinterpret_cast<BfmeShadowObjectState *>(mesh->m_unreconstructed_0c8);
			if ((state->m_flags & mask) != 0)
				++index;
			else
			{
				objects.begin()[index] = objects.back();
				objects.pop_back();
			}
		}
	}

	m_entryCount = (int)objects.size();
	m_entries = new BfmeShadowBufferEntry[m_entryCount];
	BfmeShadowBufferEntry *entry = m_entries;
	int entryIndex = 0;
	while (entryIndex < m_entryCount)
	{
		Object *object = *(objects.begin() + entryIndex);
		entry->m_object = object;
		++object->m_refCount;

		MeshModelClass *model = reinterpret_cast<MeshClass *>(object)->Get_Model();
		entry->m_allocation0 = new char[model->m_unreconstructed_28 * 12];
		entry->m_allocation1 = new char[model->m_unreconstructed_24];
		entry->m_allocation2 = new char[model->m_unreconstructed_24 * 12];
		entry->m_unreconstructed_10 = 0;

		if (object->s18() != 0)
			entry->m_hasShadow = strstr(object->s18(), "SHADOW") != 0;
		else
			entry->m_hasShadow = 0;

		if (--object->m_refCount == 0)
			object->releaseSelf();
		++entryIndex;
		++entry;
	}

	BfmeShadowBounds bounds;
	m_resource->getBounds(&bounds);
	float xExtent = (float)fabs(bounds.m_values[0]) + bounds.m_values[3];
	float yExtent = (float)fabs(bounds.m_values[1]) + bounds.m_values[4];
	Real extentRadius = (Real)sqrt(xExtent * xExtent + yExtent * yExtent);
	m_unreconstructed_080 = extentRadius;
	m_unreconstructed_084 = bounds.m_values[5] + bounds.m_values[2] + *(float *)0x010977e0;
}

class BfmeShadowBufferManager007C3260
{
public:
	BfmeVolumetricShadowBufferOwner *createShadow(BfmeShadowResource *resource,
		Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw);

private:
	unsigned char m_unreconstructed_00[8];
	BfmeVolumetricShadowBufferOwner *m_shadowList;
};

BfmeVolumetricShadowBufferOwner *BfmeShadowBufferManager007C3260::createShadow(
	BfmeShadowResource *resource, Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw)
{
	if (!DX8Wrapper::Has_Stencil() || !resource || !TheGlobalData->m_useShadowVolumes)
		return 0;

	BfmeVolumetricShadowBufferOwner *shadow =
		new BfmeVolumetricShadowBufferOwner(&m_shadowList, resource);

	if (shadowInfo->m_sizeX != 0.0f)
		shadow->m_shadowLengthScale = tan(shadowInfo->m_sizeX * (180.0f / 3.14159265358979323846f));  // retail scales by 180/pi here, not pi/180

	if (!draw || !draw->isKindOf(KindOfType(2)))
		shadow->m_extraExtrusionPadding = 0.1f;

	return shadow;
}
