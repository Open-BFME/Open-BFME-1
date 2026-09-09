// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4

#include "Lib/BaseType.h"
#include "Common/PlayerList.h"
#include "Common/Player.h"
#include "GameClient/Drawable.h"
#include "WW3D2/rendobj.h"
#include "WW3D2/RInfo.h"
#include "WW3D2/dx8wrapper.h"
#include "WW3D2/sortingrenderer.h"

// BFME stores the mesh renderer as a pointer at 0x0134B0E8 (the upstream
// Zero Hour header declares an object, so keep this TU-local ABI view).
class DX8MeshRendererClass
{
public:
	void Flush();
};
extern DX8MeshRendererClass *TheDX8MeshRenderer;

// TU-local virtual views describe only the slots observed by this body.
// They do not model the complete RenderObjClass hierarchy.
class RetailRenderObjUserDataView
{
public:
	virtual void userDataSlot00() = 0;
	virtual void userDataSlot01() = 0;
	virtual void userDataSlot02() = 0;
	virtual void userDataSlot03() = 0;
	virtual void userDataSlot04() = 0;
	virtual void userDataSlot05() = 0;
	virtual void userDataSlot06() = 0;
	virtual void userDataSlot07() = 0;
	virtual void userDataSlot08() = 0;
	virtual void userDataSlot09() = 0;
	virtual void userDataSlot10() = 0;
	virtual void userDataSlot11() = 0;
	virtual void userDataSlot12() = 0;
	virtual void userDataSlot13() = 0;
	virtual void userDataSlot14() = 0;
	virtual void userDataSlot15() = 0;
	virtual void userDataSlot16() = 0;
	virtual void userDataSlot17() = 0;
	virtual void userDataSlot18() = 0;
	virtual void userDataSlot19() = 0;
	virtual void userDataSlot20() = 0;
	virtual void userDataSlot21() = 0;
	virtual void userDataSlot22() = 0;
	virtual void userDataSlot23() = 0;
	virtual void userDataSlot24() = 0;
	virtual void userDataSlot25() = 0;
	virtual void userDataSlot26() = 0;
	virtual void userDataSlot27() = 0;
	virtual void userDataSlot28() = 0;
	virtual void userDataSlot29() = 0;
	virtual void userDataSlot30() = 0;
	virtual void userDataSlot31() = 0;
	virtual void userDataSlot32() = 0;
	virtual void userDataSlot33() = 0;
	virtual void userDataSlot34() = 0;
	virtual void userDataSlot35() = 0;
	virtual void userDataSlot36() = 0;
	virtual void userDataSlot37() = 0;
	virtual void userDataSlot38() = 0;
	virtual void userDataSlot39() = 0;
	virtual void userDataSlot40() = 0;
	virtual void userDataSlot41() = 0;
	virtual void userDataSlot42() = 0;
	virtual void userDataSlot43() = 0;
	virtual void userDataSlot44() = 0;
	virtual void userDataSlot45() = 0;
	virtual void userDataSlot46() = 0;
	virtual void userDataSlot47() = 0;
	virtual void userDataSlot48() = 0;
	virtual void userDataSlot49() = 0;
	virtual void userDataSlot50() = 0;
	virtual void userDataSlot51() = 0;
	virtual void userDataSlot52() = 0;
	virtual void userDataSlot53() = 0;
	virtual void userDataSlot54() = 0;
	virtual void userDataSlot55() = 0;
	virtual void userDataSlot56() = 0;
	virtual void userDataSlot57() = 0;
	virtual void userDataSlot58() = 0;
	virtual void userDataSlot59() = 0;
	virtual void userDataSlot60() = 0;
	virtual void userDataSlot61() = 0;
	virtual void userDataSlot62() = 0;
	virtual void userDataSlot63() = 0;
	virtual void userDataSlot64() = 0;
	virtual void userDataSlot65() = 0;
	virtual void userDataSlot66() = 0;
	virtual void userDataSlot67() = 0;
	virtual void userDataSlot68() = 0;
	virtual void userDataSlot69() = 0;
	virtual void userDataSlot70() = 0;
	virtual void userDataSlot71() = 0;
	virtual void userDataSlot72() = 0;
	virtual void userDataSlot73() = 0;
	virtual void userDataSlot74() = 0;
	virtual void userDataSlot75() = 0;
	virtual void userDataSlot76() = 0;
	virtual void userDataSlot77() = 0;
	virtual void userDataSlot78() = 0;
	virtual void userDataSlot79() = 0;
	virtual void userDataSlot80() = 0;
	virtual void userDataSlot81() = 0;
	virtual void userDataSlot82() = 0;
	virtual void userDataSlot83() = 0;
	virtual void userDataSlot84() = 0;
	virtual void userDataSlot85() = 0;
	virtual void *getUserData() = 0; // retail vtable slot +0x158
};

class RetailRenderObjOpacityView
{
public:
	virtual void v00() = 0; virtual void v01() = 0; virtual void v02() = 0; virtual void v03() = 0;
	virtual void v04() = 0; virtual void v05() = 0; virtual void v06() = 0; virtual void v07() = 0;
	virtual void v08() = 0; virtual void v09() = 0; virtual void v10() = 0; virtual void v11() = 0;
	virtual void v12() = 0; virtual void v13() = 0; virtual void v14() = 0; virtual void v15() = 0;
	virtual void v16() = 0; virtual void v17() = 0; virtual void v18() = 0; virtual void v19() = 0;
	virtual void v20() = 0; virtual void v21() = 0; virtual void v22() = 0; virtual void v23() = 0;
	virtual Real getRetailOpacity() = 0; // retail vtable slot +0x60
};

struct RetailDrawableOpacityView
{
	char m_pad[0xb0];
	Real m_explicitOpacity;
	Real m_effectiveStealthOpacity;
};

class RTS3DScene
{
public:
	virtual void bfmeSceneVirtual0() = 0;
	virtual void bfmeSceneVirtual1() = 0;
	virtual void bfmeSceneVirtual2() = 0;
	virtual void bfmeSceneVirtual3() = 0;
	virtual void bfmeSceneVirtual4() = 0;
	virtual void bfmeSceneVirtual5() = 0;
	virtual void bfmeSceneVirtual6() = 0;
	virtual const Vector3 &Get_Ambient_Light() = 0;

protected:
	void flushTranslucentObjects(RenderInfoClass &);
	char m_bfmeSceneMembers[0x868];
	Int m_translucentObjectsCount;
	RenderObjClass **m_translucentObjectsBuffer;
};

// Existing matched ILT 0x00017238 routes to the BFME render helper at
// 0x00713780. Preserve its unresolved identity; the caller supplies four
// stack words, with the last always zero. No new canonical helper pin.
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

// The color conversion below uses the existing WW3D x87 rounding helper;
// all scene traversal, opacity selection and dispatch are reconstructed C++.
// ?flushTranslucentObjects@RTS3DScene@@IAEXAAVRenderInfoClass@@@Z
void RTS3DScene::flushTranslucentObjects(RenderInfoClass &rinfo)
{
	RenderObjClass *robj;
	Drawable *draw;

	if (m_translucentObjectsCount)
	{
		Int localPlayerIndex = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;

		for (Int i=0; i<m_translucentObjectsCount; i++)
		{
			robj=m_translucentObjectsBuffer[i];
			draw = ((DrawableInfo *)reinterpret_cast<RetailRenderObjUserDataView *>(robj)->getUserData())->m_drawable;
			if (*(const UnsignedByte *)(reinterpret_cast<const char *>(robj) + 0xc4))
				continue;

			RetailRenderObjOpacityView *opacityView = reinterpret_cast<RetailRenderObjOpacityView *>(robj);
			if (opacityView->getRetailOpacity() >= 0.0f)
			{
				rinfo.alphaOverride = opacityView->getRetailOpacity();
			}
			else
			{
				RetailDrawableOpacityView *drawView = reinterpret_cast<RetailDrawableOpacityView *>(draw);
				rinfo.alphaOverride = drawView->m_effectiveStealthOpacity * drawView->m_explicitOpacity;
			}

			callRenderOneObject(this, rinfo, robj, localPlayerIndex);
		}

		TheDX8MeshRenderer->Flush();
		WW3D::Render_And_Clear_Static_Sort_Lists(rinfo);
		rinfo.alphaOverride = 1.0f;
	}

	DX8Wrapper::Set_DX8_Render_State(D3DRS_AMBIENT,DX8Wrapper::Convert_Color(this->Get_Ambient_Light(),0.0f));
}
