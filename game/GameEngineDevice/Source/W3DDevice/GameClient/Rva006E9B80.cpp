// cl: /DNDEBUG /MD
// The existing address-qualified callee name is retained. Retail 00934940
// consumes ECX, has no stack arguments, and returns void; the one-register
// fastcall view supplies exactly that thiscall ABI, without a new pin.
void d_00934940();
typedef void (__fastcall *Rva00934940Call)(void *);
class Rva006E9B80
{
public:
 virtual void method();
 unsigned char m_unreconstructed04[0x160];
 void *m_target164;
};
void Rva006E9B80::method()
{
 reinterpret_cast<Rva00934940Call>(&d_00934940)(m_target164);
}

// Boundary and ABI evidence: identity_evidence/006e9b80-0092c320-wrappers.md.
