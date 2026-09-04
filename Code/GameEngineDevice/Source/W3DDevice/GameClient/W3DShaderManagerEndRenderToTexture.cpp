// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Readable BFME body for the static render-to-texture teardown at retail 0x00717420.

#include "dx8wrapper.h"

struct IDirect3DTexture8;
struct IDirect3DSurface8;

typedef long (__stdcall *BFMESetSamplerStateFn)(IDirect3DDevice8 *, unsigned, unsigned, unsigned);
extern unsigned number_of_DX8_calls;

class DX8CounterAccess : public DX8Wrapper
{
public:
	static unsigned &textureCount(void) { return texture_stage_state_changes; }
};

#define BFME_SET_SAMP(stage_, type_, value_)                                                \
	{                                                                                           \
		IDirect3DDevice8 *samp_device_ = DX8Wrapper::_Get_D3D_Device8();                          \
		(*(BFMESetSamplerStateFn **)samp_device_)[69](samp_device_,                            \
			(stage_), (type_), (value_));                                                         \
		number_of_DX8_calls++;                                                                  \
		DX8CounterAccess::textureCount()++;                                                       \
	}

class W3DShaderManager
{
public:
	static IDirect3DTexture8 *endRenderToTexture(void);
};

IDirect3DTexture8 *W3DShaderManager::endRenderToTexture(void)
{
	if (!*(unsigned char *)0x012F9D00)
		return 0;

	DX8Wrapper::Set_Render_Target(*(IDirect3DSurface8 **)0x012F9D04, true);
	BFME_SET_SAMP(0, 1, 3);
	BFME_SET_SAMP(0, 2, 3);
	BFME_SET_SAMP(0, 3, 3);
	BFME_SET_SAMP(0, 5, 2);
	BFME_SET_SAMP(0, 6, 2);
	BFME_SET_SAMP(0, 7, 0);
	IDirect3DTexture8 *texture = *(IDirect3DTexture8 **)0x012F9D08;
	*(unsigned char *)0x012F9D00 = 0;
	return texture;
}
