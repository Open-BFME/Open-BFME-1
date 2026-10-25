// ?bfmeRelinkEAT@BfmeNodeEAT@Rva0035E510@@QAEXPAV12@PAH1@Z
// partial score=0.3701 date=2026-10-25
// stlport
// cl: /DNDEBUG /MD /O2 /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Oa
#define _STLP_NO_EXCEPTIONS 1
#include <stl/_algobase.h>
struct Rva0035D9B0Node;
struct Rva0035D9B0Slot { Rva0035D9B0Node **address; };
namespace _STL {
template<> struct __type_traits<Rva0035D9B0Slot> : __type_traits_aux<1> {};
}
#include <deque>
#include "ascii_string.h"
struct Rva0035D9B0Node {
    Rva0035D9B0Node *next;
    int index;
    int references;
};
struct Rva0035D9B0Link { Rva0035D9B0Link *next; };
struct Rva0035D9B0Record {
    int previous;
    int next;
    AsciiString name;
    unsigned char released;
    unsigned char pad;
    short references;
    Rva0035D9B0Link *nodes;
};
struct Rva0035D9B0Table {
    int *begin;
    int *end;
    int *capacity;
    Rva0035D9B0Record *records;
};
class Rva0035D2B0StringRecordTable {
public:
    int findOrCreateIndex(AsciiString *name);
    void release(int index);
};
namespace Rva0035E510 {
class BfmeNodeEAT {
public:
    void bfmeRelinkEAT(BfmeNodeEAT *source, int *from, int *to);
};
void BfmeNodeEAT::bfmeRelinkEAT(BfmeNodeEAT *source, int *from, int *to)
{
    _STL::deque<Rva0035D9B0Node **> slots;
    Rva0035D9B0Node **slot;
    slot = reinterpret_cast<Rva0035D9B0Node **>(from);
    for (; *reinterpret_cast<Rva0035D9B0Node **>(slot); slot = &(*slot)->next)
        slots.push_back(slot);
    while (!slots.empty()) {
        Rva0035D9B0Node **link = reinterpret_cast<Rva0035D9B0Node **>(slots.back());
        Rva0035D9B0Table *sourceTable = reinterpret_cast<Rva0035D9B0Table *>(reinterpret_cast<char *>(source) + 0x2c);
        Rva0035D9B0Table *table = reinterpret_cast<Rva0035D9B0Table *>(reinterpret_cast<char *>(this) + 0x2c);
        int oldIndex = (*link)->index;
        Rva0035D9B0Record *record = &sourceTable->records[oldIndex];
        int index = reinterpret_cast<Rva0035D2B0StringRecordTable *>(table)->findOrCreateIndex(&record->name);
        if (index != -1) {
            Rva0035D9B0Record *destinationRecord = &table->records[index];
            Rva0035D9B0Link *node = record->nodes;
            record->nodes = node->next;
            node->next = destinationRecord->nodes;
            destinationRecord->nodes = node;
            reinterpret_cast<Rva0035D2B0StringRecordTable *>(sourceTable)->release(oldIndex);
            (*link)->index = index;
            (*link)->references = table->records[index].references;
            Rva0035D9B0Node *next = (*link)->next;
            (*link)->next = *reinterpret_cast<Rva0035D9B0Node **>(to);
            *reinterpret_cast<Rva0035D9B0Node **>(to) = *link;
            *link = next;
        }
        slots.pop_back();
    }
}
}
