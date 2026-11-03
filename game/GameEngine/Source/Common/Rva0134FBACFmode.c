// cl: /O2 /MD
// CRT global _fmode (msvc71 CRT, vendored under inputs/toolchains/vs2003:
// Vc7/lib/msvcrt.lib). _WinMainCRTStartup (0x009F72C4, vendored=msvc71-crt)
// loads it at +0x8E (`mov ecx, [0x0134FBAC]`); retail .data holds 0 at the VA.
int _fmode;
