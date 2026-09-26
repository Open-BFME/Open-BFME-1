// cl: /DNDEBUG /MD /O2 /EHsc
// ?d_0000d828@@YAXXZ present-unmatched
// The carved thunk is the independently witnessed BFME-retail AsciiString
// destructor ILT at 0x0000D828 -> 0x0005EE90.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class BFMERetailAsciiString : public AsciiString
{
public:
	~BFMERetailAsciiString();
};

BFMERetailAsciiString::~BFMERetailAsciiString()
{
}
