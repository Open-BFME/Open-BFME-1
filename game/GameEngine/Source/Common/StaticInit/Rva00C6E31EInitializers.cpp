// cl: /O1 /Oi /MD
#include <new>
#include <string.h>

extern "C" int __cdecl atexit(void (__cdecl *callback)());
void Rva00C715CARelease();
void Rva00C715DERelease();

// Four DWORD slots at 0134FB38; cleanup 00C715CA tail-calls 009F6855,
// which walks the four slots and deletes each non-null Win32 DC.
struct Rva0134FB38Storage { unsigned long slots[4]; };
extern Rva0134FB38Storage g_rva0134FB38;

// CRT initializer table slot RVA 00EA5518 proves this entry independently
// of the preceding and following ATL initializers.
void Rva00C6E31EInitialize()
{
    memset(&g_rva0134FB38, 0, sizeof(g_rva0134FB38));
    atexit(Rva00C715CARelease);
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


