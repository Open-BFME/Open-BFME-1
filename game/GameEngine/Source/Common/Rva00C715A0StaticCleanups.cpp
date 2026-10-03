// cl: /O2 /MD /EHsc
// Retail C715A0 is an independently registered ten-byte termination callback.
// The original 32-byte dump also contained the separate C715AA callback.
class Rva000FFCA0
{
public:
    ~Rva000FFCA0();
};
extern Rva000FFCA0 g_Rva00F4FAB8;

void rva00C715A0()
{
    g_Rva00F4FAB8.~Rva000FFCA0();
}

// Existing opaque owner/global names come from the matched initializer C6E2F2.
class Rva009F67EDCriticalSection
{
    unsigned char m_storage[32];
};
extern Rva009F67EDCriticalSection g_bfmeRva0134FB18Static;
class BfmeK1040
{
public:
    void bfmeGo1040K();
};
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void *);

void rva00C715AARelease()
{
    ((BfmeK1040 *)&g_bfmeRva0134FB18Static)->bfmeGo1040K();
    DeleteCriticalSection((char *)&g_bfmeRva0134FB18Static + 4);
}
