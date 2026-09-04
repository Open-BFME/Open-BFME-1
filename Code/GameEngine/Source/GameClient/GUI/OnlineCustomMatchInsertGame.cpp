// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenOnlineCustomMatch::insertGame, retail 0x0053F210, 911 bytes.
// Apt ZH LobbyUtils::insertGame twin: listbox at this+0x18C, ret 4. Name
// column 1, players 2, password 0, ping 3. Full-game uses GameInfo
// _bfme_getMapIsOfficial (not getMaxPlayers). CRC trio through
// AptLivingWorldWindowIndex(gd+0xBD0, gd+0xBD0) vs room+0x430 then
// +0x434/+0xBC8 and +0x438/+0xBD4. Ping image via picker at this+0x34.

template <typename T> struct StringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_max;
	T m_text[ 1 ];
};

class UnicodeString;

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringData<T> *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}

	void format( UnicodeString fmt, ... );

	int getLength() const
	{
		return m_data ? m_data->m_length : 0;
	}

	const unsigned short *str() const
	{
		return m_data ? m_data->m_text : (const unsigned short *)L"";
	}
};

class GameWindow;
class Image
{
public:
	int getImageWidth() const { return m_width; }
	int getImageHeight() const { return m_height; }

private:
	unsigned char m_pad[ 0x24 ];
	int m_width;
	int m_height;
};

class GameInfo
{
public:
	int getNumNonObserverPlayers() const;
	int getNumPlayers() const;
	int _bfme_getMapIsOfficial() const;
};

class GameSpyStagingRoom : public GameInfo
{
public:
	void cleanUpSlotPointers();
	UnicodeString getGameName();
	int getID() const { return m_id; }
	int getPingAsInt() const { return m_ping; }
	int getReportedNumPlayers() const { return m_num; }
	int getReportedMaxPlayers() const { return m_max; }
	unsigned char getHasPassword() const { return m_hasPassword; }
	unsigned int getExeCRC() const { return m_exeCRC; }
	unsigned int getIniCRC() const { return m_iniCRC; }
	unsigned int getVersion() const { return m_version; }

private:
	unsigned char m_head[ 0x41C ];
	int m_id;
	unsigned char m_mid[ 0x428 - 0x420 ];
	unsigned char m_hasPassword;
	unsigned char m_crcPad[ 0x430 - 0x429 ];
	unsigned int m_exeCRC;
	unsigned int m_iniCRC;
	unsigned int m_version;
	unsigned char m_pingPad[ 0x44C - 0x43C ];
	int m_ping;
	unsigned char m_numPad[ 0x454 - 0x450 ];
	int m_num;
	int m_max;
};

class BfmeAptScreenPickByThreshold
{
public:
	void *pick( int value );
};

int GadgetListBoxGetNumColumns( GameWindow *listbox );
void GadgetListBoxSetColumnWidths( GameWindow *listbox, int count, int *widths );
int GadgetListBoxAddEntryText( GameWindow *listbox, UnicodeString text, int color,
	int row, int column, bool overwrite );
int GadgetListBoxAddEntryImage( GameWindow *listbox, const Image *image,
	int row, int column, int width, int height, bool overwrite, int color );
void GadgetListBoxSetItemData( GameWindow *listbox, void *data, int row, int column );
int AptLivingWorldWindowIndex( int low, int high );

extern int GameSpyColor[];

enum
{
	GSCOLOR_GAME = 3,
	GSCOLOR_GAME_FULL = 4,
	GSCOLOR_GAME_CRCMISMATCH = 5
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
	GAMESPY_SLOT( 48 ); GAMESPY_SLOT( 49 ); GAMESPY_SLOT( 50 ); GAMESPY_SLOT( 51 );
	GAMESPY_SLOT( 52 ); GAMESPY_SLOT( 53 ); GAMESPY_SLOT( 54 );
	virtual bool getDisallowAsianText() = 0;
	virtual bool getDisallowNonAsianText() = 0;
};
#undef GAMESPY_SLOT

extern GameSpyInfo *TheGameSpyInfo;

class GlobalData
{
public:
	unsigned char m_pad[ 0xBC8 ];
	unsigned int m_iniCRC;
	unsigned char m_gap[ 4 ];
	unsigned int m_exeCRC;
	unsigned int m_extraCRC;
};

extern GlobalData *TheWritableGlobalData;

class BfmeAptScreenOnlineCustomMatch
{
public:
	int insertGame( GameSpyStagingRoom *game );

private:
	unsigned char m_head[ 0x34 ];
	BfmeAptScreenPickByThreshold *m_picker;
	unsigned char m_mid[ 0x18C - 0x38 ];
	GameWindow *m_listbox;
	unsigned char m_gap[ 0x1B0 - 0x190 ];
	Image *m_passwordImage;
};

int BfmeAptScreenOnlineCustomMatch::insertGame( GameSpyStagingRoom *game )
{
	GameWindow *win = m_listbox;
	int widths[ 4 ] = { 7, 0x49, 0xB, 0xD };
	if( GadgetListBoxGetNumColumns( win ) < 4 )
		GadgetListBoxSetColumnWidths( win, 4, widths );

	game->cleanUpSlotPointers();
	int gameColor = GameSpyColor[ GSCOLOR_GAME ];
	int nonObs = game->getNumNonObserverPlayers();
	if( nonObs == game->_bfme_getMapIsOfficial() || game->getNumPlayers() == 8 )
		gameColor = GameSpyColor[ GSCOLOR_GAME_FULL ];

	unsigned crcKey = TheWritableGlobalData->m_exeCRC;
	if( game->getExeCRC() == (unsigned)AptLivingWorldWindowIndex( crcKey, crcKey ) )
	{
		unsigned iniCRC = game->getIniCRC();
		if( iniCRC == TheWritableGlobalData->m_iniCRC )
		{
			unsigned ver = game->getVersion();
			if( ver == TheWritableGlobalData->m_extraCRC )
				goto crc_ok;
		}
	}
	gameColor = GameSpyColor[ GSCOLOR_GAME_CRCMISMATCH ];
crc_ok:

	UnicodeString gameName = game->getGameName();
	if( TheGameSpyInfo->getDisallowAsianText() )
	{
		const unsigned short *buff = gameName.str();
		int length = gameName.getLength();
		for( int i = 0; i < length; ++i )
		{
			if( buff[ i ] >= 256 )
				return -1;
		}
	}
	else if( TheGameSpyInfo->getDisallowNonAsianText() )
	{
		const unsigned short *buff = gameName.str();
		int length = gameName.getLength();
		bool hasUnicode = false;
		for( int i = 0; i < length; ++i )
		{
			if( buff[ i ] >= 256 )
			{
				hasUnicode = true;
				break;
			}
		}
		if( !hasUnicode )
			return -1;
	}

	int index = GadgetListBoxAddEntryText( win, game->getGameName(), gameColor, -1, 1, true );
	UnicodeString s;
	s.format( UnicodeString( L"%d/%d" ), game->getReportedNumPlayers(), game->getReportedMaxPlayers() );
	GadgetListBoxAddEntryText( win, s, gameColor, index, 2, true );

	int passwordFlag = 0;
	if( game->getHasPassword() )
	{
		Image *img = m_passwordImage;
		int width = 10;
		int height = 10;
		if( img )
		{
			width = img->getImageWidth();
			height = img->getImageHeight();
			passwordFlag = 1;
		}
		GadgetListBoxAddEntryImage( win, img, index, 0, width, height, true, -1 );
	}
	else
	{
		GadgetListBoxAddEntryText( win, UnicodeString( L" " ), gameColor, index, 0, true );
	}
	GadgetListBoxSetItemData( win, (void *)passwordFlag, index, 1 );

	s.format( UnicodeString( L"%d" ), game->getPingAsInt() );
	GadgetListBoxAddEntryText( win, s, gameColor, index, 3, true );
	int ping = game->getPingAsInt();
	int width = 10;
	int height = 10;
	Image *def = (Image *)m_picker->pick( 0 );
	if( def )
	{
		width = def->getImageWidth();
		height = def->getImageHeight();
	}
	GadgetListBoxAddEntryImage( win, (Image *)m_picker->pick( ping ), index, 3, width, height, true, -1 );
	GadgetListBoxSetItemData( win, (void *)game->getID(), index, 0 );
	return index;
}
