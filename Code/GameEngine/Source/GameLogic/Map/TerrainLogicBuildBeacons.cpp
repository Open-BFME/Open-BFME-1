// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// TerrainLogic::buildBeacons, retail 0x001ADF10, 465 bytes.
//
// Identity: the body's own string literal at 0x0109C520 reads
// "TerrainLogic::buildBeacons - A beacon waypoint path has more than one
// link. Not allowed.", which names class and method.  The matched
// TerrainLogic::newMap at 0x001AE190 is the single caller, and the body
// dispatches TerrainLogic vtable slot 0x78 on its own ECX receiver, so the
// private no-argument member encoding of the existing 0x001ADF10 pin holds.
//
// ECX/ESI holds `this` only up to +0x67; from there ESI walks a Waypoint,
// so +0x0c, +0x20, +0x4c and +0x60 are Waypoint fields.  Earlier passes read
// +0x4c as a TerrainLogic field and were chasing a layout that is not there.
// TerrainLogic keeps the beacon path list at +0x48; its out-of-line clear()
// is the ledger row at 0x001ACC70, whose element type carries that address,
// so the element struct keeps that name and the resolver finds the body.
//
// _STLP_NO_EXCEPTIONS is what lets list::_M_create_node inline the way retail
// has it: with _STLP_TRY/_STLP_UNWIND expanded, MSVC 7.1 refuses to inline it
// and both node constructions become calls.  The EH frame and its three
// states still come from /EHsc and the path list's own destructor.

#include <list>

typedef bool Bool;
typedef float Real;
typedef int Int;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

typedef _STL::list<Coord3D> Coord3DList;

// Element type of the beacon path list.  The name is the one the resolver
// already holds for _List_base<...>::clear() at 0x001ACC70.
struct Gen_t_001acc70_p4cd : public Coord3DList
{
	Gen_t_001acc70_p4cd() {}
	Gen_t_001acc70_p4cd(const Gen_t_001acc70_p4cd &other) : Coord3DList(other) {}
};

// Layout shared with the matched TerrainLogic::newMap: the location is at
// +0x0c and the all-waypoints link at +0x1c.  The remaining reads keep
// offset-derived names; no witness names them.
class Waypoint
{
public:
	Waypoint *getNext(void) const
	{
		return m_next;
	}

	Waypoint *getPtr20(void) const
	{
		return m_ptr_20;
	}

	Int getDword4C(void) const
	{
		return m_dword_4c;
	}

	Int getDword60(void) const
	{
		return m_dword_60;
	}

	unsigned char m_unreconstructed_00[0x0c];
	Coord3D m_location;
	unsigned char m_unreconstructed_18[4];
	Waypoint *m_next;
	Waypoint *m_ptr_20;
	unsigned char m_unreconstructed_24[0x28];
	Int m_dword_4c;
	unsigned char m_unreconstructed_50[0x10];
	Int m_dword_60;
};

class BfmeAwakenLog
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C(int report);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern void _bfme_debugRecordCallsite(int kind);
extern bool _bfme_debugReportingEnabled(void);

class TerrainLogic
{
public:
	virtual void tlSlot00(void) = 0;
	virtual void tlSlot04(void) = 0;
	virtual void tlSlot08(void) = 0;
	virtual void tlSlot0C(void) = 0;
	virtual void tlSlot10(void) = 0;
	virtual void tlSlot14(void) = 0;
	virtual void tlSlot18(void) = 0;
	virtual void tlSlot1C(void) = 0;
	virtual void tlSlot20(void) = 0;
	virtual void tlSlot24(void) = 0;
	virtual void tlSlot28(void) = 0;
	virtual void tlSlot2C(void) = 0;
	virtual void tlSlot30(void) = 0;
	virtual void tlSlot34(void) = 0;
	virtual void tlSlot38(void) = 0;
	virtual void tlSlot3C(void) = 0;
	virtual void tlSlot40(void) = 0;
	virtual void tlSlot44(void) = 0;
	virtual void tlSlot48(void) = 0;
	virtual void tlSlot4C(void) = 0;
	virtual void tlSlot50(void) = 0;
	virtual void tlSlot54(void) = 0;
	virtual void tlSlot58(void) = 0;
	virtual void tlSlot5C(void) = 0;
	virtual void tlSlot60(void) = 0;
	virtual void tlSlot64(void) = 0;
	virtual void tlSlot68(void) = 0;
	virtual void tlSlot6C(void) = 0;
	virtual void tlSlot70(void) = 0;
	virtual void tlSlot74(void) = 0;
	virtual Waypoint *tlSlot78(void) = 0;

private:
	unsigned char m_unreconstructed_04[0x44];
	_STL::list<Gen_t_001acc70_p4cd> m_beaconPaths;

	void buildBeacons(void);
};

void TerrainLogic::buildBeacons(void)
{
	m_beaconPaths.clear();

	for (Waypoint *start = tlSlot78(); start != 0; start = start->getNext())
	{
		if (start->getDword60() != 5)
			continue;

		Gen_t_001acc70_p4cd path;

		for (Waypoint *way = start;;)
		{
			Coord3D point;
			point.x = way->m_location.x;
			point.y = way->m_location.y;
			point.z = way->m_location.z;
			path.push_front(point);

			Int links = way->getDword4C();
			if (links == 0)
				break;

			if (links != 1)
			{
				if (_bfme_debugReportingEnabled())
				{
					_bfme_debugRecordCallsite(1);
					TheBfmeAwakenDebug->slot60();
					TheBfmeAwakenDebug->slot6C(0, 0)->slot38(
						"TerrainLogic::buildBeacons - A beacon waypoint path has more than one link. Not allowed.")->slot4C(2);
				}

				path.clear();
				break;
			}

			way = way->getPtr20();
			if (way == start)
				break;
			if (way == 0)
				break;
		}

		if (!path.empty())
			m_beaconPaths.push_front(path);
	}
}
