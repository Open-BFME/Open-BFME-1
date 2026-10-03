// ?notifyMembers@Rva001562C0Owner@@QAEXHH@Z
// The forwarded command is real: payload->target+0x20 is the member's
// AICommandInterface (AIGroupForwardedOrders.cpp reads the same chain), so the
// callee is AICommandInterface::aiRepair and this call reaches its ILT thunk
// 0x00029C08 exactly as retail does. The owner's own symbol and its two int
// parameters are kept as the ledger has them; the casts are the only difference
// from the retail source.
#include "../../GameLogic/command_source_type.h"

class Object;

class AICommandInterface
{
public:
	void aiRepair(Object *object, CommandSourceType commandSource);
};

struct Rva001562C0Target { char m_pad[0x20]; AICommandInterface m_commands; };
struct Rva001562C0Payload { char m_pad[0x204]; Rva001562C0Target* m_target; };
struct Rva001562C0Link { Rva001562C0Link* m_next; Rva001562C0Link* m_prev; Rva001562C0Payload* m_payload; };
struct Rva001562C0Owner {
	int m_0;
	Rva001562C0Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva001562C0Owner::notifyMembers(int a, int b)
{
	for (Rva001562C0Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva001562C0Target* t = n->m_payload->m_target;
		if (t)
			t->m_commands.aiRepair((Object *)a, (CommandSourceType)b);
	}
}