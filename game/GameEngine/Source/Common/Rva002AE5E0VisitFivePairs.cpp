// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x002AE5E0 visits two arrays of five pointer ranges at +0x50/+0x8C.
// The owner remains address-qualified because no named caller identifies it.

// ILT 0x00040412 routes to BfmeThingHF::bfmeTellHF (0x001D6860).
class BfmeThingHF {
public:
    void bfmeTellHF(void *first, void *second);
};

// ILT 0x00022D86 routes to BfmeShadowPart::bfmeSetSize (0x00428250).
class BfmeShadowPart {
public:
    void bfmeSetSize(float width, float height);
};

template <typename T>
struct Rva002AE5E0Range {
    T **begin;
    T **end;
    T **capacity;
};

struct Rva002AE5E0Owner {
    unsigned char pad[0x50];
    Rva002AE5E0Range<BfmeThingHF> first[5];
    Rva002AE5E0Range<BfmeShadowPart> second[5];
};

void rva002AE5E0VisitFivePairs(const Rva002AE5E0Owner *owner, void *first, void *second)
{
    for (int i = 0; i < 5; ++i) {
        for (BfmeThingHF **it = owner->first[i].begin;
             it != owner->first[i].end; ++it) {
            if (*it)
                (*it)->bfmeTellHF(first, second);
        }
        for (BfmeShadowPart **it = owner->second[i].begin;
             it != owner->second[i].end; ++it) {
            if (*it)
                // Preserve the existing entry point's raw argument words;
                // the matched callee interprets them as float sizes.
                (*it)->bfmeSetSize(*reinterpret_cast<const float *>(&first),
                                  *reinterpret_cast<const float *>(&second));
        }
    }
}
