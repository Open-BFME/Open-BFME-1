/* Isolate native import-library binding without CRT startup or local stubs. */
#include <string.h>

__declspec(dllexport) void *copy_bytes(void *dest, const void *src, size_t size) {
    return memmove(dest, src, size);
}
