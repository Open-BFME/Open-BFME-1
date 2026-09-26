// ?Rva007DD0E0ResetStages01@@YAXXZ
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

class DX8Wrapper
{
public:
	static void Set_DX8_Texture_Stage_State( unsigned int stage, unsigned long state, unsigned int value );
	static void Invalidate_Cached_Render_States( void );
};

void Rva007DD0E0ResetStages01( void )
{
	DX8Wrapper::Set_DX8_Texture_Stage_State( 2, 1, 1 );
	DX8Wrapper::Set_DX8_Texture_Stage_State( 2, 4, 1 );
	DX8Wrapper::Set_DX8_Texture_Stage_State( 3, 1, 1 );
	DX8Wrapper::Set_DX8_Texture_Stage_State( 3, 4, 1 );
	DX8Wrapper::Set_DX8_Texture_Stage_State( 4, 1, 1 );
	DX8Wrapper::Set_DX8_Texture_Stage_State( 4, 4, 1 );
	Rva01340534Device->SetTexture( 0, 0 );
	Rva01340534Device->SetTexture( 1, 0 );
	DX8Wrapper::Invalidate_Cached_Render_States();
}
