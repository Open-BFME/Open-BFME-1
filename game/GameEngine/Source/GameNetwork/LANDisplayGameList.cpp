// cl: /DNDEBUG /MD /EHsc
// LANDisplayGameList, retail 0x0068EBF0, 710 bytes.
//
// Identity: the Zero Hour twin in
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameNetwork/LANGameInfo.cpp
// (same selection-preserving rebuild: GetSelected / GetItemData / Reset /
// AddEntryText / SetItemData / SetSelected, the "[" "]" in-progress brackets
// around getPlayerName(0), gameInProgressColor vs gameColor, and the
// HideGameInfoWindow(TRUE) fallback). The single caller, 0x00688B10 through
// ILT 0x0002FF36, is ZH's LANAPI::OnGameList shape: `if (m_inLobby)` (+0x3D)
// then LANDisplayGameList(listbox at +0x64, gameList).
//
// BFME grows the ZH body: it returns early while the list box owns the
// window manager's grab window, lays out three columns (5/82/13), puts the
// "AptLock" image in column 0 of an in-progress game, the name in column 1
// and a "%d/%d" player count in column 2.
//
// StringBase stays TU-local: string_base.h declares the default constructor
// out of line, and retail builds each UnicodeString local with an inline
// `m_data = 0` store.

typedef int Int;
typedef bool Bool;
typedef Int Color;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	void set(const T *text, Int length);			// 0x008885C0 (wide)
	void concat(const T *text, Int length);			// 0x00888600 (wide)

private:
	struct Header
	{
		Int refCount;
		UnsignedShort length;
		UnsignedShort capacity;
		T data[1];
	};

	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &src);
	~StringBase();

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
};

__declspec(dllimport) unsigned int __cdecl bfmeLenVGI(const unsigned short *);

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString(const WideChar *text) : StringBase<WideChar>(text) {}
	UnicodeString(const UnicodeString &src) : StringBase<WideChar>(src) {}
	~UnicodeString() {}

	const WideChar *str() const { return m_data ? m_data->data : L""; }
	Int getLength() const { return m_data ? m_data->length : 0; }

	UnicodeString &operator=(const WideChar *text)
	{
		set(text, bfmeLenVGI(text));
		return *this;
	}
	void concat(const WideChar *text) { StringBase<WideChar>::concat(text, bfmeLenVGI(text)); }
	void concat(const UnicodeString &other) { StringBase<WideChar>::concat(other.str(), other.getLength()); }

	void __cdecl format(UnicodeString fmt, ...);		// 0x00889190
};

class GameWindow
{
public:
	Bool winIsChild(GameWindow *child);			// 0x00478D30
};

// Only slot 46 (vtable+0xB8, winGetGrabWindow at 0x0047D020 through ILT
// 0x0002015D in the GameWindowManager vtable 0x010F8B60) is called here.
class GameWindowManager
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
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual GameWindow *winGetGrabWindow(void);		// slot 46, vtable+0xB8
};

extern GameWindowManager *TheWindowManager;

class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);	// 0x005D2CF0
};

extern ImageCollection *TheMappedImageCollection;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	Int getNumPlayers(void) const;				// 0x0061E6B0
	Bool isGameInProgress(void) const { return m_inProgress; }

private:
	unsigned char m_unmodelled00[0x0d];
	Bool m_inProgress;					// this+0x0d, ZH GameInfo layout
};

// The slot-count getter at 0x0061EE90 keeps an address-derived owner in the
// ledger; it runs on the same GameInfo object.
class Rva0061EE90GameInfo
{
public:
	Int countNonClosed(void) const;				// 0x0061EE90
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo : public GameInfo
{
public:
	UnicodeString getPlayerName(Int who);			// 0x004C8800
	LANGameInfo *getNext(void) { return m_next; }

private:
	unsigned char m_unmodelled0e[0x398 - 0x0e];
	LANGameInfo *m_next;					// this+0x398
};

// LANAPICallbacks.cpp's colour table, in ZH order from playerColor at
// 0x00EBA0B8 to chatSystemColor (pinned) at 0x00EBA0D4; the raw values
// (0xFFFFFFFF, 0xFF808080) are ZH's GameMakeColor arguments.
extern const Color gameColor;					// 0x00EBA0BC
extern const Color gameInProgressColor;				// 0x00EBA0C0

void GadgetListBoxGetSelected(GameWindow *listbox, Int *selectList);
void *GadgetListBoxGetItemData(GameWindow *listbox, Int row, Int column);
void GadgetListBoxReset(GameWindow *listbox);
void GadgetListBoxSetColumnWidths(GameWindow *listbox, Int count, Int *widths);
Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text,
	Color color, Int row, Int column, Bool overwrite);
Int GadgetListBoxAddEntryImage(GameWindow *listbox, const Image *image,
	Int row, Int column, Bool overwrite, Color color);
void GadgetListBoxSetItemData(GameWindow *listbox, void *data, Int row, Int column);
void GadgetListBoxSetSelected(GameWindow *listbox, Int selectIndex);
void HideGameInfoWindow(Bool hide);

void LANDisplayGameList( GameWindow *gameListbox, LANGameInfo *gameList )
{
	if (gameListbox->winIsChild(TheWindowManager->winGetGrabWindow()))
		return;

	LANGameInfo *selectedPtr = 0;
	Int selectedIndex = -1;
	Int indexToSelect = -1;
	if (gameListbox)
	{
		GadgetListBoxGetSelected(gameListbox, &selectedIndex);

		if (selectedIndex != -1)
		{
			selectedPtr = (LANGameInfo *)GadgetListBoxGetItemData(gameListbox, selectedIndex, 0);
		}

		GadgetListBoxReset(gameListbox);

		Int columnWidths[3] = { 5, 82, 13 };
		GadgetListBoxSetColumnWidths(gameListbox, 3, columnWidths);

		while (gameList)
		{
			UnicodeString txtGName;
			txtGName = L"";
			if( gameList->isGameInProgress() )
			{
				txtGName.concat(L"[");
			}
			txtGName.concat(gameList->getPlayerName(0));
			if( gameList->isGameInProgress() )
			{
				txtGName.concat(L"]");
			}

			UnicodeString txtPlayers;
			txtPlayers.format(L"%d/%d", gameList->getNumPlayers(),
				((const Rva0061EE90GameInfo *)gameList)->countNonClosed());

			Color color = gameList->isGameInProgress() ? gameInProgressColor : gameColor;
			const Image *image = 0;
			if (gameList->isGameInProgress())
				image = TheMappedImageCollection->findImageByName(AsciiString("AptLock"));

			Int addedIndex = GadgetListBoxAddEntryText(gameListbox, txtGName, color, -1, 1, true);
			GadgetListBoxAddEntryImage(gameListbox, image, addedIndex, 0, true, -1);
			GadgetListBoxAddEntryText(gameListbox, txtPlayers, color, addedIndex, 2, true);
			GadgetListBoxSetItemData(gameListbox, (void *)gameList, addedIndex, 0);

			if (selectedPtr == gameList)
				indexToSelect = addedIndex;

			gameList = gameList->getNext();
		}

		if (indexToSelect >= 0)
			GadgetListBoxSetSelected(gameListbox, indexToSelect);
		else
			HideGameInfoWindow(true);
	}
}
