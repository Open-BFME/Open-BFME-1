// ?flush007B14A0@W3DProjectedShadowManager@@QAEXIPAUShadowTexture007B6D30@@0H@Z
// partial score=0.99 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc
// Retail 0x007B14A0, 3124 bytes, ret 0x10 at +0xC31 then int3.
//
// BFME's four-argument form of Zero Hour W3DProjectedShadowManager::flushDecals
// (GeneralsMD W3DProjectedShadow.cpp, EA GPL-3.0-or-later). The matched
// renderShadows (0x007B6D30) calls it through ILT 0x00012472 after every
// batch with (type, texture, second texture, mode); its pinned address-derived
// name is kept because the retail signature differs from Zero Hour's.
//
// The ZH twin is witnessed by layout, not only by shape: the six decal-batch
// globals sit at 0x01306E04..0x01306E20 in ZH's declaration order (vertex
// buffer, index buffer, VertsInBuf, StartBatchVertex, IndicesInBuf,
// StartBatchIndex, PolysInBatch, VertsInBatch), renderShadows writes ZH's
// 0x8000/0x10000 buffer sizes into VertsInBuf/IndicesInBuf, the Record and
// DrawIndexedPrimitive argument orders follow ZH, and the identity Matrix4x4
// static is set as the world transform. The single-texture switch keeps ZH's
// shader choice per decal type (0x12D6E08.. are shader.cpp's presets in
// declaration order: Opaque, Additive, Bumpenvmap, Alpha, Multiplicative).
//
// BFME adds: a second texture on stage 1 with its own inline shader bits,
// timed-decal types 0x400/0x800 sharing the alpha/additive paths, and a
// stencil type 0x1000 whose GlobalData switch (+0xA77) and alpha reference
// (+0xA78, scaled by 255) have no Zero Hour or FieldParse name. The D3D9
// device slots (base-vertex DrawIndexedPrimitive, four-argument
// SetStreamSource, SetFVF 0x242 over a 32-byte two-UV vertex) and the Z-bias
// bracket are BFME's. Release-build snapshot diagnostics stay inline in
// DX8Wrapper's render-state and shader setters, as in the other BFME bodies.

class TextureBaseClass;

class TextureClass
{
public:
	void Release_Ref();
};

class StringClass
{
	char *m_Buffer;
	static char *m_EmptyString;
	static char m_NullChar;
	void Get_String(int, bool);
	void Free_String();

public:
	StringClass(int n = 0, bool temp = false) : m_Buffer(m_EmptyString)
	{
		Get_String(n, temp);
		m_Buffer[0] = m_NullChar;
	}
	~StringClass() throw()
	{
		Free_String();
	}
};

// The texture handle retail 0x007AE6B0 returns by value (see
// W3DProjectedShadowUpdateTexture.cpp); stage binds take it by reference.
class BfmeHandleCX
{
public:
	TextureClass *m_texture;
	BfmeHandleCX() : m_texture(0) {}
	~BfmeHandleCX()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
	operator TextureBaseClass *&()
	{
		return (TextureBaseClass *&)m_texture;
	}
};

// Retail 0x007AE6B0 reads the handle at +0x30 of the shadow texture.
class Gen_007AE6B0
{
public:
	BfmeHandleCX bfmeGet(void) const;
};

void BoxSetTexture(unsigned int, TextureBaseClass *&);

static inline int decrementRef(int *p) { return --*p; }

class VertexMaterialClass
{
public:
	virtual void Delete_This();
	int refs;
	enum PresetType { PRELIT_DIFFUSE = 0 };
	static VertexMaterialClass *Get_Preset(PresetType preset);
	void ReleaseGlobalRef()
	{
		decrementRef(&refs);
		if (refs == 0)
			Delete_This();
	}
};

class ShaderClass
{
public:
	unsigned int ShaderBits;
	ShaderClass(unsigned int bits) : ShaderBits(bits) {}
	static bool ShaderDirty;
	static ShaderClass _PresetOpaqueShader;
	static ShaderClass _PresetAdditiveShader;
	static ShaderClass _PresetAlphaShader;
	static ShaderClass _PresetMultiplicativeShader;
};

// Three further shader words the stencil paths select; nothing names them.
extern ShaderClass Rva012BBE2CShader;
extern ShaderClass Rva012BBE30Shader;
extern ShaderClass Rva012BBE34Shader;

namespace Debug_Statistics { void Record_DX8_Polys_And_Vertices(int, int, const ShaderClass &); }

// The D3D9 render-state and comparison values this body sets.
enum D3DRENDERSTATETYPE
{
	D3DRS_ALPHAREF = 24,
	D3DRS_ALPHAFUNC = 25,
	D3DRS_STENCILPASS = 55,
	D3DRS_STENCILFUNC = 56
};
enum D3DCMPFUNC { D3DCMP_NOTEQUAL = 6, D3DCMP_GREATEREQUAL = 7, D3DCMP_ALWAYS = 8 };
enum D3DSTENCILOP { D3DSTENCILOP_KEEP = 1, D3DSTENCILOP_REPLACE = 3 };

struct ShadowDecalBuffer007B14A0;

// The D3D9 device interface; only the slots this body calls are named.
#define DEVICE_SLOT(n) virtual void __stdcall slot##n();
class ShadowDecalDevice007B14A0
{
public:
	DEVICE_SLOT(00) DEVICE_SLOT(01) DEVICE_SLOT(02) DEVICE_SLOT(03) DEVICE_SLOT(04)
	DEVICE_SLOT(05) DEVICE_SLOT(06) DEVICE_SLOT(07) DEVICE_SLOT(08) DEVICE_SLOT(09)
	DEVICE_SLOT(10) DEVICE_SLOT(11) DEVICE_SLOT(12) DEVICE_SLOT(13) DEVICE_SLOT(14)
	DEVICE_SLOT(15) DEVICE_SLOT(16) DEVICE_SLOT(17) DEVICE_SLOT(18) DEVICE_SLOT(19)
	DEVICE_SLOT(20) DEVICE_SLOT(21) DEVICE_SLOT(22) DEVICE_SLOT(23) DEVICE_SLOT(24)
	DEVICE_SLOT(25) DEVICE_SLOT(26) DEVICE_SLOT(27) DEVICE_SLOT(28) DEVICE_SLOT(29)
	DEVICE_SLOT(30) DEVICE_SLOT(31) DEVICE_SLOT(32) DEVICE_SLOT(33) DEVICE_SLOT(34)
	DEVICE_SLOT(35) DEVICE_SLOT(36) DEVICE_SLOT(37) DEVICE_SLOT(38) DEVICE_SLOT(39)
	DEVICE_SLOT(40) DEVICE_SLOT(41) DEVICE_SLOT(42) DEVICE_SLOT(43)
	virtual long __stdcall SetTransform(unsigned int, const void *);
	DEVICE_SLOT(45) DEVICE_SLOT(46) DEVICE_SLOT(47) DEVICE_SLOT(48) DEVICE_SLOT(49)
	DEVICE_SLOT(50) DEVICE_SLOT(51) DEVICE_SLOT(52) DEVICE_SLOT(53) DEVICE_SLOT(54)
	DEVICE_SLOT(55) DEVICE_SLOT(56)
	virtual long __stdcall SetRenderState(unsigned int, unsigned int);
	DEVICE_SLOT(58) DEVICE_SLOT(59) DEVICE_SLOT(60) DEVICE_SLOT(61) DEVICE_SLOT(62)
	DEVICE_SLOT(63) DEVICE_SLOT(64) DEVICE_SLOT(65) DEVICE_SLOT(66) DEVICE_SLOT(67)
	DEVICE_SLOT(68) DEVICE_SLOT(69) DEVICE_SLOT(70) DEVICE_SLOT(71) DEVICE_SLOT(72)
	DEVICE_SLOT(73) DEVICE_SLOT(74) DEVICE_SLOT(75) DEVICE_SLOT(76) DEVICE_SLOT(77)
	DEVICE_SLOT(78) DEVICE_SLOT(79) DEVICE_SLOT(80) DEVICE_SLOT(81)
	virtual long __stdcall DrawIndexedPrimitive(unsigned int, int, unsigned int, unsigned int,
		unsigned int, unsigned int);
	DEVICE_SLOT(83) DEVICE_SLOT(84) DEVICE_SLOT(85) DEVICE_SLOT(86) DEVICE_SLOT(87)
	DEVICE_SLOT(88)
	virtual long __stdcall SetFVF(unsigned int);
	DEVICE_SLOT(90) DEVICE_SLOT(91) DEVICE_SLOT(92) DEVICE_SLOT(93) DEVICE_SLOT(94)
	DEVICE_SLOT(95) DEVICE_SLOT(96) DEVICE_SLOT(97) DEVICE_SLOT(98) DEVICE_SLOT(99)
	virtual long __stdcall SetStreamSource(unsigned int, ShadowDecalBuffer007B14A0 *,
		unsigned int, unsigned int);
	DEVICE_SLOT(101) DEVICE_SLOT(102) DEVICE_SLOT(103)
	virtual long __stdcall SetIndices(ShadowDecalBuffer007B14A0 *);
};
#undef DEVICE_SLOT

struct RenderStateStruct
{
	ShaderClass shader;
	VertexMaterialClass *material;
};
extern unsigned int Rva0133F49CChanged;
extern bool Rva0133F451Snapshot;
extern unsigned int number_of_DX8_calls;

class DX8Wrapper
{
public:
	static void Apply_Render_State_Changes();
	static bool Has_Stencil();
	static void Get_DX8_Render_State_Value_Name(StringClass &, unsigned long, unsigned int);
	static ShadowDecalDevice007B14A0 *_Get_D3D_Device8() { return D3DDevice; }
	static bool _EnableTriangleDraw;

	static __forceinline void Set_Material(VertexMaterialClass *vmat)
	{
		if (vmat)
			++vmat->refs;
		if (render_state.material)
			render_state.material->ReleaseGlobalRef();
		render_state.material = vmat;
		Rva0133F49CChanged |= 0x4000;
	}

	static __forceinline void Set_Shader(const ShaderClass &shader)
	{
		if (ShaderClass::ShaderDirty || shader.ShaderBits != render_state.shader.ShaderBits) {
			render_state.shader = shader;
			Rva0133F49CChanged |= 0x8000;
			StringClass str;
		}
	}

	static __forceinline void Set_DX8_Render_State(D3DRENDERSTATETYPE state, unsigned int value)
	{
		if (RenderStates[state] == value)
			return;
		if (Rva0133F451Snapshot) {
			StringClass value_name(0, true);
			Get_DX8_Render_State_Value_Name(value_name, state, value);
		}
		RenderStates[state] = value;
		D3DDevice->SetRenderState(state, value);
		++number_of_DX8_calls;
		++render_state_changes;
	}

private:
	static ShadowDecalDevice007B14A0 *D3DDevice;
	static unsigned int RenderStates[256];
	static unsigned int render_state_changes;
	static RenderStateStruct render_state;
};

class BFMEZBiasSetter
{
public:
	static void set(float);
};

// Neither byte nor float has a Zero Hour member or FieldParse entry.
struct GlobalData007B14A0
{
	char pad000[0xa77];
	bool m_bfmeA77;
	float m_bfmeA78;
};
extern GlobalData007B14A0 *TheWritableGlobalData;

class WWMath
{
public:
	static int Clamp_Int(int val, int min_val, int max_val)
	{
		if (val < min_val) return min_val;
		if (val > max_val) return max_val;
		return val;
	}
};

class Matrix4x4
{
public:
	float Row[4][4];
	Matrix4x4(bool)
	{
		Row[0][0] = 1.0f; Row[0][1] = 0.0f; Row[0][2] = 0.0f; Row[0][3] = 0.0f;
		Row[1][0] = 0.0f; Row[1][1] = 1.0f; Row[1][2] = 0.0f; Row[1][3] = 0.0f;
		Row[2][0] = 0.0f; Row[2][1] = 0.0f; Row[2][2] = 1.0f; Row[2][3] = 0.0f;
		Row[3][0] = 0.0f; Row[3][1] = 0.0f; Row[3][2] = 0.0f; Row[3][3] = 1.0f;
	}
};

struct SHADOW_DECAL_VERTEX
{
	float x, y, z;
	unsigned int diffuse;
	float u, v;
	float u2, v2;
};

#define SHADOW_DECAL_FVF 0x242

extern ShadowDecalBuffer007B14A0 *shadowDecalVertexBufferD3D;
extern ShadowDecalBuffer007B14A0 *shadowDecalIndexBufferD3D;
extern int nShadowDecalVertsInBuf;
extern int nShadowDecalStartBatchVertex;
extern int nShadowDecalIndicesInBuf;
extern int nShadowDecalStartBatchIndex;
extern int nShadowDecalPolysInBatch;
extern int nShadowDecalVertsInBatch;

struct ShadowTexture007B6D30;

class W3DProjectedShadowManager
{
public:
	void flush007B14A0(unsigned, ShadowTexture007B6D30 *, ShadowTexture007B6D30 *, int);
};

static inline const Gen_007AE6B0 *decalTexture(ShadowTexture007B6D30 *texture)
{
	return (const Gen_007AE6B0 *)texture;
}

void W3DProjectedShadowManager::flush007B14A0(unsigned type, ShadowTexture007B6D30 *texture,
	ShadowTexture007B6D30 *texture2, int mode)
{
	static Matrix4x4 mWorld(true);

	if (nShadowDecalVertsInBatch == 0 && nShadowDecalPolysInBatch == 0)
		return;

	ShadowDecalDevice007B14A0 *m_pDev = DX8Wrapper::_Get_D3D_Device8();
	if (!m_pDev)
		return;

	VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(vmat);
	if (vmat) {
		if (--vmat->refs == 0)
			vmat->Delete_This();
	}
	BoxSetTexture(0, ((const Gen_007AE6B0 *)texture)->bfmeGet());

	if (texture2) {
		switch ((int)type) {
		case 1:
			BoxSetTexture(1, ((const Gen_007AE6B0 *)texture2)->bfmeGet());
			DX8Wrapper::Set_Shader(ShaderClass(0x00511853));
			break;
		case 0x20:
		case 0x400:
			BoxSetTexture(1, ((const Gen_007AE6B0 *)texture2)->bfmeGet());
			DX8Wrapper::Set_Shader(ShaderClass(0x005198B3));
			break;
		case 0x40:
		case 0x800:
			BoxSetTexture(1, ((const Gen_007AE6B0 *)texture2)->bfmeGet());
			DX8Wrapper::Set_Shader(ShaderClass(0x00515833));
			break;
		}
	} else {
		switch ((int)type) {
		case 1:
			DX8Wrapper::Set_Shader(ShaderClass::_PresetMultiplicativeShader);
			break;
		case 0x20:
		case 0x400:
			DX8Wrapper::Set_Shader(ShaderClass::_PresetAlphaShader);
			break;
		case 0x40:
		case 0x800:
			DX8Wrapper::Set_Shader(ShaderClass::_PresetAdditiveShader);
			break;
		}
	}

	if (type == 0x1000) {
		if (DX8Wrapper::Has_Stencil()) {
			if (TheWritableGlobalData->m_bfmeA77) {
				DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC, D3DCMP_NOTEQUAL);
				DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
				BoxSetTexture(1, BfmeHandleCX());
				DX8Wrapper::Set_Shader(Rva012BBE34Shader);
				DX8Wrapper::Apply_Render_State_Changes();
				DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
				int ref = (int)(TheWritableGlobalData->m_bfmeA78 * 255.0f);
				DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHAREF, ref < 0 ? 0 : (ref > 255 ? 255 : ref));
			} else if (mode == 0) {
				DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
				DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
				BoxSetTexture(0, ((const Gen_007AE6B0 *)texture2)->bfmeGet());
				BoxSetTexture(1, BfmeHandleCX());
				DX8Wrapper::Set_Shader(Rva012BBE2CShader);
			} else if (mode == 1) {
				DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC, D3DCMP_NOTEQUAL);
				DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
				BoxSetTexture(1, BfmeHandleCX());
				DX8Wrapper::Set_Shader(Rva012BBE30Shader);
			}
		} else {
			BoxSetTexture(1, BfmeHandleCX());
			DX8Wrapper::Set_Shader(Rva012BBE30Shader);
		}
	}

	BFMEZBiasSetter::set(9.0f);
	DX8Wrapper::Apply_Render_State_Changes();

	m_pDev->SetIndices(shadowDecalIndexBufferD3D);
	m_pDev->SetTransform(0x100, &mWorld);
	m_pDev->SetStreamSource(0, shadowDecalVertexBufferD3D, 0, sizeof(SHADOW_DECAL_VERTEX));
	m_pDev->SetFVF(SHADOW_DECAL_FVF);

	if (DX8Wrapper::_EnableTriangleDraw) {
		Debug_Statistics::Record_DX8_Polys_And_Vertices(nShadowDecalPolysInBatch,
			nShadowDecalVertsInBatch, ShaderClass::_PresetOpaqueShader);
		m_pDev->DrawIndexedPrimitive(4, nShadowDecalStartBatchVertex, 0,
			nShadowDecalVertsInBatch, nShadowDecalStartBatchIndex, nShadowDecalPolysInBatch);
	}

	BFMEZBiasSetter::set(0.0f);
	nShadowDecalStartBatchVertex = nShadowDecalVertsInBuf;
	nShadowDecalStartBatchIndex = nShadowDecalIndicesInBuf;
	nShadowDecalPolysInBatch = 0;
	nShadowDecalVertsInBatch = 0;
}
