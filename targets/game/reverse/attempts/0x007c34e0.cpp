// ?set@CloudTextureShader@@EAEHH@Z
// partial score=0.8701 date=2026-10-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// CloudTextureShader uses native DX8 declarations and a counted texture return.
// Evidence: targets/game/reverse/identity_evidence/007c34e0-cloud-set.md

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

typedef HRESULT (__stdcall *BFMESetTextureFn)(IDirect3DDevice8 *, DWORD, IDirect3DBaseTexture8 *);
typedef HRESULT (__stdcall *BFMESetTSSFn)(IDirect3DDevice8 *, DWORD, DWORD, DWORD);
enum { BFME_SET_TSS_SLOT = 67 };

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

#define BFME_SET_SAMP(stage_, type_, value_)                                                 \
	{                                                                                        \
		IDirect3DDevice8 *samp_device_ = DX8Wrapper::_Get_D3D_Device8();                      \
		(*(BFMESetTSSFn **)samp_device_)[BFME_SET_SAMP_SLOT](samp_device_,                    \
			(stage_), (type_), (value_));                                                     \
		number_of_DX8_calls++;                                                                \
		DX8Wrapper::texture_stage_state_changes++;                                            \
	}

enum { BFME_SAMP_MINFILTER = 6, BFME_SAMP_MAGFILTER = 5,
       BFME_SAMP_ADDRESSU = 1, BFME_SAMP_ADDRESSV = 2,
       BFME_SET_SAMP_SLOT = 69, BFME_SET_TEXTURE_SLOT = 65 };

class W3DShaderInterface
{
public:
    virtual int set(int pass);
    virtual void reset();
    virtual int init();
    virtual int shutdown();
protected:
    int m_numPasses;
};

class TerrainShader2Stage : public W3DShaderInterface
{
public:
	float m_xSlidePerSecond ;	 ///< How far the clouds move per second.
	float m_ySlidePerSecond ;	 ///< How far the clouds move per second.
	int	  m_curTick;
	float m_xOffset;
	float m_yOffset;
	virtual int set(int pass);
	virtual int init(void);
	virtual void reset(void);
	void updateNoise1 (D3DXMATRIX *destMatrix,D3DXMATRIX *curViewInverse, bool doUpdate=true);
	void updateNoise2 (D3DXMATRIX *destMatrix,D3DXMATRIX *curViewInverse, bool doUpdate=true);
};
extern TerrainShader2Stage terrainShader2Stage;

class CloudTextureShader : public W3DShaderInterface
{
	virtual int set(int stage);
	virtual int init(void);
	virtual void reset(void);
	int m_stageOfSet;
};

// ?bfmeBindCloudTexture@@YAXIABVBfmeHandleCX@@@Z absent-from-retail
__forceinline void bfmeBindCloudTexture(unsigned stage, const BfmeHandleCX &texture)
{
    IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
    (*(BFMESetTextureFn **)device)[BFME_SET_TEXTURE_SLOT](device, stage, ((const TextureBaseClass &)texture).Peek_D3D_Base_Texture());
}

// ?set@CloudTextureShader@@EAEHH@Z
int CloudTextureShader::set(int stage)
{
	Matrix4x4 curView;
	DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, curView);

	D3DXMATRIX inv;
	float det;

	D3DXMatrixInverse(&inv, &det, (D3DXMATRIX*)&curView);

	
    if (stage == 0)
    {
        const ShaderClass &shader = ShaderClass::_PresetMultiplicativeSpriteShader;
        if (ShaderClass::ShaderDirty || (unsigned &)shader != (unsigned &)DX8Wrapper::render_state.shader)
        {
            DX8Wrapper::render_state.shader = shader;
            DX8Wrapper::render_state_changed |= 0x8000;
            BFMEValueName value_name(0, false);
        }
    }

	terrainShader2Stage.updateNoise1(((D3DXMATRIX*)&curView),&inv,false);	

	BFME_SET_TSS(stage, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
	BFME_SET_TSS(stage, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
	{
		DX8Wrapper::matrix_changes++;
		IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
		typedef HRESULT (__stdcall *SetTransformFn)(IDirect3DDevice8 *, DWORD, const Matrix4 *);
		(*(SetTransformFn **)device)[44](device, D3DTS_TEXTURE0 + stage, &curView);
		number_of_DX8_calls++;
	}
	BFME_SET_SAMP(stage, BFME_SAMP_MINFILTER, D3DTEXF_LINEAR);
	BFME_SET_SAMP(stage, BFME_SAMP_MAGFILTER, D3DTEXF_LINEAR);
	BFME_SET_SAMP(stage, BFME_SAMP_ADDRESSU, D3DTADDRESS_WRAP);
	BFME_SET_SAMP(stage, BFME_SAMP_ADDRESSV, D3DTADDRESS_WRAP);

	BFME_SET_TSS(stage, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	BFME_SET_TSS(stage, D3DTSS_COLORARG2, D3DTA_CURRENT);
	BFME_SET_TSS(stage, D3DTSS_COLOROP, D3DTOP_MODULATE);
	BFME_SET_TSS(stage, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	BFME_SET_TSS(stage, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	BFME_SET_TSS(stage, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
	bfmeBindCloudTexture(stage, bfmeGet(stage));

	m_stageOfSet=stage;
	return 1;
}

