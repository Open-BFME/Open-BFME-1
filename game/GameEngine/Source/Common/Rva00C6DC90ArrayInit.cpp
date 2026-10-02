// cl: /O2 /Ob0 /MD /EHsc
// Retail .CRT initializer 0x00C6DC90 uses the compiler vector constructor
// iterator on VA 0x01338480: stride 4, count 178, ctor 0x00891B40,
// dtor 0x00891B80. Its registered cleanup at 0x00C70F60 passes the same
// array, stride, count and destructor to the vector destructor iterator.
// The constructor's one pointer names the empty block at VA 0x012D5298;
// both routines adjust that block's 16-bit refcount. The existing opaque
// Rva00891B40 type and bfmeObjDAE storage name retain unresolved identity.
// Native array lifetime emits COFF _$E1 (initializer) and _$E2 (cleanup);
// ledger object-symbol notes select these TU-local compiler artifacts.
struct Rva00891B80Block;
class Rva00891B40
{
    Rva00891B80Block *m_block;
public:
    Rva00891B40();
    ~Rva00891B40();
};
extern "C" Rva00891B40 bfmeObjDAE[178];
Rva00891B40 bfmeObjDAE[178];
