// cl: /O2 /Ob0
// Separate complete int3-bounded bodies. Names retain addresses because
// neither the class owners nor original method names have been established.
struct Rva008A04F0 { char pad00[0x50]; unsigned int field50; unsigned int value() const; };
unsigned int Rva008A04F0::value() const { return field50; }
struct Rva008A0500 { char pad00[0x50]; unsigned int field50; unsigned int value() const; };
unsigned int Rva008A0500::value() const { return field50; }
struct Rva008A0510 { char pad00[0x50]; unsigned int field50; unsigned int value() const; };
unsigned int Rva008A0510::value() const { return field50; }

// Existing address witnesses identify these two mutable callback slots.
// Allocator takes one size; deallocator takes a pointer and a size.
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int);
extern void (__cdecl *TheBfmeFree)(void *, unsigned int);
void *rva008A0520(unsigned int bytes) { return Rva008C5D70Alloc(bytes); }
void rva008A0530(void *memory, unsigned int bytes) { TheBfmeFree(memory, bytes); }

struct Rva008A0540 { char pad00[0x30]; unsigned int field30; unsigned int value() const; };
unsigned int Rva008A0540::value() const { return field30; }
struct Rva008A0550 { char pad00[0x7c]; unsigned int field7C; int value() const; };
int Rva008A0550::value() const { return field7C != 0; }
struct Rva008A0560 { char pad00[0x7c]; unsigned int field7C; unsigned int value() const; };
unsigned int Rva008A0560::value() const { return field7C; }
