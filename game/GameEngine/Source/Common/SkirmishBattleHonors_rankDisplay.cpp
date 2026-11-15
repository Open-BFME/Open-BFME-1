// cl: /DNDEBUG /MD /EHsc

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


class UserPreferences
{
public:
	virtual void _bfme_slot0( void ) = 0;
	virtual void _bfme_slot1( void ) = 0;
	virtual void _bfme_slot2( void ) = 0;
	virtual void _bfme_slot3( void ) = 0;
	virtual void _bfme_slot4( void ) = 0;
	virtual void _bfme_slot5( void ) = 0;
	virtual AsciiString _bfme_getAsciiString( AsciiString key, AsciiString defaultValue ) const = 0;
	virtual void _bfme_setAsciiString( AsciiString key, AsciiString value ) = 0;
};

class SkirmishBattleHonors : public UserPreferences
{
public:
	int getRank( AsciiString name ) const;
	int getRankDisplay( AsciiString name ) const;
};

void __cdecl j_00043a59( void );

int SkirmishBattleHonors::getRankDisplay( AsciiString name ) const
{
	int rank = getRank( name );
	return ((int (__cdecl *)( int, AsciiString * ))j_00043a59)( rank, &name );
}
