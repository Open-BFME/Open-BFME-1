// stlport
// STLport 4.5.3 Win32 _Filebuf_base file mapping.

#include <fstream>
#include <windows.h>

#define PAGE_READONLY 0x02
#define FILE_MAP_READ 0x04
extern "C" __declspec(dllimport) HANDLE WINAPI CreateFileMappingA(
    HANDLE, LPSECURITY_ATTRIBUTES, DWORD, DWORD, DWORD, LPCSTR);
extern "C" __declspec(dllimport) LPVOID WINAPI MapViewOfFile(
    HANDLE, DWORD, DWORD, DWORD, SIZE_T);

namespace _STL {

static __forceinline streamoff bfmeMmapSeekFromStart(_Filebuf_base *filebuf, streamoff offset)
{
  if (offset < 0)
    return streamoff(-1);

  LARGE_INTEGER li;
  li.QuadPart = offset;
  li.LowPart = SetFilePointer(*(HANDLE *)filebuf, li.LowPart, &li.HighPart, FILE_BEGIN);
  if (li.LowPart == (DWORD)-1 && GetLastError() != 0)
    return streamoff(-1);
  return li.QuadPart;
}

void *_Filebuf_base::_M_mmap(streamoff offset, streamoff len)
{
  void *base;
  _M_view_id = CreateFileMappingA(_M_file_id, 0, PAGE_READONLY, 0, 0, 0);
  if (_M_view_id) {
    base = MapViewOfFile(_M_view_id, FILE_MAP_READ,
                         (DWORD)((unsigned __int64)offset >> 32),
                         (DWORD)((unsigned __int64)offset & 0xffffffff),
                         (SIZE_T)len);
    if (base == 0 || bfmeMmapSeekFromStart(this, offset + len) < 0) {
      if (base)
        UnmapViewOfFile(base);
      if (_M_view_id)
        CloseHandle(_M_view_id);
      _M_view_id = 0;
      base = 0;
    }
  } else
    base = 0;
  return base;
}

}
