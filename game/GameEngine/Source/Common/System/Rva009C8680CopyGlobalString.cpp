// cl: /DNDEBUG /MD /EHsc
// RVA 0x009C8680: copy a C string to the global buffer at 0x0134C948.
// The buffer's purpose is not yet established by a matched caller, so the
// name stays address-derived. It runs 256 bytes up to byte_134CA48 (the next
// recorded datum), like its sibling path buffers byte_134CA48 and
// byte_134CB50; retail .bss zero.

extern "C" char *__cdecl strcpy(char *, const char *);
#pragma intrinsic(strcpy)

char g_0134C948[256];

void __cdecl Rva009C8680CopyGlobalString(const char *source)
{
    strcpy(g_0134C948, source);
}
