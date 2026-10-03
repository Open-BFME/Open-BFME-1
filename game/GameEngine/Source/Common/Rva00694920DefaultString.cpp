// cl: /DNDEBUG /MD /EHsc /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// Retail 0x00694920 returns the holder pointer or the shared empty string.

#include "Common/AsciiString.h"

struct Rva002E5FF0Str
{
};

class Rva00694920
{
public:
	Rva002E5FF0Str *get();

	Rva002E5FF0Str *m_pointee;
};

Rva002E5FF0Str *Rva00694920::get()
{
	if (m_pointee)
		return m_pointee;
	return reinterpret_cast<Rva002E5FF0Str *>(&AsciiString::TheEmptyString);
}
