// ?bfmeComputeQW@@YAHPAX@Z
// partial score=0.44 date=2026-09-24
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#include <string.h>
extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *left, const void *right, unsigned int count);
extern char Rva006A16B0Empty[];
struct Rva0078A490StringData
{
    int refs;
    unsigned short length;
    unsigned short capacity;
    char text[1];
};
static __forceinline const char **Rva0078A490NameTableIfPresent()
{
    if (*(const char * volatile *)0x012BB88C != 0)
        return (const char **)0x012BB88C;
    return 0;
}
static __forceinline int Rva0078A490Compare(void *item, const char *name)
{
    int nameLength = name ? strlen(name) : 0;
    Rva0078A490StringData *data = *(Rva0078A490StringData **)item;
    int length = data ? data->length : 0;
    const char *text = data ? data->text : Rva006A16B0Empty;
    int result = _memicmp(text, name, length < nameLength ? length : nameLength);
    if (result != 0)
        return result;
    return length - nameLength;
}
int __cdecl bfmeComputeQW(void *item)
{
    int index = 0;
    if (*(const char * volatile *)0x012BB88C != 0) {
        const char **base = (const char **)0x012BB88C;
        const char **cursor = base;
        const char *name = *base;
        do {
            if (Rva0078A490Compare(item, name) == 0)
                return index;
            ++index;
            ++cursor;
            name = *cursor;
        } while (name != 0);
    }
    return 0;
}
