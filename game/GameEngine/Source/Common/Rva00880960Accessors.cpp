// cl: /O2 /Ob0
// Each function is independently int3-bounded. No class identity is known.
// These field offsets and index strides are witnessed by the retail body.
struct Rva00880960 { char bytes[0x28]; void *value(); };
void *Rva00880960::value() { return bytes + 0x24; }
struct Rva00880970 { char pad00[0x30]; float field30; float value() const; };
float Rva00880970::value() const { return field30; }
struct Rva00880980 { Rva00880980 *value(); };
Rva00880980 *Rva00880980::value() { return this; }
struct Rva00880990 { char bytes[8]; void *value(int); };
void *Rva00880990::value(int index) { return bytes + 8 + index * 8; }
struct Rva008809A0 { char bytes[0x18]; void *value(int); };
void *Rva008809A0::value(int index) { return bytes + 0x18 + index * 4; }
struct Rva008809B0 { char pad00[8]; float field08; float value() const; };
float Rva008809B0::value() const { return field08; }
struct Rva008809C0 { char pad00[12]; float field0C; float value() const; };
float Rva008809C0::value() const { return field0C; }
struct Rva008809D0 { char pad00[8]; float field08; float value() const; };
float Rva008809D0::value() const { return field08; }
