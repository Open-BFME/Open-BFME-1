// cl: /DNDEBUG /MD /EHsc
// Descriptive name from the three string literals; no named caller.
// Neighbour armyNameFromIndex is also stdcall. TerrainLogic getWaypointByName
// is vtable slot 31 (+0x7C) taking AsciiString by value.

typedef int Int;
typedef unsigned short UnsignedShort;

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	struct Data
	{
		Int m_refCount;
		UnsignedShort m_length;
		UnsignedShort m_capacity;
		T m_text[1];
	};
	Data *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void __cdecl format(AsciiString fmt, ...);
	const char *str() const { return m_data ? m_data->m_text : ""; }
};

class Waypoint;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual Waypoint *getWaypointByName(AsciiString name);
};

extern TerrainLogic *TheTerrainLogic;

// ?lookupInitialWalkOnWaypoints@@YG_NPAPAVWaypoint@@0@Z
bool __stdcall lookupInitialWalkOnWaypoints(Waypoint **outSpawn, Waypoint **outGather)
{
	AsciiString name("InitialWalkOn");
	AsciiString spawnPoint;
	AsciiString gatherPoint;
	spawnPoint.format(AsciiString("%sSpawnPoint"), name.str());
	gatherPoint.format(AsciiString("%sGatherPoint"), name.str());
	*outSpawn = TheTerrainLogic->getWaypointByName(spawnPoint);
	*outGather = TheTerrainLogic->getWaypointByName(gatherPoint);
	if (*outSpawn != 0)
	{
		if (*outGather != 0)
			return true;
	}
	return false;
}
