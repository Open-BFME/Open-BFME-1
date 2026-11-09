// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AerialPathfinder::addNoFlyZone, retail 0x00148C10, 75 bytes.
//
// A null trigger does nothing; otherwise the trigger and its radius go into a
// two-word zone and onto the list at this+0x0C, which the node size of 0x10
// and the doubly-linked splice at the end identify.
//
// The element copy is the one thing that is not the obvious code: retail
// reaches STLport's _Construct through a cdecl call with both pointers on the
// stack -- the shared out-of-line copy the ledger already carries as
// tg_00148920 -- where an inlined _Construct would be a null-checked
// placement-new and four bytes shorter. Declaring the specialisation without a
// body is what reproduces the call.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef float Real;
typedef bool Bool;

class PolygonTrigger;

struct NoFlyZone
{
	NoFlyZone(void) {}

	PolygonTrigger *m_trigger;				// +0x00
	Real m_radius;						// +0x04
};

// Retail reaches the element copy through ILT 0x0002713D (?j_0002713d@@YAXXZ,
// target 0x00148920) with both pointers on the stack. The ILT is the only
// defined spelling of that call, so the node is built by hand below instead of
// through list::push_back's _Construct.
extern void j_0002713d();
typedef void (*NoFlyZoneConstructFn)(NoFlyZone *p, const NoFlyZone &val);

namespace _STL
{
class NoFlyZoneList : public list<NoFlyZone>
{
public:
	_Node *createNodeViaIlt(const NoFlyZone &zone)
	{
		_Node *node = this->_M_node.allocate(1);
		((NoFlyZoneConstructFn)j_0002713d)(&node->_M_data, zone);
		return node;
	}

	iterator insertViaIlt(iterator position, const NoFlyZone &zone)
	{
		_Node *tmp = createNodeViaIlt(zone);
		_List_node_base *n = position._M_node;
		_List_node_base *p = n->_M_prev;
		tmp->_M_next = n;
		tmp->_M_prev = p;
		p->_M_next = tmp;
		n->_M_prev = tmp;
		return tmp;
	}

	void pushBackViaIlt(const NoFlyZone &zone) { insertViaIlt(end(), zone); }
};
}

class AerialPathfinder
{
public:
	void addNoFlyZone(PolygonTrigger *trigger, Real zoneRadius);

private:
	char m_slice_pad[0x0C];					// retail this+0x00 .. +0x0B, untouched
	_STL::NoFlyZoneList m_noFlyZones;			// this+0x0C
};

void AerialPathfinder::addNoFlyZone(PolygonTrigger *trigger, Real zoneRadius)
{
	if (trigger)
	{
		NoFlyZone zone;
		zone.m_trigger = trigger;
		zone.m_radius = zoneRadius;
		m_noFlyZones.pushBackViaIlt(zone);
	}
}
