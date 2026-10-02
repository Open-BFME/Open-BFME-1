// ?notifyMembers@Rva00156630Owner@@QAEXHH@Z
#include "../../GameLogic/command_source_type.h"
class Object;
class AICommandInterface { public: void aiExit(Object *, CommandSourceType); };
struct Rva00156630Target { char m_pad[0x20]; };
struct Rva00156630Payload { char m_pad[0x204]; Rva00156630Target* m_target; };
struct Rva00156630Link { Rva00156630Link* m_next; Rva00156630Link* m_prev; Rva00156630Payload* m_payload; };
struct Rva00156630Owner {
	int m_0;
	Rva00156630Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva00156630Owner::notifyMembers(int a, int b)
{
	for (Rva00156630Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva00156630Target* t = n->m_payload->m_target;
		if (t)
			reinterpret_cast<AICommandInterface*>(reinterpret_cast<char*>(t) + 0x20)->aiExit(reinterpret_cast<Object*>(a), static_cast<CommandSourceType>(b));
	}
}
