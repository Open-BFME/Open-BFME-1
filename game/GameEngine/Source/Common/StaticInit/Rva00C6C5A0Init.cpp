// cl: /O2 /MD
class RvaSimpleDynVec
{
public:
    void *m_vptr;
    int m_04;
    int m_08;
    int m_0C;
};
extern RvaSimpleDynVec g_rva01306C6CObject;
extern void j_000463f3();
void bfmeForward_00C70AD0();
struct Rva00C6C5A0Caller
{
    Rva00C6C5A0Caller()
    {
        typedef void (RvaSimpleDynVec::*Member)(int);
        union { void (*function)(); Member method; } call;
        call.function = j_000463f3;
        (g_rva01306C6CObject.*call.method)(0);
        atexit(bfmeForward_00C70AD0);
    }
};
struct Rva00C6C5A0Global
{
    Rva00C6C5A0Caller m_caller;
    unsigned char m_pad[0xF];
};
Rva00C6C5A0Global g_rva01306C6CGlobal;
