// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: NamedReveal's destructor, retail 0x00339C30, 89 bytes. The body
// carried only a machine byte-dump row; the symbols.csv pin names it, and the
// __copy over this element type at 0x0033A9F0 is already ledgered beside it.
//
// Layout names are corroborated by ScriptEngineNamedMapReveal.cpp: the matched
// doNamedMapReveal body reads the radius at +0x08 and player name at +0x0C.
// The reference ScriptEngine.h names the same four fields.
//
// Three AsciiStrings, destroyed at +0x0C, +0x04 and +0x00, which is reverse
// declaration order. The radius at +0x08 needs no destruction.
//
// No vptr store at the top and no base call, so the class has neither. The
// unwind slot counts down 1, 0, -1, and its middle store is a byte because the
// high three are already clear.

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class NamedReveal
{
public:
	__declspec(noinline) ~NamedReveal();

private:
	AsciiString m_revealName;				// +0x00
	AsciiString m_waypointName;				// +0x04
	float m_radiusToReveal;			// +0x08
	AsciiString m_playerName;				// +0x0C
};

// ??1NamedReveal@@QAE@XZ
NamedReveal::~NamedReveal()
{
}

// Emit the retail scalar-deleting wrapper (RVA 0x0033AE00). Keep the complete
// destructor out of line: retail calls it through ILT 0x000244DD.
void forceNamedRevealDeletingDestructor(NamedReveal *value)
{
	delete value;
}
