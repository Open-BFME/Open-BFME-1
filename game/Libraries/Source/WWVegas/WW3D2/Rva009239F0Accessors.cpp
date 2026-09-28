// cl: /O2 /Ob0
// Retail 1.03: each entry below starts after int3 padding and ends at its
// complete ret before the next padding run. No semantic identity is proven.
// The offsets and scaling are witnessed by the instructions at each RVA;
// these independent address-based types do not assert a common owner.

struct Rva009239F0 {
    unsigned char pad00[0x10]; unsigned int field10;
    unsigned int value() const;
};
unsigned int Rva009239F0::value() const { return field10 * 6; }

struct Rva00923A00 {
    unsigned char pad00[0x10]; unsigned int field10;
    unsigned int value() const;
};
unsigned int Rva00923A00::value() const { return field10 * 12; }

struct Rva00923A10 { Rva00923A10 *value(); };
Rva00923A10 *Rva00923A10::value() { return this; }

struct Rva00923A20 {
    unsigned char pad00[0x10]; unsigned int field10;
    unsigned int value() const;
};
unsigned int Rva00923A20::value() const { return field10; }

struct Rva00923A30 {
    unsigned char pad00[0x0c]; unsigned int field0C;
    unsigned int value() const;
};
unsigned int Rva00923A30::value() const { return field0C; }

struct Rva00923A40 {
    unsigned char pad00[0x10]; unsigned int field10;
    unsigned int value() const;
};
unsigned int Rva00923A40::value() const { return field10 * 4; }

struct Rva00923A50 {
    unsigned char pad00[0x0c]; unsigned int field0C;
    unsigned int value() const;
};
unsigned int Rva00923A50::value() const { return field0C; }

struct Rva00923A60 {
    unsigned char pad00[0x10]; unsigned int field10;
    unsigned int value() const;
};
unsigned int Rva00923A60::value() const { return field10 * 2; }

struct Rva00923A70 {
    unsigned char pad00[0x0c]; unsigned int field0C;
    unsigned int value() const;
};
unsigned int Rva00923A70::value() const { return field0C; }
