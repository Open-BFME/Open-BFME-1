// cl: /O2 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// RVA 0x00080260: remove matching strings from a circular doubly linked list.
// Ghidra boundary 176 bytes. The historical BfmeSlotRT::bfmeUseRT name
// contradicts retail's ret 4; retain an address-qualified identity.
#include <memory>
#include "ascii_string.h"
struct Rva00080260Node {
    Rva00080260Node *next, *previous;
    AsciiString value;
};
class Rva00080260List {
public:
    void remove(const AsciiString &value);
private:
    Rva00080260Node *sentinel;
};
void Rva00080260List::remove(const AsciiString &value)
{
    Rva00080260Node *end = sentinel;
    Rva00080260Node *node = end->next;
    while (node != end) {
        Rva00080260Node *next = node->next;
        if (value.compare(node->value) == 0) {
            Rva00080260Node *previous = node->previous;
            previous->next = next;
            next->previous = previous;
            node->value.~AsciiString();
            _STL::allocator<Rva00080260Node>().deallocate(node, 1);
        }
        node = next;
    }
}