// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

#include "../../../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class AsciiString
{
public:
	AsciiString( const char *text ) : m_string( text ) {}

	StringBase<char> m_string;
};

class Rva000A19E0StateBase
{
public:
	Rva000A19E0StateBase( void *machine, AsciiString name );

	virtual void stateBaseAnchor();
};

class GiantBirdNormalFlightState : public Rva000A19E0StateBase
{
public:
	GiantBirdNormalFlightState( void *machine, bool initiallyActive );

private:
	char m_gap04[ 0x20 ];
	bool m_initiallyActive;
};

GiantBirdNormalFlightState::GiantBirdNormalFlightState( void *machine, bool initiallyActive )
	: Rva000A19E0StateBase( machine, AsciiString( "GiantBirdNormalFlightState" ) )
{
	m_initiallyActive = initiallyActive;
}

class AIGiantBirdAttackState : public Rva000A19E0StateBase
{
public:
	AIGiantBirdAttackState( void *machine, int mode );

private:
	char m_gap04[ 0x20 ];
	int m_mode;
};

AIGiantBirdAttackState::AIGiantBirdAttackState( void *machine, int mode )
	: Rva000A19E0StateBase( machine, AsciiString( "AIGiantBirdAttackState" ) )
{
	m_mode = mode;
}

class AIGiantBirdFollowThruState : public Rva000A19E0StateBase
{
public:
	AIGiantBirdFollowThruState( void *machine, bool enabled );

private:
	char m_gap04[ 0x20 ];
	bool m_enabled;
	char m_gap25[ 3 ];
	int m_counter;
};

AIGiantBirdFollowThruState::AIGiantBirdFollowThruState( void *machine, bool enabled )
	: Rva000A19E0StateBase( machine, AsciiString( "AIGiantBirdFollowThruState" ) )
{
	m_enabled = enabled;
	m_counter = 0;
}

class GiantBirdFollowWaypointPathState : public Rva000A19E0StateBase
{
public:
	GiantBirdFollowWaypointPathState( void *machine, bool enabled );

private:
	char m_gap04[ 0x20 ];
	int m_counter;
	bool m_enabled;
};

GiantBirdFollowWaypointPathState::GiantBirdFollowWaypointPathState( void *machine, bool enabled )
	: Rva000A19E0StateBase( machine, AsciiString( "GiantBirdFollowWaypointPathState" ) )
{
	m_enabled = enabled;
	m_counter = 0;
}

class AIGiantBirdSwoopState : public Rva000A19E0StateBase
{
public:
	AIGiantBirdSwoopState( void *machine, int targetID, bool enabled );

private:
	char m_gap04[ 0x20 ];
	int m_targetID;
	char m_gap28[ 0x0C ];
	bool m_enabled;
	char m_gap35[ 3 ];
	int m_counter;
	float m_scale;
};

AIGiantBirdSwoopState::AIGiantBirdSwoopState( void *machine, int targetID, bool enabled )
	: Rva000A19E0StateBase( machine, AsciiString( "AIGiantBirdSwoopState" ) )
{
	m_targetID = targetID;
	m_enabled = enabled;
	m_counter = 0;
	m_scale = 1.0f;
}
