// ?setShroudTex@W3DShaderManager@@SAHH@Z
// cl: /DNDEBUG /MD /EHsc
// ?setShroudTex@W3DShaderManager@@SAHH@Z
// Retail 0x00717E90, 2072 bytes: W3DShaderManager::setShroudTex(int stage).
// ZH semantic twin W3DShaderManager.cpp, BoxSetTexture handle, TSS snapshots,
// D3D9 transform slots. Retail ILT 0x330F targets this body; callsites
// 0x006F95F2 and 0x0071072A pass stage=1. Other calls: 0x0071F422/0x007383DC.
// No matched caller has yet supplied a decorated callee identity; these
// calling-context facts support the upstream twin rather than prove its name.
// Breakthrough: the old 1871-byte bank did NOT dead-store-eliminate StringClass
// initialization. Its COFF relocation at +0xBC calls the out-of-line ctor.
// __forceinline below restores all eight retail snapshot constructors.
// Current output: 2071 bytes. First five snapshot constructors match. Only
// null-char/buffer load scheduling differs in constructors 6-8; constructor 7
// uses 5-byte mov al,[NullChar] rather than retail 6-byte mov dl,[NullChar],
// causing the one-byte shortfall. Entire transform/return tail from retail
// +0x68E is instruction-identical at compiled offset minus one.
// Tried without improvement: null/pointer locals and declaration order,
// dereference/memcpy/inline Clear helper, out-of-class ctor, forced dtor,
// reference/temporary snapshot name, macro vs inline/template setter,
// qualifiers, /G5 /G7 /Og- /Ob1. Keep original defaults plus forced ctor.

class TextureBaseClass
{
public:
	void Release_Ref();
};

class TextureHandle
{
public:
	TextureBaseClass *m_p;

	~TextureHandle()
	{
		if (m_p)
			m_p->Release_Ref();
	}

	operator TextureBaseClass *&() { return m_p; }
};

class StringClass
{
	char *m_Buffer;
	static char *m_EmptyString;
	static char m_NullChar;

	void Get_String(int length, bool is_temp);
	void Free_String(void);

public:
	__forceinline StringClass(int initial_len, bool hint_temporary)
		: m_Buffer(m_EmptyString)
	{
		Get_String(initial_len, hint_temporary);
		m_Buffer[0] = m_NullChar;
	}
	struct LateTag {};
	__forceinline StringClass(int initial_len, bool hint_temporary, LateTag)
		: m_Buffer(m_EmptyString)
	{
		Get_String(initial_len, hint_temporary);
		m_Buffer[0] = *(volatile char *)&m_NullChar;
	}

	~StringClass(void)
	{
		Free_String();
	}
};

class WW3D
{
	static bool SnapshotActivated;

public:
	static bool Is_Snapshot_Activated() { return SnapshotActivated; }
};

struct D3DXMATRIX;
extern "C" D3DXMATRIX * __stdcall D3DXMatrixMultiply(D3DXMATRIX *pOut, const D3DXMATRIX *pM1, const D3DXMATRIX *pM2);

struct D3DXMATRIX
{
	float m[4][4];

	D3DXMATRIX() {}

	D3DXMATRIX operator*(const D3DXMATRIX &mat) const
	{
		D3DXMATRIX matT;
		D3DXMatrixMultiply(&matT, this, &mat);
		return matT;
	}
};

struct D3DMATRIX
{
	float m[4][4];
};

class DX8Wrapper
{
public:
	static unsigned TextureStageStates[8][32];
	static unsigned texture_stage_state_changes;
	static unsigned matrix_changes;
	static void *D3DDevice;

	static void * _Get_D3D_Device8() { return D3DDevice; }

	static void Get_DX8_Texture_Stage_State_Value_Name(StringClass &name, unsigned long state, unsigned value);
};

extern unsigned number_of_DX8_calls;

void __cdecl BoxSetTexture(unsigned stage, TextureBaseClass *&texture);

extern "C" {
	D3DXMATRIX * __stdcall D3DXMatrixInverse(D3DXMATRIX *pOut, float *pDeterminant, const D3DXMATRIX *pM);
	D3DXMATRIX * __stdcall D3DXMatrixTranslation(D3DXMATRIX *pOut, float x, float y, float z);
	D3DXMATRIX * __stdcall D3DXMatrixScaling(D3DXMATRIX *pOut, float sx, float sy, float sz);
	D3DXMATRIX * __stdcall D3DXMatrixMultiply(D3DXMATRIX *pOut, const D3DXMATRIX *pM1, const D3DXMATRIX *pM2);
}

class WorldHeightMap;

class W3DShroud
{
	char m_pad0[0x10];
	float m_cellWidth;
	float m_cellHeight;
	char m_pad1[8];
	int m_dstTextureWidth;
	int m_dstTextureHeight;
	char m_pad2[4];
	float m_drawOriginX;
	float m_drawOriginY;

public:
	TextureHandle getShroudTexture();
	float getCellWidth() { return m_cellWidth; }
	float getCellHeight() { return m_cellHeight; }
	int getTextureWidth() { return m_dstTextureWidth; }
	int getTextureHeight() { return m_dstTextureHeight; }
	float getDrawOriginX() { return m_drawOriginX; }
	float getDrawOriginY() { return m_drawOriginY; }
};

class BaseHeightMapRenderObjClass
{
	char m_pad0[0x2FF4];
	WorldHeightMap *m_map;
	char m_pad1[0x30B8 - 0x2FF8];
	W3DShroud *m_shroud;

public:
	WorldHeightMap *getMap() { return m_map; }
	W3DShroud *getShroud() { return m_shroud; }
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class W3DShaderManager
{
public:
	static int setShroudTex(int stage);
};

enum { BFME_SET_TSS_SLOT = 67, BFME_GET_TRANSFORM_SLOT = 45, BFME_SET_TRANSFORM_SLOT = 44 };
enum { MAX_TEXTURE_STAGES = 8 };
enum {
	D3DTSS_COLOROP = 1,
	D3DTSS_COLORARG1 = 2,
	D3DTSS_COLORARG2 = 3,
	D3DTSS_ALPHAOP = 4,
	D3DTSS_ALPHAARG1 = 5,
	D3DTSS_ALPHAARG2 = 6,
	D3DTSS_TEXCOORDINDEX = 11,
	D3DTSS_TEXTURETRANSFORMFLAGS = 24
};
enum {
	D3DTA_CURRENT = 1,
	D3DTA_TEXTURE = 2,
	D3DTOP_SELECTARG2 = 3,
	D3DTOP_MODULATE = 4,
	D3DTTFF_COUNT2 = 2,
	D3DTSS_TCI_CAMERASPACEPOSITION = 0x00020000
};
enum { D3DTS_VIEW = 2, D3DTS_TEXTURE0 = 16 };

typedef long (__stdcall *BFMESetTSSFn)(void *, unsigned long, unsigned long, unsigned long);
typedef long (__stdcall *BFMEGetTransformFn)(void *, unsigned long, D3DMATRIX *);
typedef long (__stdcall *BFMESetTransformFn)(void *, unsigned long, const D3DMATRIX *);

#define BFME_SET_TSS(stage_, state_, value_)                                                 \
	if ((unsigned)(stage_) >= MAX_TEXTURE_STAGES) {                                          \
		void *tss_raw_ = DX8Wrapper::_Get_D3D_Device8();                                     \
		(*(BFMESetTSSFn **)tss_raw_)[BFME_SET_TSS_SLOT](tss_raw_,                            \
			(stage_), (state_), (value_));                                                   \
		number_of_DX8_calls++;                                                               \
	} else if (DX8Wrapper::TextureStageStates[stage_][state_] != (unsigned)(value_)) {       \
		if (WW3D::Is_Snapshot_Activated()) {                                                 \
			StringClass value_name(0, true);                                                 \
			DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name(value_name,                   \
				(unsigned long)(state_), (value_));                                          \
		}                                                                                    \
		DX8Wrapper::TextureStageStates[stage_][state_] = (value_);                           \
		void *tss_device_ = DX8Wrapper::_Get_D3D_Device8();                                  \
		(*(BFMESetTSSFn **)tss_device_)[BFME_SET_TSS_SLOT](tss_device_,                      \
			(stage_), (state_), (value_));                                                   \
		number_of_DX8_calls++;                                                               \
		DX8Wrapper::texture_stage_state_changes++;                                           \
	}

#define BFME_SET_TSS_L(stage_, state_, value_)                                                 \
	if ((unsigned)(stage_) >= MAX_TEXTURE_STAGES) {                                          \
		void *tss_raw_ = DX8Wrapper::_Get_D3D_Device8();                                     \
		(*(BFMESetTSSFn **)tss_raw_)[BFME_SET_TSS_SLOT](tss_raw_,                            \
			(stage_), (state_), (value_));                                                   \
		number_of_DX8_calls++;                                                               \
	} else if (DX8Wrapper::TextureStageStates[stage_][state_] != (unsigned)(value_)) {       \
		if (WW3D::Is_Snapshot_Activated()) {                                                 \
			StringClass value_name(0, true, StringClass::LateTag());                                                 \
			DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name(value_name,                   \
				(unsigned long)(state_), (value_));                                          \
		}                                                                                    \
		DX8Wrapper::TextureStageStates[stage_][state_] = (value_);                           \
		void *tss_device_ = DX8Wrapper::_Get_D3D_Device8();                                  \
		(*(BFMESetTSSFn **)tss_device_)[BFME_SET_TSS_SLOT](tss_device_,                      \
			(stage_), (state_), (value_));                                                   \
		number_of_DX8_calls++;                                                               \
		DX8Wrapper::texture_stage_state_changes++;                                           \
	}

int W3DShaderManager::setShroudTex(int stage)
{
	W3DShroud *shroud;
	if ((shroud = TheTerrainRenderObject->getShroud()) != 0)
	{
		float det;
		BoxSetTexture(stage, shroud->getShroudTexture());

		BFME_SET_TSS(stage, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
		BFME_SET_TSS(stage, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
		BFME_SET_TSS(stage, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		BFME_SET_TSS(stage, D3DTSS_COLORARG2, D3DTA_CURRENT);
		BFME_SET_TSS(stage, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		BFME_SET_TSS_L(stage, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
		BFME_SET_TSS_L(stage, D3DTSS_COLOROP, D3DTOP_MODULATE);
		BFME_SET_TSS_L(stage, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);

		D3DXMATRIX inv;
		D3DXMATRIX curView;
		void *device = DX8Wrapper::_Get_D3D_Device8();
		(*(BFMEGetTransformFn **)device)[BFME_GET_TRANSFORM_SLOT](device, D3DTS_VIEW, (D3DMATRIX *)&curView);
		number_of_DX8_calls++;

		D3DXMatrixInverse(&inv, &det, &curView);

		D3DXMATRIX scale, offset;

		float xoffset = 0;
		float yoffset = 0;
		float width = shroud->getCellWidth();
		float height = shroud->getCellHeight();

		if (TheTerrainRenderObject->getMap())
		{
			xoffset = -shroud->getDrawOriginX() + width;
			yoffset = -shroud->getDrawOriginY() + height;
		}

		D3DXMatrixTranslation(&offset, xoffset, yoffset, 0);

		width = 1.0f / (width * shroud->getTextureWidth());
		height = 1.0f / (height * shroud->getTextureHeight());
		D3DXMatrixScaling(&scale, width, height, 1);
		curView = (inv * offset) * scale;

		DX8Wrapper::matrix_changes++;
		device = DX8Wrapper::_Get_D3D_Device8();
		(*(BFMESetTransformFn **)device)[BFME_SET_TRANSFORM_SLOT](
			device, (unsigned long)(D3DTS_TEXTURE0 + stage), (const D3DMATRIX *)&curView);
		number_of_DX8_calls++;
		return 1;
	}
	return 0;
}
