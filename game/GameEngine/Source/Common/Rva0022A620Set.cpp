// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

class Rva0022A620Obj
{
public:
	void set(AsciiString value);

private:
	char m_pad[0x328];
	AsciiString m_name;
};

void Rva0022A620Obj::set(AsciiString value)
{
	m_name = value;
}
