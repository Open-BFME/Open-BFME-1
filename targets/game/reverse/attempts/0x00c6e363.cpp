// ?Rva00C6E363Initialize@@YAXXZ
// partial score=1.0 date=2026-09-27
// cl: /O2 /MD
#include <new>

// Candidate entry boundaries are unproven: no incoming REL32, ILT or raw
// image pointer was found for the three starts below. Do not claim these
// bodies on byte shape alone. The surrounding routines end in plain RET.
namespace ATL {
class CAtlWinModule {
public:
    CAtlWinModule() throw();
private:
    unsigned char storage[44];
};
}
extern ATL::CAtlWinModule g_rva0130A45CObject;
extern "C" int __cdecl atexit(void (__cdecl *callback)());
void Rva00C715C0Release();
void Rva00C715D4Release();
void Rva00C715E8Release();

void Rva00C6E363Initialize()
{
    new (&g_rva0130A45CObject) ATL::CAtlWinModule;
    atexit(Rva00C715E8Release);
}
