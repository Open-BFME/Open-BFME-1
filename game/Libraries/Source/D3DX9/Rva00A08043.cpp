// cl: /O2 /MD
// Distinct native createmesh.obj code COMDATs, placed by a unique89-byte
// sequence. Their signatures are unsigned-int const-thiscall/no arguments.
// See targets/game/reverse/identity_evidence/00a08043-native-masks.md.
class Rva00A08043
{
public:
    unsigned int rva00A08043() const;
    unsigned int rva00A0804D() const;
    unsigned int rva00A08057() const;
    unsigned int rva00A08061() const;
    unsigned int rva00A0806B() const;
    unsigned int rva00A08075() const;

private:
    char at0[0x218];
    unsigned int at218;
};

unsigned int Rva00A08043::rva00A08043() const { return at218 & 1; }
unsigned int Rva00A08043::rva00A0804D() const { return at218 & 2; }
unsigned int Rva00A08043::rva00A08057() const { return at218 & 4; }
unsigned int Rva00A08043::rva00A08061() const { return at218 & 8; }
unsigned int Rva00A08043::rva00A0806B() const { return at218 & 16; }
unsigned int Rva00A08043::rva00A08075() const { return at218 & 32; }
