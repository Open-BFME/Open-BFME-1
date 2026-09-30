// cl: /O2 /MD
// The four MSVCR71 import jumps (FF 25 [IAT]) that retail's linker placed
// ahead of crtexew.obj's check_managed_app. IAT slots: _CIacos 0x01359230,
// _strnicmp 0x01359348, _mbslen 0x0135930C, srand 0x01359490.
extern "C" __declspec(dllimport) void __cdecl _CIacos(void);
extern "C" __declspec(dllimport) int __cdecl _strnicmp(const char *, const char *, unsigned int);
extern "C" __declspec(dllimport) unsigned int __cdecl _mbslen(const unsigned char *);
extern "C" __declspec(dllimport) void __cdecl srand(unsigned int);

// _CIacos takes and returns its operand on the x87 stack, so the forwarder
// has no C parameters; the tail call is the whole body.
void __cdecl Rva009F7256_CIacos(void) { _CIacos(); }
int Rva009F725C_strnicmp(const char *a, const char *b, unsigned int n) { return _strnicmp(a, b, n); }
unsigned int Rva009F7262_mbslen(const unsigned char *s) { return _mbslen(s); }
void Rva009F7268_srand(unsigned int seed) { srand(seed); }
