// cl: /DNDEBUG /MD /EHs-c- /Iinputs/reference/shims/stringinline
// LivingWorld region RegionBonus callback at 0x0061A0A0, 54 bytes.
// Table 0x01116D70 stores the string RegionBonus at row 0x01116E00 next to
// this body, and the neighbouring rows ConnectsTo and ArmyPlacementPos hold
// the landed Rva0061AD20::parseConnections and Rva0061ACA0
// ::parseCoord2DVectorEntry, so the table is the region block. The class name
// history does not carry, so the class keeps this body's address.
//
// The body hands the token to the four-entry name lookup at 0x00619FF0, whose
// ledger row already cites this table row as its own evidence. INI member
// +0x41C is m_sepsColon, the separator set the INI constructor at 0x00851230
// fills with whitespace, equals and colon.
#include "StringInline.h"

class INI
{
public:
	char m_prefix[ 0x41c ];
	const char *m_colonSeparators;

	const char *getSepsColon( void ) { return m_colonSeparators; }
	const char *getNextTokenOrNull( const char *seps );
};

// ?Rva00619FF0LookupByName@@YAHABVAsciiString@@@Z
int __cdecl Rva00619FF0LookupByName( const AsciiString &name );

class Rva0061A0A0
{
public:
	static void parseRegionBonus( INI *, void *instance, void *store, const void *userData );
};

void Rva0061A0A0::parseRegionBonus( INI *ini, void *instance, void *store,
	const void *userData )
{
	*(int *)store = Rva00619FF0LookupByName(
		AsciiString( ini->getNextTokenOrNull( ini->getSepsColon() ) ) );
}
