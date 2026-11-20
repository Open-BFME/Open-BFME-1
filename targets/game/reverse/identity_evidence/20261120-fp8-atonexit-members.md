# Native fp8 and atonexit members, unchanged CODE imports

The original libc.lib fp8.obj member defines __setdefaultprecision at
RVA0x009F7F98, exactly18B. Its native REL32 at+0xB names __controlfp and
decodes in retail to RVA0x009F7DF2. That complete six-byte body is
FF25 B0923501: IAT VA0x013592B0, MSVCR71.dll!_controlfp. Original msvcrt.lib
has its actual short CODE import public __controlfp, hint219, x86, NOPREFIX.
Public float.h declares unsigned-int cdecl _controlfp(unsigned-int,unsigned-int).
The original fp8 local CV procedure type is missing; no complete original
callee debug signature is claimed. The public declaration, named native
caller, original CODE member and exact PE route independently agree.

The whole msvcrt.lib atonexit.obj defines __onexit RVA0x009F6E00/38B,
_atexit RVA0x009F6E26/18B, and two independent4B tentative COMMON globals:
___onexitbegin VA0x01357214 and ___onexitend VA0x01357204. CodeView in both
original atonexit and crtexew independently proves pointer-to-pointer-to
void-cdecl(void) for these table globals, with pointer attributes0xA. Public
stdlib.h supplies _onexit_t as the distinct int-cdecl(void) callback type.
Native _onexit/atexit function types agree with those two callback roles.

Native onexit REL32 at+0x1E names ___dllonexit and decodes to RVA0x009F7EE0.
Its full FF25 reads IAT VA0x01359260 for MSVCR71.dll!__dllonexit; the native
short CODE import has true public ___dllonexit, hint107, x86, NOPREFIX.
The callback and two addresses pushed by the original caller establish
_onexit_t __cdecl __dllonexit(_onexit_t,void-cdecl-callback **,void-cdecl-callback **).
The import member itself contains no complete callee CV prototype. The
DLL-mode branch directly reads the existing __imp___onexit IAT entry.

The unchanged original msvcrt.lib SHA256 is
e888617fbd2e153645b92122deab1c6ec437905431243c43aa7310164c0e7779.
The original fp8 member SHA256 is
8d8f704827823901dd356f4a828a4002b21fa1ae71c3dbebe75fc3a920766cf6;
atonexit member SHA256 is
3e310763b0ef61fec791c9b84606e03e4ebf4a92394bfcb2e4ad414cbc9dea44.
Whole-member source comparisons reproduce all18/38/18 code bytes and named
relocations. The C atonexit source preserves section0/value4/storage2 for
both COMMONs; C++ would impose a wrong shared8B BSS allocation. Existing
WinMainStartup and CRT shims use the same independently corrected table type.

Normal original/native CODE libraries plus these actual two caller objects
close an isolated NOENTRY DLL without warnings or reselecting original fp8/
atonexit bodies. That fixture was not executed. Extra authored six-byte import
providers duplicate native CODE definitions; their ordinary add_match attempts
were refused because gen-import is not an admitted generic repoint/identity
class. They were not admitted, and their own candidate files are private.

B1 AGENTS.md's small-dependency and import-route rules permit one independently
proved callee route pin with its caller change. The two pins therefore name
the existing native CODE routes with route=MSVCR71.dll!_controlfp and
route=MSVCR71.dll!__dllonexit, respectively. They neither rename/repoint the
generated rows nor invent a second function identity, alias, IAT cell or map
override. Run pin_consistency before and after and normal provider/consumer
gates. Only the two new caller bodies may receive recovery credit; retained
atexit18B, two COMMONs and existing generated import coverage are separate.

Donor: BFME2 147fd3e52b36ee0306aaeef5b316beb09f7c7671,
Code/Libraries/Source/CRT/DefaultPrecision.cpp and DllOnExitImport/ControlFp
context. B1 original member, types, storage and addresses are independent;
donor table types were reconciled rather than copied. No Microsoft CRT
implementation source was read. No whole-game link, startup, runtime, memory,
crash or performance improvement is established by these scoped checks.
