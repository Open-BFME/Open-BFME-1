// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the player-table palantir write at retail 0x0052B540, 125 bytes.
// The value is handed in by the caller here; only the key is built, from a row
// and a column.

class StringBaseNarrowZG
{
public:
	void __cdecl format(class AsciiStringZG text, ...);

protected:
	StringBaseNarrowZG(void)
	{
		m_bfmeNarrowZG = 0;
	}

	StringBaseNarrowZG(const char *text);

	StringBaseNarrowZG(const StringBaseNarrowZG &other);

	~StringBaseNarrowZG(void);

	char *m_bfmeNarrowZG;
};

class AsciiStringZG : public StringBaseNarrowZG
{
public:
	AsciiStringZG(void)
	{
	}

	AsciiStringZG(const char *text) : StringBaseNarrowZG(text)
	{
	}

	AsciiStringZG(const AsciiStringZG &other);

	~AsciiStringZG(void)
	{
	}
};

class UnicodeStringZG;

class BfmePalantirZG
{
public:
	void bfmeStoreZG(const AsciiStringZG &key, const UnicodeStringZG &value);
};

// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU only needs
// the store() through it, so the pointee stays the local BfmePalantirZG view
// and the access is cast at the use.
class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;	// retail 0x012F19E8

// ?bfmePlayerTableZG@@YGXHHABVUnicodeStringZG@@@Z
void __stdcall bfmePlayerTableZG(int row, int column, const UnicodeStringZG &value)
{
	AsciiStringZG key;

	key.format(AsciiStringZG("PlayerTable:%d:%d"), row, column);

	((BfmePalantirZG *)g_rva012F19E8WindowManager)->bfmeStoreZG(key, value);
}
