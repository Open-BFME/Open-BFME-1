// ?notifyMembers@Rva001559B0Owner@@QAEXHH@Z
// The forwarded command is real: payload->target+0x20 is the member's
// AICommandInterface (AIGroupForwardedOrders.cpp reads the same chain), so the
// callee is AICommandInterface::aiMoveToAndEvacuateAndExit and this call reaches
// its ILT thunk 0x00038B9A exactly as retail does. The owner's own symbol and its
// two int parameters are kept as the ledger has them; the casts are the only
// difference from the retail source.
#include "../../GameLogic/command_source_type.h"

struct Coord3D;

class AICommandInterface
{
public:
	void aiMoveToAndEvacuateAndExit(const Coord3D *position, CommandSourceType commandSource);
};

struct Rva001559B0Target { char m_pad[0x20]; AICommandInterface m_commands; };
struct Rva001559B0Payload { char m_pad[0x204]; Rva001559B0Target* m_target; };
struct Rva001559B0Link { Rva001559B0Link* m_next; Rva001559B0Link* m_prev; Rva001559B0Payload* m_payload; };
struct Rva001559B0Owner {
	int m_0;
	Rva001559B0Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva001559B0Owner::notifyMembers(int a, int b)
{
	for (Rva001559B0Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva001559B0Target* t = n->m_payload->m_target;
		if (t)
			t->m_commands.aiMoveToAndEvacuateAndExit((const Coord3D *)a, (CommandSourceType)b);
	}
}