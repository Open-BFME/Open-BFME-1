// ?replayEntries@Rva00367E30Owner@@QAEXPAURva00367E30Sink@@@Z
struct Rva00367E30Logic { char m_pad[0x3c]; int m_frame; };
// Retail's GameLogic singleton (0x012F0898) is EA's `GameLogic *TheGameLogic`
// (mangled ?TheGameLogic@@3PAVGameLogic@@A, defined in GameLogic.cpp).  This TU
// keeps its own partial view of the object and casts at each use.
#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#define OBJECT_TU_MEMBERS bool applyAttributeModifier(const AsciiString &name, int duration);
#include "../../GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS

class GameLogic;
extern GameLogic* TheGameLogic;
struct Rva00367E30Entry { int m_0; int m_data; int m_frame; int m_c; };
struct Rva00367E30Sink {};
struct Rva00367E30Owner {
	char m_pad[0x20];
	Rva00367E30Entry* m_begin;
	Rva00367E30Entry* m_end;
	void replayEntries(Rva00367E30Sink* sink);
};
void Rva00367E30Owner::replayEntries(Rva00367E30Sink* sink)
{
	if (!sink)
		return;
	for (Rva00367E30Entry* e = m_begin; e != m_end; ++e)
		((Object *)sink)->applyAttributeModifier(*(const AsciiString *)&e->m_data,
			e->m_frame - ((Rva00367E30Logic*)TheGameLogic)->m_frame);
}
