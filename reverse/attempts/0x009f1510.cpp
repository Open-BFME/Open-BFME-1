// ?handle@Gen009F1510@@QAEXXZ
// partial score=0.99 date=2026-09-24
// ?handle@Gen009F1510@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Retail RVA 0x009F1510, 1199 bytes of code (its seven-entry switch table
// follows at 0x009F19C0). Identity is address-derived. The name is the pin the
// matched pointer-tail thunk 0x009EBA30 (IndirectMemberTailThunks.cpp) already
// calls through W3DRenderObjectSnapshot's +8 pointer; the matched 0x009F1AE0
// sweep and the unmatched AssetRegistry destructor 0x009F23C0 also call it
// with the receiver in ECX. Gen009F1510 is that pinned view of the
// Q1Receiver0134FAAC object g_theAssetRegistry (0x0134FAAC) points at, so it
// derives from the receiver layout and calls the receiver's own members.
//
// The body is the worker pass over the receiver's seven entry deques at
// +0x78 (see Q1Receiver0134FAAC_m009F1AE0.cpp for the element proof). For
// every deque but 3 (and 1 and 5 while the byte at +0x1EC is set) it pops
// entries under the +0x60 section, stops early on deques 0 and 4 while the
// next deque holds 100 or more, marks each entry queue 8, runs the entry's
// per-queue virtual outside the lock, then re-files it: queue 6 goes to queue
// 0 only when flag bit 25 is set, the rest go to queue q+1, and a queue-2
// entry with neither bit 25 nor bit 26 goes to 4 and gives back its slot +0x38
// cost at +0x20. Queue 2 also hands the entry's +8 key and a local 0x14-byte
// set wrapper to 0x009EFBF0, and requests refresh (0x009EFF50) once deques
// 0..2 drain. Last, the summed size of deques 0..2 against +0x1E4 picks the
// worker thread's (+0) priority.
//
// Codegen evidence: retail re-reads the queue number after every write (a
// volatile bit-field) but tests bit 25 in the register it just stored (a plain
// one); push_back's aux is inlined at one site and called at 0x009EF0D0 at the
// other, which this TU reproduces with STLport exceptions off.

#include <deque>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <windows.h>

#ifndef THREAD_PRIORITY_BELOW_NORMAL
#define THREAD_PRIORITY_BELOW_NORMAL (-1)
#endif

struct Rva001408C0Target;
typedef _STL::set<Rva001408C0Target *> Rva001408C0Set;

// The receiver's 0x14-byte set wrapper: tree, count, flag (the name the
// pinned 0x009EFD40 member already uses for it). Retail builds the local one
// here as header node, count 0, flag 1.
struct Q1ReceiverLocalSet
{
	Rva001408C0Set m_tree;
	unsigned int m_count;
	bool m_active;

	Q1ReceiverLocalSet()
	{
		m_count = 0;
		m_active = true;
	}
};

class Q1QueueEntry009F1510
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10(Q1ReceiverLocalSet *set);
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

	volatile unsigned int m_bits00 : 16;
	volatile unsigned int m_queue : 8;
	unsigned int m_bit24 : 1;
	unsigned int m_bit25 : 1;
	unsigned int m_bit26 : 1;
	int m_key08;
};

typedef _STL::deque<Q1QueueEntry009F1510 *> Q1Queue009F1510;

class Q1Receiver0134FAAC
{
public:
	void refresh();
	void m009EFBF0(bool known, Q1ReceiverLocalSet *set);

protected:
	unsigned int m_thread;
	unsigned char m_unmodelled_004[0x1C];
	int m_field20;
	unsigned int m_field24;
	unsigned int m_field28;
	CRITICAL_SECTION m_lock2c;
	unsigned char m_unmodelled_044[0x1C];
	CRITICAL_SECTION m_lock60;
	Q1Queue009F1510 m_deques78[7];
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

class Gen009F1510 : public Q1Receiver0134FAAC
{
public:
	void handle();
};

typedef char Gen009F1510SizeCheck[sizeof(Gen009F1510) == 0x1f4 ? 1 : -1];

void Gen009F1510::handle()
{
	bool changed = false;
	for (int q = 0; q < 7; ++q)
	{
		if (q == 3)
			continue;
		if (m_flag1ec && (q == 1 || q == 5))
			continue;
		while (!m_deques78[q].empty())
		{
			EnterCriticalSection(&m_lock60);
			if ((q == 0 || q == 4) && m_deques78[q + 1].size() >= 100)
			{
				LeaveCriticalSection(&m_lock60);
				break;
			}
			Q1QueueEntry009F1510 *entry = m_deques78[q].front();
			m_deques78[q].pop_front();
			entry->m_queue = 8;
			LeaveCriticalSection(&m_lock60);
			switch (q)
			{
			case 0:
				entry->slot04();
				break;
			case 2:
			{
				entry->slot0C();
				m_field20 += entry->slot38();
				Q1ReceiverLocalSet set;
				entry->slot10(&set);
				if (set.m_tree.size() != 0)
				{
					m009EFBF0(m_set1a4.m_tree.find((Rva001408C0Target *)entry->m_key08) !=
						m_set1a4.m_tree.end(), &set);
				}
				break;
			}
			case 4:
				entry->slot14();
				break;
			case 6:
				entry->slot1C();
				break;
			case 1:
				entry->slot08();
				break;
			case 5:
				entry->slot18();
				break;
			}
			EnterCriticalSection(&m_lock60);
			if (q == 6)
			{
				entry->m_queue = 7;
				if (entry->m_bit25)
				{
					entry->m_queue = 0;
					m_deques78[entry->m_queue].push_back(entry);
				}
			}
			else
			{
				entry->m_queue = q + 1;
				if (q == 2 && !entry->m_bit25 && !entry->m_bit26)
				{
					entry->m_queue = 4;
					m_field20 -= entry->slot38();
					if (m_field20 < 0)
						m_field20 = 0;
				}
				m_deques78[entry->m_queue].push_back(entry);
				if (q == 2 && m_deques78[0].empty() && m_deques78[1].empty() &&
					m_deques78[2].empty())
				{
					changed = true;
				}
			}
			LeaveCriticalSection(&m_lock60);
		}
	}
	if (changed)
		refresh();
	EnterCriticalSection(&m_lock60);
	unsigned int size0 = m_deques78[0].size();
	unsigned int size1 = m_deques78[1].size();
	unsigned int total = size0 + size1 + m_deques78[2].size();
	LeaveCriticalSection(&m_lock60);
	if (total <= m_field1e4)
		SetThreadPriority(reinterpret_cast<HANDLE>(m_thread), THREAD_PRIORITY_BELOW_NORMAL);
	else
		SetThreadPriority(reinterpret_cast<HANDLE>(m_thread), THREAD_PRIORITY_NORMAL);
}
