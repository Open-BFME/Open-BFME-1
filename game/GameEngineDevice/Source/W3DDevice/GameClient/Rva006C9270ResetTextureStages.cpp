// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
#define HEAP_ZERO_MEMORY 8
extern "C" __declspec(dllimport) void * __stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) void * __stdcall HeapAlloc(void *, unsigned long, unsigned long);
extern "C" __declspec(dllimport) int __stdcall HeapFree(void *, unsigned long, void *);
#include "dx8wrapper.h"

// Open-BFME7: the W3D texture-stage reset at 0x006C9270 (559 B no
// arguments).  Stages 0 and 1 get the default colour/alpha operation states
// through DX8Wrapper's cached setter and two direct device calls each
// (SetTextureStageState with the DX8 call and stage-change counters bumped
// after each) then the blend render states; when the writable global data
// exists and its byte at +0x4C is clear every one of the eight stages is
// reset (seven cached states) and its texture released through the inline
// DX8Wrapper::Set_DX8_Texture(stage NULL) (Textures[] at VA 0x0133F478 the
// texture-change counter at 0x01340560).  Address-derived names.

struct Rva006C9270Texture
{
	virtual void __stdcall QueryInterface( void );
	virtual void __stdcall AddRef( void );
	virtual void __stdcall Release( void );
};

struct Rva006C9270Device
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
	virtual long __stdcall SetTexture( unsigned int stage, Rva006C9270Texture *texture );
	virtual void __stdcall slot66( void );
	virtual void __stdcall slot67( void );
	virtual void __stdcall slot68( void );
	virtual long __stdcall SetTextureStageState( unsigned int stage, unsigned int state, unsigned int value );
};

// Header-declared storage shared with DX8Wrapper::Set_DX8_Texture:
// DIR32 witnesses map Textures to VA 0x0133F478 and the counters to
// 0x01340560/0x01340568. Preserve this retail device-slot layout view.
struct Rva006C9270DX8Access : DX8Wrapper
{
 static Rva006C9270Texture **TextureSlots()
 { return reinterpret_cast<Rva006C9270Texture **>(Textures); }
 static void RecordStageChange() { ++texture_stage_state_changes; }
 static void RecordTextureChange() { ++texture_changes; }
};

// TU-local layout view of the 0x012ED5C8 global, not the real header's body.
struct Rva006C9270GlobalData
{
	char m_unreconstructed[ 0x4C ];
	unsigned char m_flag4C;
};

// The 0x012ED5C8 global is EA's GlobalData *TheWritableGlobalData, defined
// once in game/GameEngine/Source/Common/GlobalData.cpp.
class GlobalData;
extern GlobalData *TheWritableGlobalData;



static __forceinline void Rva006C9270DeviceStageState( unsigned int stage, unsigned int state, unsigned int value )
{
	reinterpret_cast<Rva006C9270Device *>(DX8Wrapper::_Get_D3D_Device8())->SetTextureStageState( stage, state, value );
	number_of_DX8_calls++;
	Rva006C9270DX8Access::RecordStageChange();
}

static __forceinline void Rva006C9270SetTexture( unsigned int stage, Rva006C9270Texture *texture )
{
	if( stage >= 8 )
	{
		reinterpret_cast<Rva006C9270Device *>(DX8Wrapper::_Get_D3D_Device8())->SetTexture( stage, texture );
		number_of_DX8_calls++;
		return;
	}
	if( Rva006C9270DX8Access::TextureSlots()[ stage ] == texture )
		return;
	if( Rva006C9270DX8Access::TextureSlots()[ stage ] )
		Rva006C9270DX8Access::TextureSlots()[ stage ]->Release();
	Rva006C9270DX8Access::TextureSlots()[ stage ] = texture;
	if( texture )
		texture->AddRef();
	reinterpret_cast<Rva006C9270Device *>(DX8Wrapper::_Get_D3D_Device8())->SetTexture( stage, texture );
	number_of_DX8_calls++;
	Rva006C9270DX8Access::RecordTextureChange();
}

// ?Rva006C9270ResetTextureStages@@YAXXZ
void Rva006C9270ResetTextureStages( void )
{
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 0, 2, 2 );
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 0, 3, 0 );
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 0, 1, 4 );
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 0, 4, 1 );
	Rva006C9270DeviceStageState( 0, 1, 1 );
	Rva006C9270DeviceStageState( 0, 2, 1 );
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 0, 0xB, 0 );
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 0, 0x18, 0 );
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 1, 2, 2 );
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 1, 3, 0 );
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 1, 1, 4 );
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 1, 4, 1 );
	Rva006C9270DeviceStageState( 1, 1, 1 );
	Rva006C9270DeviceStageState( 1, 2, 1 );
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 1, 0xB, 0 );
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 1, 0x18, 0 );
	DX8Wrapper::Set_DX8_Render_State( 0x1B, 0 );
	DX8Wrapper::Set_DX8_Render_State( 0x13, 5 );
	DX8Wrapper::Set_DX8_Render_State( 0x14, 6 );
	if( TheWritableGlobalData && !((Rva006C9270GlobalData *)TheWritableGlobalData)->m_flag4C )
	{
		for( int stage = 0; stage < 8; stage++ )
		{
			DX8Wrapper::Set_DX8_Texture_Stage_State_Body( stage, 1, 1 );
			DX8Wrapper::Set_DX8_Texture_Stage_State_Body( stage, 0xB, stage );
			DX8Wrapper::Set_DX8_Texture_Stage_State_Body( stage, 2, 2 );
			DX8Wrapper::Set_DX8_Texture_Stage_State_Body( stage, 3, 0 );
			DX8Wrapper::Set_DX8_Texture_Stage_State_Body( stage, 4, 1 );
			DX8Wrapper::Set_DX8_Texture_Stage_State_Body( stage, 5, 2 );
			DX8Wrapper::Set_DX8_Texture_Stage_State_Body( stage, 6, 0 );
			Rva006C9270SetTexture( stage, 0 );
		}
	}
}
