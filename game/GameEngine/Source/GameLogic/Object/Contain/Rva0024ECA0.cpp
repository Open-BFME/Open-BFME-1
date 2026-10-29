// ?rva0024ECA0@Rva0024ECA0Owner@@QAEXPAURva0024ECA0Object@@@Z
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0024ECA0, 126 B (ret 4 at +0x7B). SlaughterHordeContain's +0x20
// secondary-interface slot 34 (+0x88), the same slot HordeGarrisonContain
// overrides at 0x00248C60; no header source or matched caller names this
// BFME-only virtual, so the owner and method stay address-derived.
//
// The body adjusts to the primary container (this - 0x20) and asks it,
// through ILT 0x00036C05 (matched bfmeAskDG at 0x00248AE0, called with the
// container in ECX), for a deep pointer whose slot 64 runs when present;
// otherwise container slot 27 (+0x6C) and Thing::isKindOf(0x6C) (ILT
// 0x0003251F -> 0x000A2CF0) choose container slot 29 (+0x74) or slot 30
// (+0x78), and every path ends with container slot 17 (+0x44).
//
// Shape: the slot-30 call is written in both failing arms, which VC7.1
// cross-jumps into one block; that reproduces retail's `mov ecx,esi`
// before `push edi` there (docs/shape_levers.md, tail-merge receiver order).

enum KindOfType { KINDOF_INVALID = 0 };

class Thing
{
public:
	bool isKindOf( KindOfType t ) const;
};

class Rva0024ECA0Owner;

// Pinned thiscall spelling of ILT 0x00036C05 (symbols.csv).
class Gen_0021AD10
{
	friend class Rva0024ECA0Owner;
	void *bfmeAskRaw( void *a );
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
	void rva0024ECA0( Rva0024ECA0Object *obj );
};

// ?d_0024eca0@@YAXXZ -- address-derived; the real virtual name is not
// recovered.
void Rva0024ECA0Owner::rva0024ECA0( Rva0024ECA0Object *obj )
{
	if ( obj->m_flag214 != 0 )
		return;

	Rva0024ECA0Container *container =
		reinterpret_cast<Rva0024ECA0Container *>( reinterpret_cast<char *>( this ) - 0x20 );

	Rva0024ECA0Deep *deep = static_cast<Rva0024ECA0Deep *>(
		reinterpret_cast<Gen_0021AD10 *>( container )->bfmeAskRaw( obj ) );
	if( deep != 0 )
	{
		deep->bfmeDeepCall();
		container->bfmeSlot74( obj );
	}
	else if( container->bfmeSlot6C( obj ) )
		container->bfmeSlot78( obj );
	else if( reinterpret_cast<Thing *>( obj )->isKindOf( static_cast<KindOfType>( 0x6c ) ) )
		container->bfmeSlot74( obj );
	else
		container->bfmeSlot78( obj );
	container->bfmeSlot44();
}
