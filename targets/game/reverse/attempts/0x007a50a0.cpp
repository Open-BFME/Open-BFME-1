// ?rva007A50A0RebuildPolygonOwners@WaterRenderObjClass@@QAEX_N@Z
// partial score=0.55 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc
// stlport
// Address-derived: identity of the METHOD is unproven, but the layout is:
// +0x2ac is the same WaterRenderObjClass member the only known caller
// (retail 0x007A7D70, through ILT 0x000151D6) reads right after this call
// returns, and this body itself opens by calling the real
// ?updateMapOverrides@WaterRenderObjClass@@AAEXXZ (ILT 0x00028B8C, body
// 0x007A1330).  It then walks g_bfmePolygonTriggerTable -- the same table
// TerrainLogic::getWaterHandle walks in
// Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp, whose
// BFMETerrainWaterPolygonView proves m_next@+4, m_numPoints@+0x14 and
// m_isWaterArea@+0x32 -- and for every water-area trigger with more than two
// points, constructs a Rva007A1230ArrayOwner(trigger) (constructor
// 0x007A4FD0, class 0x80 bytes; Code/GameEngineDevice/Source/W3DDevice/
// GameClient/Water/WaterPolygon.cpp) and appends the pointer to a
// std::list<Rva007A1230ArrayOwner *> at +0x2ac (the 12-byte STLport list
// node and the insert-before-sentinel store shape are the retail evidence).
// The sole caller always passes literal 0 for the one Bool argument (pushed
// from a register it zeroed and never wrote again), and this body never
// reads it.

#include <list>

typedef bool Bool;
typedef int Int;

class Rva007A1230ArrayOwner
{
public:
	Rva007A1230ArrayOwner( void *source );

private:
	unsigned char m_opaque[ 0x80 ];
};

// upstream layout: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// (BFMETerrainWaterPolygonView) -- only the three fields this body reads.
class BFMEWaterPolygonTriggerView
{
public:
	BFMEWaterPolygonTriggerView *getNext() const { return m_next; }
	Int getNumPoints() const { return m_numPoints; }
	Bool isWaterArea() const { return m_isWaterArea; }

private:
	unsigned char m_unmodelled_00[ 4 ];
	BFMEWaterPolygonTriggerView *m_next;			// +0x04
	unsigned char m_unmodelled_08[ 0x14 - 0x08 ];
	Int m_numPoints;								// +0x14
	unsigned char m_unmodelled_18[ 0x32 - 0x18 ];
	Bool m_isWaterArea;								// +0x32
};

struct BFMEWaterPolygonTriggerTableView
{
	BFMEWaterPolygonTriggerView *m_head;
};

extern "C" BFMEWaterPolygonTriggerTableView *g_bfmePolygonTriggerTable;

class WaterRenderObjClass
{
public:
	void rva007A50A0RebuildPolygonOwners( Bool );

private:
	void updateMapOverrides();

	unsigned char m_unmodelled_00[ 0x2ac ];
	std::list<Rva007A1230ArrayOwner *> m_polygonOwners;	// +0x2ac
};

void WaterRenderObjClass::rva007A50A0RebuildPolygonOwners( Bool )
{
	updateMapOverrides();

	for ( BFMEWaterPolygonTriggerView *trigger = g_bfmePolygonTriggerTable->m_head;
		trigger; trigger = trigger->getNext() )
	{
		if ( trigger->isWaterArea() && trigger->getNumPoints() > 2 )
		{
			Rva007A1230ArrayOwner *owner = new Rva007A1230ArrayOwner( trigger );
			m_polygonOwners.push_back( owner );
		}
	}
}
