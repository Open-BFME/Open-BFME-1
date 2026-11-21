// cl: /MD
// The original msvcrt.lib cinitexe.obj owns exactly these four public
// one-element _PVFV arrays. COFF names: ___xc_a, ___xc_z, ___xi_a, ___xi_z.
// Its .CRT$XCA/XCZ/XIA/XIZ sections are initialized, writable, 4-byte aligned
// and four bytes long; its original directive merges .CRT into .data.
typedef void (__cdecl *CrtInitializer)(void);

#pragma data_seg(".CRT$XCA")
CrtInitializer __xc_a[1] = {0};
#pragma data_seg(".CRT$XCZ")
CrtInitializer __xc_z[1] = {0};
#pragma data_seg(".CRT$XIA")
CrtInitializer __xi_a[1] = {0};
#pragma data_seg(".CRT$XIZ")
CrtInitializer __xi_z[1] = {0};
#pragma data_seg()

#pragma comment(linker, "/merge:.CRT=.data")

typedef char CrtInitializerMustBeFourBytes[(sizeof(CrtInitializer)==4)?1:-1];
typedef char XcBeginMustBeOnePointer[(sizeof(__xc_a)==4)?1:-1];
typedef char XcEndMustBeOnePointer[(sizeof(__xc_z)==4)?1:-1];
typedef char XiBeginMustBeOnePointer[(sizeof(__xi_a)==4)?1:-1];
typedef char XiEndMustBeOnePointer[(sizeof(__xi_z)==4)?1:-1];
