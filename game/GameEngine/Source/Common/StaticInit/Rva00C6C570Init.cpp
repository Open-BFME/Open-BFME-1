// cl: /O2 /MD
struct RvaEmptyAlloc { RvaEmptyAlloc() {} };
class RvaList
{
public:
    unsigned char m_storage[0xC];
};
extern RvaList g_rva01306978Object;
extern void j_00003427();
void bfmeForward_00C70AB0();
struct Rva00C6C570Caller
{
    Rva00C6C570Caller()
    {
        typedef void (RvaList::*Member)(const RvaEmptyAlloc &);
        union { void (*function)(); Member method; } call;
        call.function = j_00003427;
        (g_rva01306978Object.*call.method)(RvaEmptyAlloc());
        atexit(bfmeForward_00C70AB0);
    }
};
struct Rva00C6C570Global
{
    Rva00C6C570Caller m_caller;
    unsigned char m_pad[0xB];
};
Rva00C6C570Global g_rva01306978Global;
