// cl: /O2 /MD /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include "ascii_string.h"
#include "unicode_string.h"
#include <set>

// Retail CRT cleanup callbacks. The initializers at 00C6A8F0 and 00C6A910
// register these exact entry points, and their globals occupy 012ED4EC/F0.
extern "C" AsciiString g_bfmeNameVSF;
extern "C" AsciiString g_bfmeHostVSF;

void Rva00C6FC60Release()
{
    g_bfmeNameVSF.~AsciiString();
}

void Rva00C6FC70Release()
{
    g_bfmeHostVSF.~AsciiString();
}

// CRT initializer table slot RVA 00EA5E28 points to 00C6E380.
// The registered callback is independently matched at 00C71600.
extern "C" int __cdecl atexit(void (__cdecl *callback)());
void bfmeGoDXE();

void Rva00C6E380Register()
{
    atexit(bfmeGoDXE);
}

// Registered by the push at RVA 0x004555F3 before atexit at 0x004555FB.
// The complete 10-byte callback loads VA 0x012F15CC into ECX and jumps
// through ILT 0x0001F951 to the existing Rva000782A0::invoke body.
// INT3 starts at 0x00C7004A; no semantic owner name is inferred.
class Rva000782A0
{
public:
    void invoke();
};
extern Rva000782A0 g_rva012F15CC;

void Rva00C70040Release()
{
    g_rva012F15CC.invoke();
}

// Registered by the push at RVA 0x0048DE57, followed by the zero store
// constructing this UnicodeString and the atexit call at 0x0048DE6C.
// The callback jumps via ILT 0x0003B304 to its existing destructor;
// INT3 starts at 0x00C700FA, immediately after the 10-byte body.
extern UnicodeString g_rva012F3348;

void Rva00C700F0Release()
{
    g_rva012F3348.~UnicodeString();
}

// Registered at RVA 0x0098ADF1 and passed to atexit at 0x0098AE12.
// The target at 0x009845A0 already has this matched, opaque member name.
// Keep it rather than guessing an owner or destructor identity. The
// callback's final JMP ends at 0x00C714FA, where INT3 padding begins.
class BfmeThing943G
{
public:
    void bfmeGo943G();
};
extern BfmeThing943G g_rva0134C63C;

void Rva00C714F0Release()
{
    g_rva0134C63C.bfmeGo943G();
}

// ILT 0x0003B2B9 reaches the matched out-of-line set<AsciiString>
// destructor at 0x00077FB0. Its definition remains in PeerDefs.cpp.
template <> _STL::set<AsciiString>::~set();
typedef _STL::set<AsciiString> ExitStringSet;

// Registered at RVA 0x006B73DB, then passed to atexit at 0x006B73E3.
// MOV ECX / JMP ends at +0x0A, immediately before the INT3 run.
extern ExitStringSet g_rva012F7768;

void Rva00C708F0Release()
{
    g_rva012F7768.~ExitStringSet();
}

// The other set is independently registered at RVA 0x006B17D7 and
// passed to atexit at 0x006B17DF. Its callback uses the same proven
// destructor route and ends at the INT3 run at 0x00C7091A.
extern ExitStringSet g_rva012F7750;

void Rva00C70910Release()
{
    g_rva012F7750.~ExitStringSet();
}
