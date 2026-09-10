// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: address-derived. Retail 0x00248C60, 124B, HordeGarrisonContain's
// +0x20 secondary-interface slot 34 (+0x88, same slot SlaughterHordeContain
// overrides at 0x0024ECA0). No header source or matched caller names this
// BFME-only virtual (reverse/re_attempts.log 0x00248C60 / 0x0024ECA0).
//
// Inlines the same "thing->target->bfmeDoDG()" query BfmeOneHundredEightySix.cpp
// names bfmeAskDG (target field at +0x1fc, slot 26/+0x68); the returned
// pointer's own slot 64 (+0x100) is called when non-null. Falls through to a
// two-way owner dispatch (slot 27/+0x6c decides slot 30/+0x78 vs slot 29/+0x74)
// followed by an unconditional owner cleanup call (slot 17/+0x44).

#define BFME_SLOT( N ) virtual void bfmeSlot##N( void ) = 0

class Rva00248C60Deep
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

class Rva00248C60DoTarget
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03);
	BFME_SLOT(04); BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07);
	BFME_SLOT(08); BFME_SLOT(09); BFME_SLOT(10); BFME_SLOT(11);
	BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14); BFME_SLOT(15);
	BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23);
	BFME_SLOT(24); BFME_SLOT(25);
	virtual Rva00248C60Deep *bfmeDoDG( void ) = 0;   // slot 26, +0x68
};

struct Rva00248C60DGField
{
	unsigned char m_head[ 0x1fc ];
	Rva00248C60DoTarget *m_target;   // +0x1fc
};

struct Rva00248C60Object
{
	unsigned char m_head[ 0x214 ];
	int m_flag214;   // +0x214
};

class Rva00248C60Container
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
	virtual int bfmeSlot6C( Rva00248C60Object *obj ) = 0;     // slot 27, +0x6c
	BFME_SLOT(28);
	virtual void bfmeSlot74( Rva00248C60Object *obj ) = 0;    // slot 29, +0x74
	virtual void bfmeSlot78( Rva00248C60Object *obj ) = 0;    // slot 30, +0x78
};

#undef BFME_SLOT

class Rva00248C60Owner
{
public:
	void step( Rva00248C60Object *obj );
};

// ?d_00248c60@@YAXXZ -- address-derived; the real virtual name is not
// recovered.
#define CONTAINER reinterpret_cast<Rva00248C60Container *>( reinterpret_cast<char *>( this ) - 0x20 )

void Rva00248C60Owner::step( Rva00248C60Object *obj )
{
	if ( obj->m_flag214 != 0 )
		return;

	Rva00248C60Deep *deep = 0;
	Rva00248C60DGField *field = reinterpret_cast<Rva00248C60DGField *>( obj );
	Rva00248C60DoTarget *target = field->m_target;
	if ( target != 0 )
		deep = target->bfmeDoDG();

	if ( deep != 0 )
	{
		deep->bfmeDeepCall();
		CONTAINER->bfmeSlot74( obj );
	}
	else if ( CONTAINER->bfmeSlot6C( obj ) )
	{
		CONTAINER->bfmeSlot78( obj );
	}
	else
	{
		CONTAINER->bfmeSlot74( obj );
	}

	CONTAINER->bfmeSlot44();
}

#undef CONTAINER
