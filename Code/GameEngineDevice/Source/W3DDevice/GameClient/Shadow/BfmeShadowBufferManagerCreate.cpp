// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BFME's shadow-buffer manager allocates a BfmeVolumetricShadowBufferOwner
// here.  The owner class is identified by the shared vtable at 0x01128738
// and its converted destructor; the manager's public spelling is not present
// in the retail symbol evidence, so this remains an address-derived method.

typedef float Real;
typedef bool Bool;

extern "C" double __cdecl tan(double angle);

class DX8Wrapper
{
public:
	static Bool Has_Stencil(void);
};

class GlobalData
{
public:
	unsigned char m_unreconstructed_00[0x64];
	Bool m_useShadowVolumes;
};

extern GlobalData *TheGlobalData;

enum KindOfType { KINDOF_INVALID = 0 };

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

class Drawable : public Thing
{
};

class BfmeShadowResource
{
};

namespace Shadow
{
	struct ShadowTypeInfo
	{
		unsigned char m_unreconstructed_00[0x98];
		Real m_sizeX;
	};
}

class Rva007B12F0Base
{
public:
	virtual void handle(void);

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
	int m_unreconstructed_058;
	int m_unreconstructed_05c;
	Real m_unreconstructed_060;
	char m_unreconstructed_064;
	BfmeVolumetricShadowBufferOwner **m_prevLink;
	BfmeVolumetricShadowBufferOwner *m_next;
	unsigned int m_unreconstructed_070;
	BfmeShadowResource *m_resource;
	int m_entryCount;
	void *m_entries;
	Real m_unreconstructed_080;
	Real m_unreconstructed_084;

	public:
	Real m_shadowLengthScale;
	Real m_extraExtrusionPadding;
	char m_unreconstructed_090[0x10];
};

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
		shadow->m_shadowLengthScale = tan(shadowInfo->m_sizeX / 180.0f * 3.14159265358979323846f);

	if (!draw || !draw->isKindOf(KindOfType(2)))
		shadow->m_extraExtrusionPadding = 0.1f;

	return shadow;
}
