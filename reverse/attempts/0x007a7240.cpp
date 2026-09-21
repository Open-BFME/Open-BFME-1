// ?d_007a7240@@YAXXZ
// partial score=0.42 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// ?setupFlatWaterShader@WaterRenderObjClass@@QAEXPAUBfmeWaterShaderPass@@@Z
//
// Retail 0x007A7240 size 2263. Identity: WaterRenderObjClass::setupFlatWaterShader
// (ZH twin W3DWater.cpp). BFME adds a pass pointer: river tex +0x24, noise +0x28,
// sparkles +0x30, additiveBlend +0x3C. this+0x2A8 white tex, this+0x2B8 pixel shader.
//
// Current probe 2040 vs 2263, first wall +0x1B after the 0x15C frame. Retail
// saves EBX/EBP/ESI/EDI, keeps the pass in EBP and the texture slot in ESI,
// then reuses EBX for the snapshot/ADDRESS constants. The current source has
// the proven callee contracts and transform path, but still has a different
// register schedule and later state-cache sequence.

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

struct IDirect3DBaseTexture8;

class TextureClass
{
public:
	virtual void Release(void);
	void Release_Ref(void);
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

class Gen_00920a60
{
public:
	void m(int value);
};

class ShroudFilter : public Gen_00920a60
{
public:
	int m_minFilter;
	int m_magFilter;
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter(void);
	TextureClass *m_texture;
};

class TextureHandle
{
public:
	TextureHandle(void) : m_p(0) {}
	~TextureHandle(void) { if (m_p) m_p->Release_Ref(); }
	TextureClass *m_p;
};

class W3DShroud
{
public:
	TextureHandle getShroudTexture(void);
};

class W3DShaderManager
{
public:
	enum ShaderTypes
	{
		ST_INVALID,
		ST_TERRAIN_BASE,
		ST_TERRAIN_BASE_NOISE1,
		ST_TERRAIN_BASE_NOISE2,
		ST_TERRAIN_BASE_NOISE12,
		ST_SHROUD_TEXTURE,
		ST_MASK_TEXTURE,
		ST_ROAD_BASE,
		ST_ROAD_BASE_NOISE1,
		ST_ROAD_BASE_NOISE2,
		ST_ROAD_BASE_NOISE12,
		ST_CLOUD_TEXTURE,
		ST_MAX
	};
	static int setShader(ShaderTypes shader, int pass);
};

class BfmeTerrainGlobal
{
	char m_pad[0x30b8];
public:
	W3DShroud *m_shroud;
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
	float m_viewHint;					// +0x5C
};

struct IDirect3DDevice9;
typedef long (__stdcall *BfmeSetRenderState)(IDirect3DDevice9 *, unsigned, unsigned);
typedef long (__stdcall *BfmeSetTexture)(IDirect3DDevice9 *, unsigned, IDirect3DBaseTexture8 *);
typedef long (__stdcall *BfmeSetTSS)(IDirect3DDevice9 *, unsigned, unsigned, unsigned);
typedef long (__stdcall *BfmeSetSamplerState)(IDirect3DDevice9 *, unsigned, unsigned, unsigned);
typedef long (__stdcall *BfmeSetPixelShader)(IDirect3DDevice9 *, unsigned);
typedef long (__stdcall *BfmeSetPixelShaderConst)(IDirect3DDevice9 *, unsigned, const float *, unsigned);
typedef long (__stdcall *BfmeGetTransform)(IDirect3DDevice9 *, unsigned, float *);
typedef long (__stdcall *BfmeSetTransform)(IDirect3DDevice9 *, unsigned, const float *);

void BoxSetTexture(unsigned stage, TextureClass *&texture);
void Apply_Render_State_Changes(void);
void bfme5SetTextureSlot(int stage, TextureClass **tex);
void Get_DX8_Texture_Stage_State_Value_Name(StringClass &name, unsigned state, unsigned value);

#define RvaBfmeGlobal (*(BfmeTerrainGlobal **)0x012F7FE0)

#define RvaShaderDirty (*(unsigned char *)0x012D6DFC)
#define RvaAlphaShaderBits (*(unsigned *)0x012D6E14)
#define RvaAdditiveShaderBits (*(unsigned *)0x012D6E0C)
#define RvaCurrentShaderBits (*(unsigned *)0x01340EC0)
#define RvaCurrentMaterial (*(VertexMaterialClass **)0x01340EC4)
#define RvaRenderStateChanged (*(unsigned *)0x0133F49C)
#define RvaSnapshotActivated (*(unsigned char *)0x0133F451)
#define RvaBfmeCh1035 (*(unsigned char *)0x0134ECC8)
#define RvaD3DDevice (*(IDirect3DDevice9 **)0x01340534)
#define RvaDX8Calls (*(unsigned *)0x01340594)
#define RvaTextureStageChanges (*(unsigned *)0x01340568)
#define RvaTextureStageStates ((unsigned (*)[32])0x0133F9E0)
#define RvaCachedPixelConst ((float *)0x01341150)

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
	if (RvaTextureStageStates[stage][state] == value)
		return;
	if (RvaSnapshotActivated) {
		StringClass name(0, true);
		*name.Peek_Buffer() = RvaBfmeCh1035;
		Get_DX8_Texture_Stage_State_Value_Name(name, state, value);
	}
	RvaTextureStageStates[stage][state] = value;
	(*(BfmeSetTSS **)RvaD3DDevice)[67](RvaD3DDevice, stage, state, value);
	++RvaDX8Calls;
	++RvaTextureStageChanges;
}

extern "C" {
	float * __stdcall D3DXMatrixInverse(float *out, float *det, const float *in);
	float * __stdcall D3DXMatrixScaling(float *out, float x, float y, float z);
	float * __stdcall D3DXMatrixTranslation(float *out, float x, float y, float z);
	float * __stdcall D3DXMatrixMultiply(float *out, const float *left, const float *right);
}

void WaterRenderObjClass::setupFlatWaterShader(BfmeWaterShaderPass *pass)
{
	register WaterRenderObjClass *self = this;
	register BfmeWaterShaderPass *passLocal = pass;
	register TextureClass **riverSlot = &passLocal->m_riverTexture;
	BoxSetTexture(0, *riverSlot);

	unsigned bits = passLocal->m_additiveBlend ? RvaAdditiveShaderBits : RvaAlphaShaderBits;
	if (RvaShaderDirty || bits != RvaCurrentShaderBits) {
		RvaCurrentShaderBits = bits;
		RvaRenderStateChanged |= 0x8000;
		StringClass tmp(0, false);
		*tmp.Peek_Buffer() = RvaBfmeCh1035;
	}

	VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	if (vmat)
		++vmat->m_ref;
	if (RvaCurrentMaterial) {
		unsigned r = RvaCurrentMaterial->m_ref - 1;
		RvaCurrentMaterial->m_ref = r;
		if (!r)
			RvaCurrentMaterial->Delete_This();
	}
	RvaRenderStateChanged |= 0x4000;
	RvaCurrentMaterial = vmat;
	if (vmat) {
		unsigned r = vmat->m_ref - 1;
		vmat->m_ref = r;
		if (!r)
			vmat->Delete_This();
	}

	ShroudFilter *f0 = reinterpret_cast<ShroudTexture *>(riverSlot)->getFilter();
	f0->m_magFilter = 2;
	ShroudFilter *f1 = reinterpret_cast<ShroudTexture *>(riverSlot)->getFilter();
	f1->m_minFilter = 2;
	reinterpret_cast<ShroudTexture *>(riverSlot)->getFilter()->m(2);

	Apply_Render_State_Changes();

	if (self->m_trapezoidWaterPixelShader) {
		W3DShroud *shroud = RvaBfmeGlobal->m_shroud;
		if (shroud) {
			TextureHandle h = shroud->getShroudTexture();
			bfme5SetTextureSlot(0, &h.m_p);
			W3DShaderManager::setShader(W3DShaderManager::ST_SHROUD_TEXTURE, 3);
			(*(BfmeSetRenderState **)RvaD3DDevice)[57](RvaD3DDevice, 23, 4);
		} else {
			(*(BfmeSetTexture **)RvaD3DDevice)[65](RvaD3DDevice, 3, self->m_whiteTexture->Peek_D3D_Base_Texture());
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
		float matrixCopy[16];
		float det;
		(*(BfmeSetTexture **)RvaD3DDevice)[65](RvaD3DDevice, 1, passLocal->m_sparklesTexture->Peek_D3D_Base_Texture());
		(*(BfmeSetTexture **)RvaD3DDevice)[65](RvaD3DDevice, 2, passLocal->m_noiseTexture->Peek_D3D_Base_Texture());
		(*(BfmeSetSamplerState **)RvaD3DDevice)[69](RvaD3DDevice, 1, 1, 1);
		(*(BfmeSetSamplerState **)RvaD3DDevice)[69](RvaD3DDevice, 1, 2, 1);
		(*(BfmeSetSamplerState **)RvaD3DDevice)[69](RvaD3DDevice, 2, 1, 1);
		(*(BfmeSetSamplerState **)RvaD3DDevice)[69](RvaD3DDevice, 2, 2, 1);
		SetTSS(2, 11, 0x20000);
		SetTSS(2, 0x18, 2);
		(*(BfmeGetTransform **)RvaD3DDevice)[45](RvaD3DDevice, 2, view);
		++RvaDX8Calls;
		D3DXMatrixInverse(inv, &det, view);
		D3DXMatrixScaling(scale, 0.0625f, 0.0625f, 1.0f);
		D3DXMatrixMultiply(destM, inv, scale);
		for (int i = 0; i < 16; ++i)
			matrixCopy[i] = destM[i];
		D3DXMatrixTranslation(scale, passLocal->m_viewHint, passLocal->m_viewHint, 0.0f);
		D3DXMatrixMultiply(destM, matrixCopy, scale);
		++(*(unsigned *)0x0134054C);
		(*(BfmeSetTransform **)RvaD3DDevice)[44](RvaD3DDevice, 0x12, destM);
		++RvaDX8Calls;
	}

	(*(BfmeSetSamplerState **)RvaD3DDevice)[69](RvaD3DDevice, 0, 6, 2);
	(*(BfmeSetSamplerState **)RvaD3DDevice)[69](RvaD3DDevice, 0, 5, 2);
	(*(BfmeSetSamplerState **)RvaD3DDevice)[69](RvaD3DDevice, 1, 6, 2);
	(*(BfmeSetSamplerState **)RvaD3DDevice)[69](RvaD3DDevice, 1, 5, 2);
	(*(BfmeSetSamplerState **)RvaD3DDevice)[69](RvaD3DDevice, 2, 6, 2);
	(*(BfmeSetSamplerState **)RvaD3DDevice)[69](RvaD3DDevice, 2, 5, 2);

	if (self->m_trapezoidWaterPixelShader) {
		float reflection[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
		if (memcmp(reflection, RvaCachedPixelConst, 16) != 0) {
			RvaCachedPixelConst[0] = reflection[0];
			RvaCachedPixelConst[1] = reflection[1];
			RvaCachedPixelConst[2] = reflection[2];
			RvaCachedPixelConst[3] = reflection[3];
			(*(BfmeSetPixelShaderConst **)RvaD3DDevice)[109](RvaD3DDevice, 0, reflection, 1);
			++RvaDX8Calls;
		}
		(*(BfmeSetPixelShader **)RvaD3DDevice)[107](RvaD3DDevice, self->m_trapezoidWaterPixelShader);
	}
}
