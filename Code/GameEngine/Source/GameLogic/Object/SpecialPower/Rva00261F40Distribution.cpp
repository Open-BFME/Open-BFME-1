// Retail RVA 0x00261F40, 103 bytes, thiscall with two arguments (RET 8).
// The owner's original identity is unresolved; these names describe only
// this caller's verified view. The iterator advances through eight-byte
// entries; the selected destination is a vector of the first-word pointers.
// cl: /DNDEBUG /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>

class Rva00261F40Subject;
struct Rva00261F40Entry {
    Rva00261F40Subject *subject;
    unsigned int word4;
};
struct Rva00261F40IteratorState {
    Rva00261F40Entry *begin, *end, *capacity, *current;
    unsigned int word10;
};
struct Rva00261F40Iterator {
    Rva00261F40IteratorState *state;
    Rva00261F40Subject *next(Rva00261F40Subject *&subject) {
        if (state->current == state->end) return 0;
        subject = (state->current++)->subject;
        return subject;
    }
};
typedef _STL::vector<Rva00261F40Subject *> Rva00261F40Vector;
class Rva00261F40Owner {
public:
    // ILT 0x000476CC reaches the 205-byte body at 0x00261E40:
    // unchanged receiver, context and subject arguments, vector result, RET 8.
    Rva00261F40Vector *selectAt00261E40(void *, Rva00261F40Subject *);
    void distribute(void *context, Rva00261F40Iterator *range);
};
void Rva00261F40Owner::distribute(void *context, Rva00261F40Iterator *range)
{
    Rva00261F40Subject *subject;
    while (range->next(subject)) {
        // The overflow call through 0x0001F6CC reaches 0x0018B700:
        // four-byte POD elements, default small-block allocator, RET 20.
        selectAt00261E40(context, subject)->push_back(subject);
    }
}
