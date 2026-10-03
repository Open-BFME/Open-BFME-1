// ?notifyMembers@Rva00156320Owner@@QAEXHH@Z
// The forwarded command is real: payload->target+0x20 is the member's
// AICommandInterface (AIGroupForwardedOrders.cpp reads the same chain), so the
// callee is AICommandInterface::aiResumeConstruction and this call reaches its
// ILT thunk 0x00041B14 exactly as retail does. The owner's own symbol and its
// two int parameters are kept as the ledger has them; the casts are the only
// difference from the retail source.
#include "../../GameLogic/command_source_type.h"

class Object;

class AICommandInterface
{
public:
	void aiResumeConstruction(Object *object, CommandSourceType commandSource);
};

struct Rva00156320Target { char m_pad[0x20]; AICommandInterface m_commands; };
struct Rva00156320Payload { char m_pad[0x204]; Rva00156320Target* m_target; };
struct Rva00156320Link { Rva00156320Link* m_next; Rva00156320Link* m_prev; Rva00156320Payload* m_payload; };
struct Rva00156320Owner {
	int m_0;
	Rva00156320Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva00156320Owner::notifyMembers(int a, int b)
{
	for (Rva00156320Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva00156320Target* t = n->m_payload->m_target;
		if (t)
			t->m_commands.aiResumeConstruction((Object *)a, (CommandSourceType)b);
	}
}