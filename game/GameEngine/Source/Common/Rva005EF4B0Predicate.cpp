// Retail RVA 0x005EF4B0: 132 bytes of code/alignment and a 24-byte switch table.
// The receiver identity is unproven; offsets and address provenance are retained.
extern const float Rva00064680NegativeScale; // Retail VA 0x01075354.
extern const float Rva01113520;

class Rva005EF4B0PredicateClass {
public:
    bool predicate(int selector);
};

bool Rva005EF4B0PredicateClass::predicate(int selector)
{
    const unsigned char *object = reinterpret_cast<const unsigned char *>(this);
    switch (selector) {
    case 1:
    case 2:
    case 6: {
        const unsigned int index = *reinterpret_cast<const unsigned int *>(object + 0xAC);
        const unsigned int occupied = *reinterpret_cast<const unsigned int *>(object + index * 16 + 0x1C);
        return occupied == 0 &&
            (*reinterpret_cast<const float *>(object + 0x9C) +
             *reinterpret_cast<const float *>(object + 0x98) +
             *reinterpret_cast<const float *>(object + 0x94)) < Rva00064680NegativeScale;
    }
    case 5: {
        const unsigned int index = *reinterpret_cast<const unsigned int *>(object + 0xAC);
        const unsigned int occupied = *reinterpret_cast<const unsigned int *>(object + index * 16 + 0x1C);
        return occupied == 0 &&
            (*reinterpret_cast<const float *>(object + 0x9C) *
             *reinterpret_cast<const float *>(object + 0x98) *
             *reinterpret_cast<const float *>(object + 0x94)) > Rva01113520;
    }
    default:
        return true;
    }
}
