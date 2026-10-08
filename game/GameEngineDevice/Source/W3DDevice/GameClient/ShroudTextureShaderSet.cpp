// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Retail RVA 0x007C3FD0. Uses the native DX8 declarations and counted texture returns.
// Evidence: targets/game/reverse/identity_evidence/007c3fd0-shroud-set.md

#define Matrix4x4 Matrix4
#define private public
#define protected public
#include "dx8wrapper.h"
#undef private
#undef protected
#include "d3dx8math.h"
class BFMETextureRelease { public: void Release_Ref(); };
extern TCHAR g_bfmeCh1035;

class BfmeHandleCX
{
	BFMETextureRelease *m_bfmeThing;

public:
	~BfmeHandleCX()
	{
		if (m_bfmeThing)
			m_bfmeThing->Release_Ref();
	}
	operator TextureBaseClass *&()
	{
		return *(TextureBaseClass **)&m_bfmeThing;
	}
};

BfmeHandleCX __cdecl bfmeGet(int index);

class BFMEValueName
{
	TCHAR *m_Buffer;

public:
	BFMEValueName(int initial_len, bool hint_temporary)
		: m_Buffer(StringClass::m_EmptyString)
	{
		((StringClass *)this)->Get_String(initial_len, hint_temporary);
		TCHAR null_char = g_bfmeCh1035;
		TCHAR *buffer = m_Buffer;
		*buffer = null_char;
	}

	~BFMEValueName()
	{
		((StringClass *)this)->Free_String();
	}
};

class BFMEValueNameLate
{
	TCHAR *m_Buffer;

public:
	BFMEValueNameLate(int initial_len, bool hint_temporary)
		: m_Buffer(StringClass::m_EmptyString)
	{
		((StringClass *)this)->Get_String(initial_len, hint_temporary);
		m_Buffer[0] = *(volatile TCHAR *)&g_bfmeCh1035;
	}

	~BFMEValueNameLate()
	{
		((StringClass *)this)->Free_String();
	}
};

typedef HRESULT (__stdcall *BFMESetTextureFn)(IDirect3DDevice8 *, DWORD, IDirect3DBaseTexture8 *);
typedef HRESULT (__stdcall *BFMESetTSSFn)(IDirect3DDevice8 *, DWORD, DWORD, DWORD);
typedef HRESULT (__stdcall *BFMESetRSFn)(IDirect3DDevice8 *, DWORD, DWORD);
enum { BFME_SET_TSS_SLOT = 67, BFME_SET_RS_SLOT = 57 };
void BoxSetTexture(unsigned stage, TextureBaseClass *&texture);

#define BFME_SET_TSS(stage_, state_, value_)                                                 \
	if ((unsigned)(stage_) >= MAX_TEXTURE_STAGES) {                                          \
		IDirect3DDevice8 *tss_raw_ = DX8Wrapper::_Get_D3D_Device8();                         \
		(*(BFMESetTSSFn **)tss_raw_)[BFME_SET_TSS_SLOT](tss_raw_,                            \
			(stage_), (state_), (value_));                                                   \
		number_of_DX8_calls++;                                                               \
	} else if (DX8Wrapper::TextureStageStates[stage_][state_] != (unsigned)(value_)) {       \
		if (WW3D::Is_Snapshot_Activated()) {                                                 \
			BFMEValueName value_name(0, true);                                               \
			DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name(*(StringClass *)&value_name, \
				(D3DTEXTURESTAGESTATETYPE)(state_), (value_));                               \
			SNAPSHOT_SAY(("DX8 - SetTextureStageState(stage: %d, state: %s, value: %s)\n", \
				(stage_), DX8Wrapper::Get_DX8_Texture_Stage_State_Name(                    \
					(D3DTEXTURESTAGESTATETYPE)(state_)), value_name));                         \
		}                                                                                    \
		DX8Wrapper::TextureStageStates[stage_][state_] = (value_);                           \
		IDirect3DDevice8 *tss_device_ = DX8Wrapper::_Get_D3D_Device8();                      \
		(*(BFMESetTSSFn **)tss_device_)[BFME_SET_TSS_SLOT](tss_device_,                      \
			(stage_), (state_), (value_));                                                   \
		number_of_DX8_calls++;                                                               \
		DX8Wrapper::texture_stage_state_changes++;                                           \
	}

#define BFME_SET_TSS_LATE(stage_, state_, value_)                                            \
	if ((unsigned)(stage_) >= MAX_TEXTURE_STAGES) {                                           \
		IDirect3DDevice8 *tss_raw_ = DX8Wrapper::_Get_D3D_Device8();                          \
		(*(BFMESetTSSFn **)tss_raw_)[BFME_SET_TSS_SLOT](tss_raw_,                             \
			(stage_), (state_), (value_));                                                    \
		number_of_DX8_calls++;                                                               \
	} else if (DX8Wrapper::TextureStageStates[stage_][state_] != (unsigned)(value_)) {      \
		if (WW3D::Is_Snapshot_Activated()) {                                                 \
			BFMEValueNameLate value_name(0, true);                                            \
			DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name(*(StringClass *)&value_name,    \
				(D3DTEXTURESTAGESTATETYPE)(state_), (value_));                                  \
			SNAPSHOT_SAY(("DX8 - SetTextureStageState(stage: %d, state: %s, value: %s)\\n",  \
				(stage_), DX8Wrapper::Get_DX8_Texture_Stage_State_Name(                          \
					(D3DTEXTURESTAGESTATETYPE)(state_)), value_name));                             \
		}                                                                                    \
		DX8Wrapper::TextureStageStates[stage_][state_] = (value_);                            \
		IDirect3DDevice8 *tss_device_ = DX8Wrapper::_Get_D3D_Device8();                      \
		(*(BFMESetTSSFn **)tss_device_)[BFME_SET_TSS_SLOT](tss_device_,                      \
			(stage_), (state_), (value_));                                                    \
		number_of_DX8_calls++;                                                               \
		DX8Wrapper::texture_stage_state_changes++;                                           \
	}

#define BFME_SET_RS(state_, value_)                                                          \
	if (DX8Wrapper::RenderStates[state_] != (unsigned)(value_)) {                            \
		if (WW3D::Is_Snapshot_Activated()) {                                                 \
			StringClass value_name(0, true);                                                 \
			DX8Wrapper::Get_DX8_Render_State_Value_Name(value_name,                          \
				(D3DRENDERSTATETYPE)(state_), (value_));                                     \
		}                                                                                    \
		DX8Wrapper::RenderStates[state_] = (value_);                                         \
		IDirect3DDevice8 *rs_device_ = DX8Wrapper::_Get_D3D_Device8();                       \
		(*(BFMESetRSFn **)rs_device_)[BFME_SET_RS_SLOT](rs_device_, (state_), (value_));     \
		number_of_DX8_calls++;                                                               \
		DX8Wrapper::render_state_changes++;                                                  \
	}

class TextureHandle
{
    BFMETextureRelease *m_texture;
public:
    ~TextureHandle() { if (m_texture) m_texture->Release_Ref(); }
    operator TextureBaseClass *&() { return *(TextureBaseClass **)&m_texture; }
    operator TextureBaseClass &() { return *(TextureBaseClass *)&m_texture; }
};

// ?bfmeSetTexture@@YAXIABVTextureHandle@@@Z absent-from-retail
__forceinline void bfmeSetTexture(unsigned stage, const TextureHandle &texture)
{
    IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
    (*(BFMESetTextureFn **)device)[65](device, stage, ((const TextureBaseClass &)texture).Peek_D3D_Base_Texture());
}

class W3DShroud
{
    char m_head[0x10];
    float m_cellWidth;
    float m_cellHeight;
    char m_textures[8];
    int m_dstTextureWidth;
    int m_dstTextureHeight;
    char m_gap[4];
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

class WorldHeightMap;
class BaseHeightMapRenderObjClass
{
    char m_head[0x2ff4];
    WorldHeightMap *m_map;
    char m_gap[0x30b8-0x2ff8];
    W3DShroud *m_shroud;
public:
    W3DShroud *getShroud() { return m_shroud; }
    WorldHeightMap *getMap() { return m_map; }
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class ShroudTextureShader
{
    virtual int set(int stage);
    virtual void reset();
    virtual int init();
    virtual int shutdown();
    int m_numPasses;
    int m_stageOfSet;
};

// ?set@ShroudTextureShader@@EAEHH@Z
int ShroudTextureShader::set(int stage)
{
	VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(vmat);
	REF_PTR_RELEASE(vmat);

	BoxSetTexture(stage, (TextureBaseClass *&)bfmeGet(0));

	if (stage == 0)
	{
		const ShaderClass &shader = ShaderClass::_PresetMultiplicativeSpriteShader;
		if (ShaderClass::ShaderDirty || (unsigned &)shader != (unsigned &)DX8Wrapper::render_state.shader)
		{
			DX8Wrapper::render_state.shader=shader;
			DX8Wrapper::render_state_changed|=0x8000;
			BFMEValueName value_name(0,false);
		}
	}
	DX8Wrapper::Apply_Render_State_Changes();

	BFME_SET_TSS(stage, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
	BFME_SET_TSS_LATE(stage, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
	BFME_SET_RS(D3DRS_ZFUNC, D3DCMP_EQUAL);

	W3DShroud *shroud;
	if ((shroud=TheTerrainRenderObject->getShroud()) != 0)
	{
		if ((TextureBaseClass *&)shroud->getShroudTexture() != 0)
		{
			bfmeSetTexture(stage, shroud->getShroudTexture());
		}
		{
			D3DXMATRIX inv;
			float det;

			Matrix4x4 curView;
			DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);

			D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);

			D3DXMATRIX scale,offset;

			float xoffset = 0;
			float yoffset = 0;
			float width=shroud->getCellWidth();
			float height=shroud->getCellHeight();

			if (TheTerrainRenderObject->getMap())
			{
				xoffset = -(float)shroud->getDrawOriginX() + width;
				yoffset = -(float)shroud->getDrawOriginY() + height;
			}

			D3DXMatrixTranslation(&offset, xoffset, yoffset,0);

			width = 1.0f/(width*shroud->getTextureWidth());
			height = 1.0f/(height*shroud->getTextureHeight());
			D3DXMatrixScaling(&scale, width, height, 1);
			D3DXMATRIX first;
			D3DXMatrixMultiply(&first, &inv, &offset);
			D3DXMATRIX second=first;
			D3DXMATRIX third;
			D3DXMatrixMultiply(&third, &second, &scale);
			*((D3DXMATRIX *)&curView)=third;
			DX8Wrapper::matrix_changes++;
			DX8CALL(SetTransform((D3DTRANSFORMSTATETYPE)(D3DTS_TEXTURE0+stage), (D3DMATRIX *)&curView));
		}
	}
	m_stageOfSet=stage;
	return 1;
}
