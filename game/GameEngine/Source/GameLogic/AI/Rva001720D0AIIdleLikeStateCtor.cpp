// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x001720D0 constructs a State-derived object with the diagnostic name
// "AIIdleState".  Another retail body already owns the public AIIdleState
// constructor symbol, so this class name remains address-derived.

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

#include "ascii_string.h"

class Rva000A19E0StateBase
{
public:
	Rva000A19E0StateBase( void *machine, AsciiString name );

	virtual void stateBaseAnchor();
};

class Rva001720D0AIIdleLikeState : public Rva000A19E0StateBase
{
public:
	Rva001720D0AIIdleLikeState( void *machine, int targetingType );

private:
	char m_stateBaseTail[ 0x20 ];
	unsigned short m_goalPathIndex;
	bool m_shouldLookForTargets;
	bool m_initialized;
};

Rva001720D0AIIdleLikeState::Rva001720D0AIIdleLikeState(
	void *machine,
	int targetingType ) :
	Rva000A19E0StateBase( machine, AsciiString( "AIIdleState" ) )
{
	m_shouldLookForTargets = targetingType == 0;
	m_initialized = false;
	m_goalPathIndex = 0xFFFF;
}
