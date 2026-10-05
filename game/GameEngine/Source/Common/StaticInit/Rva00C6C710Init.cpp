// cl: /O2 /MD
// Retail 0x00C6C710 is the dynamic initializer for the global at 0x01307348:
// in-place construction through the 0x007DB820 ctor (reached via ILT
// 0x0000281F) with teardown registered at exit. The owning TU is unknown, so
// the class and the global take address-derived names. The ledger name is
// address-derived; the verified body is this TU's own _$E1 (see the
// object-symbol note): the source defines the global so MSVC emits the $E
// body, which runs at startup from the CRT init table.

class Rva007DB820
{
public:
    Rva007DB820();
    ~Rva007DB820();
    unsigned char m_storage[0x54];
};
extern "C" int __cdecl atexit(void (__cdecl *callback)());

Rva007DB820 RingFilterObject;
