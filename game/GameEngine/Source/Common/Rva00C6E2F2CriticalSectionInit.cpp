// cl: /O2 /MD
#include <new>

// Retail 0x009F67ED clears the two bookkeeping fields and initializes
// the embedded Win32 critical section at +4.
class Rva009F67EDCriticalSection
{
public:
    Rva009F67EDCriticalSection() throw();
private:
    unsigned char m_storage[32];
};

extern Rva009F67EDCriticalSection g_bfmeRva0134FB18Static;
void rva00C715AARelease();
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void bfmeRva00C6E2F2InitializeCriticalSection()
{
    new (&g_bfmeRva0134FB18Static) Rva009F67EDCriticalSection;
    atexit(rva00C715AARelease);
}

// Retail 0x00C6E308 (22 B) follows the RET at 0x00C6E307 that ends the body
// above and ends with the RET at 0x00C6E31D just before the CRT initializer
// at 0x00C6E31E (table slot 0x00EA5518). It is another copy of the matched
// 0x00C6C770 initializer of the ATL CAtlWinModule global at 0x0130A45C: ATL
// defines that module object selectany, so every including unit emits its
// own constructor-plus-atexit initializer and the linker kept only one table
// entry; this copy is unreferenced. Its teardown is the matched forwarder at
// 0x00C715C0.
namespace ATL
{
class CAtlWinModule
{
public:
    CAtlWinModule() throw();			// retail 0x007E85A0
private:
    unsigned char m_storage[44];
};
}
// Retire ?g_rva0130A45CObject@@3VCAtlWinModule@ATL@@A
extern "C" ATL::CAtlWinModule __identifier("?TheBfmeObject_00C70C00@@3VGen_00C70C00Target@@A");
#define g_rva0130A45CObject __identifier("?TheBfmeObject_00C70C00@@3VGen_00C70C00Target@@A")
void bfmeForward_00C715C0(void);

void Rva00C6E308Initialize()
{
    new (&g_rva0130A45CObject) ATL::CAtlWinModule;
    atexit(bfmeForward_00C715C0);
}
