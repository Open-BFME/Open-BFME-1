// stlport
// STLport 4.5.3 Win32 file-buffer implementation.

#include <fstream>
#include <windows.h>

#define _STLP_LF 10
#define _STLP_CR 13
#define _STLP_CTRLZ 26

extern "C" __declspec(dllimport) BOOL WINAPI SetEndOfFile(HANDLE);
extern "C" __declspec(dllimport) long __cdecl _get_osfhandle(int);
bool bfmeGoDXF(void *file);

namespace _SgI {
int _get_osfflags(int file_no, HANDLE os_handle);
}

_STLP_BEGIN_NAMESPACE

bool _Filebuf_base::_M_open(int file_no, ios_base::openmode init_mode)
{
  if (_M_is_open || file_no < 0)
    return false;

  if (_M_is_open || file_no == -1)
    return false;

  HANDLE os_handle = (HANDLE)_get_osfhandle(file_no);

  if ((long)os_handle != -1)
    file_no = (int)os_handle;
  else
    return false;

  if (init_mode != ios_base::__default_mode)
    _M_openmode = init_mode;
  else
    _M_openmode = _SgI::_get_osfflags(file_no, os_handle);

  _M_is_open = true;
  _M_file_id = (_STLP_fd)file_no;
  _M_should_close = false;
  _M_regular_file = bfmeGoDXF(_M_file_id);

  return true;
}

bool _Filebuf_base::_M_open(const char *name, ios_base::openmode openmode,
                            long permission)
{
  _STLP_fd file_no;

  if (_M_is_open)
    return false;

  DWORD dwDesiredAccess, dwCreationDisposition;
  bool doTruncate = false;

  switch (openmode & (~ios_base::ate & ~ios_base::binary)) {
  case ios_base::out:
  case ios_base::out | ios_base::trunc:
    dwDesiredAccess = GENERIC_WRITE;
    dwCreationDisposition = OPEN_ALWAYS;
    doTruncate = true;
    break;
  case ios_base::out | ios_base::app:
    dwDesiredAccess = GENERIC_WRITE;
    dwCreationDisposition = OPEN_ALWAYS;
    break;
  case ios_base::in:
    dwDesiredAccess = GENERIC_READ;
    dwCreationDisposition = OPEN_EXISTING;
    permission = 0;
    break;
  case ios_base::in | ios_base::out:
    dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
    dwCreationDisposition = OPEN_EXISTING;
    break;
  case ios_base::in | ios_base::out | ios_base::trunc:
    dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
    dwCreationDisposition = OPEN_ALWAYS;
    doTruncate = true;
    break;
  default:
    return false;
  }

  DWORD dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
  file_no = CreateFileA(name, dwDesiredAccess, dwShareMode, 0,
                        dwCreationDisposition, permission, 0);

  if (file_no == INVALID_HANDLE_VALUE)
    return false;

  if ((doTruncate && SetEndOfFile(file_no) == 0) ||
      (((openmode & ios_base::ate) != 0) &&
       (SetFilePointer(file_no, 0, NULL, FILE_END) == (DWORD)-1))) {
    CloseHandle(file_no);
    return false;
  }

  _M_is_open = true;
  _M_file_id = file_no;
  _M_should_close = _M_is_open;
  _M_openmode = openmode;
  _M_regular_file = bfmeGoDXF(_M_file_id);

  return _M_is_open;
}

bool _Filebuf_base::_M_close()
{
  if (!_M_is_open)
    return false;

  bool ok;

  if (!_M_should_close)
    ok = true;
  else {
    if (_M_file_id != INVALID_HANDLE_VALUE) {
      ok = (CloseHandle(_M_file_id) != 0);
    }
    else {
      ok = false;
    }
  }

  _M_is_open = _M_should_close = false;
  _M_openmode = 0;
  return ok;
}

ptrdiff_t _Filebuf_base::_M_read(char *buf, ptrdiff_t n)
{
  DWORD NumberOfBytesRead;
  ReadFile(_M_file_id, (LPVOID)buf, (DWORD)n,
           &NumberOfBytesRead, 0);

  if ((! (_M_openmode & ios_base::binary)) && NumberOfBytesRead) {
    // translate CR-LFs to LFs in the buffer
    char * to = buf, * last = buf + NumberOfBytesRead - 1;
    char * from;
    for (from = buf; from <= last && * from != _STLP_CTRLZ; ++ from ) {
      if (* from != _STLP_CR)
        * to ++ = * from;
      else { // found CR
        if (from < last) { // not at buffer end
          if (* (from + 1) != _STLP_LF)
            * to ++ = _STLP_CR;
        }
        else { // last char is CR, peek for LF
          char peek = ' ';
          DWORD NumberOfBytesPeeked;
          ReadFile(_M_file_id, (LPVOID)&peek,
                   1, &NumberOfBytesPeeked, 0);
          if (NumberOfBytesPeeked) {
            if (peek != _STLP_LF) {
              * to ++ = _STLP_CR;
              SetFilePointer(_M_file_id,(LONG)-1,0,FILE_CURRENT);
            }
            else
              SetFilePointer(_M_file_id,(LONG)-2,0,FILE_CURRENT);
          }
        }
      } // found CR
    } // for
    // seek back to TEXT end of file if hit CTRL-Z
    if (from <= last) // terminated due to CTRLZ
      SetFilePointer(_M_file_id,(LONG)((last+1) - from),0,FILE_CURRENT);
    NumberOfBytesRead = to - buf;
  }
  return (ptrdiff_t)NumberOfBytesRead;
}

static streamoff __file_size(_STLP_fd fd)
{
  LARGE_INTEGER li;
  li.LowPart = GetFileSize(fd, (DWORD *)&li.HighPart);
  if (li.LowPart == (DWORD)-1 && GetLastError() != 0)
    return streamoff(0);
  return li.QuadPart;
}

streamoff _Filebuf_base::_M_file_size()
{
  return __file_size(_M_file_id);
}

// STLport 4.5.3 Win32 file-position wrapper.
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

_STLP_END_NAMESPACE
