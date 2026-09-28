// cl: /O1 /Ob1 /DNDEBUG /MD
// Retail critical-section owner constructor. The SEH filter returns 1 and
// the handler reraises a noncontinuable access violation. The two scalar
// fields at +00/+1C are initialized before the protected API call.
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(void *);
extern "C" __declspec(dllimport) __declspec(noreturn) void __stdcall RaiseException(unsigned long,
    unsigned long, unsigned long, const unsigned long *);
class Rva009F67EDCriticalSection {
    unsigned first;
    char section[24];
    unsigned last;
public:
    Rva009F67EDCriticalSection();
};
Rva009F67EDCriticalSection::Rva009F67EDCriticalSection()
{
    first = 0;
    last = 0;
    __try {
        InitializeCriticalSection(section);
    } __except(1) {
        RaiseException(0xc0000005, 1, 0, 0);
    }
}
