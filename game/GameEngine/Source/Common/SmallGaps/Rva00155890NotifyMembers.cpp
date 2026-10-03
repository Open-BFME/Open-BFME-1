// ?notifyMembers@Rva00155890Owner@@QAEXHH@Z
// The forwarded command is real: payload->target+0x20 is the member's
// AICommandInterface (AIGroupForwardedOrders.cpp reads the same chain), so the
// callee is AICommandInterface::aiFollowWaypointPath and this call reaches its
// ILT thunk 0x00031179 exactly as retail does. The owner's own symbol and its
// two int parameters are kept as the ledger has them; the casts are the only
// difference from the retail source.
#include "../../GameLogic/command_source_type.h"

class Waypoint;

class AICommandInterface
{
public:
	void aiFollowWaypointPath(const Waypoint *waypoint, CommandSourceType commandSource);
};

struct Rva00155890Target { char m_pad[0x20]; AICommandInterface m_commands; };
struct Rva00155890Payload { char m_pad[0x204]; Rva00155890Target* m_target; };
struct Rva00155890Link { Rva00155890Link* m_next; Rva00155890Link* m_prev; Rva00155890Payload* m_payload; };
struct Rva00155890Owner {
	int m_0;
	Rva00155890Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva00155890Owner::notifyMembers(int a, int b)
{
	for (Rva00155890Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva00155890Target* t = n->m_payload->m_target;
		if (t)
			t->m_commands.aiFollowWaypointPath((const Waypoint *)a, (CommandSourceType)b);
	}
}