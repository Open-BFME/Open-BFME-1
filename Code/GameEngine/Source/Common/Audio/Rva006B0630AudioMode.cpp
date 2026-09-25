// cl: /O2 /DNDEBUG /MD /EHsc
// RVA 0x006B0630. Provider names, 12-byte entries, selected index +0x958,
// mutex +0x95C, and the room-type call are shared with Rva006B1E60ProviderState.
// Keep the opaque owner: those witnesses do not establish a complete class.
// The scoped guard mirrors WaitForSingleObject/ReleaseMutex including timeout.
#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *, unsigned long);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *);
class Rva006B0630MutexGuard {
public:
 explicit Rva006B0630MutexGuard(void *handle) {
  m_owned = false; m_handle = handle;
  if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102) m_owned = true;
 }
 ~Rva006B0630MutexGuard() { if (m_owned) ReleaseMutex(m_handle); }
 void *m_handle;
 bool m_owned;
};
struct Rva006B0630LODEntry {
 unsigned short m_field00;
 char m_gap02[2];
 bool m_field04;
 char m_gap05[3];
};
struct Rva006B0630LODView {
 char m_beforeEntries[0x170];
 Rva006B0630LODEntry m_entries[2];
 char m_beforeIndex[0x16CC - 0x180];
 int m_index;
};
class GameLODManager;
extern GameLODManager *TheGameLODManager;
struct Rva006B0630Provider { AsciiString m_name; char m_rest[8]; };
class Rva00695AB0Owner { public: void setRoomType(int); };
class Rva006B0630Owner {
public:
 void updateMode();
 void rva006B0410(unsigned char);
 char m_before628[0x628];
 unsigned short m_field628;
 char m_before654[0x654 - 0x62A];
 Rva006B0630Provider m_providers[64];
 char m_before958[4];
 int m_selectedProvider;
 void *m_mutex;
 char m_beforeB54[0xB54 - 0x960];
 int m_roomType;
 char m_beforeB60[8];
 int m_fieldB60;
};
void Rva006B0630Owner::updateMode()
{
 Rva006B0630MutexGuard guard(m_mutex);
 if (m_selectedProvider == -1) goto refresh;
 {
  AsciiString &name = m_providers[m_selectedProvider].m_name;
  bool enabled = true;
  if (name.compare("Creative Labs EAX 3 (TM)") == 0) goto keep;
  if (m_fieldB60 > 0 && m_fieldB60 <= 5) {
   Rva006B0630LODView *lod = (Rva006B0630LODView *)TheGameLODManager;
   if (lod && lod->m_index >= 0 && lod->m_index < 2)
    enabled = lod->m_entries[lod->m_index].m_field04;
  } else enabled = false;
  unsigned char surround = (name.compare("Dolby Surround") == 0);
  if (enabled != surround) {
refresh:
   rva006B0410(0);
  } else {
keep:
   ((Rva00695AB0Owner *)this)->setRoomType(m_roomType);
  }
 }
 Rva006B0630LODView *lod = (Rva006B0630LODView *)TheGameLODManager;
 if (lod && lod->m_index >= 0 && lod->m_index < 2) {
  m_field628 = lod->m_entries[lod->m_index].m_field00;
  if (m_field628 <= 2) return;
 }
 m_field628 = 2;
}
