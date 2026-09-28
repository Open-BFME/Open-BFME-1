// cl: /O2 /MD
struct RvaEmptyAlloc { RvaEmptyAlloc() {} };
class RvaList
{
public:
    unsigned char m_storage[0xC];
};
extern RvaList g_rva012F7180Object;
extern void j_00049c4c();
void bfmeForward_00C708D0();
struct Rva00C6C3F0Caller
{
    Rva00C6C3F0Caller()
    {
        typedef void (RvaList::*Member)(const RvaEmptyAlloc &);
        union { void (*function)(); Member method; } call;
        call.function = j_00049c4c;
        (g_rva012F7180Object.*call.method)(RvaEmptyAlloc());
        atexit(bfmeForward_00C708D0);
    }
};
struct Rva00C6C3F0Global
{
    Rva00C6C3F0Caller m_caller;
    unsigned char m_pad[0xB];
};
Rva00C6C3F0Global g_rva012F7180Global;
