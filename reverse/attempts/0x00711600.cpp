// ?Rva00711600FilterDraw@@YAXI@Z
// partial score=0.55 date=2026-09-05
// cl: /DNDEBUG /MD
// Retail 0x00711600, 570 bytes; prologue reads TheTacticalView (0x01306EEC),
// no SEH. Beside the matched 0x007171F0 render-to-texture shim and
// W3DShaderViewport.cpp in this directory. Shape: bail if TheTacticalView is
// null; BaseHeightMapScorchSetShader on a fixed shader object; the shared
// Get_Preset/ScreenMaterial swap idiom (family model); Apply_Render_State_Changes;
// then, guarded by ScreenDevice non-null, a long run of direct (non-inlined)
// DX8Wrapper::Set_DX8_Render_State calls -- 30 in retail, split across a
// colour-guarded cluster, a DX8 caps sign-bit branch (two five/two-call
// clusters), and a final bfmeDrawFilterUV call gated on a
// 0x12345678 "unset colour" sentinel parameter. The two clusters bracketing
// the caps check and the exact device-vtable slot (0xE8) used inside the
// negative-caps arm are reconstructed from partial disassembly, not yet
// byte-verified; see the banked partial note for the open questions.
class TacticalViewLike { public: unsigned char pad[8]; unsigned field8; };
extern TacticalViewLike *TheTacticalView; // 0x01306EEC

class ShaderClass { public: unsigned bits; };
extern ShaderClass TheScorchShader; // 0x012BAD70
void BaseHeightMapScorchSetShader(const ShaderClass &);

class VertexMaterialClass {
public:
	virtual void Delete_This();
	int refs;
	enum PresetType { PRELIT_DIFFUSE = 0 };
	static VertexMaterialClass *Get_Preset(PresetType preset);
	void Release_Ref() { if (!--refs) Delete_This(); }
};
extern VertexMaterialClass *ScreenMaterial;   // 0x01340EC4
extern unsigned TheBoxTextureDirtyMask;       // 0x0133F49C

struct Device;
struct DeviceVtable { char pad[0xE8]; long (__stdcall *SetVSConstant)(Device *, unsigned, const void *); };
struct Device { DeviceVtable *v; };
extern Device *ScreenDevice; // 0x01340534

class DX8Wrapper {
public:
	static void Apply_Render_State_Changes();
	static void Set_DX8_Render_State(unsigned long state, unsigned value);
};

struct Coord2D { float x, y; };
void bfmeDrawFilterUV(int, int, Coord2D *);

class DX8CapsLike { public: char pad[0x28]; signed char npatches; };
extern DX8CapsLike *TheDX8Caps; // 0x01340578

void Rva00711600FilterDraw(unsigned color)
{
	if (!TheTacticalView)
		return;

	BaseHeightMapScorchSetShader(TheScorchShader);

	VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	if (vmat)
		++vmat->refs;
	if (ScreenMaterial)
		ScreenMaterial->Release_Ref();
	ScreenMaterial = vmat;
	TheBoxTextureDirtyMask |= 0x4000;
	if (vmat)
		vmat->Release_Ref();

	DX8Wrapper::Apply_Render_State_Changes();

	if (ScreenDevice) {
		DX8Wrapper::Set_DX8_Render_State(0x34, 1);
		DX8Wrapper::Set_DX8_Render_State(0x07, 1);

		if (color) {
			unsigned mask = TheTacticalView->field8;
			DX8Wrapper::Set_DX8_Render_State(0x39, color);
			DX8Wrapper::Set_DX8_Render_State(0x3A, mask);
			DX8Wrapper::Set_DX8_Render_State(0x3B, mask);
			DX8Wrapper::Set_DX8_Render_State(0x38, 2);
			DX8Wrapper::Set_DX8_Render_State(0x36, 3);
			DX8Wrapper::Set_DX8_Render_State(0x37, 3);
			DX8Wrapper::Set_DX8_Render_State(0x35, 2);
			DX8Wrapper::Set_DX8_Render_State(0x17, 1);
		}

		if (TheDX8Caps->npatches < 0) {
			Coord2D dims;
			ScreenDevice->v->SetVSConstant(ScreenDevice, 0xA8, &dims);
			DX8Wrapper::Set_DX8_Render_State(0x1B, 1);
			DX8Wrapper::Set_DX8_Render_State(0x13, 1);
			DX8Wrapper::Set_DX8_Render_State(0x14, 2);
		} else {
			DX8Wrapper::Set_DX8_Render_State(0x34, 0);
			DX8Wrapper::Set_DX8_Render_State(0x1B, 0);
			DX8Wrapper::Set_DX8_Render_State(0x13, 2);
			DX8Wrapper::Set_DX8_Render_State(0x14, 1);
			DX8Wrapper::Set_DX8_Render_State(0x17, 8);
		}

		if (color != 0x12345678) {
			Coord2D dims = { 1, 1 };
			bfmeDrawFilterUV((int)color, 0xA8, &dims);
		}
	}
}
