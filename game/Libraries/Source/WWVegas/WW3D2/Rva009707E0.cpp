// cl: /O2 /MD
// Retail table VA0113E6F0 slot13 (+34) points directly to009707E0.
// The matched Rva00970880Proto constructor installs it at009708AA.
// Table VA0113E7B0 slot13 points to009715C0; the matched
// Rva00971670Proto constructor installs it at0097169A.
// Each body is MOV EAX, immediate; RET, then INT3. The owner views use
// existing constructor identities; method names remain address-derived.

class Rva00970880Proto {
public:
    unsigned int rva009707E0() const;
};

unsigned int Rva00970880Proto::rva009707E0() const
{
    return 0x484c4f44;
}

class Rva00971670Proto {
public:
    unsigned int rva009715C0() const;
};

unsigned int Rva00971670Proto::rva009715C0() const
{
    return 0x48494552;
}
