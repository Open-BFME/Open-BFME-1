// cl: /DNDEBUG /MD /GX /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

class Rva006E22E0Host
{
public:
    AsciiString copyStringAt9C();
};

AsciiString Rva006E22E0Host::copyStringAt9C()
{
    return *reinterpret_cast<const AsciiString *>(
        reinterpret_cast<const char *>(this) + 0x9C);
}
