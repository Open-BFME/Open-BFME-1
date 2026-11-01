// ?rva00329FB0@ScriptConditions@@IAE_NPAVParameter@@_N@Z
// partial score=0.3055 date=2026-11-01
// ?rva00329FB0@ScriptConditions@@IAE_NPAVParameter@@_N@Z
// Retail: 491 bytes at 0x00329FB0, RET 8 at +0x1E8.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Include

// FILE: ScriptConditionsRva00329FB0.cpp //////////////////////////////////////
//
// Team form of the "members under attack by an unreachable attacker" test.
// The matched condition dispatcher (Rva0032D720Dispatcher.cpp) calls this
// body through ILT 0x000228C2 from cases 164 and 165 with the team parameter
// and a flag of 1 / 0. The condition's EA name is not proven, so the method
// keeps its address.
//
// Shape from the Open BFME 2 donor ScriptConditions::rva003EA228
// (ScriptConditions_evaluateTeamStateIs.cpp, donor revision 45afcff3; the
// same address-named team form there): per member, an idle-AI gate, damage
// within 25 frames by a living attacker, then the possible-to-attack filter
// and the reachability statics; the flag picks whether a failing member ends
// the walk true or a matching member ends it false. BFME 1 slots and offsets
// come from this body: AI +0x204 (slot 96 gate), body +0x200 (slots 15/16),
// dead byte +0x344, position +0x38, GameLogic frame +0x3C. Team, iterator,
// parameter and body views follow ScriptConditionsTeamAttackedByType.cpp; the
// filter follows AIGuardRetaliate.cpp.
//
///////////////////////////////////////////////////////////////////////////////

#include "ObjectDlinkPmf.h"
#include "ascii_string.h"
#include "Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Parameter
{
public:
	const AsciiString &getString( void ) const { return m_string; }
	unsigned char m_pad[ 0x10 ];
	AsciiString m_string;   // +0x10
};

class DamageInfo
{
public:
	unsigned char m_beforeSourceID[ 8 ];
	Int m_sourceID;   // this+0x08
};

class BodyModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual const DamageInfo *getLastDamageInfo() const;   // slot 15, vtable+0x3C
	virtual UnsignedInt getLastDamageTimestamp() const;     // slot 16, vtable+0x40
};

#define BFME_AI_SLOT( n ) virtual void unusedSlot##n();

class AIUpdateInterface
{
public:
	BFME_AI_SLOT( 0 ) BFME_AI_SLOT( 1 ) BFME_AI_SLOT( 2 ) BFME_AI_SLOT( 3 )
	BFME_AI_SLOT( 4 ) BFME_AI_SLOT( 5 ) BFME_AI_SLOT( 6 ) BFME_AI_SLOT( 7 )
	BFME_AI_SLOT( 8 ) BFME_AI_SLOT( 9 ) BFME_AI_SLOT( 10 ) BFME_AI_SLOT( 11 )
	BFME_AI_SLOT( 12 ) BFME_AI_SLOT( 13 ) BFME_AI_SLOT( 14 ) BFME_AI_SLOT( 15 )
	BFME_AI_SLOT( 16 ) BFME_AI_SLOT( 17 ) BFME_AI_SLOT( 18 ) BFME_AI_SLOT( 19 )
	BFME_AI_SLOT( 20 ) BFME_AI_SLOT( 21 ) BFME_AI_SLOT( 22 ) BFME_AI_SLOT( 23 )
	BFME_AI_SLOT( 24 ) BFME_AI_SLOT( 25 ) BFME_AI_SLOT( 26 ) BFME_AI_SLOT( 27 )
	BFME_AI_SLOT( 28 ) BFME_AI_SLOT( 29 ) BFME_AI_SLOT( 30 ) BFME_AI_SLOT( 31 )
	BFME_AI_SLOT( 32 ) BFME_AI_SLOT( 33 ) BFME_AI_SLOT( 34 ) BFME_AI_SLOT( 35 )
	BFME_AI_SLOT( 36 ) BFME_AI_SLOT( 37 ) BFME_AI_SLOT( 38 ) BFME_AI_SLOT( 39 )
	BFME_AI_SLOT( 40 ) BFME_AI_SLOT( 41 ) BFME_AI_SLOT( 42 ) BFME_AI_SLOT( 43 )
	BFME_AI_SLOT( 44 ) BFME_AI_SLOT( 45 ) BFME_AI_SLOT( 46 ) BFME_AI_SLOT( 47 )
	BFME_AI_SLOT( 48 ) BFME_AI_SLOT( 49 ) BFME_AI_SLOT( 50 ) BFME_AI_SLOT( 51 )
	BFME_AI_SLOT( 52 ) BFME_AI_SLOT( 53 ) BFME_AI_SLOT( 54 ) BFME_AI_SLOT( 55 )
	BFME_AI_SLOT( 56 ) BFME_AI_SLOT( 57 ) BFME_AI_SLOT( 58 ) BFME_AI_SLOT( 59 )
	BFME_AI_SLOT( 60 ) BFME_AI_SLOT( 61 ) BFME_AI_SLOT( 62 ) BFME_AI_SLOT( 63 )
	BFME_AI_SLOT( 64 ) BFME_AI_SLOT( 65 ) BFME_AI_SLOT( 66 ) BFME_AI_SLOT( 67 )
	BFME_AI_SLOT( 68 ) BFME_AI_SLOT( 69 ) BFME_AI_SLOT( 70 ) BFME_AI_SLOT( 71 )
	BFME_AI_SLOT( 72 ) BFME_AI_SLOT( 73 ) BFME_AI_SLOT( 74 ) BFME_AI_SLOT( 75 )
	BFME_AI_SLOT( 76 ) BFME_AI_SLOT( 77 ) BFME_AI_SLOT( 78 ) BFME_AI_SLOT( 79 )
	BFME_AI_SLOT( 80 ) BFME_AI_SLOT( 81 ) BFME_AI_SLOT( 82 ) BFME_AI_SLOT( 83 )
	BFME_AI_SLOT( 84 ) BFME_AI_SLOT( 85 ) BFME_AI_SLOT( 86 ) BFME_AI_SLOT( 87 )
	BFME_AI_SLOT( 88 ) BFME_AI_SLOT( 89 ) BFME_AI_SLOT( 90 ) BFME_AI_SLOT( 91 )
	BFME_AI_SLOT( 92 ) BFME_AI_SLOT( 93 ) BFME_AI_SLOT( 94 ) BFME_AI_SLOT( 95 )
	virtual Bool unusedSlot96() const;	// slot 96, vtable+0x180

	Bool isQuickPathAvailable( const Coord3D *destination ) const;
};

#define callMemberFunction( object, ptrToMember ) ( ( object ).*( ptrToMember ) )

template <class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *( OBJCLASS::*GetNextFunc )() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR( OBJCLASS *cur, GetNextFunc getNextFunc )
		: m_cur( cur ), m_getNextFunc( getNextFunc ) {}

	void advance()
	{
		if( m_cur )
			m_cur = callMemberFunction( *m_cur, m_getNextFunc )();
	}

	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

static inline BodyModuleInterface *rva329FB0_getBodyModule( const Object *obj )
{
	return *(BodyModuleInterface **)( (const char *)obj + 0x200 );
}

static inline AIUpdateInterface *rva329FB0_getAI( const Object *obj )
{
	return *(AIUpdateInterface **)( (const char *)obj + 0x204 );
}

static inline Bool rva329FB0_isEffectivelyDead( const Object *obj )
{
	return ( *( (const unsigned char *)obj + 0x344 ) & 1 ) != 0;
}

static inline const Coord3D *rva329FB0_getPosition( const Object *obj )
{
	return (const Coord3D *)( (const char *)obj + 0x38 );
}

class Team
{
public:
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;   // +0xC

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>( m_head, Object::dlink_next_TeamMemberList );
	}
};

class GameLogic
{
public:
	Object *findObjectByID( Int id );
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_pad_00[ 0x3C ];
	UnsignedInt m_frame;
};

class ScriptEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
	virtual Team *getTeamNamed( AsciiString name, Bool exact ); // slot 17, vtable+0x44
};

extern ScriptEngine *TheScriptEngine;
extern GameLogic *TheGameLogic;

// 0x0014CA60: the reachability static the donor calls AI::rva002FE193.
class BfmeOutOfWeaponRangeObject;
Bool rva0014ca60( BfmeOutOfWeaponRangeObject *a, BfmeOutOfWeaponRangeObject *b );

// PartitionFilter::allows at 0x009F2A70 keeps its ledger spelling.
class BfmeThingEQ
{
public:
	unsigned char bfmeAskEQ( void *object );
};

// Retail 0x010956C4 is recorded only as this datum; the filter's vptr store
// names it (the AIGuardRetaliate.cpp possible-to-attack filter writes the
// same vftable).
extern const void **g_010956C4;

class PartitionFilter
{
public:
	PartitionFilter() : m_next( 0 ) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow( Object * ) = 0;

	PartitionFilter *m_next;
};

class __declspec( novtable ) Rva00329FB0AttackFilter : public PartitionFilter
{
public:
	Rva00329FB0AttackFilter( Object *object, Int attackType, Int commandSource )
	{
		*reinterpret_cast<const void ***>( this ) = (const void **)&g_010956C4;
		m_object = object;
		m_attackType = attackType;
		m_commandSource = commandSource;
	}
	virtual ~Rva00329FB0AttackFilter() {}
	virtual Bool allow( Object * );

	Bool allows( Object *object ) { return ( (BfmeThingEQ *)this )->bfmeAskEQ( object ) != 0; }

private:
	Object *m_object;
	Int m_attackType;
	Int m_commandSource;
};

class ScriptConditions
{
protected:
	Bool rva00329FB0( Parameter *pTeamParm, Bool failingMemberWins );
};

Bool ScriptConditions::rva00329FB0( Parameter *pTeamParm, Bool failingMemberWins )
{
	Team *team = TheScriptEngine->getTeamNamed( pTeamParm->getString(), false );
	if( team )
	{
		Bool matched = false;
		Bool reachedFilter = false;
		for( DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance() )
		{
			Object *member = iter.cur();
			if( !failingMemberWins && matched )
				return false;
			AIUpdateInterface *ai = rva329FB0_getAI( member );
			if( !ai )
				continue;
			if( !ai->unusedSlot96() )
			{
				if( failingMemberWins )
					continue;
				return false;
			}
			BodyModuleInterface *body = rva329FB0_getBodyModule( member );
			if( !body )
				continue;
			UnsignedInt frame = TheGameLogic->getFrame();
			if( body->getLastDamageTimestamp() + 25 < frame )
				continue;
			const DamageInfo *info = body->getLastDamageInfo();
			if( !info )
				continue;
			Int id = info->m_sourceID;
			Object *attacker = TheGameLogic->findObjectByID( id );
			if( !attacker )
				continue;
			if( rva329FB0_isEffectivelyDead( attacker ) )
				continue;
			reachedFilter = true;
			Rva00329FB0AttackFilter filter( member, 2, 0 );
			if( filter.allows( attacker ) )
			{
				if( rva0014ca60( (BfmeOutOfWeaponRangeObject *)member, (BfmeOutOfWeaponRangeObject *)attacker ) )
				{
					matched = true;
					continue;
				}
				if( ai->isQuickPathAvailable( rva329FB0_getPosition( attacker ) ) )
				{
					matched = true;
					continue;
				}
			}
			if( failingMemberWins )
				return true;
		}
		if( failingMemberWins )
			return false;
		if( reachedFilter )
			return matched ? false : true;
	}
	return false;
}
