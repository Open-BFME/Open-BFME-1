// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AerialPathfinder no-fly-zone ceiling query, retail 0x00148A10.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef float Real;
typedef bool Bool;

struct ICoord3D
{
	Int x;
	Int y;
	Int z;
};

class PolygonTrigger
{
public:
	Bool pointInTrigger(ICoord3D &point) const;
};

struct NoFlyZone
{
	PolygonTrigger *m_trigger;
	Real m_height;
};

class AerialPathfinder
{
public:
	Real getNoFlyZoneHeight(Real x, Real y);

private:
	char m_slice_pad[0x0C];
	_STL::list<NoFlyZone> m_noFlyZones;
};

struct NoFlyQueryState
{
	Real height;
	Int padding;
	Real zoneHeight;
	ICoord3D location;
};

Real AerialPathfinder::getNoFlyZoneHeight(Real x, Real y)
{
	NoFlyQueryState state;

	if (m_noFlyZones.empty())
		return -9999.0f;

	_STL::list<NoFlyZone>::iterator it = m_noFlyZones.begin();
	state.height = -9999.0f;
	while (it != m_noFlyZones.end())
	{
		NoFlyZone *zone = &*it;
		PolygonTrigger *trigger = zone->m_trigger;
		state.zoneHeight = zone->m_height;
		state.location.x = (Int)x;
		state.location.y = (Int)y;
		state.location.z = 0;
		Bool inside = trigger->pointInTrigger(state.location);
		if (inside && !(state.height > state.zoneHeight))
			state.height = state.zoneHeight;
		++it;
	}

	return state.height;
}
