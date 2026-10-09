// ?Rva00694230@Gen0002857EOwner@@QAEXPAVGen0002857E@@@Z
// partial score=0.8456 date=2026-10-09
// cl: /O2 /Ob2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /Iinputs/vendor/stlport /Igame/Libraries/Source/WWVegas/WWLib /I.
// stlport
// ?Rva00694230@Gen0002857EOwner@@QAEXPAVGen0002857E@@@Z
#define _STLP_NO_EXCEPTIONS 1
#include <stl/_alloc.h>
#define private public
#include <set>
#undef private
#include "game/Libraries/Source/WWVegas/WWLib/ascii_string.h"
namespace _STL {
template <> inline __declspec(noinline) pair<set<AsciiString>::iterator, bool> set<AsciiString>::insert(const AsciiString &value)
{
 pair<_Rep_type::iterator, bool> result = _M_t.insert_unique(value);
 return pair<iterator, bool>(*reinterpret_cast<const iterator *>(&result.first), result.second);
}
}


extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long ms);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
struct BfmeBlobYE { unsigned long format; unsigned long fields[8]; };
extern "C" __declspec(dllimport) int __stdcall AIL_WAV_info(const void *data, BfmeBlobYE *info);
extern "C" __declspec(dllimport) int __stdcall AIL_decompress_ADPCM(const BfmeBlobYE *info, void **out, unsigned long *size);
class BfmeAudioYE { public: void bfmeSetYE(int data, const BfmeBlobYE *info, int size, char compressed); };
class Rva006BA120ResetFlags { public: void reset(); };
class File {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
 virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
 virtual void slot20(); virtual void slot24(); virtual void slot28();
 virtual int size(); virtual void slot30(); virtual char *readEntireAndClose();
};
class FileSystem { public: File *openFile(const char *, int); };
extern FileSystem *TheFileSystem;
class Debug {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
 virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
 virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
 virtual void slot30(); virtual void slot34(); virtual Debug &operator<<(const char *);
 virtual void slot3c(); virtual void slot40(); virtual void slot44(); virtual void slot48();
 virtual bool finish(int);
};
Debug &operator<<(Debug &, const StringBase<char> &);
class DebugView00409E20 {
public:
 virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
 virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
 virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
 virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3C();
 virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4C();
 virtual void Slot50(); virtual void Slot54(); virtual void Slot58(); virtual void Slot5C();
 virtual bool Begin_Report(); virtual void Slot64(); virtual void Slot68();
 virtual Debug &Get_Stream(const char *, int);
};
extern DebugView00409E20 *DebugGlobal00409E20;
bool _bfme_debugReportingEnabled();
void _bfme_debugRecordCallsite(int);
class Rva006915E0 {
public:
 Rva006915E0() : m_owned(0), m_enabled(0) {}
 ~Rva006915E0() { release(); }
 unsigned long acquire(void *h) {
  m_owned = h;
  unsigned long status = WaitForSingleObject(h, 500);
  if (status != 0x102) m_enabled = 1;
  return status;
 }
 void release() { if(m_enabled) { ReleaseMutex(m_owned); m_enabled = 0; } }
 void *m_owned;
 char m_enabled;
};
class Gen0002857E {
public:
 AsciiString m_name;
};
class Gen0002857EOwner {
public:
 void Rva00694230(Gen0002857E *value);
 void Rva00693FB0();
 char m_pad0[0x2c];
 _STL::set<AsciiString> m_failed;
 unsigned int m_accountingTotal;
 unsigned int m_limit;
 void *m_thread;
 char m_stop;
 void *m_mutex;
};
void Gen0002857EOwner::Rva00694230(Gen0002857E *value)
{
 File *file = TheFileSystem->openFile(value->m_name.str(), 0x41);
 int fileSize;
 char *buffer;
 bool failed;
 if (!file) failed = true;
 else { fileSize = file->size(); buffer = file->readEntireAndClose(); failed = false; }
 Rva006915E0 mut;
 while (!m_stop) {
  if (mut.acquire(m_mutex) == 0x102) continue;
  if (failed) {
   reinterpret_cast<Rva006BA120ResetFlags *>(value)->reset();
   m_failed._M_t.insert_unique(value->m_name);
   mut.release();
   if (_bfme_debugReportingEnabled()) {
    _bfme_debugRecordCallsite(1);
    DebugGlobal00409E20->Begin_Report();
    ((DebugGlobal00409E20->Get_Stream(0,0) << "Missing Audio File: '") << value->m_name << "'\n").finish(2);
   }
   return;
  }
  BfmeBlobYE soundInfo;
  AIL_WAV_info(buffer, &soundInfo);
  bool compressed;
  int size;
  if (soundInfo.format == 0x11) {
   void *decompressFileBuffer;
   unsigned long newFileSize;
   AIL_decompress_ADPCM(&soundInfo, &decompressFileBuffer, &newFileSize);
   size = newFileSize;
   compressed = true;
   delete [] buffer;
   buffer = static_cast<char *>(decompressFileBuffer);
   AIL_WAV_info(buffer, &soundInfo);
  } else if (soundInfo.format == 1) {
   size = fileSize;
   compressed = false;
  } else {
   reinterpret_cast<Rva006BA120ResetFlags *>(value)->reset();
   m_failed.insert(value->m_name);
   mut.release();
   if (_bfme_debugReportingEnabled()) {
    _bfme_debugRecordCallsite(1);
    DebugGlobal00409E20->Begin_Report();
    ((DebugGlobal00409E20->Get_Stream(0,0) << "Unexpected compression type in '") << value->m_name << "'\n").finish(2);
   }
   delete [] buffer;
   return;
  }
  reinterpret_cast<BfmeAudioYE *>(value)->bfmeSetYE(reinterpret_cast<int>(buffer), &soundInfo, size, compressed);
  m_accountingTotal += size;
  if (m_accountingTotal > m_limit) Rva00693FB0();
  return;
 }
}
