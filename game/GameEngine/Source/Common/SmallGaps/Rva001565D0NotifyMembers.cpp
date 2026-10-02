// ?notifyMembers@Rva001565D0Owner@@QAEXHH@Z
#include "../../GameLogic/command_source_type.h"
struct Coord3D;
class AICommandInterface { public: void aiBfmeCommand19(const Coord3D *, CommandSourceType); };
struct Rva001565D0Target { char m_pad[0x20]; };
struct Rva001565D0Payload { char m_pad[0x204]; Rva001565D0Target* m_target; };
struct Rva001565D0Link { Rva001565D0Link* m_next; Rva001565D0Link* m_prev; Rva001565D0Payload* m_payload; };
struct Rva001565D0Owner {
	int m_0;
	Rva001565D0Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva001565D0Owner::notifyMembers(int a, int b)
{
	for (Rva001565D0Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva001565D0Target* t = n->m_payload->m_target;
		if (t)
			reinterpret_cast<AICommandInterface*>(reinterpret_cast<char*>(t) + 0x20)->aiBfmeCommand19(reinterpret_cast<const Coord3D*>(a), static_cast<CommandSourceType>(b));
	}
}
