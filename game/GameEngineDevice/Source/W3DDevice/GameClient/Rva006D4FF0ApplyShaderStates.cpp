// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: a W3D shader state block at 0x006D4FF0 (237 B; one stack
// argument callee-cleaned).  After two calls that take the argument (the
// callee-cleaned member-offset tail thunk at 0x0090C610 and the cdecl dump
// at 0x006D4690) it sets
// texture stage 0 state 0x18 to 0 through DX8Wrapper's cached setter then
// issues two direct device SetTextureStageState calls (stage 0 state 1 value 3
// and stage 0 state 2 value 3) bumping the DX8 call and stage-change counters
// after each as the DX8CALL / record macros do then five more cached stage
// states and five render states (0x1B=1 0x13=5 0x14=6 1=1 4=1).  The device
// and counter globals carry address-derived names (VA 0x01340534 0x01340594
// 0x01340568).

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

extern Rva006D4FF0Device *Rva01340534Device;
extern unsigned int Rva01340594DX8Calls;
extern unsigned int Rva01340568StageChanges;

class DX8Wrapper
{
public:
	static void Set_DX8_Texture_Stage_State_Body( unsigned int stage, unsigned long state, unsigned int value );
	static void Set_DX8_Render_State( unsigned long state, unsigned int value );
};

void __stdcall Rva0090C610Invoke( void *argument );
void __cdecl Rva006D4690Apply( void *argument );

static __forceinline void Rva006D4FF0DeviceStageState( unsigned int stage, unsigned int state, unsigned int value )
{
	Rva01340534Device->SetTextureStageState( stage, state, value );
	Rva01340594DX8Calls++;
	Rva01340568StageChanges++;
}

// ?Rva006D4FF0ApplyShaderStates@@YGXPAX@Z
void __stdcall Rva006D4FF0ApplyShaderStates( void *argument )
{
	Rva0090C610Invoke( argument );
	Rva006D4690Apply( argument );
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 0, 0x18, 0 );
	Rva006D4FF0DeviceStageState( 0, 1, 3 );
	Rva006D4FF0DeviceStageState( 0, 2, 3 );
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 0, 2, 2 );
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 0, 3, 0 );
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 0, 1, 4 );
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 0, 4, 2 );
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 0, 0xB, 0 );
	DX8Wrapper::Set_DX8_Render_State( 0x1B, 1 );
	DX8Wrapper::Set_DX8_Render_State( 0x13, 5 );
	DX8Wrapper::Set_DX8_Render_State( 0x14, 6 );
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 1, 1, 1 );
	DX8Wrapper::Set_DX8_Texture_Stage_State_Body( 1, 4, 1 );
}
