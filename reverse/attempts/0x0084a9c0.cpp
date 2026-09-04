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
#ifndef FILE_BEGIN
#define FILE_BEGIN 0
#define FILE_CURRENT 1
#define FILE_END 2
#endif
typedef void *HANDLE;
typedef unsigned long DWORD;
typedef unsigned long SIZE_T;
typedef int BOOL;
typedef union _LARGE_INTEGER {
  struct { DWORD LowPart; long HighPart; };
  __int64 QuadPart;
} LARGE_INTEGER;

namespace _STL {
typedef long streamoff;

class ios_base
{
public:
  enum seekdir { beg = 0, cur = 1, end = 2 };
};

class _Filebuf_base
{
public:
  void *_M_mmap(streamoff offset, streamoff len);
  streamoff _M_seek(streamoff offset, ios_base::seekdir dir);
  streamoff _M_file_size(void);

private:
  HANDLE _M_file_id;
  HANDLE _M_view_id;
};
}

extern "C" __declspec(dllimport) HANDLE __stdcall CreateFileMappingA(
    HANDLE, void *, DWORD, DWORD, DWORD, const char *);
extern "C" __declspec(dllimport) void *__stdcall MapViewOfFile(
    HANDLE, DWORD, DWORD, DWORD, SIZE_T);
extern "C" __declspec(dllimport) BOOL __stdcall UnmapViewOfFile(void *);
extern "C" __declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE);
extern "C" __declspec(dllimport) DWORD __stdcall SetFilePointer(
    HANDLE, long, long *, DWORD);
extern "C" __declspec(dllimport) DWORD __stdcall GetLastError(void);

namespace _STL {

streamoff _Filebuf_base::_M_seek(streamoff offset, ios_base::seekdir dir)
{
  int whence;

  switch (dir) {
  case ios_base::beg:
    if (offset < 0)
      return streamoff(-1);
    whence = FILE_BEGIN;
    break;
  case ios_base::cur:
    whence = FILE_CURRENT;
    break;
  case ios_base::end:
    if (-offset > _M_file_size())
      return streamoff(-1);
    whence = FILE_END;
    break;
  default:
    return streamoff(-1);
  }

  LARGE_INTEGER li;
  li.QuadPart = offset;
  li.LowPart = SetFilePointer(_M_file_id, li.LowPart, &li.HighPart, whence);
  if (li.LowPart == (DWORD)-1 && GetLastError() != 0)
    return streamoff(-1);
  return li.QuadPart;
}

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

}
