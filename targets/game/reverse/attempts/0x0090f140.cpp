// ?bfmePrep911E@BfmeSub911E@@QAEXXZ
// partial score=1.0 date=2026-10-03
// cl: /O2 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0090F140 transfers the receiver's pointer at +8 to the reset vector.
// The guard's constructor/destructor contracts are retail 00886F30/00886F60.
#include <windows.h>
#include <vector>

struct BfmeLockTEA
{
    char m_pad[0x18];
    bool m_armed;
    void enter();
    void leave();
};

class Rva00886F60Class
{
public:
    Rva00886F60Class(BfmeLockTEA *lock)
    {
        m_lock = lock;
        if (lock && lock->m_armed)
            EnterCriticalSection(reinterpret_cast<CRITICAL_SECTION *>(lock));
    }

    virtual ~Rva00886F60Class()
    {
        if (m_lock && m_lock->m_armed)
            LeaveCriticalSection(reinterpret_cast<CRITICAL_SECTION *>(m_lock));
    }

    BfmeLockTEA *m_lock;
};

class Rva0090F050Resource
{
public:
    virtual ~Rva0090F050Resource();
    virtual void unusedVirtual();
    virtual void __stdcall releaseResources();
};

class Rva009EB960;
extern Rva009EB960 *Rva0134FAA0;
extern std::vector<Rva0090F050Resource *> Rva013411F0;
extern CRITICAL_SECTION g_bfmeRva012D6DE0CriticalSection;

// Retain the opaque member identity used by the matched caller at 0090F210.
class BfmeSub911E
{
public:
    virtual void bfmeSlot911F0();
    virtual void bfmeDrop911E(int f);
    void bfmePrep911E();

    char m_rva0090F140At04[4];
    Rva0090F050Resource *m_rva0090F140At08;
};

void BfmeSub911E::bfmePrep911E()
{
    if (m_rva0090F140At08)
    {
        if (Rva0134FAA0)
        {
            Rva00886F60Class guard(reinterpret_cast<BfmeLockTEA *>(
                &g_bfmeRva012D6DE0CriticalSection));
            Rva013411F0.push_back(m_rva0090F140At08);
        }
        else
        {
            m_rva0090F140At08->releaseResources();
        }
        m_rva0090F140At08 = 0;
    }
}
