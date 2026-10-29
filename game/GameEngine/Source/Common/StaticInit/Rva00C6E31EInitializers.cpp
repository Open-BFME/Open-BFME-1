// cl: /O1 /Oi /MD
#include <new>
#include <string.h>

extern "C" int __cdecl atexit(void (__cdecl *callback)());
void rva00C715CAForward();
void Rva00C715DERelease();

// Four DWORD slots at 0134FB38; cleanup 00C715CA tail-calls 009F6855,
// which walks the four slots and deletes each non-null Win32 DC.
// Use the same object as Win32DcCache.cpp and Rva00C715CAForwarder.cpp.
// Retired binding: ?g_rva0134FB38@@3URva0134FB38Storage@@A.
// The pool itself (VA 0134FB38, 16 bytes): zero-filled storage this
// initializer clears and registers for teardown; same four-slot layout as
// the Win32DcCache.cpp view.
class DcPool
{
private:
    long m_slots[4];
};
DcPool TheDcPool;

// CRT initializer table slot RVA 00EA5518 proves this entry independently
// of the preceding and following ATL initializers.
void Rva00C6E31EInitialize()
{
    memset(&TheDcPool, 0, 4 * sizeof(unsigned long));
    atexit(rva00C715CAForward);
}

// The retail constructor at 009F6ADB takes ECX, no stack arguments,
// returns ECX in EAX and ends with RET at 009F6B85. Its object is 60 bytes.
class Rva009F6ADBObject
{
public:
    Rva009F6ADBObject() throw();
private:
    unsigned char storage[60];
};
extern Rva009F6ADBObject g_rva0134FB48;

// CRT initializer table slot RVA 00EA551C proves the start.
void Rva00C6E34DInitialize()
{
    new (&g_rva0134FB48) Rva009F6ADBObject;
    atexit(Rva00C715DERelease);
}

// Retail 0x00C6E337 and 0x00C6E363 (22 B each) are further unreferenced copies
// of the matched 0x00C6C770 initializer of the ATL CAtlWinModule global at
// 0x0130A45C (ATL defines it selectany, so each including unit emits one and
// the linker kept a single table entry). 0x00C6E337 starts right after the
// RET at 0x00C6E336 and ends before the table-proven 0x00C6E34D; 0x00C6E363
// starts after the RET at 0x00C6E362 and ends with the RET at 0x00C6E378
// before int3 padding. Teardowns are the matched forwarders at 0x00C715D4 and
// 0x00C715E8.
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
extern ATL::CAtlWinModule g_rva0130A45CObject;
void bfmeForward_00C715D4(void);
void bfmeForward_00C715E8(void);

void Rva00C6E337Initialize()
{
    new (&g_rva0130A45CObject) ATL::CAtlWinModule;
    atexit(bfmeForward_00C715D4);
}

void Rva00C6E363Initialize()
{
    new (&g_rva0130A45CObject) ATL::CAtlWinModule;
    atexit(bfmeForward_00C715E8);
}
