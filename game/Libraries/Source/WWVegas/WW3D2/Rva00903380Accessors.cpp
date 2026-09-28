// cl: /O2 /Ob0
// Separate int3-bounded retail entries. The layout resembles light accessors,
// but no caller proves their names; keep independent address-derived views.
struct Rva00903380 { float value(int) const; };
float Rva00903380::value(int index) const {
    return *(const float *)((const char *)this + index * 0x54 + 0x4c);
}
struct Rva00903390 { const void *value(int) const; };
const void *Rva00903390::value(int index) const {
    return (const char *)this + index * 0x54 + 0x5c;
}
struct Rva009033A0 { const void *value(int) const; };
const void *Rva009033A0::value(int index) const {
    return (const char *)this + index * 0x54 + 0x50;
}
struct Rva009033B0 { const void *value(int) const; };
const void *Rva009033B0::value(int index) const {
    return (const char *)this + index * 0x54 + 0x3c;
}
struct Rva009033C0 { unsigned int field00; unsigned int value() const; };
unsigned int Rva009033C0::value() const { return field00; }
struct Rva009033D0 { char pad00[12]; unsigned short field0C; unsigned short value() const; };
unsigned short Rva009033D0::value() const { return field0C; }
struct Rva009033E0 { char pad00[8]; unsigned int field08; unsigned int value() const; };
unsigned int Rva009033E0::value() const { return field08; }
struct Rva009033F0 { char pad00[0x18]; unsigned char field18; unsigned char value() const; };
unsigned char Rva009033F0::value() const { return field18; }
