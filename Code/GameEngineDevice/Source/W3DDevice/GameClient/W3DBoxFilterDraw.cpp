// Retail RVA 0x00711600, 570 bytes: screen-box highlight filter draw.
// Called from the box-highlight loop (0x00714FB6, 0x00715033) with four
// stack args; the third selects between two disjoint Set_DX8_Render_State
// clusters and only one of them re-checks the DX8 caps sign bit.
// cl: /DNDEBUG /MD

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
struct DeviceVtable { char pad[0xE8]; long (__stdcall *GetVSConstant)(Device *, unsigned, void *); };
struct Device { DeviceVtable *v; };
extern Device *ScreenDevice; // 0x01340534

class DX8Wrapper {
public:
	static void Apply_Render_State_Changes();
	static void Set_DX8_Render_State(unsigned long state, unsigned value);
};

struct Coord2D { float x, y; };
void bfmeDrawFilterUV(int, int, Coord2D *);

class DX8CapsLike { public: char pad[0x28]; char npatches; };
extern DX8CapsLike *TheDX8Caps; // 0x01340578

extern bool TheBoxFilterUVEnabled; // 0x012D6DAD

void Rva00711600FilterDraw(unsigned color, unsigned mask, bool useAltCluster, unsigned altMaskValue)
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

		unsigned queryResult = 0x12345678;

		if (useAltCluster) {
			unsigned fieldMask = TheTacticalView->field8;
			DX8Wrapper::Set_DX8_Render_State(0x39, mask);
			DX8Wrapper::Set_DX8_Render_State(0x3A, fieldMask);
			DX8Wrapper::Set_DX8_Render_State(0x3B, fieldMask);
			DX8Wrapper::Set_DX8_Render_State(0x38, 2);
			DX8Wrapper::Set_DX8_Render_State(0x36, 3);
			DX8Wrapper::Set_DX8_Render_State(0x37, 3);
			DX8Wrapper::Set_DX8_Render_State(0x35, 2);
			DX8Wrapper::Set_DX8_Render_State(0x17, 1);

			if ((TheDX8Caps->npatches & 0x80) != 0) {
				ScreenDevice->v->GetVSConstant(ScreenDevice, 0xA8, &queryResult);
				DX8Wrapper::Set_DX8_Render_State(0xA8, 0);
			} else {
				DX8Wrapper::Set_DX8_Render_State(0x1B, 1);
				DX8Wrapper::Set_DX8_Render_State(0x13, 1);
				DX8Wrapper::Set_DX8_Render_State(0x14, 2);
			}
		} else {
			DX8Wrapper::Set_DX8_Render_State(0x39, mask);
			DX8Wrapper::Set_DX8_Render_State(0x3A, altMaskValue);
			DX8Wrapper::Set_DX8_Render_State(0x3B, -1);
			DX8Wrapper::Set_DX8_Render_State(0x38, 3);
			DX8Wrapper::Set_DX8_Render_State(0x36, 1);
			DX8Wrapper::Set_DX8_Render_State(0x37, 1);
			DX8Wrapper::Set_DX8_Render_State(0x35, 1);
			DX8Wrapper::Set_DX8_Render_State(0x1B, 1);
			DX8Wrapper::Set_DX8_Render_State(0x13, 5);
			DX8Wrapper::Set_DX8_Render_State(0x14, 6);
		}

		if (TheBoxFilterUVEnabled) {
			Coord2D dims = { 1.0f, 1.0f };
			bfmeDrawFilterUV((int)color, 0, &dims);
		}

		DX8Wrapper::Set_DX8_Render_State(0x34, 0);
		DX8Wrapper::Set_DX8_Render_State(0x1B, 0);
		DX8Wrapper::Set_DX8_Render_State(0x13, 2);
		DX8Wrapper::Set_DX8_Render_State(0x14, 1);
		DX8Wrapper::Set_DX8_Render_State(0x17, 8);

		if (queryResult != 0x12345678)
			DX8Wrapper::Set_DX8_Render_State(0xA8, queryResult);
	}
}
