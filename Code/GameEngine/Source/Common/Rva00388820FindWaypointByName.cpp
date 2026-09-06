// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Fuzzy twin: 0x000A7AF0 TerrainTypeCollection::findTerrain (r0.925), but the
// actual matching shape and classes come from the already-landed sibling
// ?getWaypointByName@TerrainLogic@@UAEPAVWaypoint@@VAsciiString@@@Z at
// 0x001AA900 (Code/GameEngine/Source/GameLogic/Map/TerrainLogicGetWaypointByName.cpp):
// same AsciiString/BfmeWaypointNameString/Waypoint layout and the same inlined
// compareWaypointName body (memcmp shorter-length compare, releaseBuffer via
// 0x00887940). This caller differs from that one by fetching the list head
// through TheTerrainLogic's vtable (slot +0x78, zero-argument, matching
// TerrainLogic::getFirstWaypoint's signature) instead of a plain global, and
// it does not short-circuit on an empty search name.
//
// retail 0x00388820, size 245, dump d_00384fd0.asm.
//   callees: 0x0001026C x1 -> pinned ?getName@Waypoint@@QBE?AVBfmeWaypointNameString@@XZ (still a dump)
//            0x00887940 x3 -> ?releaseBuffer@BFMERetailAsciiString@@AAEXXZ, matched, string_base.cpp
//   globals: 0x012EF4CC -> ?TheTerrainLogic@@3PAVTerrainLogic@@A

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

	const BfmeAsciiStringData *m_data;
};

class TerrainLogic;

class BfmeWaypointNameString
{
public:
	~BfmeWaypointNameString();

	const BfmeAsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
// Slot 0x78 padded with placeholder virtuals; only the getFirstWaypoint-shaped
// slot (zero args, returns Waypoint*) at +0x78 is real for this body.
class TerrainLogic
{
public:
	virtual void _slot00() = 0;
	virtual void _slot04() = 0;
	virtual void _slot08() = 0;
	virtual void _slot0c() = 0;
	virtual void _slot10() = 0;
	virtual void _slot14() = 0;
	virtual void _slot18() = 0;
	virtual void _slot1c() = 0;
	virtual void _slot20() = 0;
	virtual void _slot24() = 0;
	virtual void _slot28() = 0;
	virtual void _slot2c() = 0;
	virtual void _slot30() = 0;
	virtual void _slot34() = 0;
	virtual void _slot38() = 0;
	virtual void _slot3c() = 0;
	virtual void _slot40() = 0;
	virtual void _slot44() = 0;
	virtual void _slot48() = 0;
	virtual void _slot4c() = 0;
	virtual void _slot50() = 0;
	virtual void _slot54() = 0;
	virtual void _slot58() = 0;
	virtual void _slot5c() = 0;
	virtual void _slot60() = 0;
	virtual void _slot64() = 0;
	virtual void _slot68() = 0;
	virtual void _slot6c() = 0;
	virtual void _slot70() = 0;
	virtual void _slot74() = 0;
	virtual Waypoint *getFirstWaypoint(void) = 0;			// +0x78
};

extern TerrainLogic *TheTerrainLogic;

// ?d_00388820@@YAXXZ -- address-derived; real name/signature not recovered.
Waypoint *Rva00388820_FindWaypointByName( AsciiString name )
{
	for ( Waypoint *way = TheTerrainLogic->getFirstWaypoint(); way; way = way->getNext() )
	{
		if ( compareWaypointName( way->getName(), name ) == 0 )
			return way;
	}

	return 0;
}
