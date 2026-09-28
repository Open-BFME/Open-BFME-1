// cl: /O2 /MD
class MouseThreadClass
{
public:
    unsigned char m_storage[0x54];
};
extern MouseThreadClass g_rva012F9808Object;
extern void j_0003cdd0();
void bfmeForward_00C709C0();
struct Rva00C6C4F0Caller
{
    Rva00C6C4F0Caller()
    {
        typedef void (MouseThreadClass::*Member)();
        union { void (*function)(); Member method; } call;
        call.function = j_0003cdd0;
        (g_rva012F9808Object.*call.method)();
        atexit(bfmeForward_00C709C0);
    }
};
struct Rva00C6C4F0Global
{
    Rva00C6C4F0Caller m_caller;
    unsigned char m_pad[0x53];
};
Rva00C6C4F0Global g_rva012F9808Global;
