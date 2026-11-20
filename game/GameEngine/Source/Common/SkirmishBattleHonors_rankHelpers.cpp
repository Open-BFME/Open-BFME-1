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
	int m_pad[5];
	int m_rankPoints[9];
	int getPoints( AsciiString name ) const;
	int getRank( AsciiString name ) const;
};

int SkirmishBattleHonors::getRank( AsciiString name ) const
{
	int points = getPoints( name );
	int rank = 0;
	while ( rank < 9 && points >= m_rankPoints[rank] )
		++rank;
	return rank + 1;
}

