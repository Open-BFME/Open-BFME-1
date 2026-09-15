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
// The 298-byte builder at 0x00261CC0 reads subject X/Y at +0x38/+0x3C,
// ranks 16-byte input entries by squared distance, and outputs pointers to
// their embedded destination vectors. The first pair word is float, not int.
struct Rva00261E40InputEntry {
    Rva00261F40Subject *subject;
    Rva00261F40Vector destination;
};
typedef _STL::vector<Rva00261E40InputEntry> Rva00261E40InputCollection;
typedef _STL::pair<float, Rva00261F40Vector *> Rva00261E40Pair;
typedef _STL::vector<Rva00261E40Pair> Rva00261E40PairVector;
class Rva00261F40Owner {
public:
    // ILT 0x000476CC reaches the 205-byte body at 0x00261E40:
    // unchanged receiver, context and subject arguments, vector result, RET 8.
    Rva00261F40Vector *selectAt00261E40(void *, Rva00261F40Subject *);
    void distribute(void *context, Rva00261F40Iterator *range);
    void buildPairsAt00261CC0(Rva00261E40InputCollection *, Rva00261F40Subject *, Rva00261E40PairVector *);
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

// Retail [0x00261E40,0x00261F0D): 205 bytes, RET 8. The builder consumes
// three stack arguments (RET 12) while preserving the owner receiver in ECX.
Rva00261F40Vector *Rva00261F40Owner::selectAt00261E40(
    void *context, Rva00261F40Subject *subject)
{
    Rva00261E40PairVector pairs;
    buildPairsAt00261CC0(static_cast<Rva00261E40InputCollection *>(context), subject, &pairs);
    Rva00261E40Pair *end = pairs.end();
    Rva00261E40Pair *begin = pairs.begin();
    for (int threshold=0; threshold<10; ++threshold) {
        for (Rva00261E40Pair *it=begin; it!=end; ++it) {
            if (it->second->size() <= threshold)
                return it->second;
        }
    }
    // Retail assumes a nonempty result here; do not add a fallback.
    return begin->second;
}

// Retail [0x00260650,0x0026066C): 28 bytes, followed by INT3 padding.
// The builder at 0x00261CC0 passes this address into the STL sorting helpers
// at +0xBF, +0xD7 and +0xF7. It compares the float distance keys, not vectors.
bool __cdecl compareDistanceAt00260650(
    const Rva00261E40Pair &a, const Rva00261E40Pair &b)
{
    return a.first < b.first;
}
