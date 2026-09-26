// cl: /DNDEBUG /MD /EHsc
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

extern Rva006C9270Device *Rva01340534Device;
extern unsigned int Rva01340594DX8Calls;
extern unsigned int Rva01340568StageChanges;
extern unsigned int Rva01340560TextureChanges;
extern Rva006C9270Texture *Rva0133F478Textures[];

struct Rva006C9270GlobalData
{
	char m_unreconstructed[ 0x4C ];
	unsigned char m_flag4C;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

class DX8Wrapper
{
public:
	static void Set_DX8_Texture_Stage_State_Body( unsigned int stage, unsigned long state, unsigned int value );
	static void Set_DX8_Render_State( unsigned long state, unsigned int value );
};

static __forceinline void Rva006C9270DeviceStageState( unsigned int stage, unsigned int state, unsigned int value )
{
	Rva01340534Device->SetTextureStageState( stage, state, value );
	Rva01340594DX8Calls++;
	Rva01340568StageChanges++;
}

static __forceinline void Rva006C9270SetTexture( unsigned int stage, Rva006C9270Texture *texture )
{
	if( stage >= 8 )
	{
		Rva01340534Device->SetTexture( stage, texture );
		Rva01340594DX8Calls++;
		return;
	}
	if( Rva0133F478Textures[ stage ] == texture )
		return;
	if( Rva0133F478Textures[ stage ] )
		Rva0133F478Textures[ stage ]->Release();
	Rva0133F478Textures[ stage ] = texture;
	if( texture )
		texture->AddRef();
	Rva01340534Device->SetTexture( stage, texture );
	Rva01340594DX8Calls++;
	Rva01340560TextureChanges++;
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
	if( TheWritableGlobalData && !TheWritableGlobalData->m_flag4C )
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
