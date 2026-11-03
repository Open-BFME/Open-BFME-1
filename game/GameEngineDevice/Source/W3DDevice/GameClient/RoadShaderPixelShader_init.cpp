// readable body of ?set007CCF50@RoadShaderPixelShader@@EAEHH@Z: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main 
// Retail RVA 0x007CCF50. Road shader with counted texture returns.
// Evidence: targets/game/reverse/identity_evidence/007ccf50-road-shader.md

// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#define Matrix4x4 Matrix4
#define private public
#define protected public
#include "../../../../Libraries/Source/WWVegas/WWLib/wwstring.h"
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
	__forceinline BFMEValueName(int initial_len, bool hint_temporary)
		: m_Buffer(StringClass::m_EmptyString)
	{
		((StringClass *)this)->Get_String(initial_len, hint_temporary);
		m_Buffer[0] = *(volatile TCHAR *)&g_bfmeCh1035;
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
    TextureHandle() : m_texture(0) {}
    TextureHandle(const TextureHandle &other) : m_texture(other.m_texture) {
        if (m_texture) ++*(unsigned short *)((char *)m_texture + 4);
    }
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
    char m_texture18[4];
    TextureHandle m_dstTexture;
    int m_dstTextureWidth;
    int m_dstTextureHeight;
    char m_gap[4];
    float m_drawOriginX;
    float m_drawOriginY;
public:
    __declspec(noinline) TextureHandle getShroudTexture();
    float getCellWidth() { return m_cellWidth; }
    float getCellHeight() { return m_cellHeight; }
    int getTextureWidth() { return m_dstTextureWidth; }
    int getTextureHeight() { return m_dstTextureHeight; }
    float getDrawOriginX() { return m_drawOriginX; }
    float getDrawOriginY() { return m_drawOriginY; }
};

TextureHandle W3DShroud::getShroudTexture() { return m_dstTexture; }

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


#include "Lib/BaseType.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"
#include "Common/GlobalData.h"
	enum { BFME_SAMP_ADDRESSU = 1, BFME_SAMP_ADDRESSV = 2, BFME_SAMP_MAGFILTER = 5,
	       BFME_SAMP_MINFILTER = 6, BFME_SAMP_MIPFILTER = 7, BFME_SAMP_MAXANISOTROPY = 10 };
	enum { BFME_SET_SAMP_SLOT = 69 };
#define BFME_SET_SAMP(stage_, type_, value_)                                                 \
	{                                                                                        \
		IDirect3DDevice8 *samp_device_ = DX8Wrapper::_Get_D3D_Device8();                      \
		(*(BFMESetTSSFn **)samp_device_)[BFME_SET_SAMP_SLOT](samp_device_,                    \
			(stage_), (type_), (value_));                                                     \
		number_of_DX8_calls++;                                                                \
		DX8Wrapper::texture_stage_state_changes++;                                            \
	}

// BFME hoisted the per-stage min/mag/mip filter selection (TheGlobalData's
// bilinear/trilinear flags, plus an anisotropy cap check) out of every shader
// pass into one helper each pass calls once per texture stage.
void __cdecl setTerrainTextureFilters(unsigned stage);
void BoxSetTexture(unsigned stage, TextureBaseClass *&texture);

namespace {
struct FlatTerrainDeviceRva01340534 {
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual HRESULT __stdcall SetTransform(DWORD, const void*) = 0;
	virtual HRESULT __stdcall GetTransform(DWORD, void*) = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual HRESULT __stdcall SetRenderState(DWORD, DWORD) = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual HRESULT __stdcall SetTexture(DWORD, IDirect3DBaseTexture8*) = 0;
	virtual void slot66() = 0;
	virtual HRESULT __stdcall SetTextureStageState(DWORD, DWORD, DWORD) = 0;
	virtual void slot68() = 0;
	virtual HRESULT __stdcall SetSamplerState(DWORD, DWORD, DWORD) = 0;
};
// Four-byte StringClass storage. Preserve the witnessed null-byte read order;
// the original qualifier is unknown, so this view uses a volatile byte load.
class FlatTerrainValueNameRva007C5690
{
	TCHAR *m_Buffer;

public:
	__forceinline FlatTerrainValueNameRva007C5690(int initial_len, bool hint_temporary)
		: m_Buffer(StringClass::m_EmptyString)
	{
		((StringClass *)this)->Get_String(initial_len, hint_temporary);
		m_Buffer[0] = *(volatile TCHAR *)&g_bfmeCh1035;
	}

	~FlatTerrainValueNameRva007C5690()
	{
		((StringClass *)this)->Free_String();
	}
};
__forceinline void bfmeFlatSetTransform(D3DTRANSFORMSTATETYPE type, const Matrix4x4 &m)
{
    DX8Wrapper::matrix_changes++;
    DX8Wrapper::_Get_D3D_Device8()->SetTransform(type, (const D3DMATRIX *)&m);
    number_of_DX8_calls++;
}
__forceinline D3DXMATRIX bfmeFlatMultiply(const D3DXMATRIX &a, const D3DXMATRIX &b)
{
    D3DXMATRIX result;
    D3DXMatrixMultiply(&result, &a, &b);
    return result;
}
#define BFME_FLAT_TEXTURE(stage, texture) ((FlatTerrainDeviceRva01340534 *)DX8Wrapper::_Get_D3D_Device8())->SetTexture(stage, texture)
// These BFME offsets differ from the ZH texture/origin layout. Accessor return
// boundaries also preserve retail scalar temporaries in the matrix calculation.
__forceinline float flatShroudCellWidth(W3DShroud *shroud) { return *(float *)((char *)shroud + 0x10); }
__forceinline float flatShroudCellHeight(W3DShroud *shroud) { return *(float *)((char *)shroud + 0x14); }
__forceinline int flatShroudTextureWidth(W3DShroud *shroud) { return *(int *)((char *)shroud + 0x20); }
__forceinline int flatShroudTextureHeight(W3DShroud *shroud) { return *(int *)((char *)shroud + 0x24); }
__forceinline float flatShroudDrawOriginX(W3DShroud *shroud) { return *(float *)((char *)shroud + 0x2c); }
__forceinline float flatShroudDrawOriginY(W3DShroud *shroud) { return *(float *)((char *)shroud + 0x30); }

} // namespace


class TerrainShader2Stage {
public:
    void updateNoise1(D3DXMATRIX *, D3DXMATRIX *, bool);
};
extern TerrainShader2Stage terrainShader2Stage;
struct Rva007DCF00Matrix { float m[16]; };
class Rva007DCF00TextureMatrix {
public:
    void build(Rva007DCF00Matrix *, Rva007DCF00Matrix *, bool);
};
__forceinline void bfmeSetPixelShader(unsigned long handle)
{
    IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
    typedef HRESULT (__stdcall *SetFn)(IDirect3DDevice8 *, unsigned long);
    (*(SetFn **)device)[107](device, handle);
}
// ?bfmeSetPixelShaderConstant@@YAXHPBXH@Z absent-from-retail
static __forceinline void bfmeSetPixelShaderConstant(int reg, const void *data, int count)
{
    int memsize = sizeof(Vector4) * count;
    // may be incorrect if shaders are created and destroyed dynamically
    if (memcmp(data, &DX8Wrapper::Pixel_Shader_Constants[reg], memsize) == 0)
        return;
    memcpy(&DX8Wrapper::Pixel_Shader_Constants[reg], data, memsize);
    IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
    typedef HRESULT (__stdcall *SetFn)(IDirect3DDevice8 *, unsigned, const void *, unsigned);
    (*(SetFn **)device)[109](device, reg, data, count);
    number_of_DX8_calls++;
}
class RoadShaderPixelShader {
    virtual int set007CCF50(int pass);  // vtable slot 0; spelling unproven (ILT order contradicts set)
    virtual void reset();
    virtual int init();
    virtual int shutdown();
    int m_numPasses;
    unsigned long m_roadNoise1;
    unsigned long m_roadNoise2;
    unsigned long m_roadNoise3;
};

// ?set007CCF50@RoadShaderPixelShader@@EAEHH@Z
int RoadShaderPixelShader::set007CCF50(int pass)
{
	//setup base pass
	// setup terrain [3/31/2003]
	BoxSetTexture(0, (TextureBaseClass *&)bfmeGet(0));
	BoxSetTexture(1, (TextureBaseClass *&)bfmeGet(1));
	//force WW3D2 system to set it's states so it won't later overwrite our custom settings.
	DX8Wrapper::Apply_Render_State_Changes();
	if ((TextureBaseClass *&)bfmeGet(0) != 0) {
		BFME_FLAT_TEXTURE(0, ((TextureBaseClass &)bfmeGet(0)).Peek_D3D_Base_Texture());
	}
	BFME_SET_SAMP(0, BFME_SAMP_ADDRESSU, D3DTADDRESS_WRAP);
	BFME_SET_SAMP(0, BFME_SAMP_ADDRESSV, D3DTADDRESS_WRAP);
	//tell pixel shader which UV set to use for each stage
	BFME_SET_TSS(0, D3DTSS_TEXCOORDINDEX, 0);
	setTerrainTextureFilters(0);
	if ((TextureBaseClass *&)bfmeGet(1) != 0) {
		BFME_FLAT_TEXTURE(1, ((TextureBaseClass &)bfmeGet(1)).Peek_D3D_Base_Texture());
	}
	BFME_SET_TSS(1, D3DTSS_TEXCOORDINDEX, 0);
	W3DShroud *shroud = TheTerrainRenderObject->getShroud();
	if (shroud) {
		BFME_SET_TSS(1, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
		// Two output coordinates are used.
		BFME_SET_TSS(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
		//We need to scale so shroud texel stretches over one full terrain cell.  Each texel
		//is 1/128 the size of full texture. (assuming 128x128 vid-mem texture).
		{
			D3DXMATRIX inv;
			float det;
			Matrix4x4 curView;
			DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);
			D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);
			D3DXMATRIX scale,offset;
			//We need to make all world coordinates be relative to the heightmap data origin since that
			//is where the shroud begins.
			float xoffset = 0;
			float yoffset = 0;
			float width=shroud->getCellWidth();
			float height=shroud->getCellHeight();
			if (TheTerrainRenderObject->getMap())
			{	//subtract origin position from all coordinates.  Origin is shifted by 1 cell width/height to allow for unused border texels.
				xoffset = -(float)shroud->getDrawOriginX() + width;
				yoffset = -(float)shroud->getDrawOriginY() + height;
			}
			D3DXMatrixTranslation(&offset, xoffset, yoffset,0);
			width = 1.0f/(width*shroud->getTextureWidth());
			height = 1.0f/(height*shroud->getTextureHeight());
			D3DXMatrixScaling(&scale, width, height, 1);
			*((D3DXMATRIX *)&curView) = bfmeFlatMultiply(bfmeFlatMultiply(inv, offset), scale);
			bfmeFlatSetTransform(D3DTS_TEXTURE1, curView);
		}
		if ((TextureBaseClass *&)shroud->getShroudTexture() != 0) {
			bfmeSetTexture(1, shroud->getShroudTexture());
		}
		BoxSetTexture(1, shroud->getShroudTexture());
	}
	BFME_SET_SAMP(1, BFME_SAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	BFME_SET_SAMP(1, BFME_SAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	BFME_SET_SAMP(1, BFME_SAMP_MINFILTER, D3DTEXF_LINEAR);
	BFME_SET_SAMP(1, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
	int curStage = 2;
	bool doNoise1 = (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_ROAD_BASE_NOISE1 ||
		W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_ROAD_BASE_NOISE12);
	if (doNoise1) {	 // Cloud pass.
		Matrix4x4 curView;
		DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);
		D3DXMATRIX inv;
		float det;
		D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);
		BFME_SET_TSS(2, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
		// Two output coordinates are used.
		BFME_SET_TSS(2, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
		BFME_SET_SAMP(2, BFME_SAMP_ADDRESSU, D3DTADDRESS_WRAP);
		BFME_SET_SAMP(2, BFME_SAMP_ADDRESSV, D3DTADDRESS_WRAP);
		BFME_FLAT_TEXTURE(2, ((TextureBaseClass &)bfmeGet(2)).Peek_D3D_Base_Texture());
		terrainShader2Stage.updateNoise1(((D3DXMATRIX*)&curView),&inv, true);	//update curView with texture matrix
		bfmeFlatSetTransform(D3DTS_TEXTURE2, curView);
		BFME_SET_SAMP(2, BFME_SAMP_MINFILTER, D3DTEXF_LINEAR);
		BFME_SET_SAMP(2, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
		curStage++;
	}
	bool doNoise2 = (W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_ROAD_BASE_NOISE2 ||
		W3DShaderManager::getCurrentShader() == W3DShaderManager::ST_ROAD_BASE_NOISE12);
	if (doNoise2) {
		Matrix4x4 curView;
		DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);
		D3DXMATRIX inv;
		float det;
		D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);
		BFME_SET_TSS(curStage, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
		// Two output coordinates are used.
		BFME_SET_TSS(curStage, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
		BFME_SET_SAMP(curStage, BFME_SAMP_ADDRESSU, D3DTADDRESS_WRAP);
		BFME_SET_SAMP(curStage, BFME_SAMP_ADDRESSV, D3DTADDRESS_WRAP);
		BFME_FLAT_TEXTURE(curStage, ((TextureBaseClass &)bfmeGet(3)).Peek_D3D_Base_Texture());
		((Rva007DCF00TextureMatrix *)&terrainShader2Stage)->build((Rva007DCF00Matrix *)&curView, (Rva007DCF00Matrix *)&inv, true);	//update curView with texture matrix
		bfmeFlatSetTransform((D3DTRANSFORMSTATETYPE)(D3DTS_TEXTURE0+curStage), curView);
		BFME_SET_SAMP(curStage, BFME_SAMP_MINFILTER, D3DTEXF_LINEAR);
		BFME_SET_SAMP(curStage, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
		curStage++;
	}
	for (int stage = curStage; stage < 4; stage++) {
		BFME_SET_TSS(stage, D3DTSS_COLOROP, D3DTOP_DISABLE);
		BFME_SET_TSS(stage, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	}
	float blend = 0.5f;
	if (TheWritableGlobalData && *(bool *)((char *)TheWritableGlobalData + 0xdbc)) blend = 1.0f;
	{ Vector4 blendVector(blend, blend, blend, blend);
	bfmeSetPixelShaderConstant(1, &blendVector, 1); }
	if (curStage < 3) bfmeSetPixelShader(m_roadNoise1);
	else if (curStage == 3) bfmeSetPixelShader(m_roadNoise2);
	else if (curStage == 4) bfmeSetPixelShader(m_roadNoise3);
	DX8Wrapper::_Get_D3D_Device8()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);	//blend roads into terrain
	return TRUE;
}

extern int g_bfmeDefaultFE[];
extern int g_bfmeAltFE[];
extern int g_bfmeFlagsFE[4];
extern int *g_bfmePointersFE[4];

enum { BFME_DC_GENERIC_PIXEL_SHADER_1_1 = 3 };

class BfmeShaderLoader
{
public:
	static long LoadAndCreateD3DShader(const char *filename, unsigned long *shader);
};

int RoadShaderPixelShader::init(void)
{
	int *def = g_bfmeDefaultFE;
	int one = 1;

	g_bfmePointersFE[0] = def;
	g_bfmeFlagsFE[0] = one;
	g_bfmePointersFE[1] = def;
	g_bfmeFlagsFE[1] = one;
	g_bfmePointersFE[2] = def;
	g_bfmeFlagsFE[2] = one;
	g_bfmePointersFE[3] = def;
	g_bfmeFlagsFE[3] = one;

	if (W3DShaderManager::getChipset() >= BFME_DC_GENERIC_PIXEL_SHADER_1_1)
	{
		if (BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\roadnoise1.pso", &m_roadNoise1) >= 0)
		{
			if (BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\roadnoise2.pso", &m_roadNoise2) >= 0)
			{
				if (BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\roadnoise3.pso", &m_roadNoise3) >= 0)
				{
					int *alt = g_bfmeAltFE;
					g_bfmePointersFE[1] = alt;
					g_bfmePointersFE[2] = alt;
					g_bfmePointersFE[3] = alt;
					g_bfmeFlagsFE[1] = one;
					g_bfmeFlagsFE[2] = one;
					g_bfmeFlagsFE[3] = one;
					return one;
				}
			}
		}
	}

	return 0;
}
