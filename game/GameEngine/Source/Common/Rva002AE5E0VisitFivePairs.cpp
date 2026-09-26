// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x002AE5E0 visits two arrays of five pointer ranges at +0x50/+0x8C.
// The owner remains address-qualified because no named caller identifies it.

class BfmeSubBNC {
public:
    void bfmeDoBNC(void *first, void *second);
};

class Gen_002DDCC0Target {
public:
    void bfmeForward(void *first, void *second);
};

template <typename T>
struct Rva002AE5E0Range {
    T **begin;
    T **end;
    T **capacity;
};

struct Rva002AE5E0Owner {
    unsigned char pad[0x50];
    Rva002AE5E0Range<BfmeSubBNC> first[5];
    Rva002AE5E0Range<Gen_002DDCC0Target> second[5];
};

void rva002AE5E0VisitFivePairs(const Rva002AE5E0Owner *owner, void *first, void *second)
{
    for (int i = 0; i < 5; ++i) {
        for (BfmeSubBNC **it = owner->first[i].begin;
             it != owner->first[i].end; ++it) {
            if (*it)
                (*it)->bfmeDoBNC(first, second);
        }
        for (Gen_002DDCC0Target **it = owner->second[i].begin;
             it != owner->second[i].end; ++it) {
            if (*it)
                (*it)->bfmeForward(first, second);
        }
    }
}
