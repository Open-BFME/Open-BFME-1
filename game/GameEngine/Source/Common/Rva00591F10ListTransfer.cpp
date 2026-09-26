// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Retail 0x00591F10, complete 425-byte thiscall body (RET 8).
// Canonical Xfer slots: IsStoring +8, integer transfer +0x78.
// Rva0010C3C0 is the proved cdecl two-pointer enum-transfer adapter;
// its full 25-byte body dispatches receiver slot+0x90 with table VA0108920C.
// The list holds three DWORDs in 20-byte nodes. On load, swap the rebuilt
// list into +4 and reset 17 iterators at +8 with stride 24 before cleanup.
// No semantic owner or record identity is asserted.
#include <list>
#include "System/xfer.h"
class MidVirtualSlot90Receiver;
void Rva0010C3C0(MidVirtualSlot90Receiver *, void *);
struct Rva00591F10Record { int word0, word4, word8; };
typedef _STL::list<Rva00591F10Record> Rva00591F10List;
struct Rva00591F10Cursor {
    Rva00591F10List::iterator iterator;
    char opaque04[0x14];
};
class Rva00591F10Owner {
public:
    void transfer(Xfer *xfer, int unused);
    unsigned int opaque00;
    Rva00591F10List records;
    Rva00591F10Cursor cursors[17];
};
void Rva00591F10Owner::transfer(Xfer *xfer, int unused)
{
    if (xfer->IsStoring()) {
        int count = records.size();
        *xfer == count;
        for (Rva00591F10List::iterator i = records.begin(); i != records.end(); ++i) {
            Rva0010C3C0((MidVirtualSlot90Receiver *)xfer, &i->word0);
            *xfer == i->word4;
            *xfer == i->word8;
        }
    } else {
        int count;
        *xfer == count;
        Rva00591F10List replacement;
        Rva00591F10Record record = {0, 0, 0};
        while (count > 0) {
            Rva0010C3C0((MidVirtualSlot90Receiver *)xfer, &record.word0);
            *xfer == record.word4;
            *xfer == record.word8;
            replacement.push_back(record);
            --count;
        }
        records.swap(replacement);
        for (int i = 0; i < 17; ++i)
            cursors[i].iterator = records.end();
    }
}
