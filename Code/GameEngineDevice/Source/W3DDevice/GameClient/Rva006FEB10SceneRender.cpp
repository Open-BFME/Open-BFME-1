// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug
// BFME scene-render mirror for the anonymous retail body at 0x006FEB10.
// The scene/list offsets and render-object slots are kept TU-local because
// this body is a wider BFME render path than the shared ZH SimpleScene class.

#define Matrix4x4 Matrix4
#include "WW3D2/rendobj.h"
#include "WW3D2/ww3d.h"
#include "WW3D2/dx8wrapper.h"
#include "WW3D2/camera.h"
#include "WW3D2/rinfo.h"
#include "WW3D2/lightenvironment.h"
#include "WW3D2/robjlist.h"

// The target dispatches through SimpleScene's Visibility_Check slot at +0x6c.
// Only that slot and the three list/ambient members used below are claimed.
class __declspec(novtable) Rva006FEB10Scene
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
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void Visibility_Check(CameraClass *camera);

	void Customized_Render(RenderInfoClass &rinfo);

	char pad004[4];
	Vector3 AmbientLight;
	char pad014[0x60];
	RefRenderObjListClass UpdateList;
	RefRenderObjListClass LightList;
	char pad0a8[0x48];
	RefRenderObjListClass VisibleList;
	char padAfterVisible[4];
};

typedef char Rva006FEB10SceneLayout[
	(sizeof(Rva006FEB10Scene) == 0x108) ? 1 : -1];

// The BFME primary particle-manager table places doParticles at +0x2c and
// queueParticleRender at +0x34.  The preceding virtuals are deliberately
// unnamed ABI slots; no implementation is invented for them here.
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
	virtual void doParticles(RenderInfoClass &rinfo);
	virtual void slot12();
	virtual void queueParticleRender();
};

extern ParticleSystemManager *TheParticleSystemManager;

class BfmeGlobQE
{
public:
	unsigned char ready;
};

extern BfmeGlobQE *g_bfmeGlobQE;

class DX8MeshRendererClass
{
public:
	void Flush(void);
};

extern DX8MeshRendererClass *TheDX8MeshRenderer;

// This is the real body behind the retail ILT at 0x00011B71.  Keep the real
// symbol name in the source; the thunk is an import/linker detail.
extern void __cdecl DoShadows(RenderInfoClass &rinfo, bool stencilPass);

// ?Customized_Render@Rva006FEB10Scene@@QAEXAAVRenderInfoClass@@@Z
void Rva006FEB10Scene::Customized_Render(RenderInfoClass &rinfo)
{
	Visibility_Check(&rinfo.Camera);

	RefRenderObjListIterator it(&UpdateList);
	for (it.First(); !it.Is_Done(); it.Next()) {
		it.Peek_Obj()->On_Frame_Update();
	}

	DX8Wrapper::Set_Light(0, NULL);
	DX8Wrapper::Set_Light(1, NULL);
	DX8Wrapper::Set_Light(2, NULL);
	DX8Wrapper::Set_Light(3, NULL);

	if (!rinfo.light_environment) {
		static LightEnvironmentClass lenv;

		lenv.Reset(Vector3(0, 0, 0), AmbientLight);
		for (it.First(&LightList); !it.Is_Done(); it.Next()) {
			lenv.Add_Light(*(LightClass *)it.Peek_Obj());
		}
		lenv.Pre_Render_Update(rinfo.Camera.Get_Transform());
		rinfo.light_environment = &lenv;
	}

	DX8Wrapper::Apply_Render_State_Changes();
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZWRITEENABLE, FALSE);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZENABLE, TRUE);

	for (it.First(&VisibleList); !it.Is_Done(); it.Next()) {
		RenderObjClass *robj = it.Peek_Obj();
		if (robj->Is_Really_Visible() && !robj->_bfme_ro_flag109()) {
			robj->Render(rinfo);
		}
	}

	for (it.First(&VisibleList); !it.Is_Done(); it.Next()) {
		RenderObjClass *robj = it.Peek_Obj();
		if (robj->Is_Really_Visible() && robj->_bfme_ro_flag109()) {
			robj->Render(rinfo);
		}
	}

	TheDX8MeshRenderer->Flush();
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZWRITEENABLE, TRUE);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	g_bfmeGlobQE->ready = 1;
	DoShadows(rinfo, true);
	TheParticleSystemManager->queueParticleRender();
	TheParticleSystemManager->doParticles(rinfo);
}
