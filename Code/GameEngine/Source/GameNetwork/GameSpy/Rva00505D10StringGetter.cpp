// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Full32B getter: receiver+0x48 copied by StringBase<char> at887B60.
// Actual callers: WOL quick-match506C84 and ladder packet639472 via28565.
// Original receiver class and field name are not yet established.
#include "ascii_string.h"
class Rva00505D10StringOwner
{
public:
    AsciiString value();
private:
    char m_unrecovered00[0x48];
    AsciiString m_value;
};
// ?value@Rva00505D10StringOwner@@QAE?AVAsciiString@@XZ
AsciiString Rva00505D10StringOwner::value()
{
    return m_value;
}
