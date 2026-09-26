// cl: /DNDEBUG /MD /EHsc
//
// ?_bfme_getInternetPlayerStatus@@QAEHABVUnicodeString@@@Z
// Retail 0x00513740. The APT callback checks the internet game mode, finds a
// connected occupied slot by display name, and reports its player state.

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

typedef int Int;
typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}

	int compare( const UnicodeString &other ) const throw()
	{
		return ((const StringBase<unsigned short> *)this)->compare(
			(const StringBase<unsigned short> &)other );
	}
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

class GameSlot
{
public:
	const GameSlot *getConstSlot( Int slotNum ) const;
	Bool isOccupied() const;
	UnicodeString getName() const;
};

class GameInfo
{
public:
	const GameSlot *getConstSlot( Int slotNum ) const;
};

extern GameInfo *TheGameInfo;

class NetworkInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual Bool isPlayerConnected( Int slotNum ) = 0;
};

extern NetworkInterface *TheNetwork;

class Rva00367E30Logic
{
private:
	char m_pad[ 0x10c ];

public:
	Int m_gameMode;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class Player;

class PlayerList
{
public:
	Player *findPlayerWithNameKey( NameKeyType key );
};

class Rva002EE330PlayerList : public PlayerList
{
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

class Player
{
public:
	Bool isPlayerObserver() const;
};

class VictoryConditionsInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual Bool hasSinglePlayerBeenDefeated( Player *player ) = 0;
};

extern VictoryConditionsInterface *TheVictoryConditions;

NameKeyType NAMEKEY( const AsciiString &name );

class Rva00513740Owner
{
public:
	int _bfme_getInternetPlayerStatus( const UnicodeString &name );
};

int Rva00513740Owner::_bfme_getInternetPlayerStatus( const UnicodeString &name )
{
	if( TheNetwork == 0 )
		return 0;
	if( TheBfmeGameLogic == 0 )
		return 0;
	if( TheBfmeGameLogic->m_gameMode != 5 )
		return 0;

	if( Rva002EE330ThePlayers == 0 )
		return 0;

	for( Int slotNum = 0; slotNum < 8; ++slotNum )
	{
		const GameSlot *slot = TheGameInfo->getConstSlot( slotNum );
		if( slot == 0 || !slot->isOccupied() )
			continue;

		UnicodeString slotName = slot->getName();
		if( name.compare( slotName ) != 0 )
			continue;

		if( !TheNetwork->isPlayerConnected( slotNum ) )
			return 0;

		AsciiString playerName(
			*(const AsciiString *)( (const char *)slot + 0x2c ) );
		Player *player = Rva002EE330ThePlayers->findPlayerWithNameKey(
			NAMEKEY( playerName ) );
		if( player == 0 )
			return 0;

		Bool alive = !TheVictoryConditions->hasSinglePlayerBeenDefeated( player );
		Bool observer = player->isPlayerObserver();
		Int result;
		if( alive && !observer )
			result = 1;
		else
			result = 2;
		return result;
	}

	return 0;
}
