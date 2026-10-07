// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// EnumeratedIP complete destructor at retail 0x00624C70 (5 bytes).
// ??_GEnumeratedIP (0x00625010) and IPEnumeration::~IPEnumeration
// (0x00625040) call it through ILT 0x00028FB0. Its only destructible member
// is the AsciiString at +0x00, whose inline StringBase<char> destructor
// leaves one tail jump to StringBase<char>::releaseBuffer (0x00887940).

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/IPEnumeration.h
class EnumeratedIP
{
public:
	~EnumeratedIP();

private:
	AsciiString m_text;
	unsigned int m_address;
	EnumeratedIP *m_next;
};

EnumeratedIP::~EnumeratedIP()
{
}
