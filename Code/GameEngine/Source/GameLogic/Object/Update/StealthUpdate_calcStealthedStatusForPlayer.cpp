// cl: /O2
// readable body of ?calcStealthedStatusForPlayer@StealthUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/StealthUpdate.cpp
// Retail 0x002AD150: StealthUpdate::calcStealthedStatusForPlayer.
// The BFME Object and StealthUpdate layouts used here are the retail layouts;
// the public ZH headers describe a different Object status/private-status
// arrangement and therefore cannot be used for this body.

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;

enum Relationship
{
	NEUTRAL = 1,
	ALLIES = 2
};

enum StealthLookType
{
	STEALTHLOOK_NONE = 0,
	STEALTHLOOK_VISIBLE_FRIENDLY = 1,
	STEALTHLOOK_DISGUISED_ENEMY = 2,
	STEALTHLOOK_VISIBLE_DETECTED = 3,
	STEALTHLOOK_VISIBLE_FRIENDLY_DETECTED = 4,
	STEALTHLOOK_INVISIBLE = 5
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Relationship getRelationship( const Team *that ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Team *getDefaultTeam() const
	{
		return *reinterpret_cast<Team * const *>( reinterpret_cast<const char *>( this ) + 0x230 );
	}
};

extern void j_000179bd();
typedef Bool (__fastcall *PlayerActiveCall)( const Player * );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool isEffectivelyDead() const
	{
		return ( *reinterpret_cast<const unsigned char *>( reinterpret_cast<const char *>( this ) + 0x344 ) ) & 1;
	}

	Bool testStealthed() const
	{
		return ( *reinterpret_cast<const unsigned int *>( reinterpret_cast<const char *>( this ) + 0x90 ) ) & 0x8000;
	}

	Bool testDetected() const
	{
		return ( *reinterpret_cast<const unsigned int *>( reinterpret_cast<const char *>( this ) + 0x90 ) ) & 0x20000;
	}

	Team *getTeam() const
	{
		return *reinterpret_cast<Team * const *>( reinterpret_cast<const char *>( this ) + 0x23c );
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StealthUpdate.h
class StealthUpdateModuleData
{
public:
	unsigned char m_pad[ 0x2c ];
	Bool m_teamDisguised;
	unsigned char m_pad2[ 0x52 - 0x2d ];
	Bool m_disguiseDetected;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StealthUpdate.h
class StealthUpdate
{
protected:
	StealthLookType calcStealthedStatusForPlayer( const Object *obj, const Player *player );

public:
	__declspec(dllexport) __declspec(noinline) static StealthLookType probeCall( StealthUpdate *self, const Object *obj, const Player *player );

private:
	void *m_vtable;
	StealthUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad[ 0x38 - 0xc ];
	UnsignedInt m_disguised;
};

typedef StealthLookType (__cdecl *StealthUpdateProbeCall)( StealthUpdate *, const Object *, const Player * );
volatile StealthUpdateProbeCall forceStealthUpdateCalc = &StealthUpdate::probeCall;

__declspec(dllexport) __declspec(noinline) StealthLookType StealthUpdate::probeCall( StealthUpdate *self, const Object *obj, const Player *player )
{
	return self->calcStealthedStatusForPlayer( obj, player );
}

// ?calcStealthedStatusForPlayer@StealthUpdate@@IAE?AW4StealthLookType@@PBVObject@@PBVPlayer@@@Z
StealthLookType StealthUpdate::calcStealthedStatusForPlayer( const Object *obj, const Player *player )
{
	if ( !( ( *reinterpret_cast<const unsigned char *>( reinterpret_cast<const char *>( obj ) + 0x344 ) ) & 1 ) &&
		( *reinterpret_cast<const unsigned int *>( reinterpret_cast<const char *>( obj ) + 0x90 ) & 0x8000 ) )
	{
		const Team *team = *reinterpret_cast<Team * const *>( reinterpret_cast<const char *>( obj ) + 0x23c );
		Relationship r = team
			? team->getRelationship( *reinterpret_cast<Team * const *>( reinterpret_cast<const char *>( player ) + 0x230 ) )
			: NEUTRAL;

		if ( !( (PlayerActiveCall)j_000179bd )( player ) )
			r = ALLIES;

		if ( *reinterpret_cast<const unsigned char *>( reinterpret_cast<const char *>( m_moduleData ) + 0x2c ) )
		{
			if ( r != ALLIES && m_disguised )
				return STEALTHLOOK_DISGUISED_ENEMY;
			return STEALTHLOOK_NONE;
		}

		if ( *reinterpret_cast<const unsigned int *>( reinterpret_cast<const char *>( obj ) + 0x90 ) & 0x20000 )
		{
			if ( *reinterpret_cast<const unsigned char *>( reinterpret_cast<const char *>( m_moduleData ) + 0x52 ) )
				return STEALTHLOOK_NONE;
			return r == ALLIES ? STEALTHLOOK_VISIBLE_FRIENDLY_DETECTED : STEALTHLOOK_VISIBLE_DETECTED;
		}

		return r == ALLIES ? STEALTHLOOK_VISIBLE_FRIENDLY : STEALTHLOOK_INVISIBLE;
	}
	return STEALTHLOOK_NONE;
}
