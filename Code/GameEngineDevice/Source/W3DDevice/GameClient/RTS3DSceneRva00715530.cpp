// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4

#include "Lib/BaseType.h"
#include "Common/PlayerList.h"
#include "Common/Player.h"
#include "GameClient/Drawable.h"
#include "../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"
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
extern const Real BfmeZeroRange;

// TU-local virtual views describe only the slots observed by this body.
// They do not model the complete RenderObjClass hierarchy.
struct RetailDrawableOpacityView
{
	char m_pad[0xb0];
	Real m_explicitOpacity;
	Real m_effectiveStealthOpacity;
};

// RenderObjClass's BFME constructor evidence names this byte at +0xc4.
// Keep the narrow tail view local so the stock header remains untouched.
struct RetailRenderObjFlagsView
{
	char m_pad[0xc4];
	bool _bfme_unk_c4;
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
	void rva00715530(RenderInfoClass &);
	char m_bfmeSceneMembers[0x868];
	Int m_translucentObjectsCount;
	RenderObjClass **m_translucentObjectsBuffer;
};

// Existing matched ILT 0x00017238 routes to the BFME render helper at
// 0x00713780. Preserve its unresolved identity; the caller supplies four
// stack words, with the last always zero. No new canonical helper pin.
extern void j_00017238();
struct Rva00713780View { void Call(RenderInfoClass &, RenderObjClass *, Int, Int); };
typedef void (Rva00713780View::*Rva00713780Call)(RenderInfoClass &, RenderObjClass *, Int, Int);

__forceinline void callRva00713780(RTS3DScene *scene, RenderInfoClass &rinfo,
	RenderObjClass *robj, Int localPlayerIndex)
{
	union { void (*asFunction)(); Rva00713780Call asMember; } fnCast;
	fnCast.asFunction = j_00017238;
	(reinterpret_cast<Rva00713780View *>(scene)->*fnCast.asMember)(rinfo, robj, localPlayerIndex, 0);
}

// The color conversion below uses the existing WW3D x87 rounding helper;
// all scene traversal, opacity selection and dispatch are reconstructed C++.
// ?rva00715530@RTS3DScene@@IAEXAAVRenderInfoClass@@@Z
void RTS3DScene::rva00715530(RenderInfoClass &rinfo)
{
	RenderObjClass *robj;
	Drawable *draw;

	if (m_translucentObjectsCount)
	{
		Int localPlayerIndex = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;

		for (Int i=0; i<m_translucentObjectsCount; i++)
		{
			robj=m_translucentObjectsBuffer[i];
			draw = ((DrawableInfo *)robj->Get_User_Data())->m_drawable;
			RetailRenderObjFlagsView *renderObjView = reinterpret_cast<RetailRenderObjFlagsView *>(robj);
			if (!renderObjView->_bfme_unk_c4)
				continue;

			RenderObjClass *opacityView = robj;
			if (opacityView->_bfme_ro_get_98() >= BfmeZeroRange)
			{
				rinfo.alphaOverride = opacityView->_bfme_ro_get_98();
			}
			else
			{
				RetailDrawableOpacityView *drawView = reinterpret_cast<RetailDrawableOpacityView *>(draw);
				rinfo.alphaOverride = drawView->m_effectiveStealthOpacity * drawView->m_explicitOpacity;
			}

			callRva00713780(this, rinfo, robj, localPlayerIndex);
		}

		TheDX8MeshRenderer->Flush();
		WW3D::Render_And_Clear_Static_Sort_Lists(rinfo);
		rinfo.alphaOverride = 1.0f;
		m_translucentObjectsCount = 0;
	}

	DX8Wrapper::Set_DX8_Render_State(D3DRS_AMBIENT,DX8Wrapper::Convert_Color(this->Get_Ambient_Light(),0.0f));
}
