// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

#include <math.h>

typedef bool Bool;
typedef float Real;

extern const float BfmeZeroRange;
extern const float BfmeShadowTanScale;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static Bool Has_Stencil(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
	unsigned char m_unreconstructed_000[0x64];

public:
	Bool m_useShadowVolumes;
};

extern GlobalData *TheGlobalData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/sphere.h
struct SphereClass
{
	float Center[3];
	float Radius;
};

class RenderObjClass
{
public:
	virtual void v00(void);
	virtual void v01(void);
	virtual void v02(void);
	virtual void v03(void);
	virtual void v04(void);
	virtual void v05(void);
	virtual const char *Get_Name(void);
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
	virtual void Get_Obj_Space_Bounding_Sphere(SphereClass &sphere);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	Bool isKindOf(int kind) const;
};

class W3DShadowGeometry
{
};

class W3DShadowGeometryManager
{
public:
	W3DShadowGeometry *Get_Geom(const char *name);
	int Load_Geom(RenderObjClass *robj, const char *name);
};

namespace Shadow
{
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shadow.h
	struct ShadowTypeInfo
	{
		unsigned char m_unreconstructed_000[0x80];
		unsigned int m_field80;
		unsigned char m_unreconstructed_084[0x14];
		Real m_sizeX;
	};
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DVolumetricShadow.h
class W3DVolumetricShadow
{
public:
	W3DVolumetricShadow(void);
	friend class BfmeVolumetricShadowManager;

	void setRenderObject(RenderObjClass *robj)
	{
		m_robj = robj;
	}

	protected:
	void SetGeometry(W3DShadowGeometry *geometry);

	public:
	void setRenderObjExtent(Real extent)
	{
		m_robjExtent = extent;
	}

	void setShadowLengthScale(Real scale)
	{
		m_shadowLengthScale = scale;
	}

	void setOptimalExtrusionPadding(Real padding)
	{
		m_extraExtrusionPadding = padding;
	}

	unsigned char m_unreconstructed_000[0x34];
	unsigned int m_field34;
	unsigned char m_unreconstructed_038[0x30];
	W3DVolumetricShadow *m_next;
	unsigned int m_field6c;
	RenderObjClass *m_robj;
	Real m_shadowLengthScale;
	Real m_robjExtent;
	Real m_extraExtrusionPadding;
	unsigned char m_unreconstructed_080[0x4884];
};

class BfmeVolumetricShadowManager
{
public:
	W3DVolumetricShadow *addShadow(RenderObjClass *robj,
		Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw);

private:
	W3DVolumetricShadow *m_shadowList;
	unsigned char m_unreconstructed_004[4];
	W3DShadowGeometryManager *m_W3DShadowGeometryManager;
};

W3DVolumetricShadow *BfmeVolumetricShadowManager::addShadow(
	RenderObjClass *robj, Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw)
{
	if (!DX8Wrapper::Has_Stencil() || !robj || !TheGlobalData->m_useShadowVolumes)
		return 0;

	W3DShadowGeometry *sg = 0;
	if (!robj)
		return 0;

	const char *name = robj->Get_Name();
	if (!name)
		return 0;

	sg = m_W3DShadowGeometryManager->Get_Geom(name);
	if (sg == 0)
	{
		m_W3DShadowGeometryManager->Load_Geom(robj, name);
		sg = m_W3DShadowGeometryManager->Get_Geom(name);
		if (sg == 0)
			return 0;
	}

	W3DVolumetricShadow *shadow = new W3DVolumetricShadow;
	if (shadow == 0)
		return 0;

	shadow->setRenderObject(robj);
	shadow->SetGeometry(sg);

	SphereClass sphere;
	robj->Get_Obj_Space_Bounding_Sphere(sphere);
	shadow->setRenderObjExtent(sphere.Radius);

	Real sunElevationAngleTan = 0;
	if (shadowInfo->m_sizeX)
		sunElevationAngleTan = (Real)tan(shadowInfo->m_sizeX / 180.0f *
			3.1415927f);
	shadow->setShadowLengthScale(sunElevationAngleTan);

	shadow->m_field34 = shadowInfo->m_field80;
	if (!draw || !draw->isKindOf(2))
		shadow->setOptimalExtrusionPadding(0.1f);

	shadow->m_next = m_shadowList;
	m_shadowList = shadow;
	return shadow;
}
