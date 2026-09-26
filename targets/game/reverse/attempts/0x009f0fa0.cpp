// ?method@Rva009F0FA0@@QAEXPAURva009F0FA0Item@@@Z
// partial score=0.0 date=2026-09-22
// cl: /DNDEBUG /MD /O2 /EHsc
// Opaque address identity. The only witnessed caller is at 0x009EB8BE.
#include <windows.h>

struct Rva009F0FA0Item {
    void **vtable;
    unsigned flags;
    void *entry;
    void *links;
};

class Rva009F0FA0 {
public:
    void method(Rva009F0FA0Item *item);
};

static unsigned &field(void *p, unsigned offset)
{
    return *(unsigned *)((char *)p + offset);
}

static unsigned invoke(Rva009F0FA0Item *item, unsigned slot)
{
    typedef unsigned (__cdecl *Method)(Rva009F0FA0Item *);
    return ((Method *)item->vtable)[slot](item);
}

void Rva009F0FA0::method(Rva009F0FA0Item *item)
{
    if (!item->entry || (item->flags & 0xff0000) == 0x30000)
        return;

    CRITICAL_SECTION *lock = (CRITICAL_SECTION *)((char *)this + 0x60);
    EnterCriticalSection(lock);

    // Retail first checks an entry tree and may emit a demand-load message.
    // The tree node type and the debug stream's ABI are not established yet.
    while (((item->flags & 0xff0000) == 0x10000 ||
            (item->flags & 0xff0000) == 0x50000) &&
           *(Rva009F0FA0Item **)field(this,
               (((item->flags >> 16) & 0xff) + 3) * 0x28) == item &&
           *((char *)this + 0x1ec)) {
        LeaveCriticalSection(lock);
        Sleep(1);
        EnterCriticalSection(lock);
    }
    while ((item->flags & 0xff0000) == 0x80000) {
        LeaveCriticalSection(lock);
        Sleep(1);
        EnterCriticalSection(lock);
    }

    unsigned state = (item->flags >> 16) & 0xff;
    if (state != 7) {
        unsigned bucket = (state + 3) * 0x28;
        unsigned count = ((field(this, bucket + 0x1c) - field(this, bucket + 0x0c)) / 4 - 1) * 32
            + (field(this, bucket + 0x10) - field(this, bucket + 0x14)) / 4
            + (field(this, bucket + 8) - field(this, bucket)) / 4;
        Rva009F0FA0Item **first = *(Rva009F0FA0Item ***)((char *)this + bucket);
        for (unsigned index = 0; index < count; ++index) {
            if (first[index] == item) {
                first[index] = first[count - 1];
                field(this, bucket + 0x10) -= 4;
                break;
            }
        }
    }
    LeaveCriticalSection(lock);
    item->flags |= 0x2000000;
    if (state == 7) item->flags &= 0xff00ffff;

    switch ((item->flags >> 16) & 0xff) {
    case 4:
        field(this, 0x20) += invoke(item, 14);
        break;
    case 5:
        invoke(item, 6);
        item->flags = (item->flags & 0xff06ffff) | 0x60000;
    case 6:
        invoke(item, 7);
        item->flags &= 0xff00ffff;
    case 0:
        invoke(item, 1);
        item->flags = (item->flags & 0xff01ffff) | 0x10000;
    case 1:
        invoke(item, 2);
        item->flags = (item->flags & 0xff02ffff) | 0x20000;
        field(this, 0x20) += invoke(item, 14);
    case 2:
        invoke(item, 3);
        invoke(item, 4);
        item->flags = (item->flags & 0xff03ffff) | 0x30000;
    }

    EnterCriticalSection(lock);
    unsigned *pending = (unsigned *)field(this, 0x100);
    if (pending) {
        *pending = (unsigned)item;
        field(this, 0x100) += 4;
    }
    LeaveCriticalSection(lock);
}
