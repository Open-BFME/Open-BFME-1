// ?bfmeReg1024@BfmeP1024@@QAEXPAVBfmeE1024@@@Z
// partial score=0.0 date=2026-09-22
// cl: /DNDEBUG /MD /O2
// BfmeE1024::bfmeGo1024E calls this member. Boundary ends at 0x009EF692.
#include <windows.h>

class BfmeE1024 { public: void *vtable; unsigned flags; void *entry; };
class BfmeP1024 { public: void bfmeReg1024(BfmeE1024 *); };

static unsigned &word(void *p, unsigned offset)
{
    return *(unsigned *)((char *)p + offset);
}

static unsigned callVirtual(BfmeE1024 *p, unsigned slot)
{
    typedef unsigned (__cdecl *Method)(BfmeE1024 *);
    return ((Method *)p->vtable)[slot](p);
}

void BfmeP1024::bfmeReg1024(BfmeE1024 *item)
{
    if (!item->entry || (item->flags & 0xff0000) == 0x70000)
        return;

    CRITICAL_SECTION *lock = (CRITICAL_SECTION *)((char *)this + 0x60);
    EnterCriticalSection(lock);
    while (((item->flags & 0xff0000) == 0x10000 ||
            (item->flags & 0xff0000) == 0x50000) &&
           *(BfmeE1024 **)word(this, (((item->flags >> 16) & 0xff) + 3) * 0x28) == item) {
        LeaveCriticalSection(lock);
        Sleep(1);
        EnterCriticalSection(lock);
    }
    while ((item->flags & 0xff0000) == 0x80000) {
        LeaveCriticalSection(lock);
        Sleep(1);
        EnterCriticalSection(lock);
    }

    unsigned bucket = (((item->flags >> 16) & 0xff) + 3) * 0x28;
    unsigned count = ((word(this, bucket + 0x1c) - word(this, bucket + 0x0c)) / 4 - 1) * 32
        + (word(this, bucket + 0x10) - word(this, bucket + 0x14)) / 4
        + (word(this, bucket + 8) - word(this, bucket)) / 4;
    unsigned index = 0;
    for (; index < count; ++index) {
        // The retail deque iterator calls _M_advance here; its typed ABI
        // and node layout still need independent confirmation.
        BfmeE1024 **slot = *(BfmeE1024 ***)((char *)this + bucket);
        if (slot[index] == item) break;
    }
    if (index < count) {
        BfmeE1024 **first = *(BfmeE1024 ***)((char *)this + bucket);
        first[index] = first[count - 1];
        word(this, bucket + 0x10) -= 4;
    }
    LeaveCriticalSection(lock);

    item->flags &= 0xfdffffff;
    if ((item->flags & 0xff0000) == 0x30000) {
        word(this, 0x20) -= callVirtual(item, 14);
        item->flags = (item->flags & 0xff04ffff) | 0x40000;
        if ((int)word(this, 0x20) < 0) word(this, 0x20) = 0;
    }
    switch ((item->flags >> 16) & 0xff) {
    case 0:
        callVirtual(item, 1);
        item->flags = (item->flags & 0xff01ffff) | 0x10000;
    case 1:
        callVirtual(item, 2);
        item->flags = (item->flags & 0xff02ffff) | 0x20000;
        word(this, 0x20) += callVirtual(item, 14);
    case 2:
        callVirtual(item, 3);
        item->flags = (item->flags & 0xff04ffff) | 0x40000;
        word(this, 0x20) -= callVirtual(item, 14);
        if ((int)word(this, 0x20) < 0) word(this, 0x20) = 0;
    case 4:
        callVirtual(item, 5);
        item->flags = (item->flags & 0xff05ffff) | 0x50000;
    case 5:
        callVirtual(item, 6);
        item->flags = (item->flags & 0xff06ffff) | 0x60000;
    case 6:
        callVirtual(item, 7);
        item->flags = (item->flags & 0xff07ffff) | 0x70000;
    }
}
