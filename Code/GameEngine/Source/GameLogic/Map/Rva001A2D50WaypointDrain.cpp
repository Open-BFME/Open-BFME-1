// cl: /O2 /DNDEBUG /MD
// Drains the BFME waypoint list global at 0x012EF4D0 by virtual delete.

class Waypoint
{
public:
	virtual ~Waypoint();
};

extern Waypoint *g_waypointListHead;

void rva001A2D50(void)
{
	while (g_waypointListHead)
		delete g_waypointListHead;
}
