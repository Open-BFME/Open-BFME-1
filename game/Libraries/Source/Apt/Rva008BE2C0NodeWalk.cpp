// cl: /O2 /DNDEBUG /MD
// Complete retail body [0x008BE2C0, 0x008BE3A6), with a RET4 exit.
// Address-qualified ABI views only: ECX points to a node pointer holder;
// the one argument is only tested for null and receives the current node on
// recursion. No external caller or original class identity is proved.
// Existing AptInput.cpp corroborates flags+04, name+0C, link+4C, info+50
// and the iterator-list+10 contract. This body witnesses link+58 and the
// recursive receiver at info+24. Gaps describe only observed field offsets.
// Iterator spellings name their independently matched defining TUs.
#include <string.h>

class EAStringC { public: class StringDataC; };
extern EAStringC::StringDataC g_rva012D5298Empty;

struct Rva008BE2C0String
{
    unsigned short field00;
    unsigned short length02;
    unsigned field04;
    char text08[1];
};
struct BfmeIterator1285
{
    Rva008BE2C0String *field00;
    unsigned field04;
};
class BfmeIteratorList1285
{
public:
    BfmeIterator1285 *bfmeFirst1285();
    BfmeIterator1285 *bfmeNext1285(BfmeIterator1285 *iterator);
};
struct Rva008BE2C0Node;
struct Rva008BE2C0
{
    Rva008BE2C0Node **field00;
    void walk(Rva008BE2C0Node *argument);
};
struct Rva008BE2C0Info
{
    char gap00[0x10];
    BfmeIteratorList1285 *field10;
    char gap14[0x10];
    Rva008BE2C0 field24;
};
struct Rva008BE2C0Node
{
    void *field00;
    unsigned flags04;
    char gap08[4];
    Rva008BE2C0String *field0c;
    char gap10[0x3c];
    Rva008BE2C0Node *field4c;
    Rva008BE2C0Info *field50;
    char gap54[4];
    Rva008BE2C0Node *field58;
};
void Rva008BE2C0::walk(Rva008BE2C0Node *argument)
{
    Rva008BE2C0Node *node = (*field00)->field58;
    while (node) {
        if (argument && node->field0c != (Rva008BE2C0String *)&g_rva012D5298Empty &&
            (static_cast<unsigned char>(~(node->flags04 >> 15)) & 1) == 0) {
            Rva008BE2C0Node *parent = node->field4c;
            BfmeIterator1285 *iterator = parent->field50->field10->bfmeFirst1285();
            while (iterator) {
                Rva008BE2C0Node *candidate = reinterpret_cast<Rva008BE2C0Node *>(iterator->field04 & ~1U);
                unsigned flags = candidate->flags04;
                int kind = flags & 0x3f;
                if (kind >= 12 && kind <= 19 &&
                    (static_cast<unsigned char>(~(flags >> 15)) & 1) == 0) {
                    if (candidate == node)
                        break;
                    Rva008BE2C0String *first = iterator->field00;
                    Rva008BE2C0String *second = node->field0c;
                    int firstLength = first->length02;
                    int secondLength = second->length02;
                    if (firstLength == secondLength &&
                        (first == second || memcmp(first->text08, second->text08, firstLength) == 0))
                        break;
                }
                BfmeIteratorList1285 *list = parent->field50->field10;
                iterator = list->bfmeNext1285(iterator);
            }
        }
        if (((node->flags04 & 0x3f) == 13 && (static_cast<unsigned char>(~(node->flags04 >> 15)) & 1) == 0) ||
            ((node->flags04 & 0x3f) == 18 && (static_cast<unsigned char>(~(node->flags04 >> 15)) & 1) == 0))
            node->field50->field24.walk(node);
        node = node->field58;
    }
}
