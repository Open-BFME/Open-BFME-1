// ?rebuildPolygonList007A50A0@WaterRenderObjClass@@QAEXH@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

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

class BFMEWaterPolygonTriggerView
{
public:
	BFMEWaterPolygonTriggerView *getNext() const { return m_next; }
	Int getNumPoints() const { return m_numPoints; }
	Bool isWaterArea() const { return m_isWaterArea; }

private:
	unsigned char m_unmodelled_00[ 4 ];
	BFMEWaterPolygonTriggerView *m_next;
	unsigned char m_unmodelled_08[ 0x14 - 0x08 ];
	Int m_numPoints;
	unsigned char m_unmodelled_18[ 0x32 - 0x18 ];
	Bool m_isWaterArea;
};

struct BFMEWaterPolygonTriggerTableView
{
	BFMEWaterPolygonTriggerView *m_head;
};

extern int *g_rva0018EC80;		// retail 0x012ACB50, defined in Rva0018EC80Get.cpp

class WaterRenderObjClass
{
public:
	void rebuildPolygonList007A50A0(int);

private:
	void updateMapOverrides() throw();

	unsigned char m_unmodelled_00[ 0x2ac ];
	std::list<Rva007A1230ArrayOwner *> m_polygonOwners;
};

void WaterRenderObjClass::rebuildPolygonList007A50A0(int)
{
	BFMEWaterPolygonTriggerView *trigger = ((BFMEWaterPolygonTriggerTableView*)g_rva0018EC80)->m_head;
	updateMapOverrides();

	for ( ; trigger; trigger = trigger->getNext() )
	{
		if ( trigger->isWaterArea() && trigger->getNumPoints() > 2 )
		{
			Rva007A1230ArrayOwner *owner = new Rva007A1230ArrayOwner( trigger );
			m_polygonOwners.push_back( owner );
		}
	}
}
