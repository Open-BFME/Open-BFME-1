// ?setGoalWaypoint@AIStateMachine@@QAEXPBVWaypoint@@@Z
// BFME AIStateMachine::setGoalWaypoint, RVA 0x0016AEB0, 10 bytes: stores m_goalWaypoint at +0x50.
// Evidence: targets/game/reverse/identity_evidence/0016aeb0.md.

class Waypoint;

class AIStateMachine
{
public:
	void setGoalWaypoint(const Waypoint *way);
	char m_lead[0x50];
	const Waypoint *m_goalWaypoint;
};

void AIStateMachine::setGoalWaypoint(const Waypoint *way)
{
	m_goalWaypoint = way;
}
