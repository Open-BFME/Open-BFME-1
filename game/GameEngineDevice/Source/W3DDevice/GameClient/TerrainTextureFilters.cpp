// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
#define HEAP_ZERO_MEMORY 8
extern "C" __declspec(dllimport) void * __stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) void * __stdcall HeapAlloc(void *, unsigned long, unsigned long);
extern "C" __declspec(dllimport) int __stdcall HeapFree(void *, unsigned long, void *);
#include "dx8wrapper.h"

// ?setTerrainTextureFilters@@YAXI@Z
// Per-stage terrain min/mag/mip filter selection from the anisotropic filter
// caps and GlobalData's bilinear/trilinear terrain flags; +0x47 stays unwitnessed.

struct Rva006D4FF0Device
{
	virtual void __stdcall slot0( void );
	virtual void __stdcall slot1( void );
	virtual void __stdcall slot2( void );
	virtual void __stdcall slot3( void );
	virtual void __stdcall slot4( void );
	virtual void __stdcall slot5( void );
	virtual void __stdcall slot6( void );
	virtual void __stdcall slot7( void );
	virtual void __stdcall slot8( void );
	virtual void __stdcall slot9( void );
	virtual void __stdcall slot10( void );
	virtual void __stdcall slot11( void );
	virtual void __stdcall slot12( void );
	virtual void __stdcall slot13( void );
	virtual void __stdcall slot14( void );
	virtual void __stdcall slot15( void );
	virtual void __stdcall slot16( void );
	virtual void __stdcall slot17( void );
	virtual void __stdcall slot18( void );
	virtual void __stdcall slot19( void );
	virtual void __stdcall slot20( void );
	virtual void __stdcall slot21( void );
	virtual void __stdcall slot22( void );
	virtual void __stdcall slot23( void );
	virtual void __stdcall slot24( void );
	virtual void __stdcall slot25( void );
	virtual void __stdcall slot26( void );
	virtual void __stdcall slot27( void );
	virtual void __stdcall slot28( void );
	virtual void __stdcall slot29( void );
	virtual void __stdcall slot30( void );
	virtual void __stdcall slot31( void );
	virtual void __stdcall slot32( void );
	virtual void __stdcall slot33( void );
	virtual void __stdcall slot34( void );
	virtual void __stdcall slot35( void );
	virtual void __stdcall slot36( void );
	virtual void __stdcall slot37( void );
	virtual void __stdcall slot38( void );
	virtual void __stdcall slot39( void );
	virtual void __stdcall slot40( void );
	virtual void __stdcall slot41( void );
	virtual void __stdcall slot42( void );
	virtual void __stdcall slot43( void );
	virtual void __stdcall slot44( void );
	virtual void __stdcall slot45( void );
	virtual void __stdcall slot46( void );
	virtual void __stdcall slot47( void );
	virtual void __stdcall slot48( void );
	virtual void __stdcall slot49( void );
	virtual void __stdcall slot50( void );
	virtual void __stdcall slot51( void );
	virtual void __stdcall slot52( void );
	virtual void __stdcall slot53( void );
	virtual void __stdcall slot54( void );
	virtual void __stdcall slot55( void );
	virtual void __stdcall slot56( void );
	virtual void __stdcall slot57( void );
	virtual void __stdcall slot58( void );
	virtual void __stdcall slot59( void );
	virtual void __stdcall slot60( void );
	virtual void __stdcall slot61( void );
	virtual void __stdcall slot62( void );
	virtual void __stdcall slot63( void );
	virtual void __stdcall slot64( void );
	virtual void __stdcall slot65( void );
	virtual void __stdcall slot66( void );
	virtual void __stdcall slot67( void );
	virtual void __stdcall slot68( void );
	virtual long __stdcall SetTextureStageState( unsigned int stage, unsigned int state, unsigned int value );
};

// Canonical storage is shared with the verified DX8Wrapper device-state bodies.
struct Rva006D4690DX8Access : DX8Wrapper
{
 static void RecordStageChange() { ++texture_stage_state_changes; }
};

struct Rva006C9270GlobalData
{
	char m_unreconstructed[ 0x45 ];
	unsigned char m_bilinearTerrainTex;
	unsigned char m_trilinearTerrainTex;
	unsigned char m_unknown47;
};

class GlobalData;

// Retail [0x012ED5C8] is EA's writable GlobalData (Common/GlobalData.cpp); this
// file views the same object through Rva006C9270GlobalData.
extern GlobalData *TheWritableGlobalData;


#define SET_TERRAIN_TEXTURE_FILTER_STATE(stage_, state_, value_) \
	do { \
		reinterpret_cast<Rva006D4FF0Device *>(DX8Wrapper::_Get_D3D_Device8())->SetTextureStageState( (stage_), (state_), (value_) ); \
		number_of_DX8_calls++; \
		Rva006D4690DX8Access::RecordStageChange(); \
	} while( 0 )

// ?setTerrainTextureFilters@@YAXI@Z
void __cdecl setTerrainTextureFilters( unsigned stage )
{
	unsigned char filter_mode = ((Rva006C9270GlobalData *)TheWritableGlobalData)->m_unknown47;
	if( (reinterpret_cast<const unsigned int *>( DX8Wrapper::Get_Current_Caps() )[ 0x12 ] & 0x400) == 0 )
		filter_mode = 0;
	if( (reinterpret_cast<const unsigned int *>( DX8Wrapper::Get_Current_Caps() )[ 0x12 ] & 0x04000000) == 0 )
		filter_mode = 0;

	if( filter_mode )
	{
		SET_TERRAIN_TEXTURE_FILTER_STATE( stage, 6, 3 );
		SET_TERRAIN_TEXTURE_FILTER_STATE( stage, 5, 3 );
		SET_TERRAIN_TEXTURE_FILTER_STATE( stage, 10, 2 );
	}
	else if( ((Rva006C9270GlobalData *)TheWritableGlobalData)->m_bilinearTerrainTex || ((Rva006C9270GlobalData *)TheWritableGlobalData)->m_trilinearTerrainTex )
	{
		SET_TERRAIN_TEXTURE_FILTER_STATE( stage, 6, 2 );
		SET_TERRAIN_TEXTURE_FILTER_STATE( stage, 5, 2 );
	}
	else
	{
		SET_TERRAIN_TEXTURE_FILTER_STATE( stage, 6, 1 );
		SET_TERRAIN_TEXTURE_FILTER_STATE( stage, 5, 1 );
	}

	if( ((Rva006C9270GlobalData *)TheWritableGlobalData)->m_trilinearTerrainTex || filter_mode )
		SET_TERRAIN_TEXTURE_FILTER_STATE( stage, 7, 2 );
	else
		SET_TERRAIN_TEXTURE_FILTER_STATE( stage, 7, 1 );
}
