// cl: /DNDEBUG /DWIN32 /MD /EHsc
// readable body of ?getWaterHandleByName@TerrainLogic@@UAEPBVWaterHandle@@VAsciiString@@@Z:
// Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
//
// The reference implementation is TerrainLogic::getWaterHandleByName.  The
// retail body uses the narrow StringBase<char> layout directly in its trigger
// name comparison: length is the word at data+4 and bytes begin at data+8.

#include <string.h>

#pragma intrinsic(memcmp)

typedef bool Bool;
typedef int Int;

struct BfmeAsciiStringData
{
	int m_refCount;
	unsigned short m_numChars;
	unsigned short m_numCharsAllocated;
};

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

	int compare(const char *text) const;

	int compare(const AsciiString &other) const
	{
		const BfmeAsciiStringData *otherData = other.m_data;
		Int otherLength = otherData ? otherData->m_numChars : 0;
		const char *otherChars = otherData ? (const char *)(otherData + 1) : "";
		Int selfLength = m_data ? m_data->m_numChars : 0;
		const char *selfChars = m_data ? (const char *)(m_data + 1) : "";
		Int length = selfLength < otherLength ? selfLength : otherLength;
		Int result = memcmp(selfChars, otherChars, length);
		if (result != 0)
			return result;
		return selfLength - otherLength;
	}

	const BfmeAsciiStringData *m_data;
};

class PolygonTrigger;

class WaterHandle
{
public:
	PolygonTrigger *m_polygon;
};

// The name and water-area offsets are independently visible in the retail
// body: m_triggerName is at +0x08 and m_isWaterArea is at +0x32.  The other
// members are deliberately not modeled because this body only dispatches
// getNext, isWaterArea, and getWaterHandle.
class PolygonTrigger
{
public:
	static PolygonTrigger *getFirstPolygonTrigger();

	PolygonTrigger *getNext() const
	{
		return m_nextPolygonTrigger;
	}

	const AsciiString &getTriggerName() const
	{
		return m_triggerName;
	}

	Bool isWaterArea() const
	{
		return m_isWaterArea;
	}

	const WaterHandle *getWaterHandle() const;

private:
	void *m_vtable;
	PolygonTrigger *m_nextPolygonTrigger;
	AsciiString m_triggerName;
	unsigned char m_unreconstructed_0c[0x26];
	Bool m_isWaterArea;
};

struct BfmePolygonTriggerTable
{
	PolygonTrigger *m_head;
};

extern "C" BfmePolygonTriggerTable *g_bfmePolygonTriggerTable;
extern "C" WaterHandle g_bfmeGridWaterHandle;

class TerrainLogic
{
public:
	virtual const WaterHandle *getWaterHandleByName(AsciiString name);
};

const WaterHandle *TerrainLogic::getWaterHandleByName(AsciiString name)
{
	if (name.compare("Water Grid") == 0)
		return &g_bfmeGridWaterHandle;

	PolygonTrigger *trig = g_bfmePolygonTriggerTable->m_head;
	while (trig)
	{
		if (trig->getTriggerName().compare(name) == 0 && trig->isWaterArea())
			return trig->getWaterHandle();
		trig = trig->getNext();
	}

	return 0;
}
