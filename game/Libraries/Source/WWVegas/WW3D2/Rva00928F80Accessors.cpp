// cl: /O2 /Ob0
// Independent opaque accessors, each proven by surrounding int3 padding
// and a complete ret. Field offsets and integer scaling come from retail.
struct Rva00928F80 {
    char pad00[0x10]; unsigned int field10; unsigned int value() const;
};
unsigned int Rva00928F80::value() const { return field10; }
struct Rva00928F90 {
    char pad00[0x10]; unsigned int field10; unsigned int value() const;
};
unsigned int Rva00928F90::value() const { return field10 * 4; }
struct Rva00928FA0 {
    char pad00[0x10]; unsigned int field10; unsigned int value() const;
};
unsigned int Rva00928FA0::value() const { return field10 * 4; }
struct Rva00928FB0 {
    char pad00[0x10]; unsigned int field10; unsigned int value() const;
};
unsigned int Rva00928FB0::value() const { return field10; }
struct Rva00928FC0 {
    char pad00[0x10]; unsigned int field10; unsigned int value() const;
};
unsigned int Rva00928FC0::value() const { return field10 * 8; }
struct Rva00928FD0 {
    char pad00[0x10]; unsigned int field10; unsigned int value() const;
};
unsigned int Rva00928FD0::value() const { return field10 * 4; }
struct Rva00928FE0 {
    char pad00[0x0c]; unsigned int field0C; unsigned int value() const;
};
unsigned int Rva00928FE0::value() const { return field0C; }
struct Rva00928FF0 {
    char pad00[0x10]; unsigned int field10; unsigned int value() const;
};
unsigned int Rva00928FF0::value() const { return field10 * 4; }
