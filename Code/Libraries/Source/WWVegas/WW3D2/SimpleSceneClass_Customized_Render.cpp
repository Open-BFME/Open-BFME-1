// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
#define Matrix4x4 Matrix4

#include "camera.h"
#include "dx8wrapper.h"
#include "light.h"
#include "lightenvironment.h"
#include "rendobj.h"
#include "rinfo.h"
#include "robjlist.h"

class SimpleSceneClass
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual void Visibility_Check(CameraClass *camera);

protected:
	virtual void Customized_Render(RenderInfoClass &rinfo);

	int m_refCount;
	Vector3 AmbientLight;
	char m_pad[0x48];
	RefRenderObjListClass m_renderList;
	RefRenderObjListClass m_updateList;
	RefRenderObjListClass m_lightList;
	RefRenderObjListClass m_releaseList;
	RefRenderObjListClass m_listBC;
	RefRenderObjListClass m_listD4;
	RefRenderObjListClass m_visibleList;
};

void SimpleSceneClass::Customized_Render(RenderInfoClass &rinfo)
{
	Visibility_Check(&rinfo.Camera);

	RefRenderObjListIterator it(&m_updateList);
	for (; !it.Is_Done(); it.Next()) {
		it.Peek_Obj()->On_Frame_Update();
	}

	DX8Wrapper::Set_Light(0, NULL);
	DX8Wrapper::Set_Light(1, NULL);
	DX8Wrapper::Set_Light(2, NULL);
	DX8Wrapper::Set_Light(3, NULL);

	if (!rinfo.light_environment) {
		static LightEnvironmentClass lenv;

		lenv.Reset(Vector3(0, 0, 0), AmbientLight);
		for (it.First(&m_lightList); !it.Is_Done(); it.Next()) {
			lenv.Add_Light(*(LightClass *)it.Peek_Obj());
		}
		lenv.Pre_Render_Update(rinfo.Camera.Get_Transform());
		rinfo.light_environment = &lenv;
	}

	for (it.First(&m_visibleList); !it.Is_Done(); it.Next()) {
		RenderObjClass *robj = it.Peek_Obj();
		if (robj->Is_Really_Visible()) {
			robj->Render(rinfo);
		}
	}
}
