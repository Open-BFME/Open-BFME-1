// cl: /DNDEBUG /MD /EHsc
// GettingBuiltBehavior member at 0x001FF060 (242 B, ret at +0xF1 before int3
// padding). Identity: GettingBuiltBehavior::update (0x001FF880, matched in
// GettingBuiltBehavior_update.cpp) calls it on its own object through ILT
// 0x00036449 and sets the same +0x30 flag this body tests and clears; it sits
// between the GettingBuiltBehavior bodies 0x001FEC30 and ??_G 0x001FF190.
// Meaning unproven, so the name keeps the address. With the flag clear the
// owner's castle-member module (finder 0x0036BB10, check through ILT
// 0x0004B015) is consulted; otherwise the pending object (+0x7C id) must answer
// its AI update's slot 96 and differ from the +0x74 id. Either path raises
// model-condition bit 241 (word 7 of the +0x110 flags, 0x20000; the same
// test/set shape as AIMoveAndDeleteState_onEnter.cpp) and kills it with
// damage 8 death 0x16.

#include "../../../../Include/Common/ScalarTypes.h"

enum Relationship { ENEMIES = 2 };
enum DamageType { DAMAGE_UNRESISTABLE_8 = 8 };
enum DeathType { DEATH_0x16 = 0x16 };

class Object;
class Rva001FF060AIUpdate
{
public:
	virtual void slot0( void );
	virtual void slot1( void );
	virtual void slot2( void );
	virtual void slot3( void );
	virtual void slot4( void );
	virtual void slot5( void );
	virtual void slot6( void );
	virtual void slot7( void );
	virtual void slot8( void );
	virtual void slot9( void );
	virtual void slot10( void );
	virtual void slot11( void );
	virtual void slot12( void );
	virtual void slot13( void );
	virtual void slot14( void );
	virtual void slot15( void );
	virtual void slot16( void );
	virtual void slot17( void );
	virtual void slot18( void );
	virtual void slot19( void );
	virtual void slot20( void );
	virtual void slot21( void );
	virtual void slot22( void );
	virtual void slot23( void );
	virtual void slot24( void );
	virtual void slot25( void );
	virtual void slot26( void );
	virtual void slot27( void );
	virtual void slot28( void );
	virtual void slot29( void );
	virtual void slot30( void );
	virtual void slot31( void );
	virtual void slot32( void );
	virtual void slot33( void );
	virtual void slot34( void );
	virtual void slot35( void );
	virtual void slot36( void );
	virtual void slot37( void );
	virtual void slot38( void );
	virtual void slot39( void );
	virtual void slot40( void );
	virtual void slot41( void );
	virtual void slot42( void );
	virtual void slot43( void );
	virtual void slot44( void );
	virtual void slot45( void );
	virtual void slot46( void );
	virtual void slot47( void );
	virtual void slot48( void );
	virtual void slot49( void );
	virtual void slot50( void );
	virtual void slot51( void );
	virtual void slot52( void );
	virtual void slot53( void );
	virtual void slot54( void );
	virtual void slot55( void );
	virtual void slot56( void );
	virtual void slot57( void );
	virtual void slot58( void );
	virtual void slot59( void );
	virtual void slot60( void );
	virtual void slot61( void );
	virtual void slot62( void );
	virtual void slot63( void );
	virtual void slot64( void );
	virtual void slot65( void );
	virtual void slot66( void );
	virtual void slot67( void );
	virtual void slot68( void );
	virtual void slot69( void );
	virtual void slot70( void );
	virtual void slot71( void );
	virtual void slot72( void );
	virtual void slot73( void );
	virtual void slot74( void );
	virtual void slot75( void );
	virtual void slot76( void );
	virtual void slot77( void );
	virtual void slot78( void );
	virtual void slot79( void );
	virtual void slot80( void );
	virtual void slot81( void );
	virtual void slot82( void );
	virtual void slot83( void );
	virtual void slot84( void );
	virtual void slot85( void );
	virtual void slot86( void );
	virtual void slot87( void );
	virtual void slot88( void );
	virtual void slot89( void );
	virtual void slot90( void );
	virtual void slot91( void );
	virtual void slot92( void );
	virtual void slot93( void );
	virtual void slot94( void );
	virtual void slot95( void );
	virtual Bool isReadyForPendingMember( void );
};

struct ModelConditionFlags
{
	// Returns the masked word, not a bool: retail keeps the mask in a register
	// for the test and the set that follows.
	unsigned int test( int i ) const { return m_bits[i >> 5] & (1u << (i & 31)); }
	unsigned int m_bits[10];
};

// File-static so this TU does not emit a non-retail
// ?set@ModelConditionFlags@@QAEXH@Z COMDAT ahead of the bitset copy.
static inline void setModelConditionBit( ModelConditionFlags &flags, int i )
{
	flags.m_bits[i >> 5] |= (1u << (i & 31));
}

class Object
{
public:
	void bfmeSetModelConditionState( int bit )
	{
		if (!m_modelConditionFlags.test( bit ))
		{
			setModelConditionBit( m_modelConditionFlags, bit );
			notifyModelConditionChanged();
		}
	}

	Relationship getRelationship( const Object *other ) const;
	void notifyModelConditionChanged( void );
	void kill( DamageType damage, DeathType death );

	char m_unreconstructed00[ 0x74 ];
	int m_secondId;
	int m_unreconstructed78;
	int m_pendingId;
	char m_unreconstructed80[ 0x110 - 0x80 ];
	ModelConditionFlags m_modelConditionFlags;
	char m_unreconstructed138[ 0x204 - 0x138 ];
	Rva001FF060AIUpdate *m_ai;
};

class Module;

class CastleBehavior
{
public:
	Bool isPendingObjectUnavailable( void ) const;

	char m_unreconstructed00[ 0x14 ];
	void *m_live14;
	char m_unreconstructed18[ 0x24 - 0x18 ];
	unsigned char m_marked24;
};

Module *rva0036BB10FindCastleMemberBehavior( const Object *object );

class GameLogic
{
public:
	Object *findObjectByID( int id );
};

extern GameLogic *TheGameLogic;

class GettingBuiltBehavior
{
public:
	Bool rva001FF060( void );

private:
	char m_unreconstructed00[ 8 ];
	Object *m_object;
	char m_unreconstructed0C[ 0x30 - 0x0C ];
	Bool m_flag30;
};

static __forceinline void Rva001FF060ConditionAndKill( Object *target )
{
	target->bfmeSetModelConditionState( 241 );
	target->kill( DAMAGE_UNRESISTABLE_8, DEATH_0x16 );
}

// ?rva001FF060@GettingBuiltBehavior@@QAE_NXZ
Bool GettingBuiltBehavior::rva001FF060( void )
{
	Object *owner = m_object;
	if( !m_flag30 )
	{
		CastleBehavior *castle = (CastleBehavior *)rva0036BB10FindCastleMemberBehavior( owner );
		if( !( castle && castle->m_live14 && !castle->m_marked24 && castle->isPendingObjectUnavailable() ) )
		{
			Object *target = TheGameLogic->findObjectByID( owner->m_pendingId );
			if( target && target->getRelationship( owner ) != ENEMIES )
			{
				Rva001FF060ConditionAndKill( target );
				return true;
			}
			return false;
		}
	}
	Object *target = TheGameLogic->findObjectByID( owner->m_pendingId );
	if( target )
	{
		Rva001FF060AIUpdate *ai = target->m_ai;
		if( ai && ai->isReadyForPendingMember() && owner->m_pendingId != owner->m_secondId )
		{
			Rva001FF060ConditionAndKill( target );
			m_flag30 = 0;
		}
		return true;
	}
	m_flag30 = 0;
	return true;
}
