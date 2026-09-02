// cl: /DNDEBUG /MD /EHsc
//
// AIFollowWaypointPathState::getNextWaypoint — retail 0x0016C480 (75B).
// Named callers: AIFollowWaypointPathState::update and AIPanicState::update.
// ALLOW_BACKTRACK shape: random link in [0, 8), prior = current, setGoalPosition
// to current location. Waypoint links sit at +0x20, count at +0x4c, location at +0xC.

struct Coord3D
{
	float x, y, z;
};

class Waypoint
{
public:
	int getNumLinks() const { return m_numLinks; }
	const Waypoint *getLink(int ndx) const
	{
		if (ndx < 0 || ndx >= 8)
			return 0;
		return m_links[ndx];
	}
	const Coord3D *getLocation() const { return &m_location; }

private:
	void *m_vptr;
	int m_id;
	void *m_name;
	Coord3D m_location;
	unsigned char m_pad_018[8];
	const Waypoint *m_links[8];
	unsigned char m_pad_040[0xC];
	int m_numLinks;
};

class StateMachine
{
public:
	void setGoalPosition(const Coord3D *pos);
};

class AIFollowWaypointPathState
{
protected:
	const Waypoint *getNextWaypoint();
	StateMachine *getMachine() { return m_machine; }

private:
	void *m_vptr;
	unsigned char m_pad[0x18];
	StateMachine *m_machine;
	unsigned char m_pad_020[0x40];
	const Waypoint *m_currentWaypoint;
	const Waypoint *m_priorWaypoint;
};

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

const Waypoint *AIFollowWaypointPathState::getNextWaypoint()
{
	int linkCount = m_currentWaypoint->getNumLinks();
	int which = GetGameLogicRandomValue(
		0,
		linkCount - 1,
		"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp",
		0x22A6);
	const Waypoint *nextWay = m_currentWaypoint->getLink(which);
	m_priorWaypoint = m_currentWaypoint;
	getMachine()->setGoalPosition(m_currentWaypoint->getLocation());
	return nextWay;
}
