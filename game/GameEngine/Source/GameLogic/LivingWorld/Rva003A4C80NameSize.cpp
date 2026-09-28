// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x003A4C80/251: the receiver at ECX is passed UNCHANGED to the
// matched Rva003A48B0Owner::rva003A4BD0 through ILT 0x000394E6, and the
// argument at [ESP+0x0C] is the object the three StringBase<char>::compare
// calls run on (ECX = argument), so the parameter is an AsciiString, not the
// GameWindow* the lift name claimed.  No source-level spelling is known for
// the method either, so the address stays in the name.
//
// Only the "Small" arm calls the out-of-line state transition.  Retail expands
// the same transition for "Medium" and "Large" with the new state folded in --
// the second of its two switches collapses to a single lea and the state store
// becomes an immediate -- so those two arms are written here as calls to a
// TU-local helper carrying the transition body instead of being spelled out by
// hand.  Spelling the expansion out by hand compiles 251 bytes with the game
// pointer in EDI (it is live across the first applyByName call, so it takes the
// callee-saved register) and the new name rematerialised after that call;
// letting the compiler expand the shared body puts the pointer in ECX and
// materialises the new name in EDI before the first call, as retail does.
#include "ascii_string.h"

class BfmeGameCW
{
public:
	char m_pad00[0x188];
	AsciiString m_string188;
	AsciiString m_string18C;
	AsciiString m_string190;
};
extern BfmeGameCW *g_bfmeGameCW;
extern AsciiString Rva01336E50EmptyString;

class Rva003A48B0Owner
{
public:
	void applyByName(const AsciiString *name, char value, int mode);
	void rva003A4BD0(int state);
	void rva003A4C80(const AsciiString &name);
private:
	char m_pad00[0x3c];
	int m_state3C;
	void setStateName(int state);
};

// Same body as the out-of-line Rva003A48B0Owner::rva003A4BD0 in
// Rva003A4BD0NameTransition.cpp, with the new state known.  Both call sites
// inline it, but MSVC 7.1 still emits one COMDAT copy of it, which claims
// nothing: no retail body is asserted for it.
// ?setStateName@Rva003A48B0Owner@@AAEXH@Z absent-from-retail
void Rva003A48B0Owner::setStateName(int state)
{
	AsciiString *oldName;
	switch (m_state3C) {
	case 0: oldName = &g_bfmeGameCW->m_string190; break;
	case 1: oldName = &g_bfmeGameCW->m_string18C; break;
	case 2: oldName = &g_bfmeGameCW->m_string188; break;
	default: oldName = &Rva01336E50EmptyString; break;
	}
	AsciiString *newName;
	switch (state) {
	case 0: newName = &g_bfmeGameCW->m_string190; break;
	case 1: newName = &g_bfmeGameCW->m_string18C; break;
	case 2: newName = &g_bfmeGameCW->m_string188; break;
	default: newName = &Rva01336E50EmptyString; break;
	}
	applyByName(oldName, 0, 0);
	applyByName(newName, 1, 0);
	m_state3C = state;
}

void Rva003A48B0Owner::rva003A4C80(const AsciiString &name)
{
	if (name.compare("Small") == 0)
	{
		rva003A4BD0(0);
		return;
	}
	else if (name.compare("Medium") == 0)
	{
		setStateName(1);
		return;
	}
	else if (name.compare("Large") == 0)
	{
		setStateName(2);
	}
}
