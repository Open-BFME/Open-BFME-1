// Address-derived identity: retail RVA 0x0006B150 calls MSVCR71 _memicmp.
// No original class ownership is asserted; replaces the false BlitBackward claim.
extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *left, const void *right, unsigned int count);

int __stdcall Rva0006B150Compare(const void *left, const void *right, unsigned int count)
{
    return _memicmp(left, right, count);
}
