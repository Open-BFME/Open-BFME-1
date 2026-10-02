// Open-BFME5 conversions.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "../../../Libraries/Source/WWVegas/WWMath/coord2d.h"

typedef AsciiString BfmeStrVVC;
typedef Coord2D BfmeElemVVC;

class BfmeOwnVVC
{
public:
	~BfmeOwnVVC();
	char m_bfmePad00[0x24];
	BfmeElemVVC m_bfme24[2];
	BfmeElemVVC m_bfme34[2];
	char m_bfmePad44[4];
	BfmeStrVVC m_bfme48;
	BfmeStrVVC m_bfme4c;
	BfmeStrVVC m_bfme50;
	BfmeStrVVC m_bfme54;
};

BfmeOwnVVC::~BfmeOwnVVC()
{
}
