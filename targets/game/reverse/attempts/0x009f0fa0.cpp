// ?m009F0FA0@Q1Receiver0134FAAC@@QAEXPAVRva009EF0D0Element@@@Z
// partial score=0.4015 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?m009F0FA0@Q1Receiver0134FAAC@@QAEXPAVRva009EF0D0Element@@@Z
// Retail RVA 0x009F0FA0: 1198 bytes of code, ret 4, then a 7-entry switch
// table (row size 1228). Identity is address-derived. Receiver layout is the
// matched 0x009F1510 sibling's Q1Receiver0134FAAC (lock +0x60, seven entry
// deques +0x78, set wrappers +0x190..+0x1cc, flags +0x1EC..+0x1EE, cost +0x20).
// Body: demand-load an entry. Record its +8 key in set +0x1CC (and +0x190)
// unless +0x190 already has it or bit 26 is set, with an "[info] Demand load: "
// debug report for names that are not '#'/apt_/sfe_ (returns holding the lock
// when +0x1ED is clear, as retail does). Then wait out queues 1/5/8, remove the
// entry from its deque (swap with last, pop_back), set bit 25 and run the
// fall-through per-queue virtuals 5->6->0->1->2 (queue 2 gathers its keys into
// a local set and hands them to Queue_Keys_009EFBF0 under a lock guard). Last,
// queue it on deque 3.
// Callees needing pins before landing: _Deque_iterator<Rva009EF0D0Element*>::
// operator[] (0x009EF060) and deque<Rva009EF0D0Element*>::pop_back
// (0x009ED8A0), both byte-identical deque<int> instances.

#include <deque>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <windows.h>
#include <string.h>

struct Rva001408C0Target;
typedef _STL::set<Rva001408C0Target *> Rva001408C0Set;

struct Q1ReceiverLocalSet
{
	Rva001408C0Set m_set;
	int m_zero;
	bool m_one;

	Q1ReceiverLocalSet()
	{
		m_zero = 0;
		m_one = true;
	}
};

class BfmeList950B
{
public:
	BfmeList950B();
	Rva001408C0Set m_set;
	int m_zero;
	bool m_one;
};

class Rva009EF0D0Element
{
public:
	virtual const char *slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10(BfmeList950B *set);
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual int slot38();

	Rva001408C0Target *key() const { return m_key08; }

	volatile unsigned int m_bits00 : 16;
	volatile unsigned int m_queue : 8;
	unsigned int m_bit24 : 1;
	unsigned int m_bit25 : 1;
	unsigned int m_bit26 : 1;
	Rva001408C0Target *m_key08;
	Rva001408C0Target **m_keys0c;
};

typedef _STL::deque<Rva009EF0D0Element *> Q1Queue009F0FA0;

// Retail calls the iterator subscript out of line and reloads the deque's
// iterators after every call: the body is not visible to this TU.
template <>
Rva009EF0D0Element *&_STL::_Deque_iterator<Rva009EF0D0Element *,
	_STL::_Nonconst_traits<Rva009EF0D0Element *> >::operator[](difference_type n) const;

class BFMEIndexBufferDebugStream
{
public:
	virtual BFMEIndexBufferDebugStream *Put_Unsigned(unsigned value);
	virtual void Slot04(void);
	virtual void Slot08(void);
	virtual void Slot0C(void);
	virtual void Slot10(void);
	virtual void Slot14(void);
	virtual void Slot18(void);
	virtual void Slot1C(void);
	virtual void Slot20(void);
	virtual void Slot24(void);
	virtual void Slot28(void);
	virtual void Slot2C(void);
	virtual void Slot30(void);
	virtual void Slot34(void);
	virtual BFMEIndexBufferDebugStream *Put_String(const char *text);
	virtual void Slot3C(void);
	virtual void Slot40(void);
	virtual void Slot44(void);
	virtual void Slot48(void);
	virtual BFMEIndexBufferDebugStream *Finish(int report);
};

class BFMEIndexBufferDebugClass
{
public:
	virtual void Slot00(void); virtual void Slot04(void); virtual void Slot08(void); virtual void Slot0C(void);
	virtual void Slot10(void); virtual void Slot14(void); virtual void Slot18(void); virtual void Slot1C(void);
	virtual void Slot20(void); virtual void Slot24(void); virtual void Slot28(void); virtual void Slot2C(void);
	virtual void Slot30(void); virtual void Slot34(void); virtual void Slot38(void); virtual void Slot3C(void);
	virtual void Slot40(void); virtual void Slot44(void); virtual void Slot48(void); virtual void Slot4C(void);
	virtual void Slot50(void); virtual void Slot54(void); virtual void Slot58(void); virtual void Slot5C(void);
	virtual void Begin_Report(void);
	virtual void Slot64(void); virtual void Slot68(void);
	virtual BFMEIndexBufferDebugStream *Get_Stream(void *owner, void *context);
};

extern BFMEIndexBufferDebugClass *g_BFMEIndexBufferDebug;
bool _bfme_debugReportingEnabled();
void _bfme_debugRecordCallsite(int kind);

class AssetRegistry
{
public:
	void Queue_Keys_009EFBF0(bool known, const Rva001408C0Set &keys);
};

class Q1ReceiverLock009F0FA0
{
public:
	Q1ReceiverLock009F0FA0(CRITICAL_SECTION *lock) : m_lock(lock)
	{
		EnterCriticalSection(m_lock);
	}
	~Q1ReceiverLock009F0FA0()
	{
		LeaveCriticalSection(m_lock);
	}

private:
	CRITICAL_SECTION *m_lock;
};

class Q1Receiver0134FAAC
{
public:
	void m009F0FA0(Rva009EF0D0Element *entry);

protected:
	unsigned int m_thread;
	unsigned char m_unmodelled_004[0x1C];
	int m_field20;
	unsigned int m_field24;
	unsigned int m_field28;
	CRITICAL_SECTION m_lock2c;
	unsigned char m_unmodelled_044[0x1C];
	CRITICAL_SECTION m_lock60;
	Q1Queue009F0FA0 m_deques78[7];
	Q1ReceiverLocalSet m_set190;
	Q1ReceiverLocalSet m_set1a4;
	Q1ReceiverLocalSet m_set1b8;
	Q1ReceiverLocalSet m_set1cc;
	unsigned int m_field1e0;
	unsigned int m_field1e4;
	unsigned char m_unmodelled_1e8[4];
	bool m_flag1ec;
	bool m_flag1ed;
	bool m_flag1ee;
	unsigned char m_unmodelled_1ef[5];
};

typedef char Q1Receiver009F0FA0SizeCheck[sizeof(Q1Receiver0134FAAC) == 0x1f4 ? 1 : -1];

void Q1Receiver0134FAAC::m009F0FA0(Rva009EF0D0Element *entry)
{
	if (entry->m_key08 == 0 || entry->m_queue == 3)
		return;

	EnterCriticalSection(&m_lock60);
	if (m_set190.m_set.find(entry->key()) == m_set190.m_set.end() &&
		!entry->m_bit26)
	{
		m_set1cc.m_set.insert(entry->m_key08);
		if (!m_flag1ed)
			return;
		if (m_flag1ee)
		{
			const char *name = entry->slot00();
			if (name && name[0] != '#' && _strnicmp(name, "apt_", 4) &&
				_strnicmp(name, "sfe_", 4) && _bfme_debugReportingEnabled())
			{
				_bfme_debugRecordCallsite(1);
				g_BFMEIndexBufferDebug->Begin_Report();
				g_BFMEIndexBufferDebug->Get_Stream(0, 0)
					->Put_String("[info] Demand load: ")
					->Put_String(name)
					->Finish(2);
			}
		}
		m_set190.m_set.insert(entry->m_key08);
	}

	while ((entry->m_queue == 1 || entry->m_queue == 5) &&
		m_deques78[entry->m_queue].front() == entry && m_flag1ec)
	{
		LeaveCriticalSection(&m_lock60);
		Sleep(1);
		EnterCriticalSection(&m_lock60);
	}
	while (entry->m_queue == 8)
	{
		LeaveCriticalSection(&m_lock60);
		Sleep(1);
		EnterCriticalSection(&m_lock60);
	}

	int queue = entry->m_queue;
	if (queue != 7)
	{
		Q1Queue009F0FA0 &deque = m_deques78[queue];
		unsigned int i;
		for (i = 0; i < deque.size(); ++i)
		{
			if (deque[i] == entry)
				break;
		}
		if (i < deque.size())
		{
			Rva009EF0D0Element *&last = deque[deque.size() - 1];
			deque[i] = last;
			deque.pop_back();
		}
	}
	LeaveCriticalSection(&m_lock60);

	entry->m_bit25 = 1;
	if (queue == 7)
		entry->m_queue = 0;

	switch (entry->m_queue)
	{
	case 4:
		m_field20 += entry->slot38();
		goto loaded;
	case 5:
		entry->slot18();
		entry->m_queue = 6;
	case 6:
		entry->slot1C();
		entry->m_queue = 0;
	case 0:
		entry->slot04();
		entry->m_queue = 1;
	case 1:
		entry->slot08();
		entry->m_queue = 2;
		m_field20 += entry->slot38();
	case 2:
	{
		entry->slot0C();
		BfmeList950B set;
		entry->slot10(&set);
		if (entry->m_keys0c && entry->m_keys0c[0])
		{
			int k = 0;
			do
			{
				set.m_set.insert(entry->m_keys0c[k]);
			} while (entry->m_keys0c[++k]);
		}
		if (set.m_set.size() != 0)
		{
			Q1ReceiverLock009F0FA0 lock(&m_lock60);
			((AssetRegistry *)this)->Queue_Keys_009EFBF0(true, set.m_set);
		}
	}
	loaded:
		entry->m_queue = 3;
		break;
	}

	Q1ReceiverLock009F0FA0 lock(&m_lock60);
	Rva009EF0D0Element *queued = entry;
	m_deques78[3].push_back(queued);
}
