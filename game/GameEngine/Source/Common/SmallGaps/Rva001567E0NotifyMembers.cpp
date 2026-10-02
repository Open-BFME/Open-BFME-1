// ?notifyMembers@Rva001567E0Owner@@QAEXHH@Z
#include "../../GameLogic/command_source_type.h"
class DamageInfo;
class AICommandInterface { public: void aiGoProne(const DamageInfo *, CommandSourceType); };
struct Rva001567E0Target { char m_pad[0x20]; };
struct Rva001567E0Payload { char m_pad[0x204]; Rva001567E0Target* m_target; };
struct Rva001567E0Link { Rva001567E0Link* m_next; Rva001567E0Link* m_prev; Rva001567E0Payload* m_payload; };
struct Rva001567E0Owner {
	int m_0;
	Rva001567E0Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva001567E0Owner::notifyMembers(int a, int b)
{
	for (Rva001567E0Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva001567E0Target* t = n->m_payload->m_target;
		if (t)
			reinterpret_cast<AICommandInterface*>(reinterpret_cast<char*>(t) + 0x20)->aiGoProne(reinterpret_cast<const DamageInfo*>(a), static_cast<CommandSourceType>(b));
	}
}
