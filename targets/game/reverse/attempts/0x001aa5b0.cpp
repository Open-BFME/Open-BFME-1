// ?resolve@TerrainLogicFireSpreadHelper@@QAEPAVObject@@PAVTerrainLogicFireSpreadRecord@@@Z
// partial score=0.42 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// BFME TerrainLogic helper at retail RVA 0x001AA5B0 (367 bytes).
//
// The matched FireSpreadUpdate::update caller supplies TheTerrainLogic and
// consumes this body's Object* result as the receiver of findModule.  The
// helper first turns a terrain P48 record into an object; its no-record path
// performs the same ten-unit filtered partition query used by FireSpread.

// stlport

typedef bool Bool;
typedef int Int;
typedef float Real;

class Object;
class Team;
class ThingTemplate;
class TerrainLogic;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct ObjectStatusMaskType
{
	unsigned int m_bits[3];
};

struct KindOfMaskType
{
	unsigned int m_bits[6];

	KindOfMaskType(Int bit)
	{
		m_bits[0] = 0;
		m_bits[1] = 0;
		m_bits[2] = 0;
		m_bits[3] = 0;
		m_bits[4] = 0;
		m_bits[5] = 0;
		m_bits[bit >> 5] = 1u << (bit & 31);
	}
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *object) = 0;
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		Int distanceCalculation, PartitionFilter *filters);
};

class ThingFactory
{
};

class TerrainLogicFireSpreadRecord
{
	public:
	int m_word00;
	int m_word04;
	int m_word08;
	int m_key;
	int m_word10;
	const ThingTemplate *m_template;
	unsigned char m_byte18;
	unsigned char m_pad19[0x0F];
	int m_word28;
	unsigned char m_byte2c;
	unsigned char m_byte2d;
	unsigned char m_pad2e[2];
};

class BfmeQ1275
{
public:
	BfmeQ1275()
	{
		m_word0c = 0;
		m_word10 = 0x4B189680;
		m_word14 = 0;
		m_word00 = 0;
		m_word04 = 0;
		m_word08 = 0;
	}

	void *m_word00;
	int m_word04;
	int m_word08;
	int m_word0c;
	int m_word10;
	TerrainLogicFireSpreadRecord *m_word14;
};

class BfmeA1275
{
public:
	void bfmeDo1275(int a1, int a2, BfmeQ1275 *query, int a3, int a4);
};

class PartitionFilterFlammable : public PartitionFilter
{
public:
	PartitionFilterFlammable() {}
	virtual Bool allow(Object *object);
};

struct VptrZeroBlock24
{
	unsigned int m_dword00;
	unsigned int m_dword04;
	unsigned int m_dword08;
	unsigned int m_dword0c;
	unsigned int m_dword10;
	unsigned int m_dword14;
};

class Rva000C3DD0VptrZeroBlockObject : public PartitionFilter
{
public:
	Rva000C3DD0VptrZeroBlockObject(const VptrZeroBlock24 &first,
		const VptrZeroBlock24 &second);
	virtual Bool allow(Object *object);
	VptrZeroBlock24 m_first;
	VptrZeroBlock24 m_second;
};

class TerrainLogicP48Clear
{
public:
	void clear(int key);
};

class Rva002EE330PlayerList
{
public:
	char m_pad00[0x14];
	struct PlayerListState
	{
		char m_pad00[0x230];
		Team *m_currentTeam;
	};
	PlayerListState *m_state;
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;
extern ThingFactory *TheThingFactory;
extern TerrainLogic *TheTerrainLogic;
extern PartitionManager *ThePartitionManager;

static const KindOfMaskType &terrainFireSpreadKindOfMaskNone =
	*(const KindOfMaskType *)0x012ED8B8;

static __forceinline Object *terrainFireSpreadNewObject(
	ThingFactory *factory, const ThingTemplate *thingTemplate, Team *team,
	const volatile ObjectStatusMaskType &statusBits, void *extra)
{
	typedef Object *(ThingFactory::*NewObjectCall)(
		const ThingTemplate *, Team *, const volatile ObjectStatusMaskType &, void *);
	union { void (*raw)(); NewObjectCall member; } call;
	extern void j_0004494a();
	call.raw = j_0004494a;
	return (factory->*call.member)(thingTemplate, team, statusBits, extra);
}

static __forceinline void terrainFireSpreadSetPosition(
	Object *object, const TerrainLogicFireSpreadRecord *record)
{
	class BfmeHostTP
	{
	public:
		void setPosition(const TerrainLogicFireSpreadRecord *position, bool flag);
	};
	typedef void (BfmeHostTP::*SetPositionCall)(
		const TerrainLogicFireSpreadRecord *, bool);
	union { void (*raw)(); SetPositionCall member; } call;
	extern void j_0001621b();
	call.raw = j_0001621b;
	(reinterpret_cast<BfmeHostTP *>(object)->*call.member)(record, false);
}

// ?resolve@TerrainLogicFireSpreadHelper@@QAEPAVObject@@PAVTerrainLogicFireSpreadRecord@@@Z
class TerrainLogicFireSpreadHelper
{
public:
	Object *resolve(TerrainLogicFireSpreadRecord *record);
};

Object *TerrainLogicFireSpreadHelper::resolve(TerrainLogicFireSpreadRecord *record)
{
	BfmeQ1275 query;
	(reinterpret_cast<BfmeA1275 *>(this))->bfmeDo1275(
		reinterpret_cast<int>(record), 0x41200000, &query, 0, 0);

	TerrainLogicFireSpreadRecord *found = query.m_word14;
	if (found != 0)
	{
		if (found->m_template == 0)
			return 0;

		ObjectStatusMaskType statusBits;
		Rva002EE330PlayerList *players = Rva002EE330ThePlayers;
		Team *team = players->m_state->m_currentTeam;
		Object *object = terrainFireSpreadNewObject(
			TheThingFactory, found->m_template, team, statusBits, 0);
		terrainFireSpreadSetPosition(object, found);

		int key = found->m_key;
		found->m_word00 = 0;
		found->m_word04 = 0;
		found->m_word08 = 0;
		found->m_key = 0;
		found->m_word10 = 0;
		found->m_template = 0;
		found->m_byte18 = 0;
		found->m_word28 = 1;
		found->m_byte2c = 1;
		found->m_byte2d = 1;
		reinterpret_cast<TerrainLogicP48Clear *>(TheTerrainLogic)->clear(key);
		return object;
	}

	KindOfMaskType wanted(117);
	Rva000C3DD0VptrZeroBlockObject kindFilter(
		*(const VptrZeroBlock24 *)&wanted,
		*(const VptrZeroBlock24 *)&terrainFireSpreadKindOfMaskNone);
	PartitionFilterFlammable flammableFilter;
	flammableFilter.link(&kindFilter);
	return ThePartitionManager->getClosestObject(
		reinterpret_cast<const Coord3D *>(record), 10.0f, 1,
		&flammableFilter);
}
