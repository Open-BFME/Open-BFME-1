// ?_M_mmap@_Filebuf_base@_STL@@QAEPAXJJ@Z
// partial score=0.9 date=2026-09-04
// stlport
// STLport 4.5.3 Win32 _Filebuf_base::_M_mmap — 187/187 size, 19B edi<->esi wall.
// Same-TU _M_seek inlines the SetFilePointer/GetLastError shape and forward je.
// Wholesale this/offset register swap vs retail (edi/esi); TU-flag wall.

#ifndef PAGE_READONLY
#define PAGE_READONLY 0x02
#endif
#ifndef FILE_MAP_READ
#define FILE_MAP_READ 0x04
#endif
extern "C" __declspec(dllimport) HANDLE __stdcall CreateFileMappingA(
    HANDLE, void *, DWORD, DWORD, DWORD, const char *);
extern "C" __declspec(dllimport) void *__stdcall MapViewOfFile(
    HANDLE, DWORD, DWORD, DWORD, SIZE_T);
extern "C" __declspec(dllimport) BOOL __stdcall UnmapViewOfFile(void *);

void *_Filebuf_base::_M_mmap(streamoff offset, streamoff len)
{
  void *base;
  _M_view_id = CreateFileMappingA(_M_file_id, 0, PAGE_READONLY, 0, 0, 0);
  if (_M_view_id) {
    LARGE_INTEGER li;
    li.QuadPart = offset;
    base = MapViewOfFile(_M_view_id, FILE_MAP_READ, li.HighPart, li.LowPart,
                         (SIZE_T)len);
    if (base == 0 || _M_seek(offset + len, ios_base::beg) < 0) {
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
