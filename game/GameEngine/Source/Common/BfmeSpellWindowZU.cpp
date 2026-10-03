// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the spell-window name at retail 0x0058BA80, 141 bytes.
// A free function returning the built string by value.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// The canonical string preserves the native constructor forwarding and
// emits the real AsciiString destructor in the guarded return cleanup.

// ?bfmeSpellWindowZU@@YA?AVAsciiString@@H@Z
AsciiString bfmeSpellWindowZU(int slot)
{
	AsciiString name;

	name.format(AsciiString("SpellBookUI/Spell%d"), slot + 1);

	return name;
}
