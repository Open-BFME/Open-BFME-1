// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/languagefilter /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

#include "string_base.h"

extern int g_bfmeDirtyBG;

// The retail value and member slots are narrow shared-buffer strings.  Keep
// this local view one word wide, but use the real StringBase<char> member
// functions so both calls carry the canonical object symbols.
#include "ascii_string.h"

class Rva00190590
{
public:
	void rva00190590(AsciiString value, unsigned int index);

private:
	unsigned char m_pad[0x48];
	AsciiString m_values[6];
};

// ?rva00190590@Rva00190590@@QAEXVAsciiString@@I@Z
void Rva00190590::rva00190590(AsciiString value, unsigned int index)
{
	if (index >= 6)
		return;

	int dirty = g_bfmeDirtyBG;
	*reinterpret_cast<volatile int *>(&g_bfmeDirtyBG) = dirty | 1;
	m_values[index] = value;
}
