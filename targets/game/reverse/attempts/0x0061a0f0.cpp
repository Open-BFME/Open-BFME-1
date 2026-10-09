// ?dispatch@Rva0061A0F0Owner@@QAEXXZ
// partial score=0.5446 date=2026-10-10
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
class Rva003B3950StringOwner {
public:
    AsciiString getString();
};
extern Rva003B3950StringOwner *Rva012F1024StringOwner;
class Rva006196F0Entry {
public:
    AsciiString getString();
    char opaque00[0x18];
    unsigned char byte18;
    char opaque19[0xB];
};
struct Rva00619C40Entry;
void __stdcall dispatchEntry(Rva00619C40Entry *, int, const AsciiString &);
class Rva0061A0F0Owner {
public:
    void dispatch();
    void dispatchEntry(Rva006196F0Entry *, int, const AsciiString &);
    char opaque00[0x9C];
    Rva006196F0Entry *entries;
};
void Rva0061A0F0Owner::dispatch()
{
    AsciiString name = Rva012F1024StringOwner->getString();
    if (name.getLength() == 0)
        name.format(AsciiString("NoActNameFound"));
    bool found = false;
    for (int index = 0; !found; ++index) {
        if (entries[index].byte18 == 0) {
            ::dispatchEntry((Rva00619C40Entry *)&entries[index], 1, entries[index].getString());
            found = true;
        }
    }
}
