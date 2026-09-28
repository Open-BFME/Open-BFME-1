// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x001EC8E0: WeaponSet::getAbleToAttackSpecificObject (BFME four-argument
// form, no specificSlot).  Identity: the matched Object::getAbleToAttackSpecificObject
// (ObjectGetAbleToAttackSpecificObjectBFME.cpp) makes Zero Hour's
// m_weaponSet.getAbleToAttackSpecificObject(attackType, this, target, commandSource)
// call through ILT 0x000291D6, which jumps here.  The body is Zero Hour's
// WeaponSet.cpp sanity/stealth/relationship/container checks with BFME
// additions, and it forwards to the matched getAbleToUseWeaponAgainstTarget
// (0x001EBEB0) with the victim's position.  The StealthUpdate module key is a
// function-local static, which is what buys the SEH frame.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum AbleToAttackType
{
	_ATTACK_FORCED = 0x01
};

inline Bool isForcedAttack( AbleToAttackType t ) { return ( ( (Int)t ) & _ATTACK_FORCED ) != 0; }

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 2
};

enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum KindOfType
{
	KINDOF_2 = 2,
	KINDOF_7 = 7,
	KINDOF_UNATTACKABLE = 0x35,
	KINDOF_36 = 0x36,
	KINDOF_DISGUISER = 0x57,
	KINDOF_5D = 0x5D,
	KINDOF_8B = 0x8B
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

struct Coord3D
{
	float x, y, z;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Team;

class Player
{
public:
	Relationship getRelationship( const Team *team ) const;
	Team *getDefaultTeam() const { return m_defaultTeam; }

private:
	unsigned char m_pad[ 0x230 ];
	Team *m_defaultTeam;			// +0x230
};

class PlayerList
{
public:
	Player *getNthPlayer( Int i );
};

extern PlayerList *ThePlayerList;

class Team
{
public:
	Relationship getRelationship( const Team *that ) const;
};

class AIInnerData
{
public:
	unsigned char m_pad[ 0xB8 ];
	Bool m_flagB8;
};

class AI
{
public:
	unsigned char m_pad[ 0x14 ];
	AIInnerData *m_data14;
};

extern AI *TheAI;

class Module;

class StealthUpdate
{
public:
	Int getDisguisedPlayerIndex() const { return m_disguisedPlayerIndex; }
	Bool isDisguised() const { return m_disguised != 0; }

private:
	unsigned char m_pad[ 0x34 ];
	Int m_disguisedPlayerIndex;		// +0x34
	Int m_disguised;				// +0x38
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual const Player *getApparentControllingPlayer( const Player *observingPlayer ) const;
};

class WeaponTemplate
{
public:
	Bool bfmeAllowsRelationship( Int kind, void *weapon ) const;
};

class Weapon
{
public:
	unsigned char m_pad[ 4 ];
	const WeaponTemplate *m_template;	// +0x04
};

class WordBitTest000D2F40
{
public:
	Bool test( UnsignedInt bit ) const;
};

class Thing
{
public:
	Bool isKindOf( KindOfType t ) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Bool testStatus( Int bit ) const;
	Player *getControllingPlayer() const;
	Bool isStealthedAndUndetected( const Player *viewer ) const;
	Relationship getRelationship( const Object *that ) const;
	void *find( Int index );
	Bool isEffectivelyDead() const { return ( m_privateStatus & 1 ) != 0; }
	Bool isDestroyed() const { return ( m_status & 1 ) != 0; }
	Bool testScriptStatusBit( Int bit ) const { return ( m_scriptStatus & bit ) != 0; }
	const Object *getContainedBy() const { return m_containedBy; }
	ContainModuleInterface *getContain() const { return m_contain; }
	Team *getTeam() const { return m_team; }
	const Coord3D *getPosition() const { return &m_position; }
	StealthUpdate *getStealth( NameKeyType key ) const { return (StealthUpdate *)findModule( key ); }
	const WordBitTest000D2F40 *getBits110() const { return &m_field110; }

protected:
	Module *findModule( NameKeyType key ) const;

private:
	unsigned char m_pad00[ 0x38 ];
	Coord3D m_position;					// +0x38
	unsigned char m_pad44[ 0x90 - 0x44 ];
	UnsignedInt m_status;				// +0x90
	unsigned char m_pad94[ 0x110 - 0x94 ];
	WordBitTest000D2F40 m_field110;		// +0x110
	unsigned char m_pad_script[ 0x1FC - 0x111 ];
	ContainModuleInterface *m_contain;	// +0x1FC
	unsigned char m_pad200[ 0x214 - 0x200 ];
	const Object *m_containedBy;			// +0x214
	unsigned char m_pad218[ 0x23C - 0x218 ];
	Team *m_team;						// +0x23C
	unsigned char m_pad240[ 0x343 - 0x240 ];
	unsigned char m_scriptStatus;		// +0x343
	unsigned char m_privateStatus;		// +0x344
	unsigned char m_field345;			// +0x345

	friend class WeaponSet;
};

class WeaponSet
{
public:
	CanAttackResult getAbleToAttackSpecificObject( AbleToAttackType attackType, const Object *source,
		const Object *victim, CommandSourceType commandSource ) const;
	CanAttackResult getAbleToUseWeaponAgainstTarget( AbleToAttackType attackType, const Object *source,
		const Object *victim, const Coord3D *pos, CommandSourceType commandSource ) const;
};

CanAttackResult WeaponSet::getAbleToAttackSpecificObject( AbleToAttackType attackType, const Object *source,
	const Object *victim, CommandSourceType commandSource ) const
{
	static NameKeyType key_StealthUpdate = TheNameKeyGenerator->nameToKey( "StealthUpdate" );

	// basic sanity checks.
	if (!source ||
			!victim ||
			source->isEffectivelyDead() ||
			victim->isEffectivelyDead() ||
			source->isDestroyed() ||
			victim->isDestroyed() ||
			victim == source)
		return ATTACKRESULT_NOT_POSSIBLE;

	if (victim->testStatus( 0x32 ))
		return ATTACKRESULT_NOT_POSSIBLE;

	Bool sameOwnerForceAttack = ((source->getControllingPlayer() == victim->getControllingPlayer()) && isForcedAttack( attackType ));

	Int ignoring = 0;
	if (source->testStatus( 0x24 ))
		ignoring = 1;
	if (victim->m_field345 & ~ignoring)
		return ATTACKRESULT_NOT_POSSIBLE;

	if (victim->isKindOf( KINDOF_UNATTACKABLE ))
		return ATTACKRESULT_NOT_POSSIBLE;

	if (victim->testStatus( 0x3B ))
		return ATTACKRESULT_NOT_POSSIBLE;

	if (victim->testStatus( 0x1A ) && commandSource == CMD_FROM_AI)
		return ATTACKRESULT_NOT_POSSIBLE;

	Bool allowStealthToPreventAttacks = true;
	if (source->testStatus( 0x1B ) || sameOwnerForceAttack)
		allowStealthToPreventAttacks = false;
	if (isForcedAttack( attackType ) && victim->isKindOf( KINDOF_DISGUISER ))
	{
		StealthUpdate *update = victim->getStealth( key_StealthUpdate );
		if (update && update->isDisguised())
			allowStealthToPreventAttacks = false;
	}

	if (allowStealthToPreventAttacks && victim->isStealthedAndUndetected( source->getControllingPlayer() ))
	{
		if (!victim->isKindOf( KINDOF_DISGUISER ))
		{
			return ATTACKRESULT_NOT_POSSIBLE;
		}
		else
		{
			StealthUpdate *update = victim->getStealth( key_StealthUpdate );
			if (update && update->isDisguised())
			{
				Player *ourPlayer = source->getControllingPlayer();
				Player *otherPlayer = ThePlayerList->getNthPlayer( update->getDisguisedPlayerIndex() );
				if (ourPlayer && otherPlayer)
				{
					if (ourPlayer->getRelationship( otherPlayer->getDefaultTeam() ) != ENEMIES)
						return ATTACKRESULT_NOT_POSSIBLE;
				}
			}
		}
	}

	Bool reject = false;
	if (victim->isKindOf( KINDOF_36 ) && victim->isKindOf( KINDOF_2 ))
	{
		if (source->isKindOf( KINDOF_8B ) && source->getBits110()->test( 0x10C ))
			reject = true;
		Weapon *weapon = (Weapon *)((Object *)source)->find( 0 );
		if (weapon && weapon->m_template->bfmeAllowsRelationship( 6, weapon ))
			reject = true;
	}

	Relationship r = reject ? ENEMIES : source->getRelationship( victim );

	if (source->isKindOf( KINDOF_36 ))
	{
		if (r == ALLIES)
			return ATTACKRESULT_NOT_POSSIBLE;
		if (!victim->isKindOf( KINDOF_7 ))
			return ATTACKRESULT_NOT_POSSIBLE;
	}
	else if (!(victim->isKindOf( KINDOF_5D ) && TheAI->m_data14->m_flagB8) &&
			r != ENEMIES &&
			!isForcedAttack( attackType ) &&
			!reject)
	{
		if (commandSource == CMD_FROM_PLAYER && !victim->testScriptStatusBit( 0x10 ))
			return ATTACKRESULT_NOT_POSSIBLE;
	}

	const Object *victimsContainer = victim->getContainedBy();
	ContainModuleInterface *containerContain = victimsContainer ? victimsContainer->getContain() : 0;
	if (victim->testStatus( 0x3B ))
	{
		if (!containerContain ||
				source->getContainedBy() != victimsContainer ||
				!victim->testStatus( 0x24 ) ||
				!source->testStatus( 0x24 ))
			return ATTACKRESULT_NOT_POSSIBLE;
	}

	if (!isForcedAttack( attackType ))
	{
		const ContainModuleInterface *victimContain = victim->getContain();
		if (victimContain)
		{
			const Player *victimApparentController = victimContain->getApparentControllingPlayer( source->getControllingPlayer() );
			if (victimApparentController && source->getTeam()->getRelationship( victimApparentController->getDefaultTeam() ) != ENEMIES)
			{
				if (commandSource == CMD_FROM_PLAYER && !victim->testScriptStatusBit( 0x10 ))
					return ATTACKRESULT_NOT_POSSIBLE;
			}
		}
	}

	return getAbleToUseWeaponAgainstTarget( attackType, source, victim, victim->getPosition(), commandSource );
}
