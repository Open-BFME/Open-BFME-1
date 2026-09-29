// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// LAN custom-games list tooltip callback, retail 0x00518150, 402 bytes.
// Installed by BfmeAptScreenLanLobby_onInitGadget.cpp through winSetTooltipFunc.

typedef int Int;
typedef bool Bool;
typedef unsigned short WideChar;

extern const unsigned short BFMEEmptyUnicodeString;

template <typename T>
class StringBase
{
	friend class UnicodeString;

private:
	struct Header
	{
		Int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &source);
	~StringBase();

public:
	void concat(const T *text, Int length);

	Header *m_data;
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString(const UnicodeString &source) : StringBase<WideChar>(source) {}
	~UnicodeString() {}

	const WideChar *str() const
	{
		return m_data ? m_data->data : &BFMEEmptyUnicodeString;
	}

	Int getLength() const
	{
		return m_data ? m_data->length : 0;
	}

	Bool isEmpty() const
	{
		return !m_data || m_data->length == 0;
	}

	UnicodeString &operator+=(const WideChar *text);

	static UnicodeString TheEmptyString;
};

class GameWindow;
class WinInstanceData;

Int GadgetListBoxGetEntryBasedOnXY(GameWindow *listbox, Int x, Int y,
	Int &row, Int &column);
void *GadgetListBoxGetItemData(GameWindow *listbox, Int row, Int column);

class GameSlot
{
public:
	Bool isHuman(void) const;
	UnicodeString getName(void) const;
};

__forceinline void appendLanTooltipName(UnicodeString &tooltip,
	const UnicodeString &name)
{
	((StringBase<WideChar> *)&tooltip)->concat(name.str(), name.getLength());
}

class GameInfo
{
public:
	const GameSlot *getConstSlot(Int slot) const;
};

class LANGameInfo : public GameInfo
{
};

class LANAPI
{
};

extern LANAPI *TheLAN;

struct Rva00685200Node
{
	char m_padding[0x398];
	Rva00685200Node *m_next;
};

class Rva00685200
{
public:
	Bool has(Rva00685200Node *node);
};

struct RGBColor
{
};

class Mouse
{
public:
	void setCursorTooltip(UnicodeString tooltip, Int delay = -1,
		const RGBColor *color = 0, float width = 1.0f);
};

extern Mouse *TheMouse;

// Retail folds this lookup into its caller; the single null test it leaves
// is what lets the empty-tooltip returns share one tail.
// ?lookupListedLanGame@@YAPAVLANGameInfo@@PAV1@@Z absent-from-retail
inline LANGameInfo *lookupListedLanGame(LANGameInfo *game)
{
	if (((Rva00685200 *)TheLAN)->has((Rva00685200Node *)game))
		return game;
	return 0;
}

void Rva00518150LanLobbyTooltip(GameWindow *window, WinInstanceData *,
	unsigned int mouse)
{
	Int x, y, row, column;
	x = mouse & 0xffff;
	y = mouse >> 16;
	GadgetListBoxGetEntryBasedOnXY(window, x, y, row, column);

	if (row == -1 || column == -1)
	{
		TheMouse->setCursorTooltip(UnicodeString::TheEmptyString);
		return;
	}

	LANGameInfo *game = lookupListedLanGame(
		(LANGameInfo *)GadgetListBoxGetItemData(window, row, 0));
	if (game == 0)
	{
		TheMouse->setCursorTooltip(UnicodeString::TheEmptyString, -1, 0, 1.0f);
		return;
	}

	UnicodeString tooltip;
	for (Int i = 0; i < 8; ++i)
	{
		const GameSlot *slot = game->getConstSlot(i);
		if (slot->isHuman())
		{
			if (tooltip.getLength() != 0)
				tooltip += reinterpret_cast<const WideChar *>(L"\n");
			appendLanTooltipName(tooltip, slot->getName());
		}
	}
	TheMouse->setCursorTooltip(tooltip, -1, 0, 1.0f);
}
