// ?d_0052a2e0@@YAXXZ
// partial score=0.23 date=2026-09-18
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Retail 0x0052A2E0, 1306 bytes.  The body is the map-list refresh owned by
// SkirmishScreenState: the matched state layout puts its listbox at +0x108,
// its retained filename vector at +0x10c, and its transient flag at +0x16.
// The method spelling is deliberately address-derived.  The callers and the
// neighbouring matched methods prove the class and fields, but do not prove a
// semantic method name.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <vector>

typedef int Int;
typedef bool Bool;

template <class T>
class StringBase
{
private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	friend class AsciiString;
	friend class UnicodeString;
};

class AsciiString
{
public:
	AsciiString() { m_text = 0; }
	AsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString();

	const char *str() const
	{
		return m_text ? (const char *)m_text + 8 : "";
	}

private:
	void *m_text;
};

class UnicodeString
{
public:
	UnicodeString(const UnicodeString &other)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&other);
	}
	~UnicodeString();

private:
	void *m_text;
};

class GameWindow;
class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

int GadgetListBoxGetNumColumns(GameWindow *listbox);
int GadgetListBoxGetColumnWidth(GameWindow *listbox, int column) throw();
void GadgetListBoxReset(GameWindow *listbox);
int GadgetListBoxAddEntryImage(GameWindow *listbox, const Image *image,
	int row, int column, int width, int height, Bool overwrite, int color);
int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text,
	int color, int row, int column, Bool overwrite);
void GadgetListBoxSetItemData(GameWindow *listbox, void *data,
	int row, int column);

class MapMetaData
{
public:
	unsigned char m_beforePlayerCount[0x20];
	int m_numPlayers;
	unsigned char m_isMultiplayer;
	unsigned char m_isScenarioMP;
	unsigned char m_isOfficial;
	unsigned char m_betweenFlagsAndFileName[0x50 - 0x27];
	AsciiString m_fileName;

	UnicodeString bfme_getDisplayName();
};

typedef _STL::vector<MapMetaData *> Rva00453480Vector;

extern "C" void Rva00453480Collect(unsigned int flags,
	Rva00453480Vector *out);

struct Q3SortItem003CDC60
{
	char m_padding30[0x30];
	int m_key;
	char m_padding34[5];
	char m_tie;
};

struct Q3SortElem4
{
	Q3SortItem003CDC60 *m_item;
};

struct Q3SortCompare
{
	void *m_state;
};

void Rva004568C0(Q3SortElem4 *first, Q3SortElem4 *last,
	Q3SortCompare compare);

class SkirmishPreferences
{
public:
	virtual ~SkirmishPreferences();
	virtual void slot1();
	virtual Bool load();
	virtual Bool write();
	SkirmishPreferences();
	UnicodeString getUserName();

private:
	char m_unmodelled[0x14];
};

class Rva005672C0Map
{
public:
	virtual void slot0();
	void *m_head;
};

struct SkirmishBattleHonorsValues
{
	int m_value[10];
};

class SkirmishBattleHonors
{
public:
	virtual ~SkirmishBattleHonors();
	virtual void slot1();
	virtual Bool load();
	virtual Bool write();
	SkirmishBattleHonors(UnicodeString userName);
	Int getEnduranceMedal(AsciiString mapName, Int difficulty) const;

	Rva005672C0Map m_map;
	char m_unmodelled_0c[4];
	UnicodeString m_userName;
	SkirmishBattleHonorsValues m_values;
};

class SkirmishScreenStateMember28
{
public:
	unsigned char m_padding[0x39];
	Bool m_flag39;
	unsigned char m_tail[6];
};

class SkirmishScreenState
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;

	void rva0052a2e0(int flags);

private:
	void *m_owner;
	void *m_game;
	void *m_secondaryGame;
	Bool m_flag10;
	Bool m_flag11;
	Bool m_flag12;
	Bool m_flag13;
	Bool m_flag14;
	Bool m_flag15;
	Bool m_flag16;
	Bool m_flag17;
	Bool m_visible;
	unsigned char m_padding19[3];
	int m_value1c;
	int m_value20;
	int m_value24;
	SkirmishScreenStateMember28 m_member28;
	GameWindow *m_first[8];
	GameWindow *m_elements[8];
	GameWindow *m_second[8];
	GameWindow *m_third[8];
	GameWindow *m_fourth[8];
	GameWindow *m_mapListbox;
	_STL::vector<AsciiString> m_mapNames;
	unsigned char m_memberTail[0x10];
	int m_field128;
};

class MapCache;
extern MapCache *TheMapCache;

// ?rva0052a2e0@SkirmishScreenState@@QAEXH@Z
void SkirmishScreenState::rva0052a2e0(int flags)
{
	if (!TheMapCache)
		return;
	if (!m_mapListbox)
		return;

	int numColumns;
	const Image *notConquered = 0;
	const Image *easyImage = 0;
	const Image *mediumImage = 0;
	const Image *hardImage = 0;
	const Image *hardGlowImage = 0;
	SkirmishBattleHonors *battleHonors = 0;
	int width = 10;

	m_flag16 = true;
	numColumns = GadgetListBoxGetNumColumns(m_mapListbox);
	if (numColumns > 1)
	{
		notConquered = TheMappedImageCollection->findImageByName(
			AsciiString("AptDifficultyNotConquered"));
		easyImage = TheMappedImageCollection->findImageByName(
			AsciiString("AptDifficultyEasyConquered"));
		mediumImage = TheMappedImageCollection->findImageByName(
			AsciiString("AptDifficultyMedConquered"));
		hardImage = TheMappedImageCollection->findImageByName(
			AsciiString("AptDifficultyHardConquered"));
		hardGlowImage = TheMappedImageCollection->findImageByName(
			AsciiString("AptDifficultyHardGlowConquered"));

		SkirmishPreferences preferences;
		battleHonors = new SkirmishBattleHonors(preferences.getUserName());
		width = 10;
		if (GadgetListBoxGetColumnWidth(m_mapListbox, 0) < width)
			width = GadgetListBoxGetColumnWidth(m_mapListbox, 0);
	}

	if ((flags & 0x40) == 0)
	{
		GadgetListBoxReset(m_mapListbox);
		m_mapNames.erase(m_mapNames.begin(), m_mapNames.end());
	}

	Rva00453480Vector maps;
	Rva00453480Collect((unsigned int)flags, &maps);
	Q3SortCompare compare = { 0 };
	Rva004568C0((Q3SortElem4 *)maps.begin(),
		(Q3SortElem4 *)maps.end(), compare);

	Rva00453480Vector::iterator cursor = maps.begin();
	Rva00453480Vector::iterator end = maps.end();
	while (cursor != end)
	{
		MapMetaData *map = *cursor;
		int index = -1;
		int imageItemData = -1;
		const Image *image = notConquered;

		if (numColumns > 1 && map->m_isMultiplayer)
		{
			int easy = battleHonors->getEnduranceMedal(
				AsciiString(map->m_fileName.str()), 2);
			int medium = battleHonors->getEnduranceMedal(
				AsciiString(map->m_fileName.str()), 3);
			int hard = battleHonors->getEnduranceMedal(
				AsciiString(map->m_fileName.str()), 4);
			int hardGlow = battleHonors->getEnduranceMedal(
				AsciiString(map->m_fileName.str()), 5);

			if (hardGlow)
			{
				image = hardGlowImage;
				imageItemData = 4;
			}
			else if (hard)
			{
				image = hardImage;
				imageItemData = 3;
			}
			else if (medium)
			{
				image = mediumImage;
				imageItemData = 2;
			}
			else if (easy)
			{
				image = easyImage;
				imageItemData = 1;
			}
		}

		index = GadgetListBoxAddEntryImage(m_mapListbox, image,
			index, 0, width, width, true, -1);
		index = GadgetListBoxAddEntryText(m_mapListbox,
			map->bfme_getDisplayName(), -1, index, numColumns - 1, true);
		m_mapNames.push_back(map->m_fileName);

		if (numColumns > 1)
			GadgetListBoxSetItemData(m_mapListbox,
				(void *)imageItemData, index, 1);

		++cursor;
	}

	if (battleHonors)
		delete battleHonors;

	m_flag16 = false;
}
