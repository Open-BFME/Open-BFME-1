// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DNDEBUG /MD
#include "dx8wrapper.h"

// Retail RVA 0x00711600, 570 bytes: screen-box highlight filter draw.
// Called from the box-highlight loop (0x00714FB6, 0x00715033) with four
// stack args; the third selects between two disjoint Set_DX8_Render_State
// clusters and only one of them re-checks the DX8 caps sign bit.

// Retail's shadow-manager global at 0x01306EEC is `W3DShadowManager
// *TheW3DShadowManager`, the same name the W3D shadow TUs already use.  The
// class here is a stand-in (retail's own `View *TheTacticalView` is a
// different global, at 0x012F1600), but retail mangles the pointer type into
// the data symbol, so both spellings have to match retail's.
class W3DShadowManager { public: unsigned char pad[8]; unsigned field8; };
extern W3DShadowManager *TheW3DShadowManager; // 0x01306EEC


extern ShaderClass TheScorchShader; // 0x012BAD70


extern VertexMaterialClass *ScreenMaterial;   // 0x01340EC4
extern unsigned TheBoxTextureDirtyMask;       // 0x0133F49C

struct Device;
struct DeviceVtable { char pad[0xE8]; long (__stdcall *GetVSConstant)(Device *, unsigned, void *); };
struct Device { DeviceVtable *v; };



struct Coord2D { float x, y; };
void bfmeDrawFilterUV(int, int, Coord2D *);

class DX8CapsLike { public: char pad[0x28]; char npatches; };
extern DX8CapsLike *TheDX8Caps; // 0x01340578


void Rva00711600FilterDraw(unsigned color, unsigned mask, bool useAltCluster, unsigned altMaskValue)
{
	if (!TheW3DShadowManager)
		return;

	DX8Wrapper::Set_Shader(TheScorchShader);

	VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	if (vmat)
		vmat->Add_Ref();
	if (ScreenMaterial)
		ScreenMaterial->Release_Ref();
	ScreenMaterial = vmat;
	TheBoxTextureDirtyMask |= 0x4000;
	if (vmat)
		vmat->Release_Ref();

	DX8Wrapper::Apply_Render_State_Changes();

	if (reinterpret_cast<Device *>(DX8Wrapper::_Get_D3D_Device8())) {
		(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x34, 1);
		(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x07, 1);

		unsigned queryResult = 0x12345678;

		if (useAltCluster) {
			unsigned fieldMask = TheW3DShadowManager->field8;
			(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x39, mask);
			(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x3A, fieldMask);
			(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x3B, fieldMask);
			(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x38, 2);
			(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x36, 3);
			(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x37, 3);
			(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x35, 2);
			(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x17, 1);

			if ((TheDX8Caps->npatches & 0x80) != 0) {
				reinterpret_cast<Device *>(DX8Wrapper::_Get_D3D_Device8())->v->GetVSConstant(reinterpret_cast<Device *>(DX8Wrapper::_Get_D3D_Device8()), 0xA8, &queryResult);
				(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0xA8, 0);
			} else {
				(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x1B, 1);
				(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x13, 1);
				(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x14, 2);
			}
		} else {
			(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x39, mask);
			(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x3A, altMaskValue);
			(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x3B, -1);
			(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x38, 3);
			(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x36, 1);
			(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x37, 1);
			(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x35, 1);
			(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x1B, 1);
			(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x13, 5);
			(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x14, 6);
		}

		if (DX8Wrapper::_Is_Triangle_Draw_Enabled()) {
			Coord2D dims = { 1.0f, 1.0f };
			bfmeDrawFilterUV((int)color, 0, &dims);
		}

		(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x34, 0);
		(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x1B, 0);
		(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x13, 2);
		(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x14, 1);
		(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0x17, 8);

		if (queryResult != 0x12345678)
			(*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(0xA8, queryResult);
	}
}
