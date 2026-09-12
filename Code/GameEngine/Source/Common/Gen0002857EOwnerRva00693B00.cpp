// ?d_00693b00@@YAXXZ
// Scratch clean-C++ codegen probe. The by-value key constructor evaluates its
// name argument first under MSVC 7.1; after that copy, the dead value pointer
// parameter can carry the scalar stamp without changing observable behavior.
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
#include "StringInline.h"
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
class Rva00691ED0Key
{
public:
    Rva00691ED0Key(UnsignedInt primary, AsciiString name);
    ~Rva00691ED0Key() {}
private:
    UnsignedInt m_primary;
    AsciiString m_name;
};
// The key constructor is the existing matched Rva00691ED0Key body; keeping
// its natural declaration makes the COFF relocation resolve through that row.
// The tree body is still a generated STL row, so call its known ILT through a
// typed member-pointer adapter.  The raw thunk declaration intentionally has
// its existing zero-argument name; the typed member view supplies this/key
// ABI at the call site without a new alias or pin.
struct Gen0002857EKeyTreeCall
{
    UnsignedInt erase(const Rva00691ED0Key &key);
};
extern void j_00007027(void);
static __forceinline UnsignedInt eraseKey(Gen0002857EKeyTreeCall *tree,
    const Rva00691ED0Key &key)
{
    typedef UnsignedInt (Gen0002857EKeyTreeCall::*EraseCall)(
        const Rva00691ED0Key &);
    union
    {
        void (*raw)(void);
        EraseCall member;
    } call;
    call.raw = j_00007027;
    return (tree->*call.member)(key);
}
class Gen0002857E
{
public:
    AsciiString m_name;
    UnsignedByte m_beforeOwner[0x34 - 4];
    int m_count;
    UnsignedInt m_stamp;
    int m_bucket;
    UnsignedByte m_compressed;
    UnsignedByte m_active;
    UnsignedByte m_reserved;
};
class Gen0002857EOwner
{
public:
    // The caller proves this member's class, thiscall ABI, and one argument;
    // the method's semantic name is not recovered, so retain the RVA label.
    void Rva00693B00(Gen0002857E *value);
private:
    UnsignedByte m_beforeMap[0x20];
    Gen0002857EKeyTreeCall m_map;
};
// ?Rva00693B00@Gen0002857EOwner@@QAEXPAVGen0002857E@@@Z
void Gen0002857EOwner::Rva00693B00(Gen0002857E *value)
{
    Gen0002857E *nameValue = value;
    Rva00691ED0Key key(
        (UnsignedInt)(value = reinterpret_cast<Gen0002857E *>(value->m_stamp)),
        nameValue->m_name);
    eraseKey(&m_map, key);
}
