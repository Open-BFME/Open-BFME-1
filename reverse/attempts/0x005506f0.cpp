// ?_bfme_populateCountryList@BfmeAptScreenOnlineLogin@@QAEXXZ
// partial score=0.78 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /Ireference/shims/stlp_nodealloc
// Complete typed candidate retained after the retail control-flow and ABI
// reconstruction.  The source-order lever moved selectedRow before the map
// and changed the loop to i < 0x25; the remaining mismatch is compiler local
// layout/register allocation, not an unresolved identity or generated thunk.
// Retail body: 0x005506F0, 791 bytes.  Named caller: _bfme_onInitGadget at
// 0x00551DD0 through ILT 0x00005F83.  The map, string helpers, and UI calls
// are pinned to their actual retail bodies in reverse/symbols.csv.

class GameWindow;
class AsciiString;
class UnicodeString;
class GameTextInterface;
class BfmeAptScreenOnlineLogin
{
public:
	void _bfme_populateCountryList();

private:
	GameWindow *m_countryList;
};

extern GameTextInterface *TheGameText;
extern int GameSpyColor[];
extern AsciiString GetRegistryLanguage();
extern unsigned int __cdecl bfmeLenVGI(const unsigned short *);

extern int GadgetListBoxAddEntryText(GameWindow *, UnicodeString, int, int, int, bool);
extern void GadgetListBoxSetItemData(GameWindow *, void *, int, int);
extern void GadgetListBoxSetSelected(GameWindow *, int);

class AsciiString
{
public:
	AsciiString();
	AsciiString(const char *);
	AsciiString(const AsciiString &);
	~AsciiString();
	void format(AsciiString, ...);
	const char *str() const;
};

class UnicodeString
{
public:
	UnicodeString();
	UnicodeString(const UnicodeString &);
	~UnicodeString();
	void translate(const AsciiString &);
	void set(const unsigned short *, int);
	bool isEmpty() const;
	int compareNoCase(const unsigned short *) const;
	int compareNoCase(const UnicodeString &) const;
};

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09();
	virtual UnicodeString fetch(const char *, bool *exists = 0);
};

struct UnicodeStringLessThan
{
	bool operator()(UnicodeString left, UnicodeString right) const
	{
		return left.compareNoCase(right) < 0;
	}
};

namespace _STL
{
	template <typename K, typename V, typename C> class map;
}

typedef _STL::map<UnicodeString, int, UnicodeStringLessThan> CountryLocaleMap;

void BfmeAptScreenOnlineLogin::_bfme_populateCountryList()
{
	AsciiString id;
	id.format(AsciiString("WOL:Locale%2.2d"), 1);
	int row = GadgetListBoxAddEntryText(m_countryList,
		TheGameText->fetch(id.str(), 0), GameSpyColor[0], -1, -1, true);
	GadgetListBoxSetItemData(m_countryList, (void *)1, row, 0);

	int selectedRow = 0;
	CountryLocaleMap locales;
	for (int i = 2; i < 0x25; ++i)
	{
		id.format(AsciiString("WOL:Locale%2.2d"), i);
		UnicodeString text = TheGameText->fetch(id.str(), 0);
		locales[text] = i;
	}

	UnicodeString selected;
	selected.translate(GetRegistryLanguage());
	if (!selected.isEmpty()
		&& selected.compareNoCase((const unsigned short *)L"english") == 0)
	{
		const unsigned short *unitedStates =
			(const unsigned short *)L"United States";
		selected.set(unitedStates, (int)bfmeLenVGI(unitedStates));
	}

	for (CountryLocaleMap::iterator it = locales.begin();
		it != locales.end(); ++it)
	{
		row = GadgetListBoxAddEntryText(m_countryList, it->first,
			GameSpyColor[0], -1, -1, true);
		GadgetListBoxSetItemData(m_countryList, (void *)it->second, row, 0);
		if (it->first.compareNoCase(selected) == 0)
			selectedRow = row;
	}

	GadgetListBoxSetSelected(m_countryList, selectedRow);
}
