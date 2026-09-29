// cl: /DNDEBUG /MD /EHsc
// RVA 0x009C8680: copy a C string to the global buffer at 0x0134C948.
// The buffer's purpose is not yet established by a matched caller, so the
// name stays address-derived; its extent is not proven either, so the extern
// is an incomplete array type and only its address is ever taken.

extern "C" char *__cdecl strcpy(char *, const char *);
#pragma intrinsic(strcpy)

extern char g_0134C948[];

void __cdecl Rva009C8680CopyGlobalString(const char *source)
{
    strcpy(g_0134C948, source);
}
