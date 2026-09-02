// stlport
// STLport 4.5.3 Win32 file-size helper used by _Filebuf_base.

#include <windows.h>

long Rva00849E80FileSize(HANDLE fd)
{
    LARGE_INTEGER size;
    size.LowPart = GetFileSize(fd, (DWORD *)&size.HighPart);
    if (size.LowPart == (DWORD)-1 && GetLastError() != 0)
        return 0;
    return (long)size.QuadPart;
}
