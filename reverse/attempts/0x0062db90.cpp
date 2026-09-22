// ?insertGame@@YAHPAVGameWindow@@PAVGameSpyStagingRoom@@_N@Z
// partial score=0.51 date=2026-09-22
// BFME LobbyUtils::insertGame reconstruction, retail 0x0062DB90.
// The local declarations preserve the BFME member offsets and string ABI.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef bool Bool;
typedef int Color;

extern const char g_bfmeEmptyUnicode[];
extern const char g_bfmeEmptyAscii[];

template <typename T> struct StringInlineData
{
	Int m_refCount;
	unsigned short m_length;
	unsigned short m_max;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString;

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}

	Int getLength(void) const { return m_data ? m_data->m_length : 0; }
	const unsigned short *str(void) const;
	void translate(const AsciiString &stringSrc);
	void format(const unsigned short *format, ...);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	const char *str(void) const;
	const char *reverseFind(char c) const;
};

const unsigned short *UnicodeString::str(void) const
{
	return m_data ? m_data->m_text : reinterpret_cast<const unsigned short *>(g_bfmeEmptyUnicode);
}

const char *AsciiString::str(void) const
{
	return m_data ? m_data->m_text : g_bfmeEmptyAscii;
}

extern "C" const char *__cdecl strrchr(const char *, int);
const char *AsciiString::reverseFind(char c) const
{
	return strrchr(str(), c);
}

#define TRUE 1
#define FALSE 0

class GameWindow;

class Image
{
public:
	Int getImageWidth(void) const { return m_width; }
	Int getImageHeight(void) const { return m_height; }

private:
	unsigned char m_pad[0x24];
	Int m_width;
	Int m_height;
};

class GameInfo
{
public:
	Int getNumNonObserverPlayers(void) const;
	Int getNumPlayers(void) const;
	Int _bfme_getMapIsOfficial(void) const;
	AsciiString getMap(void) const;
};

class GameSpyStagingRoom : public GameInfo
{
public:
	void cleanUpSlotPointers(void);
	UnicodeString getGameName(void);
	AsciiString getLadderIP(void) const;
	Int getID(void) const { return *reinterpret_cast<const Int *>(reinterpret_cast<const char *>(this) + 0x41C); }
	Bool getHasPassword(void) const { return *reinterpret_cast<const Bool *>(reinterpret_cast<const char *>(this) + 0x428); }
	Bool getAllowObservers(void) const { return *reinterpret_cast<const Bool *>(reinterpret_cast<const char *>(this) + 0x429); }
	UnsignedInt getExeCRC(void) const { return *reinterpret_cast<const UnsignedInt *>(reinterpret_cast<const char *>(this) + 0x430); }
	UnsignedInt getIniCRC(void) const { return *reinterpret_cast<const UnsignedInt *>(reinterpret_cast<const char *>(this) + 0x434); }
	UnsignedInt getVersion(void) const { return *reinterpret_cast<const UnsignedInt *>(reinterpret_cast<const char *>(this) + 0x438); }
	UnsignedShort getLadderPort(void) const { return *reinterpret_cast<const UnsignedShort *>(reinterpret_cast<const char *>(this) + 0x450); }
	Int getPingAsInt(void) const { return *reinterpret_cast<const Int *>(reinterpret_cast<const char *>(this) + 0x44C); }
	Int getReportedNumPlayers(void) const { return *reinterpret_cast<const Int *>(reinterpret_cast<const char *>(this) + 0x454); }
	Int getReportedMaxPlayers(void) const { return *reinterpret_cast<const Int *>(reinterpret_cast<const char *>(this) + 0x458); }
};

class GlobalData
{
public:
	unsigned char m_pad[0xBC8];
	UnsignedInt m_iniCRC;
	unsigned char m_gap[4];
	UnsignedInt m_exeCRC;
	UnsignedInt m_extraCRC;
};

class MapMetaData
{
public:
	UnicodeString m_displayName;
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

class LadderInfo
{
public:
	UnicodeString name;
};

class LadderList
{
public:
	const LadderInfo *findLadder(const AsciiString &addr, UnsignedShort port);
};

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
};

class ImageCollection
{
public:
	Image *findImageByName(const char *name);
};

class GameSpyConfigInterface
{
public:
	virtual ~GameSpyConfigInterface() {}
	virtual void v00(void) = 0;
	virtual void v01(void) = 0;
	virtual void v02(void) = 0;
	virtual Int getPingCutoffGood(void) = 0;
	virtual Int getPingCutoffBad(void) = 0;
};

#define GAMESPY_SLOT(n) virtual void gamespySlot##n(void) = 0
class GameSpyInfoInterface
{
public:
	GAMESPY_SLOT(0); GAMESPY_SLOT(1); GAMESPY_SLOT(2); GAMESPY_SLOT(3);
	GAMESPY_SLOT(4); GAMESPY_SLOT(5); GAMESPY_SLOT(6); GAMESPY_SLOT(7);
	GAMESPY_SLOT(8); GAMESPY_SLOT(9); GAMESPY_SLOT(10); GAMESPY_SLOT(11);
	GAMESPY_SLOT(12); GAMESPY_SLOT(13); GAMESPY_SLOT(14); GAMESPY_SLOT(15);
	GAMESPY_SLOT(16); GAMESPY_SLOT(17); GAMESPY_SLOT(18); GAMESPY_SLOT(19);
	GAMESPY_SLOT(20); GAMESPY_SLOT(21); GAMESPY_SLOT(22); GAMESPY_SLOT(23);
	GAMESPY_SLOT(24); GAMESPY_SLOT(25); GAMESPY_SLOT(26); GAMESPY_SLOT(27);
	GAMESPY_SLOT(28); GAMESPY_SLOT(29); GAMESPY_SLOT(30); GAMESPY_SLOT(31);
	GAMESPY_SLOT(32); GAMESPY_SLOT(33); GAMESPY_SLOT(34); GAMESPY_SLOT(35);
	GAMESPY_SLOT(36); GAMESPY_SLOT(37); GAMESPY_SLOT(38); GAMESPY_SLOT(39);
	GAMESPY_SLOT(40); GAMESPY_SLOT(41); GAMESPY_SLOT(42); GAMESPY_SLOT(43);
	GAMESPY_SLOT(44); GAMESPY_SLOT(45); GAMESPY_SLOT(46); GAMESPY_SLOT(47);
	GAMESPY_SLOT(48); GAMESPY_SLOT(49); GAMESPY_SLOT(50); GAMESPY_SLOT(51);
	GAMESPY_SLOT(52); GAMESPY_SLOT(53); GAMESPY_SLOT(54);
	virtual Bool getDisallowAsianText(void) = 0;
	virtual Bool getDisallowNonAsianText(void) = 0;
};
#undef GAMESPY_SLOT

extern MapCache *TheMapCache;
extern LadderList *TheLadderList;
extern GameTextInterface *TheGameText;
extern ImageCollection *TheMappedImageCollection;
extern GameSpyConfigInterface *TheGameSpyConfig;
extern GameSpyInfoInterface *TheGameSpyInfo;
extern GlobalData *TheWritableGlobalData;
extern Int GameSpyColor[];
extern Image *pingImages[3];

enum
{
	GSCOLOR_GAME = 3,
	GSCOLOR_GAME_FULL = 4,
	GSCOLOR_GAME_CRCMISMATCH = 5,
	COLUMN_NAME = 0,
	COLUMN_MAP = 1,
	COLUMN_LADDER = 2,
	COLUMN_NUMPLAYERS = 3,
	COLUMN_PASSWORD = 4,
	COLUMN_OBSERVER = 5
};

Int GadgetListBoxAddEntryText(GameWindow *win, UnicodeString text, Int color, Int row, Int column = -1, Bool overwrite = TRUE);
Int GadgetListBoxAddEntryImage(GameWindow *win, const Image *image, Int row, Int column = -1, Bool overwrite = TRUE, Color color = 0xFFFFFFFF);
Int GadgetListBoxAddEntryImage(GameWindow *win, const Image *image, Int row, Int column, Int height, Int width, Bool overwrite = TRUE, Color color = 0xFFFFFFFF);
void GadgetListBoxSetItemData(GameWindow *win, void *data, Int row, Int column = 0);
Int AptLivingWorldWindowIndex(Int low, Int high);

__declspec(noinline) static Int insertGame(GameWindow *win, GameSpyStagingRoom *game, Bool showMap)
{
	game->cleanUpSlotPointers();
	Color gameColor = GameSpyColor[GSCOLOR_GAME];
	Int mapIsOfficial = game->_bfme_getMapIsOfficial();
	if (game->getNumNonObserverPlayers() == mapIsOfficial || game->getNumPlayers() == 8)
	{
		gameColor = GameSpyColor[GSCOLOR_GAME_FULL];
	}

	UnsignedInt crcKey = TheWritableGlobalData->m_exeCRC;
	if (game->getExeCRC() == (UnsignedInt)AptLivingWorldWindowIndex(crcKey, crcKey))
	{
		UnsignedInt iniCRC = game->getIniCRC();
		if (iniCRC == TheWritableGlobalData->m_iniCRC)
		{
			UnsignedInt ver = game->getVersion();
			if (ver == TheWritableGlobalData->m_extraCRC)
				goto crc_ok;
		}
	}
	gameColor = GameSpyColor[GSCOLOR_GAME_CRCMISMATCH];
crc_ok:

	UnicodeString gameName = game->getGameName();
	if (TheGameSpyInfo->getDisallowAsianText())
	{
		const WideChar *buff = gameName.str();
		Int length = gameName.getLength();
		for (Int i = 0; i < length; ++i)
		{
			if (buff[i] >= 256)
				return -1;
		}
	}
	else if (TheGameSpyInfo->getDisallowNonAsianText())
	{
		const WideChar *buff = gameName.str();
		Int length = gameName.getLength();
		Bool hasUnicode = FALSE;
		for (Int i = 0; i < length; ++i)
		{
			if (buff[i] >= 256)
			{
				hasUnicode = TRUE;
				break;
			}
		}
		if (!hasUnicode)
			return -1;
	}

	Int index = GadgetListBoxAddEntryText(win, game->getGameName(), gameColor,
		-1 + (Int)((const char *)&gameName - (const char *)&gameName), COLUMN_NAME);
	GadgetListBoxSetItemData(win, (void *)game->getID(), index);

	{
	UnicodeString s;
	if (showMap)
	{
		UnicodeString mapName;
		const MapMetaData *md = TheMapCache->findMap(game->getMap());
		if (md)
		{
			mapName = md->m_displayName;
		}
		else
		{
			const char *start = game->getMap().reverseFind('\\');
			if (start)
				++start;
			else
				start = game->getMap().str();
			mapName.translate(start);
		}
		GadgetListBoxAddEntryText(win, mapName, gameColor, index, COLUMN_MAP);

		const LadderInfo *li = TheLadderList->findLadder(game->getLadderIP(), game->getLadderPort());
		if (li)
			GadgetListBoxAddEntryText(win, li->name, gameColor, index, COLUMN_LADDER);
		else if (game->getLadderPort())
			GadgetListBoxAddEntryText(win, TheGameText->fetch("GUI:UnknownLadder"), gameColor, index, COLUMN_LADDER);
		else
			GadgetListBoxAddEntryText(win, TheGameText->fetch("GUI:NoLadder"), gameColor, index, COLUMN_LADDER);
	}
	else
	{
		GadgetListBoxAddEntryText(win, UnicodeString(L" "), gameColor, index, COLUMN_MAP);
		GadgetListBoxAddEntryText(win, UnicodeString(L" "), gameColor, index, COLUMN_LADDER);
	}

	s.format(L"%d/%d", game->getReportedNumPlayers(), game->getReportedMaxPlayers());
	GadgetListBoxAddEntryText(win, s, gameColor, index, COLUMN_NUMPLAYERS);

	if (game->getHasPassword())
	{
		const Image *img = TheMappedImageCollection->findImageByName("Password");
		Int width = 10, height = 10;
		if (img)
		{
			width = img->getImageWidth();
			height = img->getImageHeight();
		}
		GadgetListBoxAddEntryImage(win, (Image *)img, index, COLUMN_PASSWORD, width, height);
	}
	else
	{
		GadgetListBoxAddEntryText(win, UnicodeString(L" "), gameColor, index, COLUMN_PASSWORD);
	}

	if (game->getAllowObservers())
	{
		const Image *img = TheMappedImageCollection->findImageByName("Observer");
		GadgetListBoxAddEntryImage(win, (Image *)img, index, COLUMN_OBSERVER);
	}
	else
	{
		GadgetListBoxAddEntryText(win, UnicodeString(L" "), gameColor, index, COLUMN_OBSERVER);
	}

	s.format(L"%d", game->getPingAsInt());
	GadgetListBoxAddEntryText(win, s, gameColor, index, 6);
	Int ping = game->getPingAsInt();
	Int width = 10, height = 10;
	if (pingImages[0])
	{
		width = pingImages[0]->getImageWidth();
		height = pingImages[0]->getImageHeight();
	}
	if (ping < TheGameSpyConfig->getPingCutoffGood())
		GadgetListBoxAddEntryImage(win, pingImages[0], index, 6, width, height);
	else if (ping < TheGameSpyConfig->getPingCutoffBad())
		GadgetListBoxAddEntryImage(win, pingImages[1], index, 6, width, height);
	else
		GadgetListBoxAddEntryImage(win, pingImages[2], index, 6, width, height);

	}
	return index;
}

__declspec(noinline) static Int invoke_insertGame(GameWindow *win, GameSpyStagingRoom *game, Bool showMap)
{
	return insertGame(win, game, showMap);
}

Int (__cdecl * volatile keep_insertGame)(GameWindow *, GameSpyStagingRoom *, Bool) = invoke_insertGame;
