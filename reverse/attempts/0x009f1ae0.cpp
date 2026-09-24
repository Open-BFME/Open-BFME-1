// ?m009F1AE0@Q1Receiver0134FAAC@@QAEXXZ
// partial score=0.99 date=2026-09-24
// ?m009F1AE0@Q1Receiver0134FAAC@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Retail RVA 0x009F1AE0, 1470 bytes. Identity is address-derived: no caller,
// vtable slot or string names this body, so the method keeps its address.
//
// The receiver is the object g_theAssetRegistry (0x0134FAAC) points at, the
// same object as the matched Q1Receiver0134FAAC methods beside this file and
// the Gen_dtor_009eb9e0 constructor in
// W3DDevice/GameLogic/W3DRenderObjectSnapshotCtor.cpp: it holds the section
// at +0x60, seven 0x28-byte STLport deques from +0x78 and four 0x14-byte set
// wrappers from +0x190. Retail proves each piece here:
//   * every deque block is 0x80 bytes and operator[] advances 32 elements per
//     node, so the element is one pointer;
//   * each element has a vtable (slot +0x38 returns an int that is subtracted
//     from +0x20 and clamped at zero) and a flag word at +4 whose bits 16..23
//     name the deque the element belongs in (the push target is
//     m_deques78[queue]) and whose bit 25 is cleared on every visit. Retail
//     loads, masks and stores the queue number and re-reads it after writing
//     it, which is a volatile bit-field; the single-bit flags are plain (the
//     sibling 0x009F1510 tests bit 25 in the register it just stored);
//   * push_back's _M_push_back_aux_v is inlined, so the TU was built without
//     STLport exceptions (a try block keeps MSVC from inlining it);
//   * the +0x1CC wrapper's tree is cleared through an inline member that also
//     sets the flag at wrapper +0x10, addressed from the wrapper pointer.
// 0x009F1510 is pinned as Gen009F1510::handle (the pointer-tail thunk at
// 0x009EBA30 reaches it); retail passes this same receiver in ECX.

#include <deque>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <windows.h>

struct Rva001408C0Target;
typedef _STL::set<Rva001408C0Target *> Rva001408C0Set;

// The receiver's 0x14-byte set wrapper: tree, count, flag (the name the
// pinned 0x009EFD40 member already uses for it).
struct Q1ReceiverLocalSet
{
	Rva001408C0Set m_tree;
	unsigned int m_count;
	bool m_active;

	void reset()
	{
		m_tree.clear();
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

class Gen009F1510
{
public:
	void handle();
};

class Q1Receiver0134FAAC
{
public:
	void m009F1AE0();

private:
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
	unsigned char m_unmodelled_1e8[0x0C];
};

typedef char Q1Receiver009F1AE0SizeCheck[sizeof(Q1Receiver0134FAAC) == 0x1f4 ? 1 : -1];

void Q1Receiver0134FAAC::m009F1AE0()
{
	EnterCriticalSection(&m_lock60);
	for (;;)
	{
		for (int q = 0; q <= 3; ++q)
		{
			for (unsigned int i = 0; i < m_deques78[q].size(); ++i)
			{
				Q1QueueEntry009F1510 *entry = m_deques78[q][i];
				entry->m_bit25 = 0;
				if (q == 3)
				{
					m_field20 -= entry->slot38();
					if (m_field20 < 0)
						m_field20 = 0;
					entry->m_queue = 4;
					m_deques78[entry->m_queue].push_back(m_deques78[3][i]);
					m_deques78[3][i] = m_deques78[3][m_deques78[3].size() - 1];
					m_deques78[3].pop_back();
					--i;
				}
				else if (q == 0)
				{
					entry->m_queue = 7;
					m_deques78[0][i] = m_deques78[0][m_deques78[0].size() - 1];
					m_deques78[0].pop_back();
					--i;
				}
			}
		}
		int k;
		for (k = 0; k < 7; ++k)
		{
			if (!m_deques78[k].empty())
				break;
		}
		if (k == 7)
			break;
		LeaveCriticalSection(&m_lock60);
		reinterpret_cast<Gen009F1510 *>(this)->handle();
		Sleep(1);
		EnterCriticalSection(&m_lock60);
	}
	m_set1cc.reset();
	LeaveCriticalSection(&m_lock60);
}
