// ?notifyMembers@Rva00155950Owner@@QAEXHH@Z
// The forwarded command is real: payload->target+0x20 is the member's
// AICommandInterface (AIGroupForwardedOrders.cpp reads the same chain), so the
// callee is AICommandInterface::aiMoveToAndEvacuate and this call reaches its
// ILT thunk 0x00027903 exactly as retail does. The owner's own symbol and its
// two int parameters are kept as the ledger has them; the casts are the only
// difference from the retail source.
#include "../../GameLogic/command_source_type.h"

struct Coord3D;

class AICommandInterface
{
public:
	void aiMoveToAndEvacuate(const Coord3D *position, CommandSourceType commandSource);
};

struct Rva00155950Target { char m_pad[0x20]; AICommandInterface m_commands; };
struct Rva00155950Payload { char m_pad[0x204]; Rva00155950Target* m_target; };
struct Rva00155950Link { Rva00155950Link* m_next; Rva00155950Link* m_prev; Rva00155950Payload* m_payload; };
struct Rva00155950Owner {
	int m_0;
	Rva00155950Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva00155950Owner::notifyMembers(int a, int b)
{
	for (Rva00155950Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva00155950Target* t = n->m_payload->m_target;
		if (t)
			t->m_commands.aiMoveToAndEvacuate((const Coord3D *)a, (CommandSourceType)b);
	}
}