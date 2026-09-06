// Two more: a second ten word mask with the same intersection, and an axis
// classifier.

class BfmeBitsNB
{
public:
	void bfmeAndWith(const BfmeBitsNB *other);
private:
	unsigned int m_bfmeWords[10];
};

void BfmeBitsNB::bfmeAndWith(const BfmeBitsNB *other)
{
	m_bfmeWords[0] &= other->m_bfmeWords[0];
	m_bfmeWords[1] &= other->m_bfmeWords[1];
	m_bfmeWords[2] &= other->m_bfmeWords[2];
	m_bfmeWords[3] &= other->m_bfmeWords[3];
	m_bfmeWords[4] &= other->m_bfmeWords[4];
	m_bfmeWords[5] &= other->m_bfmeWords[5];
	m_bfmeWords[6] &= other->m_bfmeWords[6];
	m_bfmeWords[7] &= other->m_bfmeWords[7];
	m_bfmeWords[8] &= other->m_bfmeWords[8];
	m_bfmeWords[9] &= other->m_bfmeWords[9];
}

extern "C" double fabs(double value);
#pragma intrinsic(fabs)

class BfmePointNC
{
public:
	float m_bfmeX;								// +0x00
	float m_bfmeY;								// +0x04
};

// Which way the offset leans, and which side of nothing it sits on.
int bfmeAxisOf(const BfmePointNC *offset)
{
	if ((float)fabs(offset->m_bfmeX) > (float)fabs(offset->m_bfmeY))
	{
		if (offset->m_bfmeX > 0.0f)
			return 1;
		return 2;
	}

	if (offset->m_bfmeY > 0.0f)
		return 0;
	return 3;
}

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

// The caller at retail 0x00360400 uses this member after the InitialWalkOn
// lookup fails. The two format strings and TerrainLogic slot 31 identify the
// axis-specific SpawnPoint and GatherPoint lookup.
class BfmeFirstWalkOnArmy
{
public:
	bool lookupWaypoints(const BfmePointNC *point, Waypoint **outSpawn, Waypoint **outGather);
	void armyNameFromIndex(unsigned int index, AsciiString *out);
};

bool BfmeFirstWalkOnArmy::lookupWaypoints(
	const BfmePointNC *point, Waypoint **outSpawn, Waypoint **outGather)
{
	int axis = bfmeAxisOf(point);
	AsciiString name;
	armyNameFromIndex(axis, &name);
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
