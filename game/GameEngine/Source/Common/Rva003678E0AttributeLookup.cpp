// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// The data table at 0x012B4040 starts with ATTRIBUTE_NONE, then ARMOR and the
// remaining attribute names, and ends with a null pointer.  The body performs
// a case-sensitive scan and returns the zero-based entry, falling back to the
// ATTRIBUTE_NONE value.  The owner and method name remain descriptive because
// no trustworthy class identity is available.

#include <string.h>

// Retail .data 0x012B4040: 18 name pointers and a terminating null (76 bytes),
// read from the retail image.
const char *Rva003678E0AttributeNames[] =
{
	"ATTRIBUTE_NONE",
	"ARMOR",
	"DAMAGE_ADD",
	"DAMAGE_MULT",
	"RESIST_FEAR",
	"EXPERIENCE",
	"RANGE",
	"SPEED",
	"CRUSH_DECELERATE",
	"RESIST_KNOCKBACK",
	"SPELL_DAMAGE",
	"RECHARGE_TIME",
	"PRODUCTION",
	"HEALTH",
	"VISION",
	"BOUNTY_PERCENTAGE",
	"MINIMUM_CRUSH_VELOCITY",
	"AUTO_HEAL",
	NULL
};

class Rva003678E0AttributeLookup
{
public:
	int find( const char *name ) const;
};

int Rva003678E0AttributeLookup::find( const char *name ) const
{
	for( int attribute = 0; Rva003678E0AttributeNames[ attribute ]; ++attribute )
	{
		if( strcmp( Rva003678E0AttributeNames[ attribute ], name ) == 0 )
			return attribute;
	}

	return 0;
}
