// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

// Real C++ reconstruction of the BFME RTS3DScene render override.  The retail
// extent is 0x00715B70..0x00715CE0 (368 bytes), ending at ret 4.

#include "WW3D2/dx8wrapper.h"

// GlobalData's byte at +0x70 is the behind-building marker switch.  This
// narrow declaration keeps the genuine decorated global while avoiding a
// shared-header change for a one-field access.
class GlobalData
{
	char pad000[0x70];

public:
	bool m_enableBehindBuildingMarkers;
};

extern GlobalData *TheWritableGlobalData;

class RenderInfoClass;

// The RTS3DScene constructor at 0x00712F60 installs primary vtable
// 0x01120BE0.  Its slot 22 is the 0x00427D27 ILT to this body and slot 23 is
// Customized_Render.  This TU-local ABI view names only those proven slots;
// its fields are the proven SceneClass offsets (+0x18, +0x1c, +0x20, +0x2c,
// +0x30) and the constructor-confirmed BFME custom-pass word at +0x868.
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

	void Flush(RenderInfoClass &);

	char pad004[0x14];
	int extraPassPolygonMode;
	bool FogEnabled;
	char fogPad01D[3];
	Vector3 FogColor;
	float FogStart;
	float FogEnd;
	char pad034[0x834];
	int customPassMode;
};

// Retail calls updateFixedLightEnvironments through the already matched ILT
// ?j_0002d961@@YAXXZ (0x0002D961 -> 0x007112B0).  VC7.1 reserves __thiscall
// in a free-function-pointer typedef, so use the established pointer-to-member
// cast idiom: the call still has ECX=this and one RenderInfoClass stack
// argument, while the relocation names the verified ILT rather than inventing
// a second pin for the unresolved helper body.
extern void j_0002d961();
struct RTS3DSceneUpdateThunk { void Call(RenderInfoClass &); };
typedef void (RTS3DSceneUpdateThunk::*RTS3DSceneUpdateCall)(RenderInfoClass &);

__forceinline void callUpdateFixedLightEnvironments(RTS3DScene *scene,
	RenderInfoClass &rinfo)
{
	union { void (*asFunction)(); RTS3DSceneUpdateCall asMember; } fnCast;
	fnCast.asFunction = j_0002d961;
	(reinterpret_cast<RTS3DSceneUpdateThunk *>(scene)->*fnCast.asMember)(rinfo);
}

void RTS3DScene::Render(RenderInfoClass &rinfo)
{
	DX8Wrapper::Set_Fog(FogEnabled, FogColor, FogStart, FogEnd);
	TheWritableGlobalData->m_enableBehindBuildingMarkers =
		TheWritableGlobalData->m_enableBehindBuildingMarkers && DX8Wrapper::Has_Stencil();

	if (extraPassPolygonMode == 0)
	{
		if (customPassMode == 0 || customPassMode == 3 || customPassMode == 4)
		{
			callUpdateFixedLightEnvironments(this, rinfo);
			Customized_Render(rinfo);
			Flush(rinfo);
		}
		else if (customPassMode == 5 || customPassMode == 6 || customPassMode == 7)
		{
			Customized_Render(rinfo);
			Flush(rinfo);
		}
	}
}
