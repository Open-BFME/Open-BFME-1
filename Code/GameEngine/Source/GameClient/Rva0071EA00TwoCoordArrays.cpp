// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /Ireference/shims/stringinline
//
// The reciprocal 0x0071EA00/0x0071EAC0 bodies own two Coord2D arrays and four
// inline AsciiString slots.  The retail vector helpers pass Coord2D's already
// matched constructor/destructor bodies (0x00421710/0x0043EAB8).

#include "coord2d.h"
#include "StringInline.h"

class Rva0071EA00
{
public:
	Rva0071EA00();
	~Rva0071EA00();

private:
	unsigned char m_pad24[0x24];
	Coord2D m_arr24[2];
	Coord2D m_arr34[2];
	unsigned char m_pad44[4];
	AsciiString m_string48;
	AsciiString m_string4c;
	AsciiString m_string50;
	AsciiString m_string54;
};

// ??0Rva0071EA00@@QAE@XZ
Rva0071EA00::Rva0071EA00()
{
}

// ??1Rva0071EA00@@QAE@XZ
Rva0071EA00::~Rva0071EA00()
{
}
