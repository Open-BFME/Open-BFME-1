// ?notifyMembers@Rva00156630Owner@@QAEXHH@Z
#include "../../GameLogic/command_source_type.h"
class Object;
class AICommandInterface { public: void aiExit(Object *, CommandSourceType); };
// Retail calls the ILT stub 0x0000A5DD (gen_small ?j_0000a5dd), not the body.
void j_0000a5dd(void);
typedef void (AICommandInterface::*AiExitCall)(Object *, CommandSourceType);
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
		if (t) {
			union { void (*raw)(void); AiExitCall member; } call;
			call.raw = j_0000a5dd;
			(reinterpret_cast<AICommandInterface*>(reinterpret_cast<char*>(t) + 0x20)->*call.member)(reinterpret_cast<Object*>(a), static_cast<CommandSourceType>(b));
		}
	}
}
