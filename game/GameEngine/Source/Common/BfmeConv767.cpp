// cl: /Igame/Libraries/Source/WWVegas/WWLib
//
// Rva00367E30Logic::rva003870f0, retail 0x003870F0, 45 bytes.
//
// __thiscall AsciiString getter taking const AsciiString& (hidden return
// slot, ret 8): forwards the name to the store at this+0x170 (ILT 0x00014943,
// 0x003636C0) and copy-constructs the result (StringBase<char> 0x00887B60)
// into the return slot. The matched caller Rva003BF540::applyOwner
// (0x003BF190 +0xDA) calls it on TheBfmeGameLogic through ILT 0x000228DB.
// Address-derived name; see targets/game/reverse/identity_evidence/003870f0.md.

#include "ascii_string.h"

// The ILT thunk at 0x00014943 is the retail body at this call site
// (targets/game/reverse/functions.csv ?j_00014943@@YAXXZ, 5 bytes, tail
// jmp to 0x003636C0).  Retail calls it thiscall with ECX = this+0x170 and
// the name in the hidden first stack slot, so the route is a member-pointer
// union over the defined thunk symbol rather than a TU-local placeholder.
extern void j_00014943();

class Rva00367E30Sub
{
public:
	void *route(void *what);
};

struct Rva00367E30Logic
{
	AsciiString rva003870f0(const AsciiString &name);

	unsigned char m_head[0x170];
};

AsciiString Rva00367E30Logic::rva003870f0(const AsciiString &name)
{
	union
	{
		void (*raw)();
		void *(Rva00367E30Sub::*member)(void *);
	} route;

	route.raw = j_00014943;
	return *(const AsciiString *)(
		reinterpret_cast<Rva00367E30Sub *>((char *)this + 0x170)->*route.member)((void *)&name);
}
