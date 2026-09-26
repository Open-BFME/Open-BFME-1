// ?Rva007D9940ResetStages@@YAXXZ
struct Rva007D9940Texture
{
	virtual void __stdcall QueryInterface( void );
	virtual void __stdcall AddRef( void );
	virtual void __stdcall Release( void );
};

struct Rva007D9940Device
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
	virtual long __stdcall SetTexture( unsigned int stage, Rva007D9940Texture *texture );
	virtual void __stdcall slot66( void );
	virtual void __stdcall slot67( void );
	virtual void __stdcall slot68( void );
	virtual void __stdcall slot69( void );
	virtual void __stdcall slot70( void );
	virtual void __stdcall slot71( void );
	virtual void __stdcall slot72( void );
	virtual void __stdcall slot73( void );
	virtual void __stdcall slot74( void );
	virtual void __stdcall slot75( void );
	virtual void __stdcall slot76( void );
	virtual void __stdcall slot77( void );
	virtual void __stdcall slot78( void );
	virtual void __stdcall slot79( void );
	virtual void __stdcall slot80( void );
	virtual void __stdcall slot81( void );
	virtual void __stdcall slot82( void );
	virtual void __stdcall slot83( void );
	virtual void __stdcall slot84( void );
	virtual void __stdcall slot85( void );
	virtual void __stdcall slot86( void );
	virtual void __stdcall slot87( void );
	virtual void __stdcall slot88( void );
	virtual void __stdcall slot89( void );
	virtual void __stdcall slot90( void );
	virtual void __stdcall slot91( void );
	virtual void __stdcall slot92( void );
	virtual void __stdcall slot93( void );
	virtual void __stdcall slot94( void );
	virtual void __stdcall slot95( void );
	virtual void __stdcall slot96( void );
	virtual void __stdcall slot97( void );
	virtual void __stdcall slot98( void );
	virtual void __stdcall slot99( void );
	virtual void __stdcall slot100( void );
	virtual void __stdcall slot101( void );
	virtual void __stdcall slot102( void );
	virtual void __stdcall slot103( void );
	virtual void __stdcall slot104( void );
	virtual void __stdcall slot105( void );
	virtual void __stdcall slot106( void );
	virtual long __stdcall slot107( unsigned int value );
};

extern Rva007D9940Device *Rva01340534DeviceB;

class DX8Wrapper
{
public:
	static void Invalidate_Cached_Render_States( void );
};

void Rva007D9940ResetStages( void )
{
	Rva01340534DeviceB->SetTexture( 0, 0 );
	Rva01340534DeviceB->SetTexture( 1, 0 );
	Rva01340534DeviceB->SetTexture( 2, 0 );
	Rva01340534DeviceB->SetTexture( 3, 0 );
	Rva01340534DeviceB->SetTexture( 4, 0 );
	Rva01340534DeviceB->slot107( 0 );
	DX8Wrapper::Invalidate_Cached_Render_States();
}
