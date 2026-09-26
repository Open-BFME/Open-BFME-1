// cl: /DNDEBUG /MD /EHsc

// BFME's testHardwareSupport is the GeneralsMD smudge probe with the D3D9
// device and render-state shims used by this port.  Keep the mirror classes in
// this TU: the shared headers describe the Zero Hour object, not BFME's
// witnessed member offsets and interface slots.

#include <string.h>

typedef int Int;
typedef int Bool;
typedef float Real;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef unsigned long ULONG;
typedef long HRESULT;
typedef char TCHAR;

#define FALSE 0
#define TRUE 1
#define UNIQUE_COLOR (0x12345678)
#define BLOCK_SIZE (8)
#define Rva00722640BlockSize (*(const Real *)0x010A265C)

// vector4.h gives Vector4 a user-defined default constructor.  That matters:
// with /EHsc the four-element vertex array then uses the retail vector
// constructor iterator at the same point in the frame.
class Vector4
{
public:
	float X;
	float Y;
	float Z;
	float W;

	Vector4(void) {}
	Vector4(float x, float y, float z, float w)
		: X(x), Y(y), Z(z), W(w) {}
	Vector4(const Vector4 &other)
		: X(other.X), Y(other.Y), Z(other.Z), W(other.W) {}
	Vector4 &operator=(const Vector4 &other)
	{
		X = other.X;
		Y = other.Y;
		Z = other.Z;
		W = other.W;
		return *this;
	}
};

struct IDirect3DBaseTexture8
{
	virtual HRESULT __stdcall QueryInterface(void) = 0;
	virtual ULONG __stdcall AddRef(void) = 0;
	virtual ULONG __stdcall Release(void) = 0;
};

struct IDirect3DTexture8 : public IDirect3DBaseTexture8
{
};

// BFME's device retains the D3D9 method positions used by the target body.
// SetTexture is slot 65, DrawPrimitiveUP slot 83, and SetVertexShader slot 89.
struct IDirect3DDevice8
{
	virtual HRESULT __stdcall unused00(void) = 0;
	virtual HRESULT __stdcall unused01(void) = 0;
	virtual HRESULT __stdcall unused02(void) = 0;
	virtual HRESULT __stdcall unused03(void) = 0;
	virtual HRESULT __stdcall unused04(void) = 0;
	virtual HRESULT __stdcall unused05(void) = 0;
	virtual HRESULT __stdcall unused06(void) = 0;
	virtual HRESULT __stdcall unused07(void) = 0;
	virtual HRESULT __stdcall unused08(void) = 0;
	virtual HRESULT __stdcall unused09(void) = 0;
	virtual HRESULT __stdcall unused10(void) = 0;
	virtual HRESULT __stdcall unused11(void) = 0;
	virtual HRESULT __stdcall unused12(void) = 0;
	virtual HRESULT __stdcall unused13(void) = 0;
	virtual HRESULT __stdcall unused14(void) = 0;
	virtual HRESULT __stdcall unused15(void) = 0;
	virtual HRESULT __stdcall unused16(void) = 0;
	virtual HRESULT __stdcall unused17(void) = 0;
	virtual HRESULT __stdcall unused18(void) = 0;
	virtual HRESULT __stdcall unused19(void) = 0;
	virtual HRESULT __stdcall unused20(void) = 0;
	virtual HRESULT __stdcall unused21(void) = 0;
	virtual HRESULT __stdcall unused22(void) = 0;
	virtual HRESULT __stdcall unused23(void) = 0;
	virtual HRESULT __stdcall unused24(void) = 0;
	virtual HRESULT __stdcall unused25(void) = 0;
	virtual HRESULT __stdcall unused26(void) = 0;
	virtual HRESULT __stdcall unused27(void) = 0;
	virtual HRESULT __stdcall unused28(void) = 0;
	virtual HRESULT __stdcall unused29(void) = 0;
	virtual HRESULT __stdcall unused30(void) = 0;
	virtual HRESULT __stdcall unused31(void) = 0;
	virtual HRESULT __stdcall unused32(void) = 0;
	virtual HRESULT __stdcall unused33(void) = 0;
	virtual HRESULT __stdcall unused34(void) = 0;
	virtual HRESULT __stdcall unused35(void) = 0;
	virtual HRESULT __stdcall unused36(void) = 0;
	virtual HRESULT __stdcall unused37(void) = 0;
	virtual HRESULT __stdcall unused38(void) = 0;
	virtual HRESULT __stdcall unused39(void) = 0;
	virtual HRESULT __stdcall unused40(void) = 0;
	virtual HRESULT __stdcall unused41(void) = 0;
	virtual HRESULT __stdcall unused42(void) = 0;
	virtual HRESULT __stdcall unused43(void) = 0;
	virtual HRESULT __stdcall unused44(void) = 0;
	virtual HRESULT __stdcall unused45(void) = 0;
	virtual HRESULT __stdcall unused46(void) = 0;
	virtual HRESULT __stdcall unused47(void) = 0;
	virtual HRESULT __stdcall unused48(void) = 0;
	virtual HRESULT __stdcall unused49(void) = 0;
	virtual HRESULT __stdcall unused50(void) = 0;
	virtual HRESULT __stdcall unused51(void) = 0;
	virtual HRESULT __stdcall unused52(void) = 0;
	virtual HRESULT __stdcall unused53(void) = 0;
	virtual HRESULT __stdcall unused54(void) = 0;
	virtual HRESULT __stdcall unused55(void) = 0;
	virtual HRESULT __stdcall unused56(void) = 0;
	virtual HRESULT __stdcall unused57(void) = 0;
	virtual HRESULT __stdcall unused58(void) = 0;
	virtual HRESULT __stdcall unused59(void) = 0;
	virtual HRESULT __stdcall unused60(void) = 0;
	virtual HRESULT __stdcall unused61(void) = 0;
	virtual HRESULT __stdcall unused62(void) = 0;
	virtual HRESULT __stdcall unused63(void) = 0;
	virtual HRESULT __stdcall unused64(void) = 0;
	virtual HRESULT __stdcall SetTexture(DWORD stage, IDirect3DBaseTexture8 *texture) = 0;
	virtual HRESULT __stdcall unused66(void) = 0;
	virtual HRESULT __stdcall unused67(void) = 0;
	virtual HRESULT __stdcall unused68(void) = 0;
	virtual HRESULT __stdcall unused69(void) = 0;
	virtual HRESULT __stdcall unused70(void) = 0;
	virtual HRESULT __stdcall unused71(void) = 0;
	virtual HRESULT __stdcall unused72(void) = 0;
	virtual HRESULT __stdcall unused73(void) = 0;
	virtual HRESULT __stdcall unused74(void) = 0;
	virtual HRESULT __stdcall unused75(void) = 0;
	virtual HRESULT __stdcall unused76(void) = 0;
	virtual HRESULT __stdcall unused77(void) = 0;
	virtual HRESULT __stdcall unused78(void) = 0;
	virtual HRESULT __stdcall unused79(void) = 0;
	virtual HRESULT __stdcall unused80(void) = 0;
	virtual HRESULT __stdcall unused81(void) = 0;
	virtual HRESULT __stdcall unused82(void) = 0;
	virtual HRESULT __stdcall DrawPrimitiveUP(UINT primitive_type, UINT primitive_count,
		const void *vertex_data, UINT vertex_stride) = 0;
	virtual HRESULT __stdcall unused84(void) = 0;
	virtual HRESULT __stdcall unused85(void) = 0;
	virtual HRESULT __stdcall unused86(void) = 0;
	virtual HRESULT __stdcall unused87(void) = 0;
	virtual HRESULT __stdcall unused88(void) = 0;
	virtual HRESULT __stdcall SetVertexShader(DWORD shader) = 0;
};

class W3DShaderManager
{
public:
	static IDirect3DTexture8 *getRenderTexture(void);
};

class RefCountClass
{
public:
	virtual void Delete_This(void);
	virtual ~RefCountClass(void);
	__forceinline void Add_Ref(void)
	{
		++m_numRefs;
	}
	__forceinline void Release_Ref(void)
	{
		--m_numRefs;
		if (m_numRefs == 0)
			Delete_This();
	}

private:
	int m_numRefs;
};

class W3DMPO
{
};

class VertexMaterialClass : public W3DMPO, public RefCountClass
{
public:
	enum PresetType { PRELIT_DIFFUSE = 0 };
	static VertexMaterialClass *Get_Preset(PresetType type);
};

class StringClass
{
	void Get_String(int length, bool is_temp);
	void Free_String(void);

public:
	StringClass(int initial_len = 0, bool hint_temporary = false)
		: m_Buffer(m_EmptyString)
	{
		Get_String(initial_len, hint_temporary);
		m_Buffer[0] = m_NullChar;
	}
	~StringClass(void)
	{
		Free_String();
	}
	char *m_Buffer;
	static char m_NullChar;
	static char *m_EmptyString;
};

class ShaderClass
{
public:
	unsigned int ShaderBits;
	static bool ShaderDirty;
	static ShaderClass _PresetOpaqueShader;

	ShaderClass(const ShaderClass &other)
		: ShaderBits(other.ShaderBits) {}
	ShaderClass(unsigned int bits)
		: ShaderBits(bits) {}

	void Set_Depth_Compare(int value)
	{
		ShaderBits &= ~7U;
		ShaderBits |= (unsigned int)value;
	}

	void Set_Depth_Mask(int value)
	{
		ShaderBits &= ~8U;
		ShaderBits |= ((unsigned int)value << 3);
	}
};

struct RenderStateStruct
{
	ShaderClass shader;
	VertexMaterialClass *material;
};

class BFMETextureRelease
{
public:
	void Release_Ref(void);
};

class TextureBaseClass
{
};

class StageTextureRef
{
	BFMETextureRelease *Texture;

public:
	StageTextureRef(void) : Texture(NULL) {}
	~StageTextureRef(void)
	{
		if (Texture)
			Texture->Release_Ref();
	}
	operator TextureBaseClass *&(void)
	{
		return *(TextureBaseClass **)&Texture;
	}
};

extern void BoxSetTexture(unsigned index, TextureBaseClass *&texture);
extern unsigned number_of_DX8_calls;

class DX8Wrapper
{
	static RenderStateStruct render_state;
	static unsigned render_state_changed;
	static IDirect3DBaseTexture8 *Textures[8];
	static IDirect3DDevice8 *D3DDevice;
	static unsigned texture_changes;

public:
	static void Apply_Render_State_Changes(void);
	static IDirect3DDevice8 *_Get_D3D_Device8(void)
	{
		return D3DDevice;
	}

	static __forceinline void Set_Material(const VertexMaterialClass *material)
	{
		if (material)
			const_cast<VertexMaterialClass *>(material)->Add_Ref();
		if (render_state.material)
			render_state.material->Release_Ref();
		render_state.material = const_cast<VertexMaterialClass *>(material);
		render_state_changed |= 0x4000;
	}

	static __forceinline void Set_Shader(const ShaderClass &shader)
	{
		if (!ShaderClass::ShaderDirty &&
			shader.ShaderBits == render_state.shader.ShaderBits)
			return;

		render_state.shader = shader;
		render_state_changed |= 0x8000;
		StringClass str;
	}

	static __forceinline void Set_DX8_Texture(unsigned int stage,
		IDirect3DBaseTexture8 *texture)
	{
		if (stage >= 8)
		{
			IDirect3DDevice8 *device = _Get_D3D_Device8();
			device->SetTexture(stage, texture);
			++number_of_DX8_calls;
			return;
		}

		if (Textures[stage] == texture)
			return;
		if (Textures[stage])
			Textures[stage]->Release();
		Textures[stage] = texture;
		if (texture)
			texture->AddRef();
		IDirect3DDevice8 *device = _Get_D3D_Device8();
		device->SetTexture(stage, texture);
		++number_of_DX8_calls;
		++texture_changes;
	}
};

class Rva00722640SmudgeManager
{
public:
	virtual ~Rva00722640SmudgeManager(void);
	virtual void init(void);
	virtual void reset(void);
	virtual void ReleaseResources(void);
	virtual void ReAcquireResources(void);

	enum HardwareSmudgeSupport
	{
		SMUDGE_SUPPORT_UNKNOWN = 0,
		SMUDGE_SUPPORT_NO = 1,
		SMUDGE_SUPPORT_YES = 2
	};

	HardwareSmudgeSupport m_hardwareSupportStatus;
	char m_pad[0x1C];
};

class Rva00722640W3DSmudgeManager : public Rva00722640SmudgeManager
{
public:
	bool testHardwareSupport(void);
};

class Display
{
public:
	virtual void unused00(void) = 0;
	virtual void unused01(void) = 0;
	virtual void unused02(void) = 0;
	virtual void unused03(void) = 0;
	virtual void unused04(void) = 0;
	virtual void unused05(void) = 0;
	virtual void unused06(void) = 0;
	virtual void unused07(void) = 0;
	virtual void unused08(void) = 0;
	virtual void unused09(void) = 0;
	virtual void unused10(void) = 0;
	virtual unsigned int getWidth(void) = 0;
	virtual unsigned int getHeight(void) = 0;
};

extern Display *TheDisplay;

extern Int copyRect(unsigned char *buffer, Int buffer_size, int origin_x,
	int origin_y, int width, int height);

// ?testHardwareSupport@W3DSmudgeManager@@QAE_NXZ
bool Rva00722640W3DSmudgeManager::testHardwareSupport(void)
{
	if (m_hardwareSupportStatus == SMUDGE_SUPPORT_UNKNOWN)
	{
		IDirect3DTexture8 *backTexture = W3DShaderManager::getRenderTexture();
		if (!backTexture)
		{
			m_hardwareSupportStatus = SMUDGE_SUPPORT_NO;
			return false;
		}

		if (!*(unsigned char *)0x012F9D00)
			return false;

		VertexMaterialClass *vmat =
			VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		DX8Wrapper::Set_Material(vmat);
		if (vmat)
			vmat->Release_Ref();

		ShaderClass shader = ShaderClass::_PresetOpaqueShader;
		shader.Set_Depth_Compare(7);
		shader.Set_Depth_Mask(0);
		DX8Wrapper::Set_Shader(shader);
		{
			StageTextureRef texture;
			BoxSetTexture(0, texture);
		}
		DX8Wrapper::Apply_Render_State_Changes();

		struct _TRANS_LIT_TEX_VERTEX
		{
			Vector4 p;
			DWORD color;
			float u;
			float v;
		} v[4];

		v[0].p = Vector4(BLOCK_SIZE - 0.5f, BLOCK_SIZE - 0.5f, 0.0f, 1.0f);
		v[0].u = Rva00722640BlockSize / (Real)TheDisplay->getWidth();
		v[0].v = Rva00722640BlockSize / (Real)TheDisplay->getHeight();
		v[1].p = Vector4(BLOCK_SIZE - 0.5f, 0 - 0.5f, 0.0f, 1.0f);
		v[1].u = Rva00722640BlockSize / (Real)TheDisplay->getWidth();
		v[1].v = 0;
		v[2].p = Vector4(0 - 0.5f, BLOCK_SIZE - 0.5f, 0.0f, 1.0f);
		v[2].u = 0;
		v[2].v = Rva00722640BlockSize / (Real)TheDisplay->getHeight();
		v[3].p = Vector4(0 - 0.5f, 0 - 0.5f, 0.0f, 1.0f);
		v[3].u = 0;
		v[3].v = 0;

		v[0].color = UNIQUE_COLOR;
		v[1].color = UNIQUE_COLOR;
		v[2].color = UNIQUE_COLOR;
		v[3].color = UNIQUE_COLOR;

		IDirect3DDevice8 *pDev = DX8Wrapper::_Get_D3D_Device8();
		pDev->SetVertexShader(0x144);
		pDev->DrawPrimitiveUP(5, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));

		DWORD refData[BLOCK_SIZE * BLOCK_SIZE];
		memset(refData, 0, sizeof(refData));
		Int bufSize = copyRect((unsigned char *)refData, sizeof(refData),
			0, 0, BLOCK_SIZE, BLOCK_SIZE);
		if (!bufSize)
		{
			m_hardwareSupportStatus = SMUDGE_SUPPORT_NO;
			return false;
		}

		DX8Wrapper::Set_DX8_Texture(0, backTexture);

		DWORD testData[BLOCK_SIZE * BLOCK_SIZE];
		memset(testData, 0xff, sizeof(testData));

		v[0].color = 0xffffffff;
		v[1].color = 0xffffffff;
		v[2].color = 0xffffffff;
		v[3].color = 0xffffffff;

		pDev->DrawPrimitiveUP(5, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));
		bufSize = copyRect((unsigned char *)testData, sizeof(testData),
			0, 0, BLOCK_SIZE, BLOCK_SIZE);
		if (!bufSize)
		{
			m_hardwareSupportStatus = SMUDGE_SUPPORT_NO;
			return false;
		}

		if (memcmp(testData, refData, (unsigned)bufSize) == 0)
		{
			m_hardwareSupportStatus = SMUDGE_SUPPORT_YES;
			return true;
		}
		m_hardwareSupportStatus = SMUDGE_SUPPORT_NO;
	}

	return m_hardwareSupportStatus == SMUDGE_SUPPORT_YES;
}
