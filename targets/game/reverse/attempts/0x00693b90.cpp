// ?rva00693B90@Rva00694710AudioWorker@@QAE?AVRva006910F0Handle@@ABVAsciiString@@H@Z
// partial score=0.9829 date=2026-11-02
// ?Rva00694230@Gen0002857EOwner@@QAEXPAVGen0002857E@@@Z
// cl: /O2 /Ob2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /Iinputs/vendor/stlport /Igame/Libraries/Source/WWVegas/WWLib /I.
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <stl/_alloc.h>
#include <functional>
#include "game/Libraries/Source/WWVegas/WWLib/ascii_string.h"
namespace _STL {
template <> struct less<AsciiString> {
 bool operator()(const AsciiString &left, const AsciiString &right) const { return left.compare(right) < 0; }
};
}
#include <set>
typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>, _STL::less<AsciiString>, _STL::allocator<AsciiString> > Rva000BFCC0Tree;
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
class ScopedMutex {
public:
 // ??0ScopedMutex@@QAE@XZ absent-from-retail
 ScopedMutex() : m_owned(0), m_enabled(0) {}
 // ??1ScopedMutex@@QAE@XZ
 ~ScopedMutex() { release(); }
 // ?acquire@ScopedMutex@@QAEKPAX@Z absent-from-retail
 unsigned long acquire(void *h) {
  m_owned = h;
  unsigned long status = WaitForSingleObject(h, 500);
  if (status != 0x102) m_enabled = 1;
  return status;
 }
 // ?release@ScopedMutex@@QAEXXZ absent-from-retail
 void release() { if(m_enabled) { ReleaseMutex(m_owned); m_enabled = 0; } }
 void *m_owned;
 char m_enabled;
};
typedef ScopedMutex Rva006915E0;
class Gen0002857E {
public:
 AsciiString m_name;
};
class Gen0002857EOwner {
public:
 void Rva00694230(Gen0002857E *value);
 void Rva00693FB0();
 void Rva00693B00(Gen0002857E *value);
 char m_pad0[0x2c];
 _STL::set<AsciiString> m_failed;
 unsigned int m_accountingTotal;
 unsigned int m_limit;
 void *m_thread;
 char m_stop;
 void *m_mutex;
};
// Boundary, ABI, and dependency evidence: targets/game/reverse/identity_evidence/00694230-statement-order.md
// ?Rva00694230@Gen0002857EOwner@@QAEXPAVGen0002857E@@@Z
//-------------------------------------------------------------------------------------------------
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
   reinterpret_cast<Rva000BFCC0Tree *>(&m_failed)->insert_unique(value->m_name);
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
   compressed = true;
   size = newFileSize;
   delete [] buffer;
   buffer = static_cast<char *>(decompressFileBuffer);
   AIL_WAV_info(buffer, &soundInfo);
  } else if (soundInfo.format == 1) {
   compressed = false;
   size = fileSize;
  } else {
   reinterpret_cast<Rva006BA120ResetFlags *>(value)->reset();
   m_failed.insert(value->m_name);
   mut.release();
   if (_bfme_debugReportingEnabled()) {
    _bfme_debugRecordCallsite(1);
    DebugGlobal00409E20->Begin_Report();
    ((DebugGlobal00409E20->Get_Stream(0,0) << "Unexpected compression type in '") << value->m_name << "'\n").finish(2);
   }
   // prevent leaks
   delete [] buffer;
   return;
  }
  reinterpret_cast<BfmeAudioYE *>(value)->bfmeSetYE(reinterpret_cast<int>(buffer), &soundInfo, size, compressed);
  m_accountingTotal += size;
  if (m_accountingTotal > m_limit) {
   // We need to free some samples, or we're not going to be able to play this sound.
   Rva00693FB0();
  }
  return;
 }
}

// Address-derived cache lookup at retail 0x00693B90 (525 bytes, ret 0xC):
// under the cache mutex (+0x48, waited on without timeout), find the named
// sample in the hash map at +0x00; a hit is promoted into the per-priority
// list (+0x14) for the clamped priority and handed out, a name already in the
// failed set (+0x2C) yields an empty handle, and a miss creates the 0x44-byte
// record, registers it in the map and the priority list and hands it out.
// Callers: Rva00694130 (0x00694130).  Callee identities are the matched rows
// named below; the hash-map, priority-list and record helpers are still
// address-named, so they are called through their defined ledger names.
extern "C" void __cdecl __identifier("??0Rva00691110Handle@@QAE@ABV0@@Z")();
extern "C" void __cdecl __identifier("??$_M_find@VAsciiString@@@?$hashtable@URva006931A0Value@@VAsciiString@@U?$hash@VAsciiString@@@rts@@URva006931A0ExtractKey@@U?$equal_to@VAsciiString@@@_STL@@V?$allocator@URva006931A0Value@@@7@@_STL@@ABEPAU?$_Hashtable_node@URva006931A0Value@@@1@ABVAsciiString@@@Z")();
extern "C" void __cdecl __identifier("??A?$hash_map@VAsciiString@@W4Rva00693020Mapped@@U?$hash@VAsciiString@@@rts@@U?$equal_to@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@W4Rva00693020Mapped@@@_STL@@@6@@_STL@@QAEAAW4Rva00693020Mapped@@ABVAsciiString@@@Z")();
extern "C" void __cdecl __identifier("?dup_006925f0@@YAXXZ")();

class Rva006910F0Handle
{
public:
	Rva006910F0Handle();
	Rva006910F0Handle(Gen0002857E *target);
	// ??0Rva006910F0Handle@@QAE@ABV0@@Z absent-from-retail
	// The copy constructor at 0x00691110 is ledgered as Rva00691110Handle.
	Rva006910F0Handle(const Rva006910F0Handle &other)
	{
		union { void (__cdecl *symbol)(); void (Rva006910F0Handle::*member)(const Rva006910F0Handle &); } c;
		c.symbol = &__identifier("??0Rva00691110Handle@@QAE@ABV0@@Z");
		(this->*c.member)(other);
	}
	~Rva006910F0Handle();

	Gen0002857E *m_target;
};

class Rva006BA130MaxField
{
public:
	void update(int value);
};

class AsciiStringBQ;

class BfmeRecordBQ
{
public:
	BfmeRecordBQ(int owner, const AsciiStringBQ &name);

	unsigned char m_bytes[0x44];
};

struct Rva00693B90Record
{
	unsigned char m_pad00[0x34];
	int m_count;					// 0x34
	unsigned char m_pad38[4];
	int m_priority;					// 0x3c
	unsigned char m_pad40;
	unsigned char m_pinned;				// 0x41
};

struct Rva00693B90Node
{
	Rva00693B90Node *m_next;
	Rva00693B90Node *m_prev;
	Gen0002857E *m_data;
};

struct Rva00693B90HashNode
{
	Rva00693B90HashNode *m_next;
	AsciiString m_key;
	Gen0002857E *m_value;
};

class Rva00693B90HashTable;

struct Rva00693B90HashIterator
{
	Rva00693B90HashNode *m_cur;
	Rva00693B90HashTable *m_ht;
};

class Rva00693B90HashTable
{
public:
	Rva00693B90HashIterator find(const AsciiString &name)
	{
		union { void (__cdecl *symbol)(); Rva00693B90HashNode *(Rva00693B90HashTable::*member)(const AsciiString &) const; } c;
		c.symbol = &__identifier("??$_M_find@VAsciiString@@@?$hashtable@URva006931A0Value@@VAsciiString@@U?$hash@VAsciiString@@@rts@@URva006931A0ExtractKey@@U?$equal_to@VAsciiString@@@_STL@@V?$allocator@URva006931A0Value@@@7@@_STL@@ABEPAU?$_Hashtable_node@URva006931A0Value@@@1@ABVAsciiString@@@Z");
		Rva00693B90HashIterator it;
		it.m_cur = (this->*c.member)(name);
		it.m_ht = this;
		return it;
	}

	Gen0002857E *&operator[](const AsciiString &name)
	{
		union { void (__cdecl *symbol)(); Gen0002857E *&(Rva00693B90HashTable::*member)(const AsciiString &); } c;
		c.symbol = &__identifier("??A?$hash_map@VAsciiString@@W4Rva00693020Mapped@@U?$hash@VAsciiString@@@rts@@U?$equal_to@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@W4Rva00693020Mapped@@@_STL@@@6@@_STL@@QAEAAW4Rva00693020Mapped@@ABVAsciiString@@@Z");
		return (this->*c.member)(name);
	}

	unsigned char m_rep[0x14];
};

class Rva00693B90List
{
public:
	void push_back(Gen0002857E *const &value)
	{
		union { void (__cdecl *symbol)(); void (Rva00693B90List::*member)(Gen0002857E *const &); } c;
		c.symbol = &__identifier("?dup_006925f0@@YAXXZ");
		(this->*c.member)(value);
	}

	Rva00693B90Node *m_node;
};

struct Rva00693B90StringData
{
	unsigned short m_refCount;
	unsigned short m_pad02;
	unsigned short m_length;			// 0x04
};

static __forceinline bool isEmptyName(const AsciiString &name)
{
	const Rva00693B90StringData *data = *(Rva00693B90StringData *const *)&name;
	return data == 0 || data->m_length == 0;
}

class Rva00693B90Mutex
{
public:
	Rva00693B90Mutex(void *h)
	{
		m_enabled = 0;
		m_owned = h;
		if (WaitForSingleObject(h, 0xffffffff) != 0x102)
			m_enabled = 1;
	}
	~Rva00693B90Mutex() { if (m_enabled) ReleaseMutex(m_owned); }

	void *m_owned;
	volatile char m_enabled;
};

class Rva00694710AudioWorker
{
public:
	Rva006910F0Handle rva00693B90(const AsciiString &name, int priority);

	Rva00693B90HashTable m_files;			// 0x00
	Rva00693B90List m_lists[3];			// 0x14
	unsigned char m_pad20[0x0c];
	_STL::set<AsciiString> m_failed;		// 0x2c
	unsigned int m_accountingTotal;
	unsigned int m_limit;
	void *m_thread;
	char m_stop;
	void *m_mutex;					// 0x48
};


static __forceinline Rva00693B90Node *findNode(Rva00693B90Node *head, Gen0002857E *file)
{
	Rva00693B90Node *n = head->m_next;
	while (n != head && n->m_data != file)
		n = n->m_next;
	return n;
}
static __forceinline Rva00693B90Node *findNode0(Rva00693B90Node *head, Gen0002857E *file)
{
	for (Rva00693B90Node *n = head->m_next; n != head; n = n->m_next)
		if (n->m_data == file)
			return n;
	return 0;
}
// ?rva00693B90@Rva00694710AudioWorker@@QAE?AVRva006910F0Handle@@ABVAsciiString@@H@Z
Rva006910F0Handle Rva00694710AudioWorker::rva00693B90(const AsciiString &name, int priority)
{
	int level;
	if (priority < 0)
		level = 0;
	else if (priority >= 3)
		level = 2;
	else
		level = priority;

	Rva00693B90Mutex mut(m_mutex);

	if (isEmptyName(name))
		return Rva006910F0Handle();

	Rva00693B90HashIterator it = m_files.find(name);
	if (it.m_cur != 0)
	{
		Gen0002857E *file = it.m_cur->m_value;
		Rva00693B90Record *record = (Rva00693B90Record *)file;
		if (record->m_count == 0)
			((Gen0002857EOwner *)this)->Rva00693B00(file);
		if (!record->m_pinned && record->m_priority < level)
		{
			Rva00693B90Node *head = m_lists[record->m_priority].m_node;
			bool searching = true;
			Rva00693B90Node *n = head->m_next;
			while (searching && n != head)
			{
				if (n->m_data == file)
				{
					Rva00693B90Node *next = n->m_next;
					Rva00693B90Node *prev = n->m_prev;
					prev->m_next = next;
					next->m_prev = prev;
					_STL::__node_alloc<true, 0>::deallocate(n, sizeof(Rva00693B90Node));

					Rva00693B90Node *pos = m_lists[level].m_node;
					Rva00693B90Node *node = (Rva00693B90Node *)_STL::__node_alloc<true, 0>::allocate(sizeof(Rva00693B90Node));
					Gen0002857E **data = &node->m_data;
					if (data != 0)
						*data = file;
					Rva00693B90Node *last = pos->m_prev;
					node->m_next = pos;
					node->m_prev = last;
					last->m_next = node;
					pos->m_prev = node;
					break;
				}
				n = n->m_next;
			}
		}
		((Rva006BA130MaxField *)file)->update(level);
		return Rva006910F0Handle(file);
	}

	if (m_failed.find(name) != m_failed.end())
		return Rva006910F0Handle();

	Gen0002857E *file;
	{
	BfmeRecordBQ *record = new BfmeRecordBQ((int)this, (const AsciiStringBQ &)name);
	file = (Gen0002857E *)record;
	{
	Rva006910F0Handle handle(file);
	m_files[name] = (Gen0002857E *)record;
	m_lists[level].push_back(file);
	((Rva006BA130MaxField *)record)->update(level);
	return handle;
	}
	}
}

