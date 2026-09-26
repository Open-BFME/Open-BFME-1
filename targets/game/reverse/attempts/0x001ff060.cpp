// ?killPendingCastleMember@Rva001FF060Behavior@@QAE_NXZ
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: a castle-member behaviour method at 0x001FF060 (242 B).  The
// module owns an object (+8) whose +0x7C holds the pending member's id and
// +0x74 a second id; the module's flag byte at +0x30 selects the path.  With
// the flag clear the owner's castle-member behaviour (finder 0x0036BB10) is
// consulted: unless it is live (+0x14) not marked (+0x24) and reports the
// pending object unavailable the pending object is looked up its relationship
// to the owner must not be ENEMIES the 0x20000 model-condition bit is raised
// (notifyModelConditionChanged) and it is killed with damage 8 death 0x16
// (returns true; false when the object is missing or an enemy).  Otherwise
// the pending object's AI update (+0x204) must answer virtual slot 96 and the
// two ids must differ before the same condition-and-kill; the flag is then
// cleared and true returned in every case of that path.  Address-derived
// names.

typedef bool Bool;

enum Relationship { ENEMIES = 2 };
enum DamageType { DAMAGE_UNRESISTABLE_8 = 8 };
enum DeathType { DEATH_0x16 = 0x16 };

class Object;
class Module;

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

class Object
{
public:
	Relationship getRelationship( const Object *other ) const;
	void notifyModelConditionChanged( void );
	void kill( DamageType damage, DeathType death );

	char m_unreconstructed00[ 0x74 ];
	int m_secondId;
	int m_unreconstructed78;
	int m_pendingId;
	char m_unreconstructed80[ 0x12C - 0x80 ];
	unsigned int m_modelCondition12C;
	char m_unreconstructed130[ 0x204 - 0x130 ];
	Rva001FF060AIUpdate *m_ai;
};

class CastleBehavior
{
public:
	Bool isPendingObjectUnavailable( void ) const;

	char m_unreconstructed00[ 0x14 ];
	void *m_live14;
	char m_unreconstructed18[ 0x24 - 0x18 ];
	unsigned char m_marked24;
};

CastleBehavior *rva0036BB10FindCastleMemberBehavior( const Object *object );

class GameLogic
{
public:
	Object *findObjectByID( int id );
};

extern GameLogic *TheGameLogic;

class Rva001FF060Behavior
{
public:
	Bool killPendingCastleMember( void );

private:
	char m_unreconstructed00[ 8 ];
	Object *m_owner;
	char m_unreconstructed0C[ 0x30 - 0x0C ];
	unsigned char m_flag30;
};

static __forceinline void Rva001FF060ConditionAndKill( Object *target )
{
	unsigned int bit = 0x20000;
	if( !( target->m_modelCondition12C & bit ) )
	{
		target->m_modelCondition12C |= bit;
		target->notifyModelConditionChanged();
	}
	target->kill( DAMAGE_UNRESISTABLE_8, DEATH_0x16 );
}

// ?killPendingCastleMember@Rva001FF060Behavior@@QAE_NXZ
Bool Rva001FF060Behavior::killPendingCastleMember( void )
{
	Object *owner = m_owner;
	if( !m_flag30 )
	{
		CastleBehavior *castle = rva0036BB10FindCastleMemberBehavior( owner );
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
		if( !ai )
			return true;
		if( !ai->isReadyForPendingMember() )
			return true;
		if( owner->m_pendingId == owner->m_secondId )
			return true;
		Rva001FF060ConditionAndKill( target );
	}
	m_flag30 = 0;
	return true;
}
