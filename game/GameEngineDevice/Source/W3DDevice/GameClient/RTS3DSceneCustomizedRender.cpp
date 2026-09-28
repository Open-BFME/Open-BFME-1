// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// RTS3DScene::Customized_Render, retail 007143B0, 888 bytes ending ret 4.
// Identity: constructor 00712F60 installs 01120BE0; slot 23 routes through
// ILT 000133B8 to this body. Landed Render (00715B70) calls that slot.
// Uses reconciled BFME render-object/list headers: secondary list base +8;
// native vtable slots include Class_ID +0x0c and On_Frame_Update +0x34.
// Scene fields are witnessed by the constructor and this retail body.
//
// Retail updates non-terrain objects too. Terrain alone may skip its frame
// update through TerrainLogic+18f4; every remaining object tests backface
// inversion, then reloads the iterator object before On_Frame_Update.
// Pass mode 4 returns before both shadow and particle queues. Shared render
// tails require the mode-7 branch's continue and a Bool flag, not an Int.
// ParticleSystemManager queueParticleRender is slot 13 (+0x34), also
// witnessed by Rva006FEB10SceneRender.cpp. Model: gpt-6-astra.


#define Matrix4x4 Matrix4

#include "Lib/BaseType.h"
#include "Common/PlayerList.h"
#include "Common/Player.h"
#include "WW3D2/rendobj.h"
#include "WW3D2/robjlist.h"
#include "WW3D2/rinfo.h"
#include "WW3D2/camera.h"
#include "WW3D2/shader.h"

class __declspec(novtable) RTS3DScene
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void Render(RenderInfoClass &);
	virtual void Customized_Render(RenderInfoClass &);
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void Visibility_Check(CameraClass *camera);

	char pad000[0x14];
	Int m_extraPassPolygonMode;						// +0x18
	char pad01c[0x74 - 0x1c];
	RefRenderObjListClass UpdateList;				// +0x74
	char pad08c[0xec - 0x8c];
	RefRenderObjListClass RenderList;				// +0xec
	char pad104[0x128 - 0x104];
	Bool m_drawTerrainOnly;							// +0x128
	char pad129[0x868 - 0x129];
	Int m_customPassMode;							// +0x868
	Int m_translucentObjectsCount;					// +0x86c
	RenderObjClass **m_translucentObjectsBuffer;		// +0x870
	Int m_occludedObjectsCount;						// +0x874
};

enum
{
	SCENE_PASS_DEFAULT = 0,			// W3DCustomScene.h
	SCENE_PASS_ALPHA_MASK = 1		// W3DCustomScene.h
};

class GlobalData
{
public:
	char pad000[0xdbd];
	unsigned char m_bfmeByteDBD;			// +0xdbd
	char pad_dbe[0xdcc - 0xdbe];
	unsigned char m_bfmeByteDCC;			// +0xdcc
};
extern GlobalData *TheWritableGlobalData;

class TerrainLogic
{
public:
	char pad000[0x18f4];
	Bool m_bfmeField;
};
extern TerrainLogic *TheTerrainLogic;

class __declspec(novtable) BfmeGlobCC0
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual bool v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
};
extern BfmeGlobCC0 *g_bfmeGlobCC0;

class BfmeGlobQE
{
public:
	unsigned char ready;
};
extern BfmeGlobQE *g_bfmeGlobQE;

class __declspec(novtable) ParticleSystemManager
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void queueParticleRender();
};
extern ParticleSystemManager *TheParticleSystemManager;

struct Rva012F8048State
{
	char pad000[1];
};
extern Rva012F8048State *Rva012F8048StateInstance;

extern unsigned char g_bfmeRva00EF9C32;		// retail 0x012F9C32

extern bool HighlightRendering;

extern unsigned int __cdecl bfmeCurrentCU();

extern void j_00017238();
struct RTS3DSceneRenderOneObjectThunk { void Call(RenderInfoClass &, RenderObjClass *, Int, Int); };
typedef void (RTS3DSceneRenderOneObjectThunk::*RTS3DSceneRenderOneObjectCall)(RenderInfoClass &, RenderObjClass *, Int, Int);

__forceinline void callRenderOneObject(RTS3DScene *scene, RenderInfoClass &rinfo,
	RenderObjClass *robj, Int localPlayerIndex)
{
	union { void (*asFunction)(); RTS3DSceneRenderOneObjectCall asMember; } fnCast;
	fnCast.asFunction = j_00017238;
	(reinterpret_cast<RTS3DSceneRenderOneObjectThunk *>(scene)->*fnCast.asMember)(rinfo, robj, localPlayerIndex, 0);
}

struct RetailDrawableInfo
{
	enum ExtraRenderFlags
	{
		ERF_IS_NORMAL = 0,
		ERF_IS_OCCLUDED = 0x01,
		ERF_POTENTIAL_OCCLUDER = 0x02,
		ERF_POTENTIAL_OCCLUDEE = 0x04,
		ERF_IS_TRANSLUCENT = 0x08,
		ERF_IS_NON_OCCLUDER_OR_OCCLUDEE = 0x10,
		ERF_DELAYED_RENDER = ERF_IS_TRANSLUCENT | ERF_POTENTIAL_OCCLUDEE
	};

	int m_shroudStatusObjectID;
	Drawable *m_drawable;					// +0x04
	void *m_ghostObject;					// +0x08
	unsigned char m_flags;					// +0x0c
};

void RTS3DScene::Customized_Render(RenderInfoClass &rinfo)
{
	RenderObjClass *terrainObject = NULL, *robj;
	m_translucentObjectsCount = 0;		// start of new frame, no translucent objects
	m_occludedObjectsCount = 0;

	Int localPlayerIndex = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;

	Int suppressTerrainPass;
	if (m_customPassMode == SCENE_PASS_DEFAULT)
		Visibility_Check(&rinfo.Camera);
	suppressTerrainPass = 0;
	if (TheTerrainLogic) suppressTerrainPass = TheTerrainLogic->m_bfmeField;

	if (m_customPassMode == SCENE_PASS_DEFAULT)
	{
		RefRenderObjListIterator it(&UpdateList);
		for (it.First(); !it.Is_Done(); it.Next())
		{
			robj = it.Peek_Obj();
            if (robj->Class_ID() == RenderObjClass::CLASSID_TILEMAP) {
                terrainObject = robj;
                if (suppressTerrainPass) continue;
            }
            if (!ShaderClass::Is_Backface_Culling_Inverted())
                it.Peek_Obj()->On_Frame_Update();
		}

		if (terrainObject && !TheWritableGlobalData->m_bfmeByteDCC && !suppressTerrainPass)
		{
			robj = terrainObject;
			rinfo.light_environment = NULL;		// terrain is self lit
			rinfo.Camera.Set_User_Data(this);	// pass the scene via user data

			if (m_customPassMode == SCENE_PASS_DEFAULT)
			{
				robj->Render(rinfo);
				if (g_bfmeGlobCC0)
				{
					g_bfmeGlobCC0->v3c();
					if (g_bfmeGlobCC0->v28())
					{
						rinfo.Push_Override_Flags(RenderInfoClass::RINFO_OVERRIDE_ADDITIONAL_PASSES_ONLY);
						rinfo.Push_Material_Pass((MaterialPassClass *)Rva012F8048StateInstance);
						robj->Render(rinfo);
						rinfo.Pop_Material_Pass();
						rinfo.Pop_Override_Flags();
					}
				}
			}
			else
			if (m_customPassMode == 3 || m_customPassMode == 4)
			{
				if (robj->_bfme_ro_flag111() || ((unsigned char *)bfmeCurrentCU())[0x20])
					robj->Render(rinfo);
			}
			else
			if (m_customPassMode == 5 || m_customPassMode == 7 || m_customPassMode == 6)
			{
			}
			else
				robj->Render(rinfo);
		}
	}

	if (m_drawTerrainOnly)
		return;

	if (m_customPassMode == 4)
		return;
	{
		RefRenderObjListIterator it(&RenderList);
		for (it.First(); !it.Is_Done();)
		{
			robj = it.Peek_Obj();
			it.Next();	// advance now, in case this one gets deleted

			if (robj->Class_ID() == RenderObjClass::CLASSID_TILEMAP)
				continue;		// we already rendered terrain

			if (!robj->Is_Really_Visible())
				continue;

			if (m_customPassMode == 3 || m_customPassMode == 5 || m_customPassMode == 6)
			{
				if (TheWritableGlobalData->m_bfmeByteDBD)
				{
					Bool wants = robj->_bfme_ro_flag109() != 0;
                    if ((m_customPassMode != 6 || wants) && (m_customPassMode != 5 || !wants))
                        callRenderOneObject(this, rinfo, robj, localPlayerIndex);
				}
				else
				if (robj->_bfme_ro_flag111())
				{
					Bool highlight = robj->_bfme_ro_flag113() != 0;
					HighlightRendering = highlight;
					callRenderOneObject(this, rinfo, robj, localPlayerIndex);
					HighlightRendering = false;
				}
			}
			else
			if (m_customPassMode == 7)
			{
				Bool wants = robj->_bfme_ro_flag109();
				if (g_bfmeRva00EF9C32 || wants)
				{
					callRenderOneObject(this, rinfo, robj, localPlayerIndex);
					continue;
				}
			}
			else
			if (m_customPassMode == SCENE_PASS_DEFAULT)
			{
				RetailDrawableInfo *drawInfo = (RetailDrawableInfo *)robj->Get_User_Data();
				Drawable *draw = NULL;
				if (drawInfo)
					draw = drawInfo->m_drawable;
				if (!(draw && (drawInfo->m_flags & (RetailDrawableInfo::ERF_DELAYED_RENDER |
					RetailDrawableInfo::ERF_POTENTIAL_OCCLUDER |
					RetailDrawableInfo::ERF_IS_NON_OCCLUDER_OR_OCCLUDEE))))
					callRenderOneObject(this, rinfo, robj, localPlayerIndex);
			}
			else
				robj->Render(rinfo);
		}
	}

	if (g_bfmeGlobQE && terrainObject && !ShaderClass::Is_Backface_Culling_Inverted() &&
		m_extraPassPolygonMode == 0 && m_customPassMode == SCENE_PASS_DEFAULT)
		g_bfmeGlobQE->ready = 1;

	if (terrainObject && TheParticleSystemManager && m_extraPassPolygonMode == 0 &&
		m_customPassMode == SCENE_PASS_DEFAULT)
		TheParticleSystemManager->queueParticleRender();
}
