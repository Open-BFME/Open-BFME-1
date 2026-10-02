// ?notifyMembers@Rva001563E0Owner@@QAEXHH@Z
#include "../../GameLogic/command_source_type.h"
class Object;
class AICommandInterface { public: void aiGetRepaired(Object *, CommandSourceType); };
struct Rva001563E0Target { char m_pad[0x20]; };
struct Rva001563E0Payload { char m_pad[0x204]; Rva001563E0Target* m_target; };
struct Rva001563E0Link { Rva001563E0Link* m_next; Rva001563E0Link* m_prev; Rva001563E0Payload* m_payload; };
struct Rva001563E0Owner {
	int m_0;
	Rva001563E0Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva001563E0Owner::notifyMembers(int a, int b)
{
	for (Rva001563E0Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva001563E0Target* t = n->m_payload->m_target;
		if (t)
			reinterpret_cast<AICommandInterface*>(reinterpret_cast<char*>(t) + 0x20)->aiGetRepaired(reinterpret_cast<Object*>(a), static_cast<CommandSourceType>(b));
	}
}
