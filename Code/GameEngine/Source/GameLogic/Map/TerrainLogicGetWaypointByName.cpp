// cl: /DNDEBUG /DWIN32 /MD /EHsc
// TerrainLogic::getWaypointByName, retail 0x001AA900.
//
// BFME keeps the waypoint chain in the same process-global list used by the
// Waypoint constructor/destructor bodies.  The name argument is an
// AsciiString value, and Waypoint::getName returns the separately named
// BfmeWaypointNameString value whose destructor is the retail StringBase
// destructor at 0x00887940.

#include <string.h>

#pragma intrinsic(memcmp)

typedef bool Bool;
typedef int Int;

struct BfmeAsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_numChars;
	unsigned short m_unreconstructed_06;
};

class AsciiString
{
public:
	~AsciiString();

	Bool isEmpty(void) const
	{
		return m_data == 0 || m_data->m_numChars == 0;
	}

	const BfmeAsciiStringData *m_data;
};

class TerrainLogic;

class BfmeWaypointNameString
{
friend class TerrainLogic;

private:
	~BfmeWaypointNameString();

public:
	const BfmeAsciiStringData *m_data;
};

class Waypoint
{
public:
	BfmeWaypointNameString getName(void) const;

	Waypoint *getNext(void) const
	{
		return m_next;
	}

private:
	unsigned char m_unreconstructed_00[0x1c];
	Waypoint *m_next;
};

extern Waypoint *g_waypointListHead;

static Int compareWaypointName(const BfmeWaypointNameString &self,
	const AsciiString &other)
{
	const BfmeAsciiStringData *otherData = other.m_data;
	Int otherLength;
	const char *otherChars;
	if (otherData) {
		otherLength = otherData->m_numChars;
		otherChars = (const char *)(otherData + 1);
	} else {
		otherLength = 0;
		otherChars = "";
	}
	const BfmeAsciiStringData *selfData = self.m_data;
	Int selfLength;
	if (selfData)
		selfLength = *(volatile const unsigned short *)((const char *)selfData + 4);
	else
		selfLength = 0;
	register unsigned int selfAddress;
	if (self.m_data)
		selfAddress = (unsigned int)(self.m_data + 1);
	else
		selfAddress = (unsigned int)"";
	Int length = selfLength < otherLength ? selfLength : otherLength;
	Int result = memcmp((const char *)selfAddress, otherChars, length);
	if (result == 0)
		result = selfLength - otherLength;
	return result;
}

class TerrainLogic
{
public:
	virtual Waypoint *getWaypointByName(AsciiString name);
};

Waypoint *TerrainLogic::getWaypointByName(AsciiString name)
{
	if (name.isEmpty())
		return 0;

	for (Waypoint *way = g_waypointListHead; way; way = way->getNext())
	{
		if (compareWaypointName(way->getName(), name) == 0)
			return way;
	}

	return 0;
}
