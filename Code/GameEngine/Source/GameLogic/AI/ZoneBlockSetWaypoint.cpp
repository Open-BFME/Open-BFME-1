// Maintain the compact twelve-entry waypoint array owned by a BFME ZoneBlock.
// Erase is unordered: the final entry replaces the removed slot.

typedef bool Bool;

class Waypoint;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class ZoneBlock
{
public:
	void bfmeSetWaypoint(Bool insert, Waypoint *waypoint);

private:
	int m_numWaypoints;
	int m_unknown04;
	Waypoint *m_waypoints[12];
};

// ?bfmeSetWaypoint@ZoneBlock@@QAEX_NPAVWaypoint@@@Z
void ZoneBlock::bfmeSetWaypoint(Bool insert, Waypoint *waypoint)
{
	if (insert)
	{
		if (m_numWaypoints < 12)
		{
			m_waypoints[m_numWaypoints] = waypoint;
			++m_numWaypoints;
		}
	}
	else
	{
		for (int i = 0; i < m_numWaypoints; ++i)
		{
			if (m_waypoints[i] == waypoint)
			{
				--m_numWaypoints;
				m_waypoints[i] = m_waypoints[m_numWaypoints];
				break;
			}
		}
	}
}
