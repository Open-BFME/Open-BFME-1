// cl: /DNDEBUG /MD /EHsc
// RVA 0x009C8680: copy a C string to the buffer at 0x0134C948.
// The buffer's purpose is not yet established by a matched caller.

extern "C" char *__cdecl strcpy(char *, const char *);
#pragma intrinsic(strcpy)

void __cdecl Rva009C8680CopyGlobalString(const char *source)
{
    strcpy((char *)0x0134C948, source);
}
