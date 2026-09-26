// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x0036F2D0, 403 bytes through the int3 run at +0x193; Ghidra split it
// at the null-player exit (+0x3B).  W3DRadar::renderObjectList calls it through
// ILT 0x0002E8D4.  It walks the 12-byte records of the module data's vector at
// +0x60 (two AsciiStrings and a Real), copying each, and returns the Real of
// the first whose leading name equals the player's name at +0x28; 0 otherwise.
// The method keeps the address.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

#include "ascii_string.h"

typedef float Real;
typedef int Int;

class Player
{
public:
	char m_unmodelled00[ 0x28 ];
	AsciiString m_playerName;
};

struct Rva0036F2D0Record
{
	AsciiString m_name;
	AsciiString m_other;
	Real m_value;
};

class CastleBehaviorModuleData
{
public:
	char m_unmodelled00[ 0x60 ];
	_STL::vector<Rva0036F2D0Record> m_records;
};

class CastleBehavior
{
public:
	Real rva0036F2D0( const Player *player );
private:
	void *m_vptr;
	const CastleBehaviorModuleData *m_moduleData;
};

Real CastleBehavior::rva0036F2D0( const Player *player )
{
	if( player == 0 )
		return 0.0f;

	const CastleBehaviorModuleData *data = m_moduleData;
	Int count = data->m_records.size();
	for( Int i = 0; i < count; ++i )
	{
		Rva0036F2D0Record record = data->m_records[ i ];
		if( record.m_name.compare( player->m_playerName ) == 0 )
			return record.m_value;
	}

	return 0.0f;
}
