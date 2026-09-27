// ?customMatchGameListTooltip@@YAXPAVGameWindow@@PAVWinInstanceData@@I@Z
// partial score=0.95 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BfmeAptScreenOnlineCustomMatch::customMatchGameListTooltip, retail 0x0053A280, 634 bytes.
// Identity: callback installed by the landed OnlineCustomMatch onInitGadget body.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	struct Header
	{
		Int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[ 1 ];
	};

	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	Header *m_data;

public:
	void concat( const T *text, Int length );
};

class UnicodeString;

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	~AsciiString() {}

	void translate( const UnicodeString &text );
	const char *str() const { return m_data ? m_data->data : ""; }
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<WideChar>( other ) {}
	UnicodeString( const WideChar *text ) : StringBase<WideChar>( text ) {}
	~UnicodeString() {}

	const WideChar *str() const { return m_data ? m_data->data : L""; }
	Int getLength() const { return m_data ? m_data->length : 0; }
	Bool isEmpty() const { return getLength() == 0; }
	UnicodeString &operator+=( const WideChar *text );
	UnicodeString &operator+=( const UnicodeString &other )
	{
		((StringBase<WideChar> *)this)->concat( other.str(), other.getLength() );
		return *this;
	}
	void __cdecl format( UnicodeString fmt, ... );
};

class WinInstanceData;
class GameWindow;
class RGBColor;

class Mouse
{
public:
	void setCursorTooltip( UnicodeString text, Int delay, const RGBColor *color, float width );
};

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 );
};

class GameSpyStagingRoom;

struct StagingRoomMapNode
{
	unsigned char links[ 0x14 ];
	GameSpyStagingRoom *room;
};

struct StagingRoomMapIterator
{
	StagingRoomMapIterator( const StagingRoomMapIterator &other );
	StagingRoomMapNode *node;
};

struct StagingRoomMap
{
	StagingRoomMapNode *header;
	StagingRoomMapIterator find( const Int &key );
};

class GameSlot
{
public:
	Bool isHuman() const;
	UnicodeString getName() const;
};

class GameInfo
{
public:
	GameSlot *getSlot( Int index );
};

class GameSpyStagingRoom : public GameInfo
{
};

class PlayerInfo
{
public:
	AsciiString name;
	AsciiString locale;
	AsciiString extra;
	Int wins;
	Int losses;
};

class GameSpyInfo
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0; virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0; virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0; virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0; virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0; virtual void slot48() = 0;
	virtual PlayerInfo *findPlayerName( const char *name );
	virtual void slot50() = 0; virtual void slot54() = 0; virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0; virtual void slot64() = 0; virtual void slot68() = 0; virtual void slot6C() = 0;
	virtual void slot70() = 0; virtual void slot74() = 0; virtual void slot78() = 0; virtual void slot7C() = 0;
	virtual void slot80() = 0; virtual void slot84() = 0; virtual void slot88() = 0; virtual void slot8C() = 0;
	virtual void slot90() = 0; virtual void slot94() = 0;
	virtual StagingRoomMap *getStagingRoomList();
};

extern Mouse *TheMouse;
extern GameTextInterface *TheGameText;
extern GameSpyInfo *TheGameSpyInfo;

Int GadgetListBoxGetEntryBasedOnXY( GameWindow *window, Int x, Int y, Int &row, Int &column );
void *GadgetListBoxGetItemData( GameWindow *window, Int row, Int column );

#define LOLONGTOSHORT(a) ((a) & 0x0000FFFF)
#define HILONGTOSHORT(a) (((a) & 0xFFFF0000) >> 16)

void customMatchGameListTooltip( GameWindow *window, WinInstanceData *, UnsignedInt mouse )
{
	Int x;
	Int y;
	Int row;
	Int column;
	x = LOLONGTOSHORT( mouse );
	y = HILONGTOSHORT( mouse );
	GadgetListBoxGetEntryBasedOnXY( window, x, y, row, column );

	if ( row == -1 )
		return;

	if ( column == 0 )
	{
		if ( (Int)GadgetListBoxGetItemData( window, row, 1 ) != 1 )
			return;
		TheMouse->setCursorTooltip( TheGameText->fetch( "TOOLTIP:PasswordIcon" ), -1, 0, 1.0f );
		return;
	}

	StagingRoomMap *rooms = TheGameSpyInfo->getStagingRoomList();
	StagingRoomMapIterator it = rooms->find(
		(Int)GadgetListBoxGetItemData( window, row, 0 ) );
	StagingRoomMapNode *header = rooms->header;
	if ( it.node == header )
		return;

	GameSpyStagingRoom *room = it.node->room;
	UnicodeString tooltip;
	for ( Int i = 0; i < 8; ++i )
	{
		GameSlot *slot = room->getSlot( i );
		if ( !slot->isHuman() )
			continue;

		if ( !tooltip.isEmpty() )
			tooltip += L"\n";
		tooltip += slot->getName();

		AsciiString player;
		player.translate( slot->getName() );
		PlayerInfo *info = TheGameSpyInfo->findPlayerName( player.str() );
		if ( info )
		{
			UnicodeString rating;
			rating.format( UnicodeString( L" (%d/%d)" ), info->wins, info->losses );
			tooltip += rating;
		}
	}

	TheMouse->setCursorTooltip( tooltip, -1, 0, 1.0f );
}
