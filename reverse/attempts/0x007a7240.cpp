// ?d_007a7240@@YAXXZ
// partial score=0.42 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// ?setupFlatWaterShader@WaterRenderObjClass@@QAEXPAUBfmeWaterShaderPass@@@Z
//
// Retail 0x007A7240 size 2263. Identity: WaterRenderObjClass::setupFlatWaterShader
// (ZH twin W3DWater.cpp). BFME adds a pass pointer: river tex +0x24, noise +0x28,
// sparkles +0x30, additiveBlend +0x3C. this+0x2A8 white tex, this+0x2B8 pixel shader.
//
// Probe 1780 vs 2263, first wall +0x15: sub esp 0x11C vs 0x15C, then push ebp
// vs push ebx. Retail copies this to ebx before BoxSetTexture and stores
// [esp+0x1c]=ebx. Next: more frame (view inverse matrices), force ebx=this,
// inline Set_Shader ShaderDirty as byte load from 0x12d6dfc, Peek via lea of
// TextureClass**, D3DX GetTransform path, sampler ADDRESS wrap.

struct IDirect3DBaseTexture8;

class TextureFilterClass
{
public:
	enum FilterType { FILTER_TYPE_NONE, FILTER_TYPE_FAST, FILTER_TYPE_BEST };
	unsigned TextureMinFilter;
	unsigned TextureMagFilter;
	void Set_Mip_Mapping(unsigned mipmap);
};

class TextureClass
{
public:
	virtual void Release(void);
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture(void) const;
};

class VertexMaterialClass
{
public:
	enum PresetType { PRELIT_DIFFUSE = 0 };
	static VertexMaterialClass *Get_Preset(PresetType preset);
	virtual void Delete_This(void);
	unsigned m_ref;
};

class StringClass
{
	char *m_buf;
	void Get_String(int size, bool hint);
	void Free_String(void);
public:
	StringClass(int size, bool hint) { Get_String(size, hint); }
	~StringClass(void) { Free_String(); }
	char *Peek_Buffer(void) { return m_buf; }
};

class ShaderClass
{
public:
	unsigned m_bits;
	static ShaderClass _PresetAdditiveShader;
	static ShaderClass _PresetAlphaShader;
	static char ShaderDirty;
};

class ShroudTextureSource
{
public:
	class Handle
	{
	public:
		Handle(const Handle &other);
		~Handle(void);
		TextureClass *m_p;
	};
	Handle getTexture(void) const;
};

class BfmeTerrainGlobal
{
	char m_pad[0x30b8];
public:
	ShroudTextureSource *m_shroud;
};

struct BfmeWaterShaderPass
{
	char m_pad00[0x24];
	TextureClass *m_riverTexture;		// +0x24
	TextureClass *m_noiseTexture;		// +0x28
	char m_pad2C[4];
	TextureClass *m_sparklesTexture;	// +0x30
	char m_pad34[8];
	unsigned char m_additiveBlend;		// +0x3C
	char m_pad3D[0x1F];
	float *m_viewHint;					// +0x5C
};

struct IDirect3DDevice9;
typedef long (__stdcall *BfmeSetRenderState)(IDirect3DDevice9 *, unsigned, unsigned);
typedef long (__stdcall *BfmeSetTexture)(IDirect3DDevice9 *, unsigned, IDirect3DBaseTexture8 *);
typedef long (__stdcall *BfmeSetTSS)(IDirect3DDevice9 *, unsigned, unsigned, unsigned);
typedef long (__stdcall *BfmeSetSamplerState)(IDirect3DDevice9 *, unsigned, unsigned, unsigned);
typedef long (__stdcall *BfmeSetPixelShader)(IDirect3DDevice9 *, unsigned);
typedef long (__stdcall *BfmeSetPixelShaderConst)(IDirect3DDevice9 *, unsigned, const float *, unsigned);

void BoxSetTexture(unsigned stage, TextureClass *&texture);
TextureFilterClass &TextureSlotGetFilter(TextureClass *&slot);
void Apply_Render_State_Changes(void);
void bfmeOneRB(int stage, TextureClass **tex);
void bfmeTwoRB(int shader, int stage);
void Get_DX8_Texture_Stage_State_Value_Name(StringClass &name, unsigned state, unsigned value);

extern BfmeTerrainGlobal *TheBfmeGlobal_012f7fe0;
extern ShaderClass CurrentShader;
extern VertexMaterialClass *CurrentMaterial;
extern unsigned RenderStateChanged;
extern char SnapshotActivated;
extern char g_bfmeCh1035;
extern char *StringClassEmptyBuf;
extern IDirect3DDevice9 *TheD3DDevice;
inline BfmeSetRenderState *DevVT(void) { return *(BfmeSetRenderState **)TheD3DDevice; }
extern unsigned number_of_DX8_calls;
extern unsigned TextureStageStateChanges;
extern unsigned TextureStageStates[8][32];
extern float CachedPixelConst[4];

class WaterRenderObjClass
{
	char m_pad[0x2A8];
public:
	TextureClass *m_whiteTexture;					// +0x2A8
	char m_pad2AC[0x0C];
	unsigned m_trapezoidWaterPixelShader;			// +0x2B8
	void setupFlatWaterShader(BfmeWaterShaderPass *pass);
};

__forceinline void SetTSS(unsigned stage, unsigned state, unsigned value)
{
	if (TextureStageStates[stage][state] == value)
		return;
	if (SnapshotActivated) {
		StringClass name(0, true);
		*name.Peek_Buffer() = g_bfmeCh1035;
		Get_DX8_Texture_Stage_State_Value_Name(name, state, value);
	}
	TextureStageStates[stage][state] = value;
	(*(BfmeSetTSS **)TheD3DDevice)[67](TheD3DDevice, stage, state, value);
	++number_of_DX8_calls;
	++TextureStageStateChanges;
}

void D3DXMatrixInverse(float *out, float *det, const float *in);
void D3DXMatrixScaling(float *out, float x, float y, float z);
void D3DXMatrixTranslation(float *out, float x, float y, float z);
void bfmeCalcVKH(float *dest, float *src, int mode);

void WaterRenderObjClass::setupFlatWaterShader(BfmeWaterShaderPass *pass)
{
	TextureClass **riverSlot = &pass->m_riverTexture;
	WaterRenderObjClass *self = this;
	BoxSetTexture(0, *riverSlot);

	unsigned bits = pass->m_additiveBlend ? ShaderClass::_PresetAdditiveShader.m_bits
	                                     : ShaderClass::_PresetAlphaShader.m_bits;
	if (ShaderClass::ShaderDirty || bits != CurrentShader.m_bits) {
		CurrentShader.m_bits = bits;
		RenderStateChanged |= 0x8000;
		StringClass tmp(0, false);
		*tmp.Peek_Buffer() = g_bfmeCh1035;
	}

	VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	if (vmat)
		++vmat->m_ref;
	if (CurrentMaterial) {
		unsigned r = CurrentMaterial->m_ref - 1;
		CurrentMaterial->m_ref = r;
		if (!r)
			CurrentMaterial->Delete_This();
	}
	RenderStateChanged |= 0x4000;
	CurrentMaterial = vmat;
	if (vmat) {
		unsigned r = vmat->m_ref - 1;
		vmat->m_ref = r;
		if (!r)
			vmat->Delete_This();
	}

	TextureFilterClass &f0 = TextureSlotGetFilter(*riverSlot);
	f0.TextureMagFilter = TextureFilterClass::FILTER_TYPE_BEST;
	TextureFilterClass &f1 = TextureSlotGetFilter(*riverSlot);
	f1.TextureMinFilter = TextureFilterClass::FILTER_TYPE_BEST;
	TextureSlotGetFilter(*riverSlot).Set_Mip_Mapping(TextureFilterClass::FILTER_TYPE_BEST);

	Apply_Render_State_Changes();

	if (self->m_trapezoidWaterPixelShader) {
		ShroudTextureSource *shroud = TheBfmeGlobal_012f7fe0->m_shroud;
		if (shroud) {
			ShroudTextureSource::Handle h = shroud->getTexture();
			bfmeOneRB(0, &h.m_p);
			bfmeTwoRB(5, 3);
			(*(BfmeSetRenderState **)TheD3DDevice)[57](TheD3DDevice, 23, 4);
		} else {
			(*(BfmeSetTexture **)TheD3DDevice)[65](TheD3DDevice, 3, self->m_whiteTexture->Peek_D3D_Base_Texture());
		}
	}

	SetTSS(0, 4, 7);
	SetTSS(0, 11, 0);
	SetTSS(1, 11, 0);

	if (self->m_trapezoidWaterPixelShader) {
		float view[16];
		float inv[16];
		float scale[16];
		float destM[16];
		float det;
		(*(BfmeSetTexture **)TheD3DDevice)[65](TheD3DDevice, 1, pass->m_sparklesTexture->Peek_D3D_Base_Texture());
		(*(BfmeSetTexture **)TheD3DDevice)[65](TheD3DDevice, 2, pass->m_noiseTexture->Peek_D3D_Base_Texture());
		(*(BfmeSetSamplerState **)TheD3DDevice)[69](TheD3DDevice, 1, 1, 1);
		(*(BfmeSetSamplerState **)TheD3DDevice)[69](TheD3DDevice, 1, 2, 1);
		(*(BfmeSetSamplerState **)TheD3DDevice)[69](TheD3DDevice, 2, 1, 1);
		(*(BfmeSetSamplerState **)TheD3DDevice)[69](TheD3DDevice, 2, 2, 1);
		SetTSS(2, 11, 0x20000);
		SetTSS(2, 0x18, 2);
		D3DXMatrixInverse(inv, &det, view);
		D3DXMatrixScaling(scale, 0.0625f, 0.0625f, 1.0f);
		bfmeCalcVKH(destM, inv, 0);
		D3DXMatrixTranslation(scale, 0, 0, 0);
		bfmeCalcVKH(destM, scale, 1);
	}

	(*(BfmeSetSamplerState **)TheD3DDevice)[69](TheD3DDevice, 0, 6, 2);
	(*(BfmeSetSamplerState **)TheD3DDevice)[69](TheD3DDevice, 0, 5, 2);
	(*(BfmeSetSamplerState **)TheD3DDevice)[69](TheD3DDevice, 1, 6, 2);
	(*(BfmeSetSamplerState **)TheD3DDevice)[69](TheD3DDevice, 1, 5, 2);
	(*(BfmeSetSamplerState **)TheD3DDevice)[69](TheD3DDevice, 2, 6, 2);
	(*(BfmeSetSamplerState **)TheD3DDevice)[69](TheD3DDevice, 2, 5, 2);

	if (self->m_trapezoidWaterPixelShader) {
		float reflection[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
		if (reflection[0] != CachedPixelConst[0] || reflection[1] != CachedPixelConst[1]
			|| reflection[2] != CachedPixelConst[2] || reflection[3] != CachedPixelConst[3]) {
			CachedPixelConst[0] = reflection[0];
			CachedPixelConst[1] = reflection[1];
			CachedPixelConst[2] = reflection[2];
			CachedPixelConst[3] = reflection[3];
			(*(BfmeSetPixelShaderConst **)TheD3DDevice)[109](TheD3DDevice, 0, reflection, 1);
			++number_of_DX8_calls;
		}
		(*(BfmeSetPixelShader **)TheD3DDevice)[107](TheD3DDevice, self->m_trapezoidWaterPixelShader);
	}
}
