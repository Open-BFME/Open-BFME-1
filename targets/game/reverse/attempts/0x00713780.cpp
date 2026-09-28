// ?rva00713780@RTS3DScene@@QAEXAAVRenderInfoClass@@PAVRenderObjClass@@H_N@Z
// partial score=0.68 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWDebug
// Retail RVA 0x00713780, 2491 bytes, ret 0x10.  Reached only through ILT
// 0x00017238 from RTS3DScene::Customized_Render, flushTranslucentObjects and
// rva00715530 (four stack words).  The Zero Hour twin is
// RTS3DScene::renderOneObject; BFME adds a fourth argument, a terrain tint
// query and a fixed-light-environment shortcut, so the address-derived name is
// kept.  Offsets below are read off this body; the member names are the Zero
// Hour twin's where the use matches and address-derived otherwise.

#define Matrix4x4 Matrix4
#include "WW3D2/rendobj.h"
#include "WW3D2/camera.h"
#include "WW3D2/rinfo.h"
#include "WW3D2/light.h"
#include "WW3D2/robjlist.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID,
	OBJECTSHROUD_CLEAR,
	OBJECTSHROUD_PARTIAL_CLEAR,
	OBJECTSHROUD_FOGGED,
	OBJECTSHROUD_SHROUDED
};

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	ObjectShroudStatus getShroudedStatus(Int playerIndex) const;
	Bool isEffectivelyDead() const { return (m_status344 & 1) != 0; }

	char m_pad000[0x344];
	UnsignedInt m_status344;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	UnsignedInt getFrame() const { return m_frame; }

	char m_pad000[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class Drawable
{
public:
	Bool isDrawableEffectivelyHidden() const;
	Object *getObject() const { return m_object; }
	const Vector3 *getColor09C() const { return &m_color09c; }

	char m_pad000[0x9c];
	Vector3 m_color09c;
	char m_pad0a8[0xe4 - 0xa8];
	Bool m_flag0e4;
	char m_pad0e5[0xf0 - 0xe5];
	UnsignedInt m_value0f0;
	char m_pad0f4[0xfc - 0xf4];
	Object *m_object;
	char m_pad100[0x134 - 0x100];
	UnsignedInt m_shroudClearFrame;
	char m_pad138[0x15c - 0x138];
	Int m_stealthLook;
	char m_pad160[0x2e4 - 0x160];
	Real m_secondMaterialPassOpacity;
};

struct DrawableInfo
{
	ObjectID m_shroudStatusObjectID;
	Drawable *m_drawable;
};

// The three colour getters are reached through ILTs that have no semantic pin.
extern void j_00013926();
extern void j_0004600b();
extern void j_000186e2();

struct Rva00713780ColorView { const Vector3 *get(); };
typedef const Vector3 *(Rva00713780ColorView::*Rva00713780ColorCall)();

static __forceinline const Vector3 *callColor(void (*fn)(), Drawable *draw)
{
	union { void (*asFunction)(); Rva00713780ColorCall asMember; } cast;
	cast.asFunction = fn;
	return (reinterpret_cast<Rva00713780ColorView *>(draw)->*cast.asMember)();
}

// TerrainLogic query reached through ILT 0x0002CF4D (body 0x001A3D30, still a
// dump): thiscall, position by reference, Vector3 out, bool result.
class TerrainLogic
{
public:
	Bool rva001A3D30(const Vector3 &pos, Vector3 *tint);
};
extern TerrainLogic *TheTerrainLogic;

struct Rva00713780DynamicLightView
{
	char m_pad000[0x148];
	Bool m_enabled;
};

struct Rva00713780RenderObjView
{
	char m_pad000[0x9c];
	void *m_pass09c;
};

// BFME's LightEnvironmentClass is 0x228 bytes (the scene's three embedded
// environments at +0x160/+0x388/+0x5B0 are 0x228 apart) and this body reads
// OutputAmbient at +0x164; the shared header is four bytes short ahead of it.
// Only the members this body touches are declared.
class LightEnvironmentClass
{
public:
	LightEnvironmentClass(void);
	~LightEnvironmentClass(void);
	void Reset(const Vector3 &object_center, const Vector3 &scene_ambient);
	void Add_Light(const LightClass &light);
	void Pre_Render_Update(const Matrix3D &camera_tm);
	const Vector3 &Get_Equivalent_Ambient(void) const { return OutputAmbient; }
	void Set_Output_Ambient(Vector3 &oa) { OutputAmbient = oa; }

private:
	char m_inputs[0x164];
	Vector3 OutputAmbient;
	char m_outputs[0x228 - 0x170];
};
typedef LightEnvironmentClass Rva00713780LightEnv;

class Rva00923800Item;
class Rva00923800
{
public:
	void append(Rva00923800Item *item);
};

class BfmeHostFT
{
public:
	void bfmePopFT();
};

extern bool g_rva01341220Flag;
extern unsigned char g_rva012D6E04Value;

class RTS3DScene
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual const Vector3 &Get_Ambient_Light() = 0;

	void rva00713780(RenderInfoClass &rinfo, RenderObjClass *robj,
		Int localPlayerIndex, Bool extraPass);

	char m_pad004[0x8c - 4];
	RefRenderObjListClass LightList;
	char m_pad0a4[0x110 - 0x8c - sizeof(RefRenderObjListClass)];
	RefRenderObjListClass m_dynamicLightList;
	char m_pad128[4];
	LightClass *m_globalLight[5];
	Vector3 m_infantryAmbient;
	LightClass *m_infantryLight[4];
	Int m_numGlobalLights;
	Rva00713780LightEnv m_defaultLightEnv;
	Rva00713780LightEnv m_foggedLightEnv;
	Rva00713780LightEnv m_lightEnv5B0;
	char m_pad7d8[4];
	MaterialPassClass *m_shroudMaterialPass;
	MaterialPassClass *m_heatVisionMaterialPass;
	MaterialPassClass *m_heatVisionOnlyPass;
	char m_pad7e8[0x868 - 0x7e8];
	Int m_customPassMode;
};

typedef char Rva00713780ListSize[(sizeof(RefRenderObjListClass) == 0x18) ? 1 : -1];
typedef char Rva00713780SceneLayout[(sizeof(RTS3DScene) == 0x86c) ? 1 : -1];

// ?rva00713780@RTS3DScene@@QAEXAAVRenderInfoClass@@PAVRenderObjClass@@H_N@Z
void RTS3DScene::rva00713780(RenderInfoClass &rinfo, RenderObjClass *robj,
	Int localPlayerIndex, Bool extraPass)
{
	Drawable *draw = NULL;
	DrawableInfo *drawInfo = NULL;
	Bool drawableHidden = FALSE;
	Object *obj = NULL;
	ObjectShroudStatus ss = OBJECTSHROUD_INVALID;
	Bool doExtraMaterialPop = FALSE;
	Bool doExtraFlagsPop = FALSE;
	LightClass **sceneLights = m_globalLight;

	Rva00713780LightEnv lightEnv;
	Int lightsAdded = FALSE;
	SphereClass sph = robj->Get_Bounding_Sphere();
	drawInfo = (DrawableInfo *)robj->Get_User_Data();
	if (drawInfo)
	{
		draw = drawInfo->m_drawable;
		if (!draw)
			ss = OBJECTSHROUD_FOGGED;
	}

	Vector3 ambient = Get_Ambient_Light();
	Bool terrainTinted = FALSE;
	Vector3 terrainTint;
	if (TheTerrainLogic)
	{
		Vector3 tint;
		if (TheTerrainLogic->rva001A3D30(robj->Get_Position(), &tint))
		{
			Vector3::Add(tint, ambient, &ambient); // terrain
			terrainTinted = TRUE;
			terrainTint = tint;
		}
	}

	if (draw && (drawableHidden = draw->isDrawableEffectivelyHidden()) != TRUE)
	{
		obj = draw->getObject();
		if (obj)
		{
			ss = obj->getShroudedStatus(localPlayerIndex);
			if (ss == OBJECTSHROUD_CLEAR)
			{
				draw->m_shroudClearFrame = TheGameLogic->getFrame();
			}
			else if (ss >= OBJECTSHROUD_FOGGED && draw->m_shroudClearFrame != 0)
			{
				UnsignedInt limit = 2 * 5;
				if (obj->isEffectivelyDead())
					limit += 3 * 5;
				if (TheGameLogic->getFrame() < limit + draw->m_shroudClearFrame)
					ss = OBJECTSHROUD_PARTIAL_CLEAR;
			}
			if (!robj->Peek_Scene())
				return;
		}
		else
		{
			ss = OBJECTSHROUD_CLEAR;
			if (drawInfo->m_shroudStatusObjectID != INVALID_ID)
			{
				Object *shroudObject = TheGameLogic->findObjectByID(drawInfo->m_shroudStatusObjectID);
				if (shroudObject && shroudObject->getShroudedStatus(localPlayerIndex) >= OBJECTSHROUD_FOGGED)
					ss = OBJECTSHROUD_SHROUDED;
			}
		}

		if (robj->_bfme_ro_flag109())
		{
			ambient = m_infantryAmbient;
			if (terrainTinted)
				Vector3::Add(terrainTint, ambient, &ambient); // drawn
			sceneLights = m_infantryLight;
		}

		lightEnv.Reset(sph.Center, ambient);

		const Vector3 *extraColor = draw->getColor09C();
		const Vector3 *scaleColor = callColor(j_00013926, draw);
		const Vector3 *tintColor = callColor(j_0004600b, draw);
		const Vector3 *selectionColor = callColor(j_000186e2, draw);

		if (tintColor || selectionColor || extraColor || scaleColor)
		{
			Vector3 sumTint, temp, restore, scale;

			sumTint.Set(0, 0, 0);
			if (tintColor)
				sumTint = *tintColor;
			if (selectionColor)
				Vector3::Add(sumTint, *selectionColor, &sumTint);
			if (extraColor)
				Vector3::Add(sumTint, *extraColor, &sumTint);

			scale.Set(1.0f, 1.0f, 1.0f);
			if (scaleColor)
			{
				scale.X = 1.0f - scaleColor->X;
				scale.Y = 1.0f - scaleColor->Y;
				scale.Z = 1.0f - scaleColor->Z;
			}

			for (Int globalLightIndex = 0; globalLightIndex < m_numGlobalLights; globalLightIndex++)
			{
				sceneLights[globalLightIndex]->Get_Diffuse(&temp);
				restore = temp;
				Vector3::Add(sumTint, temp, &temp);
				temp.Scale(scale);
				sceneLights[globalLightIndex]->Set_Diffuse(temp);
				lightEnv.Add_Light(*sceneLights[globalLightIndex]);
				sceneLights[globalLightIndex]->Set_Diffuse(restore);
			}

			lightsAdded = TRUE;
			temp = lightEnv.Get_Equivalent_Ambient();
			Vector3::Add(temp, sumTint, &temp);
			temp.Scale(scale);
			lightEnv.Set_Output_Ambient(temp);
		}
		else
		{
			for (Int globalLightIndex = 0; globalLightIndex < m_numGlobalLights; globalLightIndex++)
				lightEnv.Add_Light(*sceneLights[globalLightIndex]);
		}

		if (draw->m_secondMaterialPassOpacity != 0.0f)
		{
			rinfo.materialPassEmissiveOverride = draw->m_secondMaterialPassOpacity;
			if (draw->m_stealthLook == 3)
			{
				rinfo.Push_Override_Flags(RenderInfoClass::RINFO_OVERRIDE_ADDITIONAL_PASSES_ONLY);
				rinfo.Push_Material_Pass(m_heatVisionOnlyPass);
				doExtraFlagsPop = TRUE;
			}
			else
			{
				rinfo.Push_Material_Pass(m_heatVisionMaterialPass);
			}
			doExtraMaterialPop = TRUE;
		}
	}
	else
	{
		if (drawableHidden)
			return;

		if (ss == OBJECTSHROUD_FOGGED)
		{
			rinfo.light_environment = &m_foggedLightEnv;
			robj->Render(rinfo);
			rinfo.light_environment = NULL;
			return;
		}

		if (robj->_bfme_ro_flag109())
		{
			ambient = m_infantryAmbient;
			if (terrainTinted)
				Vector3::Add(terrainTint, ambient, &ambient); // undrawn
			lightEnv.Reset(sph.Center, ambient);
			for (Int globalLightIndex = 0; globalLightIndex < m_numGlobalLights; globalLightIndex++)
				lightEnv.Add_Light(*m_infantryLight[globalLightIndex]);
		}
		else
		{
			lightEnv.Reset(sph.Center, ambient);
			for (Int globalLightIndex = 0; globalLightIndex < m_numGlobalLights; globalLightIndex++)
				lightEnv.Add_Light(*m_globalLight[globalLightIndex]);
		}
	}

	if (!drawableHidden)
	{
		RefRenderObjListIterator it2(&LightList);
		for (it2.First(); !it2.Is_Done(); it2.Next())
		{
			LightClass *pLight = (LightClass *)it2.Peek_Obj();
			SphereClass lSph = pLight->Get_Bounding_Sphere();
			Bool cull = (pLight->Get_Type() == LightClass::POINT && !Spheres_Intersect(sph, lSph));
			if (!cull)
			{
				lightEnv.Add_Light(*pLight);
				lightsAdded = TRUE;
			}
		}

		RefRenderObjListIterator dynaLightIt(&m_dynamicLightList);
		for (dynaLightIt.First(); !dynaLightIt.Is_Done(); dynaLightIt.Next())
		{
			LightClass *pDyna = (LightClass *)dynaLightIt.Peek_Obj();
			if (!((Rva00713780DynamicLightView *)pDyna)->m_enabled)
				continue;
			SphereClass lSph = pDyna->Get_Bounding_Sphere();
			if (pDyna->Get_Type() == LightClass::POINT && !Spheres_Intersect(sph, lSph))
				continue;
			lightEnv.Add_Light(*(LightClass *)dynaLightIt.Peek_Obj());
			lightsAdded = TRUE;
		}

		if (!lightsAdded && !terrainTinted)
		{
			if (robj->_bfme_ro_flag109())
				rinfo.light_environment = &m_lightEnv5B0;
			else
				rinfo.light_environment = &m_defaultLightEnv;
		}
		else
		{
			lightEnv.Pre_Render_Update(rinfo.Camera.Get_Transform());
			rinfo.light_environment = &lightEnv;
		}

		if (draw && draw->m_flag0e4)
		{
			g_rva01341220Flag = true;
			g_rva012D6E04Value = (unsigned char)draw->m_value0f0;
		}
		else
		{
			g_rva01341220Flag = false;
			g_rva012D6E04Value = 0x60;
		}

		if (drawInfo)
		{
			if (m_customPassMode == 0)
			{
				if (extraPass && ((Rva00713780RenderObjView *)robj)->m_pass09c)
					((Rva00923800 *)&rinfo)->append((Rva00923800Item *)((Rva00713780RenderObjView *)robj)->m_pass09c);
				if (ss <= OBJECTSHROUD_CLEAR)
					robj->Render(rinfo);
				else if (ss == OBJECTSHROUD_PARTIAL_CLEAR)
				{
					rinfo.Push_Material_Pass(m_shroudMaterialPass);
					robj->Render(rinfo);
					rinfo.Pop_Material_Pass();
				}
				if (extraPass && ((Rva00713780RenderObjView *)robj)->m_pass09c)
					((BfmeHostFT *)&rinfo)->bfmePopFT();
			}
			else
			{
				robj->Render(rinfo);
			}
		}
		else
		{
			robj->Render(rinfo);
		}
	}

	rinfo.light_environment = NULL;
	if (doExtraMaterialPop)
		rinfo.Pop_Material_Pass();
	if (doExtraFlagsPop)
		rinfo.Pop_Override_Flags();
}
