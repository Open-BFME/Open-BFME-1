// Open-BFME: address-derived reconstruction of retail RVA 0x0035EFC0.
// The complete member body returns the five-dword value at the start of its
// owner through MSVC's hidden structure-return pointer.  No authoritative
// class or method identity is currently available.

struct Rva0035EFC0Value
{
    unsigned word0;
    unsigned word1;
    unsigned word2;
    unsigned word3;
    unsigned word4;
};

class Rva0035EFC0Owner
{
public:
    Rva0035EFC0Value copyValue();

private:
    Rva0035EFC0Value value_;
};

Rva0035EFC0Value Rva0035EFC0Owner::copyValue()
{
    return value_;
}
