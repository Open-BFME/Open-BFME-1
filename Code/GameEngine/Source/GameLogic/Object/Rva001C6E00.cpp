// carved dump placeholder: d_001c6e00
// cl: /DNDEBUG /MD /EHsc
//
// Carved body at retail 0x001C6E00. No named caller (callers_of finds none),
// so identity stays address-derived, but every field and callee below is
// proven from the bytes: the retail string literal at 0x0108FDA8 reads
// "TemporarilyDefectUpdate" (read directly from the baseline EXE), cached
// through TheNameKeyGenerator::nameToKey behind a function-local-static
// guard byte at 0x012EF580 / cache slot at 0x012EF57C -- exactly the
// once-guard MSVC emits for a static local NameKeyType. That key resolves
// the caller's own module via the proven Object::findModule (0x001BEE60).
// Fields +0x94/+0x98 are two more 32-bit Object status/kindof words (the
// proven Object::m_bfmeStatus[2] at +0x90 from HordeContainAnyMemberHeldByAI
// only names +0x90/+0x94; +0x98 is the next word, proven here by its own
// bit-0x20 test). +0x204 is a Team*, whose bfmeSwapEW and the still-dump
// 0x0026FDE0 callee both run only when the flags-98 bit is ALSO set. The
// interface at +0x1FC is the same slot ObjectUpgrades.cpp proves as
// m_contain; its slot 0xF4 (61) is not named elsewhere, so it stays a
// placeholder here. The one parameter (an Object*) is unused until the
// tail: it is both bfmeTransferDefection's Object* argument and the
// interface call's sole argument.

typedef bool Bool;
typedef unsigned int UnsignedInt;
enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Object;
class Module;

class TemporarilyDefectUpdate
{
public:
	void bfmeTransferDefection( Object *object, UnsignedInt flags );
};

class BfmeThingEW
{
public:
	void bfmeSwapEW();
	void bfmeConv1940194();		// still-dump callee at 0x0026FDE0
};
typedef BfmeThingEW Team;

// The interface at Object+0x1FC (ObjectUpgrades.cpp's m_contain). Only slot
// 61 (+0xF4) is exercised here; the rest are unnamed placeholders.
#define BFME_SLOT( N ) virtual void bfmeSlot##N() = 0
class Rva001C6E00Interface
{
public:
	BFME_SLOT( 00 ); BFME_SLOT( 01 ); BFME_SLOT( 02 ); BFME_SLOT( 03 );
	BFME_SLOT( 04 ); BFME_SLOT( 05 ); BFME_SLOT( 06 ); BFME_SLOT( 07 );
	BFME_SLOT( 08 ); BFME_SLOT( 09 ); BFME_SLOT( 10 ); BFME_SLOT( 11 );
	BFME_SLOT( 12 ); BFME_SLOT( 13 ); BFME_SLOT( 14 ); BFME_SLOT( 15 );
	BFME_SLOT( 16 ); BFME_SLOT( 17 ); BFME_SLOT( 18 ); BFME_SLOT( 19 );
	BFME_SLOT( 20 ); BFME_SLOT( 21 ); BFME_SLOT( 22 ); BFME_SLOT( 23 );
	BFME_SLOT( 24 ); BFME_SLOT( 25 ); BFME_SLOT( 26 ); BFME_SLOT( 27 );
	BFME_SLOT( 28 ); BFME_SLOT( 29 ); BFME_SLOT( 30 ); BFME_SLOT( 31 );
	BFME_SLOT( 32 ); BFME_SLOT( 33 ); BFME_SLOT( 34 ); BFME_SLOT( 35 );
	BFME_SLOT( 36 ); BFME_SLOT( 37 ); BFME_SLOT( 38 ); BFME_SLOT( 39 );
	BFME_SLOT( 40 ); BFME_SLOT( 41 ); BFME_SLOT( 42 ); BFME_SLOT( 43 );
	BFME_SLOT( 44 ); BFME_SLOT( 45 ); BFME_SLOT( 46 ); BFME_SLOT( 47 );
	BFME_SLOT( 48 ); BFME_SLOT( 49 ); BFME_SLOT( 50 ); BFME_SLOT( 51 );
	BFME_SLOT( 52 ); BFME_SLOT( 53 ); BFME_SLOT( 54 ); BFME_SLOT( 55 );
	BFME_SLOT( 56 ); BFME_SLOT( 57 ); BFME_SLOT( 58 ); BFME_SLOT( 59 );
	BFME_SLOT( 60 );
	virtual void bfmeSlot61( Object *object );			// slot 61, +0xF4
};
#undef BFME_SLOT

class Object
{
public:
	void bfmeAbortActiveSpecialAbilities() const;
	// TU-scoped public ABI spelling for the protected retail Object::findModule call.
	Module *findModule( NameKeyType key ) const;
	void bfmeRefreshCompletedUpgrades();

	void bfmeConv001C6E00( Object *object );

private:
	char m_pad00[0x90];
	UnsignedInt m_status;
	UnsignedInt m_bfmeStatus94;
	UnsignedInt m_bfmeStatus98;
	char m_pad9C[0x1fc - 0x9c];
	Rva001C6E00Interface *m_contain;
	char m_pad200[0x204 - 0x200];
	Team *m_team;
};

void Object::bfmeConv001C6E00( Object *object )
{
	static NameKeyType key = TheNameKeyGenerator->nameToKey( "TemporarilyDefectUpdate" );

	TemporarilyDefectUpdate *module =
		(TemporarilyDefectUpdate *)findModule( key );
	if ( module )
	{
		if ( !( m_bfmeStatus94 & 0x20 ) )
		{
			Team *team = m_team;
			if ( team )
			{
				if ( m_bfmeStatus98 & 0x20 )
					bfmeAbortActiveSpecialAbilities();
				team->bfmeSwapEW();
				team->bfmeConv1940194();
			}
		}

		module->bfmeTransferDefection( object, 0 );

		Rva001C6E00Interface *contain = m_contain;
		if ( contain )
			contain->bfmeSlot61( object );

		bfmeRefreshCompletedUpgrades();
	}
}
