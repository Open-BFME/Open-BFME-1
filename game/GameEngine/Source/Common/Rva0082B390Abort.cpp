// cl: /DNDEBUG /MD /EHsc /Od /Oy-
// The retail body at 0x0082B390 calls the MSVCR71 abort import at 0x01359378.

extern "C" __declspec(dllimport) __declspec(noreturn) void __cdecl abort(void);

void Rva0082B390Abort(void)
{
    abort();
}
