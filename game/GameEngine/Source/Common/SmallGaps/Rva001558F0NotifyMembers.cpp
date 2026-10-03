// ?notifyMembers@Rva001558F0Owner@@QAEXHH@Z
// The forwarded command is real: payload->target+0x20 is the member's
// AICommandInterface (AIGroupForwardedOrders.cpp reads the same chain), so the
// callee is AICommandInterface::aiFollowWaypointPathExact and this call reaches
// its ILT thunk 0x0002480C exactly as retail does. The owner's own symbol and its
// two int parameters are kept as the ledger has them; the casts are the only
// difference from the retail source.
#include "../../GameLogic/command_source_type.h"

class Waypoint;

class AICommandInterface
{
public:
	void aiFollowWaypointPathExact(const Waypoint *waypoint, CommandSourceType commandSource);
};

struct Rva001558F0Target { char m_pad[0x20]; AICommandInterface m_commands; };
struct Rva001558F0Payload { char m_pad[0x204]; Rva001558F0Target* m_target; };
struct Rva001558F0Link { Rva001558F0Link* m_next; Rva001558F0Link* m_prev; Rva001558F0Payload* m_payload; };
struct Rva001558F0Owner {
	int m_0;
	Rva001558F0Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva001558F0Owner::notifyMembers(int a, int b)
{
	for (Rva001558F0Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva001558F0Target* t = n->m_payload->m_target;
		if (t)
			t->m_commands.aiFollowWaypointPathExact((const Waypoint *)a, (CommandSourceType)b);
	}
}