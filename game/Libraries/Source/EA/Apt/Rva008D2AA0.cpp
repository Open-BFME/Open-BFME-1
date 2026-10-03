// cl: /O2 /MD
// Retail VA011362C8 slot10 selects 8D2AA0; constructor 89A6E0 stores the
// table at 89A745. Complete 56B body ends RET8 at 8D2AD5, then INT3.
// The receiver and method retain existing opaque/address-derived identities.
// Callee 89CEF0 is a 520B ECX/one-stack-slot lookup with EAX result and RET4;
// use the existing pinned BfmeTab1024 ABI view, not its dump's void signature.
// Both global cells and their +8 table subobjects are confirmed by retail.
// See identity_evidence/008d2aa0-table-lookup.md.
class BfmeTab1024 { public: int bfmeFind1024(int); };
struct BfmeMap1024;
struct Rva00899C20Registry;
extern BfmeMap1024 *g_bfmeMap1024;
extern Rva00899C20Registry *g_Va013387D8;
class Rva89A6E0Derived { public: int rva008D2AA0(int, int); };
int Rva89A6E0Derived::rva008D2AA0(int, int key)
{
    int result = reinterpret_cast<BfmeTab1024 *>(
        reinterpret_cast<char *>(g_bfmeMap1024) + 8)->bfmeFind1024(key);
    if (!result || (static_cast<unsigned char>(~(*reinterpret_cast<unsigned int *>(result + 4) >> 15)) & 1))
        result = reinterpret_cast<BfmeTab1024 *>(
            reinterpret_cast<char *>(g_Va013387D8) + 8)->bfmeFind1024(key);
    return result;
}
