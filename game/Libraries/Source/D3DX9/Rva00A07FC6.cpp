// cl: /O2 /MD
// Original createmesh.obj gives these independent ten-byte COMDAT bodies
// unsigned-int const-thiscall/no-argument signatures. See
// targets/game/reverse/identity_evidence/00a07fc6-native-masks.md.
class Rva00A07FC6
{
public:
    unsigned int rva00A07FC6() const;
    unsigned int rva00A07FD0() const;
    unsigned int rva00A07FDA() const;
    unsigned int rva00A07FE4() const;
    unsigned int rva00A07FEE() const;
    unsigned int rva00A07FF8() const;

private:
    char at0[0x218];
    unsigned int at218;
};

unsigned int Rva00A07FC6::rva00A07FC6() const { return at218 & 1; }
unsigned int Rva00A07FC6::rva00A07FD0() const { return at218 & 2; }
unsigned int Rva00A07FC6::rva00A07FDA() const { return at218 & 4; }
unsigned int Rva00A07FC6::rva00A07FE4() const { return at218 & 8; }
unsigned int Rva00A07FC6::rva00A07FEE() const { return at218 & 16; }
unsigned int Rva00A07FC6::rva00A07FF8() const { return at218 & 32; }
