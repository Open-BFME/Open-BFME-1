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
