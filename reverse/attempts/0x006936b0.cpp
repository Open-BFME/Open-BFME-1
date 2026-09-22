// ??1Gen0002857EOwner@@QAE@XZ
// partial score=0.95 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// ??1Gen0002857EOwner@@QAE@XZ
// Destructor of the Gen0002857EOwner record cache, retail 0x006936B0 (324 B).
// Layout evidence: the matched constructor at 0x00694710 builds exactly the
// members this body tears down (hash map +0x00, three lists +0x14 sharing the
// list destructor 0x0002DFA6, trees +0x20 and +0x2C, thread +0x40 from
// CreateThread, stop byte +0x44, mutex +0x48), and the matched owner methods
// 0x00693B00/0x00693E20/0x00693FB0 use the same offsets. The hash map holds
// BfmeRecordBQ pointers (delete reaches ??1BfmeRecordBQ via ILT 0x0003DAD2;
// the erase at 0x00692D50 destroys an AsciiString key). The +0x2C tree's
// destructor 0x000775F0 erases nodes through an AsciiString destructor.
// The unwind map (FuncInfo 0x00E36BF8) shows a lock at [ebp-0x1C] whose
// out-of-line destructor is 0x006915E0: release when the byte flag is set.

#include <hash_map>
#include <list>
#include <set>

#include "ascii_string.h"

typedef void *HANDLE;
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	HANDLE handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(HANDLE handle);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(HANDLE handle);

enum
{
	WAIT_TIMEOUT = 0x102
};
const unsigned long INFINITE = 0xFFFFFFFF;

namespace rts
{
template <class T>
struct hash
{
	unsigned int operator()(T value) const;
};
}

class BfmeRecordBQ
{
public:
	~BfmeRecordBQ();
};

struct Rva00691ED0Key
{
	unsigned int m_primary;
	AsciiString m_name;
};

struct Rva00691ED0Less
{
	bool operator()(const Rva00691ED0Key &, const Rva00691ED0Key &) const;
};

// Scoped mutex hold; 0x006915E0 is its destructor.
class Rva006915E0MutexLock
{
public:
	Rva006915E0MutexLock(HANDLE mutex) : m_locked(false)
	{
		m_mutex = mutex;
		if (WaitForSingleObject(mutex, INFINITE) != WAIT_TIMEOUT)
			m_locked = true;
	}
	~Rva006915E0MutexLock()
	{
		if (m_locked)
		{
			ReleaseMutex(m_mutex);
			m_locked = false;
		}
	}

private:
	HANDLE m_mutex;
	bool m_locked;
};

typedef _STL::hash_map<AsciiString, BfmeRecordBQ *, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > RecordHash;

class Gen0002857EOwner
{
public:
	~Gen0002857EOwner();

private:
	RecordHash m_byName;
	_STL::list<BfmeRecordBQ *> m_buckets[3];
	_STL::set<Rva00691ED0Key, Rva00691ED0Less> m_order;
	_STL::set<AsciiString> m_set2c;
	unsigned int m_accountingTotal;
	unsigned int m_limit;
	HANDLE m_thread;
	bool m_stop;
	HANDLE m_mutex;
};

Gen0002857EOwner::~Gen0002857EOwner()
{
	Rva006915E0MutexLock lock(m_mutex);
	m_stop = true;
	if (m_thread != 0)
	{
		WaitForSingleObject(m_thread, INFINITE);
		CloseHandle(m_thread);
		m_thread = 0;
	}
	while (m_byName.size() != 0)
	{
		RecordHash::iterator it = m_byName.begin();
		delete it->second;
		m_byName.erase(it);
	}
}
