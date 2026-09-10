// ?step@Rva0024ECA0Owner@@QAEXPAURva0024ECA0Object@@@Z
// partial score=0.94 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: address-derived. Retail 0x0024ECA0, 126B, SlaughterHordeContain's
// +0x20 secondary-interface slot 34 (+0x88, same slot HordeGarrisonContain
// overrides at 0x00248C60). No header source or matched caller names this
// BFME-only virtual (reverse/re_attempts.log 0x00248C60 / 0x0024ECA0).
//
// Calls the already-landed bfmeAskDG (BfmeOneHundredEightySix.cpp, via its
// thunk j_00036c05) as a thiscall member so retail's `mov ecx,esi` before the
// call reproduces; the returned pointer's own slot 64 (+0x100) is called when
// non-null. Otherwise checks owner slot 27 (+0x6c), then falls back to
// Thing::isKindOf(0x6c) through the pinned bfmeAskAIA thunk (j_0002130f is
// unrelated; this is j_0002e... no -- thunk 0x0003251F, still a dump) before
// choosing owner slot 29 (+0x74) or slot 30 (+0x78), always closing with the
// owner cleanup call at slot 17 (+0x44).

class Rva0024ECA0Deep;
struct Rva0024ECA0Object;

class Rva0024ECA0AskDG
{
public:
	Rva0024ECA0Deep *askDG( Rva0024ECA0Object *obj );
};

#pragma comment(linker, "/alternatename:?askDG@Rva0024ECA0AskDG@@QAEPAVRva0024ECA0Deep@@PAURva0024ECA0Object@@@Z=?j_00036c05@@YAXXZ")

class BfmeThingAIA
{
public:
	bool bfmeAskAIA( int kind );
};

#define BFME_SLOT( N ) virtual void bfmeSlot##N( void ) = 0

class Rva0024ECA0Deep
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03);
	BFME_SLOT(04); BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07);
	BFME_SLOT(08); BFME_SLOT(09); BFME_SLOT(10); BFME_SLOT(11);
	BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14); BFME_SLOT(15);
	BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23);
	BFME_SLOT(24); BFME_SLOT(25); BFME_SLOT(26); BFME_SLOT(27);
	BFME_SLOT(28); BFME_SLOT(29); BFME_SLOT(30); BFME_SLOT(31);
	BFME_SLOT(32); BFME_SLOT(33); BFME_SLOT(34); BFME_SLOT(35);
	BFME_SLOT(36); BFME_SLOT(37); BFME_SLOT(38); BFME_SLOT(39);
	BFME_SLOT(40); BFME_SLOT(41); BFME_SLOT(42); BFME_SLOT(43);
	BFME_SLOT(44); BFME_SLOT(45); BFME_SLOT(46); BFME_SLOT(47);
	BFME_SLOT(48); BFME_SLOT(49); BFME_SLOT(50); BFME_SLOT(51);
	BFME_SLOT(52); BFME_SLOT(53); BFME_SLOT(54); BFME_SLOT(55);
	BFME_SLOT(56); BFME_SLOT(57); BFME_SLOT(58); BFME_SLOT(59);
	BFME_SLOT(60); BFME_SLOT(61); BFME_SLOT(62); BFME_SLOT(63);
	virtual void bfmeDeepCall( void ) = 0;   // slot 64, +0x100
};

struct Rva0024ECA0Object
{
	unsigned char m_head[ 0x214 ];
	int m_flag214;   // +0x214
};

class Rva0024ECA0Container
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03);
	BFME_SLOT(04); BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07);
	BFME_SLOT(08); BFME_SLOT(09); BFME_SLOT(10); BFME_SLOT(11);
	BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14); BFME_SLOT(15);
	BFME_SLOT(16);
	virtual void bfmeSlot44( void ) = 0;                      // slot 17, +0x44
	BFME_SLOT(18); BFME_SLOT(19); BFME_SLOT(20); BFME_SLOT(21);
	BFME_SLOT(22); BFME_SLOT(23); BFME_SLOT(24); BFME_SLOT(25);
	BFME_SLOT(26);
	virtual int bfmeSlot6C( Rva0024ECA0Object *obj ) = 0;     // slot 27, +0x6c
	BFME_SLOT(28);
	virtual void bfmeSlot74( Rva0024ECA0Object *obj ) = 0;    // slot 29, +0x74
	virtual void bfmeSlot78( Rva0024ECA0Object *obj ) = 0;    // slot 30, +0x78
};

#undef BFME_SLOT

class Rva0024ECA0Owner
{
public:
	void step( Rva0024ECA0Object *obj );
};

// ?d_0024eca0@@YAXXZ -- address-derived; the real virtual name is not
// recovered.
void Rva0024ECA0Owner::step( Rva0024ECA0Object *obj )
{
	if ( obj->m_flag214 != 0 )
		return;

	Rva0024ECA0Container *container =
		reinterpret_cast<Rva0024ECA0Container *>( reinterpret_cast<char *>( this ) - 0x20 );

	Rva0024ECA0Deep *deep = reinterpret_cast<Rva0024ECA0AskDG *>( container )->askDG( obj );
	if ( deep != 0 )
	{
		deep->bfmeDeepCall();
		container->bfmeSlot74( obj );
		container->bfmeSlot44();
		return;
	}

	if ( !container->bfmeSlot6C( obj ) )
	{
		if ( reinterpret_cast<BfmeThingAIA *>( obj )->bfmeAskAIA( 0x6c ) )
		{
			container->bfmeSlot74( obj );
			container->bfmeSlot44();
			return;
		}
	}

	container->bfmeSlot78( obj );
	container->bfmeSlot44();
}
