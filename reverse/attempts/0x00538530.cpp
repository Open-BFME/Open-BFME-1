// ?rva00538530@BfmeAptScreenOnlineCustomMatch@@QAEXXZ
// partial score=0.9 date=2026-09-19
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
//
// BfmeAptScreenOnlineCustomMatch ping labels, retail 0x00538530, 279 bytes.
// The caller and the two format strings identify this as the Host and Join
// gadget ping update. The slot layout places the integer ping at +0x54.

#include "StringInline.h"

typedef bool Bool;

extern "C" void _ReadWriteBarrier( void );
#pragma intrinsic( _ReadWriteBarrier )

extern "C" __declspec(dllimport) int __cdecl sprintf(
	char *destination, const char *format, ... );

class GameSlot
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void *slot2() = 0;

	Bool isHuman() const;
};

class GameSpyGameSlot : public GameSlot
{
private:
	int m_profileID;
	AsciiString m_login;
	AsciiString m_locale;
	AsciiString m_pingString;
	int m_ping;
};

class GameSpyStagingRoom
{
public:
	GameSlot *getSlot( int index );
};

#define GAMESPY_SLOT( n ) virtual void gamespySlot##n() = 0
class GameSpyInfo
{
public:
	GAMESPY_SLOT( 0 ); GAMESPY_SLOT( 1 ); GAMESPY_SLOT( 2 ); GAMESPY_SLOT( 3 );
	GAMESPY_SLOT( 4 ); GAMESPY_SLOT( 5 ); GAMESPY_SLOT( 6 ); GAMESPY_SLOT( 7 );
	GAMESPY_SLOT( 8 ); GAMESPY_SLOT( 9 ); GAMESPY_SLOT( 10 ); GAMESPY_SLOT( 11 );
	GAMESPY_SLOT( 12 ); GAMESPY_SLOT( 13 ); GAMESPY_SLOT( 14 ); GAMESPY_SLOT( 15 );
	GAMESPY_SLOT( 16 ); GAMESPY_SLOT( 17 ); GAMESPY_SLOT( 18 ); GAMESPY_SLOT( 19 );
	GAMESPY_SLOT( 20 ); GAMESPY_SLOT( 21 ); GAMESPY_SLOT( 22 ); GAMESPY_SLOT( 23 );
	GAMESPY_SLOT( 24 ); GAMESPY_SLOT( 25 ); GAMESPY_SLOT( 26 ); GAMESPY_SLOT( 27 );
	GAMESPY_SLOT( 28 ); GAMESPY_SLOT( 29 ); GAMESPY_SLOT( 30 ); GAMESPY_SLOT( 31 );
	GAMESPY_SLOT( 32 ); GAMESPY_SLOT( 33 ); GAMESPY_SLOT( 34 ); GAMESPY_SLOT( 35 );
	GAMESPY_SLOT( 36 ); GAMESPY_SLOT( 37 ); GAMESPY_SLOT( 38 ); GAMESPY_SLOT( 39 );
	GAMESPY_SLOT( 40 ); GAMESPY_SLOT( 41 ); GAMESPY_SLOT( 42 ); GAMESPY_SLOT( 43 );
	GAMESPY_SLOT( 44 ); GAMESPY_SLOT( 45 ); GAMESPY_SLOT( 46 ); GAMESPY_SLOT( 47 );
	GAMESPY_SLOT( 48 );
	virtual GameSpyStagingRoom *getCurrentStagingRoom() = 0;
};
#undef GAMESPY_SLOT

extern GameSpyInfo *TheGameSpyInfo;

class BfmeThingBIF
{
public:
	void bfmeGoBIF( void *what, void *out );
};

extern BfmeThingBIF *Rva00579160TheManager;

class BfmeAptScreenPickByThreshold
{
public:
	void *pick( int value );
};

class BfmeAptGameWindow
{
public:
	virtual void slot0() = 0;

private:
	unsigned char m_unmodelled[ 0x30 ];
	BfmeAptScreenPickByThreshold *m_picker;
	unsigned char m_tail[ 4 ];

protected:
	BfmeAptScreenPickByThreshold *picker() { return m_picker; }
};

class BfmeAptScreenSecondary
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual Bool selectHostFormat() = 0;
};

class BfmeAptScreenOnlineCustomMatch : public BfmeAptGameWindow,
	public BfmeAptScreenSecondary
{
public:
	void rva00538530();
};

void BfmeAptScreenOnlineCustomMatch::rva00538530()
{
	GameSpyStagingRoom *room = 0;
	if ( TheGameSpyInfo )
		room = TheGameSpyInfo->getCurrentStagingRoom();
	if ( !room )
		return;

	const char *format;
	Bool hostFormat = selectHostFormat();
	_ReadWriteBarrier();
	format = (const char *)0x01107308;
	if ( !hostFormat )
		format = (const char *)0x01107334;
	for ( int i = 0; i < 8; ++i )
	{
		GameSlot *slot = room->getSlot( i );
		if ( !slot )
			continue;
		GameSpyGameSlot *gameSlot = (GameSpyGameSlot *)slot->slot2();
		char buffer[ 0x58 ];
		sprintf( buffer, format, 0 );
		void *image = 0;
		if ( slot->isHuman() )
			image = picker()->pick( *(int *)((char *)gameSlot + 0x54) );
		AsciiString label( buffer );
		Rva00579160TheManager->bfmeGoBIF( &label, image );
	}
}
