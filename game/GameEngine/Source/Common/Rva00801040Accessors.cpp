// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /MD
// Retail RVAs 00801040..00801133. Every entry follows INT3 padding and
// terminates with RET before the next padding run. No semantic identities
// are asserted: these are the observed thiscall loads and member addresses.

struct Rva00801040 { char pad[0x1b0]; unsigned field; unsigned read(); };
unsigned Rva00801040::read() { return field; }

struct Rva00801050 { char pad[0x26]; char field; char *read(); };
char *Rva00801050::read() { return &field; }

struct Rva00801060 { char pad[0x130]; char field; char *read(); };
char *Rva00801060::read() { return &field; }

struct Rva00801070 { char pad[0xc]; unsigned field; unsigned read(); };
unsigned Rva00801070::read() { return field; }

struct Rva00801080 { char pad[0x10]; unsigned field; unsigned read(); };
unsigned Rva00801080::read() { return field; }

struct Rva00801090 { char pad[0x14]; unsigned field; unsigned read(); };
unsigned Rva00801090::read() { return field; }

struct Rva008010A0 { char pad[0xa6]; char field; char *read(); };
char *Rva008010A0::read() { return &field; }

struct Rva008010B0 { char pad[0x128]; unsigned __int64 field; unsigned __int64 read(); };
unsigned __int64 Rva008010B0::read() { return field; }

struct Rva008010C0 { char pad[0x18]; unsigned field; unsigned read(); };
unsigned Rva008010C0::read() { return field; }

struct Rva008010D0 { char pad[0x170]; char field; char *read(); };
char *Rva008010D0::read() { return &field; }

struct Rva008010E0 { char pad[0x1c]; unsigned field; unsigned read(); };
unsigned Rva008010E0::read() { return field; }

struct Rva008010F0 { char pad[0x25]; unsigned char field; unsigned char read(); };
unsigned char Rva008010F0::read() { return field; }

struct Rva00801100 { char pad[0x24]; unsigned char field; unsigned char read(); };
unsigned char Rva00801100::read() { return field; }

struct Rva00801110 { char pad[0x20]; unsigned field; unsigned read(); };
unsigned Rva00801110::read() { return field; }

struct Rva00801120 { char pad[0xc]; char field; char *read(); };
char *Rva00801120::read() { return &field; }

struct Rva00801130 { char pad[0x8]; unsigned field; unsigned read(); };
unsigned Rva00801130::read() { return field; }
