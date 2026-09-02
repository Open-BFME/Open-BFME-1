// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Copy ctor of {dword, AsciiString}: store primary, copy the by-value string
// into the member at +4, then destroy the argument.

#include "StringInline.h"

class Rva00691ED0Key
{
public:
	Rva00691ED0Key(unsigned primary, AsciiString name);

private:
	unsigned m_primary;
	AsciiString m_name;
};

// ??0Rva00691ED0Key@@QAE@IVAsciiString@@@Z
Rva00691ED0Key::Rva00691ED0Key(unsigned primary, AsciiString name)
	: m_primary(primary), m_name(name)
{
}
