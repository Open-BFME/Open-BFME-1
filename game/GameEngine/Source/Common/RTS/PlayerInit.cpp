// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Player::init(const PlayerTemplate *), retail 0x000DA610, 2056 bytes.
// Identity: PlayerList::init calls this body through ILT 0x00020AEA and it
// rebuilds the ten hotkey squads plus the current selection with the Squad
// vtable 0x01083E78, the Zero Hour Player::init sequence. The member layout
// follows the matched Player::~Player (PlayerDestructor.cpp, 0x000DD440);
// members BFME added keep offset-derived names. The STLport containers are
// real containers so their clear/erase/iterator code inlines as in retail.
#include <list>
#include <vector>
#include <map>
#define private public
#include <hash_map>
#undef private
#include "string_base.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_data(other.m_data) {}
	const char *str() const { return m_data.m_data ? &m_data.m_data->data[0] : ""; }
	void clear() { m_data.releaseBuffer(); }
	AsciiString &operator=(const AsciiString &o) { m_data.set(o.m_data); return *this; }
	void setEmpty() { m_data.set("", 0); }
	int compare(const AsciiString &str) const
	{
		const int len = str.m_data.m_data ? str.m_data.m_data->length : 0;
		const char *data = str.m_data.m_data ? &str.m_data.m_data->data[0] : "";
		const int myLen = m_data.m_data ? m_data.m_data->length : 0;
		const char *myData = m_data.m_data ? &m_data.m_data->data[0] : "";
		const int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result != 0)
			return result;
		return myLen - len;
	}
	StringBase<char> m_data;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

class UnicodeString
{
public:
	void clear() { m_data.releaseBuffer(); }
	UnicodeString &operator=(const UnicodeString &o) { m_data.set(o.m_data); return *this; }
	StringBase<unsigned short> m_data;
	static UnicodeString TheEmptyString;
};

extern AsciiString TheEmptyAsciiString;

namespace rts
{
template <class T>
struct hash
{
	unsigned int operator()(T value) const
	{
		const char *s = value.str();
		unsigned int h = 0;
		for (; *s; ++s)
			h = 5 * h + *s;
		return h;
	}
};
}

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum VeterancyLevel { LEVEL_REGULAR = 0 };
enum Relationship { ENEMIES = 0, NEUTRAL = 1, ALLIES = 2 };
enum Rva000D6C60Mapped { Rva000D6C60MappedZero = 0 };

// The AsciiString-keyed table whose _M_copy_from is matched at 0x000D6800.
struct Rva000D6770Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva000D6770ExtractKey
{
	const AsciiString &operator()(const Rva000D6770Value &x) const { return x.m_key; }
};

typedef _STL::hashtable<Rva000D6770Value, AsciiString, rts::hash<AsciiString>,
	Rva000D6770ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva000D6770Value> > Rva000D6770Table;
typedef _STL::hash_map<AsciiString, Rva000D6C60Mapped, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva000D6C60Mapped> > > Rva000D6C60Map;

// The production-cost map's mapped type stays address-derived: its _M_erase
// body (0x000CCF00) is not the one the (NameKeyType, float) spelling is
// already pinned to (0x0007D250), so that identity is not reused here.
struct Rva000D63C0Mapped
{
	Real m_value;
};
typedef _STL::map<NameKeyType, Rva000D63C0Mapped> ProductionChangeMap;
typedef _STL::map<NameKeyType, VeterancyLevel> ProductionVeterancyMap;
typedef _STL::hash_map<Int, Relationship> PlayerRelationMap;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class GlobalData
{
public:
	char m_prefix[0xc54];
	UnsignedInt m_defaultStartingCash;
};
extern GlobalData *TheWritableGlobalData;
extern UnsignedInt g_neutralColor000DA610;

class Deletable000DA610
{
public:
	virtual ~Deletable000DA610();
};

class Rva000DA590Map
{
public:
	Rva000DA590Map();
	virtual ~Rva000DA590Map();
	PlayerRelationMap m_map;
};

class TeamRelationMap
{
public:
	TeamRelationMap();
	virtual ~TeamRelationMap();
	unsigned char m_storage[0x14];
};

class Squad
{
public:
	Squad() : m_04(0), m_08(0), m_0c(0), m_10(0), m_14(0), m_18(0) {}
	virtual ~Squad();
	UnsignedInt m_04, m_08, m_0c, m_10, m_14, m_18;
};

class Rva000C81E0
{
public:
	void reset();
	UnsignedInt m_00, m_04, m_08, m_0c;
};

class Rva000C8440
{
public:
	void reset();
	char m_00[0x10c];
};

class Money
{
public:
	virtual void s00();
	void deposit(UnsignedInt amount, Bool fromTemplate);
	Money &operator=(const Money &o) { m_money = o.m_money; m_playerIndex = o.m_playerIndex; return *this; }
	UnsignedInt m_money;
	Int m_playerIndex;
};

class Rva000C7A10
{
public:
	virtual void s00();
	void reset();
	char m_04[0x14];
};

class BfmePlayerMapState
{
public:
	void bfmeNewMap(Int index, Bool flag);
};

class ScoreKeeper
{
public:
	void reset(Int playerIndex);
	char m_00[0x2ec];
};

class Rva000FB1F0
{
public:
	void forward();
	UnsignedInt m_words[4];
};

class Rva000CE400Owner
{
public:
	void clearChainAndStats();
};

class Rva000D95C0Player
{
public:
	void applyInitialUpgrades();
};

class Energy000DA610
{
public:
	virtual void s00();
	Int m_production;
	Int m_consumption;
	void *m_owner;
};

class Gen000D1730Part
{
public:
	virtual void s00();
	Int m_field;
	_STL::vector<Int> m_vector;
};

struct Timer000DA610
{
	UnsignedInt m_id;
	Int m_frame;
	void clear() { m_frame = -1; m_id = 0; }
};

struct KindChange000DA610
{
	char m_00[4];
	_STL::vector<Int> m_kinds;
	~KindChange000DA610() {}
};

struct RGBColor000DA610
{
	Real red, green, blue;
	Int getAsInt() const
	{
		return ((Int)(red * 255.0) << 16) | ((Int)(green * 255.0) << 8) | (Int)(blue * 255.0);
	}
};

class PlayerTemplate
{
public:
	char m_00[8];
	AsciiString m_side;
	Rva000C81E0 m_0c;
	Money m_money;
	RGBColor000DA610 m_preferredColor;
	char m_34[0x60 - 0x34];
	ProductionChangeMap m_productionCostChanges;
	Rva000D6770Table m_6c;
	ProductionVeterancyMap m_productionVeterancyLevels;
	char m_8c[0xbc - 0x8c];
	Bool m_bc;
	char m_bd[0x118 - 0xbd];
	Bool m_118;
};

class TeamPrototype000DA610;
struct Science000DA610 { Int m_value; };

class Player
{
public:
	virtual ~Player();
	void init(const PlayerTemplate *pt);
	void resetRank();
	Int getPlayerIndex() const { return m_playerIndex; }

	const PlayerTemplate *m_playerTemplate;   // +0x004
	UnicodeString m_playerDisplayName;        // +0x008
	Rva000C81E0 m_0c;                         // +0x00c
	AsciiString m_playerName;                 // +0x01c
	UnsignedInt m_playerNameKey;              // +0x020
	Int m_playerIndex;                        // +0x024
	AsciiString m_side;                       // +0x028
	Int m_playerType;                         // +0x02c
	Rva000C7A10 m_30;                         // +0x030
	Money m_money;                            // +0x048
	char m_54[4];
	UnsignedInt m_58;
	UnsignedInt m_5c;
	Bool m_60;
	UnsignedInt m_64;
	UnsignedInt m_68;
	UnsignedInt m_6c;
	void *m_battlePlanBonuses;                // +0x070
	char m_74[0xa4 - 0x74];
	Energy000DA610 m_energy;                  // +0x0a4
	Rva000C8440 m_stats;                      // +0x0b4
	Deletable000DA610 *m_1c0;
	UnsignedInt m_color;                      // +0x1c4
	UnsignedInt m_nightColor;                 // +0x1c8
	ProductionChangeMap m_productionCostChanges; // +0x1cc
	Rva000D6770Table m_1d8;
	Rva000D6770Table m_1ec;
	Rva000D6C60Map m_200;
	ProductionVeterancyMap m_productionVeterancyLevels; // +0x214
	Deletable000DA610 *m_220;
	UnsignedInt m_224;
	Deletable000DA610 *m_228;
	Deletable000DA610 *m_22c;
	void *m_defaultTeam;                      // +0x230
	_STL::vector<Int> m_sciences;             // +0x234
	_STL::vector<Science000DA610> m_sciencesDisabled; // +0x240
	_STL::vector<Science000DA610> m_sciencesHidden;   // +0x24c
	char m_258[8];
	UnsignedInt m_260;
	char m_264[0x274 - 0x264];
	Gen000D1730Part m_274;
	_STL::list<TeamPrototype000DA610 *> m_playerTeamPrototypes; // +0x288
	Rva000DA590Map *m_playerRelations;        // +0x28c
	TeamRelationMap *m_teamRelations;         // +0x290
	Bool m_294;
	Bool m_295;
	Bool m_296;
	Bool m_297;
	Real m_298;
	Bool m_29c;
	Bool m_29d;
	Bool m_29e;
	Bool m_29f[32];
	UnsignedInt m_2c0;
	UnsignedInt m_2c4[32];
	unsigned short m_344;
	char m_346[2];
	ScoreKeeper m_scoreKeeper;                // +0x348
	char m_634[8];
	UnsignedInt m_63c;
	_STL::list<KindChange000DA610 *> m_kindChanges; // +0x640
	UnsignedInt m_644;
	UnsignedInt m_648;
	_STL::list<void *> m_64c;
	_STL::list<Timer000DA610> m_timers;       // +0x650
	Squad *m_squads[10];                      // +0x654
	Squad *m_currentSelection;                // +0x67c
	Bool m_680;
	Bool m_681;
	Rva000FB1F0 m_684;
	char m_694[4];
	AsciiString m_698;
};

#define CHECK_OFF(C, M, O) typedef char check_##M[(offsetof(C, M) == O) ? 1 : -1]
#include <stddef.h>
typedef char szA[sizeof(ProductionChangeMap)==0xc?1:-1];
typedef char szH[sizeof(Rva000D6770Table)==0x14?1:-1];
typedef char szR[sizeof(Rva000DA590Map)==0x18?1:-1];
typedef char oM[offsetof(PlayerTemplate, m_money)==0x1c?1:-1];
typedef char oC[offsetof(PlayerTemplate, m_productionCostChanges)==0x60?1:-1];
CHECK_OFF(PlayerTemplate, m_bc, 0xbc);
CHECK_OFF(PlayerTemplate, m_productionVeterancyLevels, 0x80);
CHECK_OFF(Player, m_1ec, 0x1ec);
CHECK_OFF(Player, m_productionVeterancyLevels, 0x214);
CHECK_OFF(Player, m_sciences, 0x234);
CHECK_OFF(Player, m_playerTeamPrototypes, 0x288);
CHECK_OFF(Player, m_scoreKeeper, 0x348);
CHECK_OFF(Player, m_kindChanges, 0x640);
CHECK_OFF(Player, m_684, 0x684);
CHECK_OFF(Player, m_698, 0x698);

void Player::init(const PlayerTemplate *pt)
{
	m_playerTemplate = pt;
	m_playerTeamPrototypes.clear();
	m_playerDisplayName.clear();
	reinterpret_cast<Rva000CE400Owner *>(this)->clearChainAndStats();

	m_58 = 0;
	m_5c = 0;
	m_60 = false;
	m_64 = 0;
	m_68 = 0;
	m_6c = 0;
	if (m_battlePlanBonuses)
	{
		delete (char *)m_battlePlanBonuses;
		m_battlePlanBonuses = 0;
	}

	m_energy.m_production = 0;
	m_energy.m_consumption = 0;
	m_energy.m_owner = this;
	m_stats.reset();

	if (m_1c0)
	{
		delete m_1c0;
		m_1c0 = 0;
	}
	if (m_220)
	{
		delete m_220;
		m_220 = 0;
	}
	m_224 = 0;
	if (m_228)
	{
		delete m_228;
		m_228 = 0;
	}
	if (m_22c)
	{
		delete m_22c;
		m_22c = 0;
	}
	m_defaultTeam = 0;
	m_260 = 0;

	m_274.m_vector.clear();
	m_274.m_field = 0;

	if (m_playerRelations)
		delete m_playerRelations;
	m_playerRelations = new Rva000DA590Map;
	if (m_teamRelations)
		delete m_teamRelations;
	m_teamRelations = new TeamRelationMap;

	m_294 = true;
	m_295 = true;
	m_296 = false;
	m_297 = false;
	m_298 = 1.0f;
	m_29c = true;
	m_29d = false;
	m_29e = false;
	for (UnsignedInt i = 0; i < 32; ++i)
	{
		m_29f[i] = false;
		m_2c4[i] = 0;
	}
	m_2c0 = 0;
	m_344 = 0;
	m_scoreKeeper.reset(m_playerIndex);
	m_63c = 0;
	m_644 = 0;
	m_648 = 0;

	for (Int s = 0; s < 10; ++s)
	{
		if (m_squads[s])
			delete m_squads[s];
		m_squads[s] = new Squad;
	}
	if (m_currentSelection)
		delete m_currentSelection;
	m_currentSelection = new Squad;

	m_680 = false;
	m_681 = true;
	m_684.forward();

	if (pt)
	{
		m_0c = pt->m_0c;
		m_playerName.clear();
		m_playerNameKey = 0;
		m_side = pt->m_side;
		m_playerType = 1;
		m_money = pt->m_money;
		m_money.m_playerIndex = m_playerIndex;
		if (m_money.m_money == 0)
			m_money.deposit(TheWritableGlobalData->m_defaultStartingCash, false);
		m_color = pt->m_preferredColor.getAsInt() | 0xff000000;
		m_nightColor = m_color;
		m_productionCostChanges = pt->m_productionCostChanges;
		m_1d8 = pt->m_6c;
		m_1ec = m_1d8;
		m_200.clear();
		m_productionVeterancyLevels = pt->m_productionVeterancyLevels;
		for (Rva000D6770Table::iterator it = m_1d8.begin(); it != m_1d8.end(); ++it)
			m_200[(*it).m_key] = Rva000D6C60MappedZero;
		Bool bc = pt->m_bc;
		m_296 = bc;
		m_680 = bc;
	}
	else
	{
		m_playerDisplayName = UnicodeString::TheEmptyString;
		m_0c.reset();
		m_playerName = TheEmptyAsciiString;
		m_playerNameKey = TheNameKeyGenerator->nameToKey(TheEmptyAsciiString.str());
		m_side.setEmpty();
		m_money.m_playerIndex = m_playerIndex;
		UnsignedInt neutral = g_neutralColor000DA610;
		m_playerType = 1;
		m_money.m_money = 0;
		m_color = neutral;
		m_nightColor = neutral;
		m_productionCostChanges.clear();
		m_1d8.clear();
		m_1ec.clear();
		m_200.clear();
		m_productionVeterancyLevels.clear();
		m_playerRelations->m_map[getPlayerIndex()] = ALLIES;
	}

	m_30.reset();
	if (m_playerTemplate)
		reinterpret_cast<BfmePlayerMapState *>(&m_30)->bfmeNewMap(m_playerIndex, m_playerTemplate->m_118);
	else
		reinterpret_cast<BfmePlayerMapState *>(&m_30)->bfmeNewMap(m_playerIndex, false);
	resetRank();
	m_sciencesDisabled.clear();
	m_sciencesHidden.clear();
	reinterpret_cast<Rva000D95C0Player *>(this)->applyInitialUpgrades();

	{
		_STL::list<Timer000DA610>::iterator it = m_timers.begin();
		while (it != m_timers.end())
		{
			Timer000DA610 *sprt = &(*it);
			it = m_timers.erase(it);
			if (sprt)
				sprt->clear();
		}
	}

	_STL::list<KindChange000DA610 *>::iterator kit = m_kindChanges.begin();
	while (kit != m_kindChanges.end())
	{
		KindChange000DA610 *tof = *kit;
		kit = m_kindChanges.erase(kit);
		if (tof)
			delete tof;
	}

	m_64c.clear();
	m_698.clear();
}
