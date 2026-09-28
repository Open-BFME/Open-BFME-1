// ?refresh@Q1Receiver0134FAAC@@QAEXXZ
// partial score=0.991 date=2026-09-28
// ?refresh@Q1Receiver0134FAAC@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Retail RVA 0x009EFF50, 3186 bytes (ret at +0xC71). Identity: the address pin
// plus five matched callers (m009F0BD0, m009F0CC0, m009F19E0, m009F1A60 and
// Gen009F1510::handle) call it as refresh on the g_theAssetRegistry receiver.
// Layout from the matched siblings: lock +0x60, hash_map<int,Element*> +0x44,
// seven deque<Element*> from +0x78, four 0x14-byte set wrappers from +0x190.
//
// Body: under the +0x60 lock, normalise the +0x190/+0x1A4 wrappers through
// m009EFD40; copy +0x190 (0x009EE8E0) and add +0x1B8 into a local key set;
// sweep deques 0..6 marking bit 25 and moving entries whose key membership
// disagrees with (q < 4): queue 3 entries (bit 26 clear) go into a multimap
// keyed by the entry's +0x10 word, queue 4 entries go back to queue 3 (adding
// their slot-0x38 cost to +0x20), queue 0 entries become queue 7. Then evict
// multimap entries to queue 4 while +0x20 >= +0x24, park the rest in queue 3,
// and twice build a key set (pass 0: +0x1A4 then 0x009EC770 with +0x190 plus
// +0x1B8; pass 1: +0x190 minus +0x1A4) whose queue-7 entries return to queue 0,
// recording the deque 0..2 totals at +0x1E0 / +0x1E4.
//
// Codegen evidence: the q==3 test is one conjunction (a nested bit-26 test
// makes MSVC spend its inline budget on queue 3 instead of queue 4, where
// retail inlines _M_advance); the two size sums are separate expressions
// (retail hoists only their node terms); pass 0 adds +0x1B8 through the
// range insert, which MSVC inlines there (cached end, insert_unique(value)
// per key) while the earlier local copy keeps the out-of-line 0x0003AFD0.

#include <deque>
#include <hash_map>
#include <map>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <windows.h>

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key> Rva001408C0Set;

struct Gen_t_009ee8e0_k4
{
	int a[1];
	Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4(const Gen_t_009ee8e0_k4 &);
	~Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4 &operator=(const Gen_t_009ee8e0_k4 &);
};

bool operator<(const Gen_t_009ee8e0_k4 &, const Gen_t_009ee8e0_k4 &);
typedef _STL::set<Gen_t_009ee8e0_k4> Q1ReceiverSet;

struct Q1ReceiverTreeStorage
{
	Q1ReceiverTreeStorage(const Q1ReceiverSet &source);
	~Q1ReceiverTreeStorage()
	{
		get().~Rva001408C0Set();
	}
	Rva001408C0Set &get() { return *(Rva001408C0Set *)m_storage; }
	int m_storage[sizeof(Rva001408C0Set) / sizeof(int)];
};

struct Q1ReceiverLocalSet
{
	Q1ReceiverTreeStorage m_set;
	int m_zero;
	bool m_one;
};

class BfmeThingBVA
{
public:
	BfmeThingBVA()
	{
		m_value = 0;
		m_active = true;
	}

	BfmeThingBVA &operator=(BfmeThingBVA &other)
	{
		if (this != &other)
		{
			bfmeStepBVA(&other);
			m_active = true;
			m_value = other.m_value;
		}
		return *this;
	}

	void bfmeStepBVA(BfmeThingBVA *other);

	Rva001408C0Set m_tree;
	unsigned int m_value;
	bool m_active;
};

class Rva009EC770Set
{
public:
	Rva009EC770Set &rva009EC770(const Rva009EC770Set &other);
};

class Rva009EC5B0Set
{
public:
	Rva009EC5B0Set &subtract(const Rva009EC5B0Set &other);
};

class Rva009EF0D0Element
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
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

	union
	{
		volatile unsigned int m_word;
		struct
		{
			volatile unsigned int m_bits00 : 16;
			volatile unsigned int m_queue : 8;
			unsigned int m_bit24 : 1;
			unsigned int m_bit25 : 1;
			unsigned int m_bit26 : 1;
		};
	};
	int m_key08;
	int m_field0c;
	unsigned int m_field10;
};

struct Rva009EDBE0Value
{
	Rva009EF0D0Element *m_entry;
};

typedef _STL::multimap<unsigned int, Rva009EDBE0Value> Q1ReceiverPending;
typedef _STL::pair<const unsigned int, Rva009EDBE0Value> Q1ReceiverPendingPair;
typedef _STL::hash_map<int, Rva009EF0D0Element *> Q1ReceiverAssetHash;
typedef _STL::deque<Rva009EF0D0Element *> Q1ReceiverQueue;

class Q1ReceiverLock
{
public:
	explicit Q1ReceiverLock(CRITICAL_SECTION *lock) : m_lock(lock)
	{
		EnterCriticalSection(m_lock);
	}
	~Q1ReceiverLock()
	{
		LeaveCriticalSection(m_lock);
	}

	CRITICAL_SECTION *m_lock;
};

class Q1Receiver0134FAAC
{
public:
	void refresh();
	void m009EFD40(Q1ReceiverLocalSet *set);

private:
	unsigned int m_thread;
	unsigned char m_unmodelled_004[0x1C];
	int m_field20;
	int m_field24;
	unsigned int m_field28;
	CRITICAL_SECTION m_lock2c;
	Q1ReceiverAssetHash m_map44;
	unsigned char m_unmodelled_058[8];
	CRITICAL_SECTION m_lock60;
	Q1ReceiverQueue m_deques78[7];
	BfmeThingBVA m_set190;
	BfmeThingBVA m_set1a4;
	BfmeThingBVA m_set1b8;
	BfmeThingBVA m_set1cc;
	unsigned int m_field1e0;
	unsigned int m_field1e4;
	unsigned char m_unmodelled_1e8[0x0C];
};

typedef char Q1ReceiverRefreshSizeCheck[sizeof(Q1Receiver0134FAAC) == 0x1f4 ? 1 : -1];

void Q1Receiver0134FAAC::refresh()
{
	Q1ReceiverLock lock(&m_lock60);
	m009EFD40((Q1ReceiverLocalSet *)&m_set190);
	m009EFD40((Q1ReceiverLocalSet *)&m_set1a4);

	Q1ReceiverPending pending;
	Q1ReceiverLocalSet known = { *(const Q1ReceiverSet *)&m_set190, 0, true };
	known.m_set.get().insert(m_set1b8.m_tree.begin(), m_set1b8.m_tree.end());
	known.m_one = true;

	for (int q = 0; q < 7; ++q)
	{
		for (unsigned int i = 0; i < m_deques78[q].size(); ++i)
		{
			Rva009EF0D0Element *entry = m_deques78[q][i];
			if ((known.m_set.get().find((Rva001408C0Key)entry->m_key08) !=
					known.m_set.get().end()) == (q < 4))
				continue;
			entry->m_bit25 = q > 3;
			if (q == 3 && !entry->m_bit26)
			{
				Q1ReceiverPendingPair value(entry->m_field10, Rva009EDBE0Value());
				const_cast<Rva009EDBE0Value &>(value.second).m_entry = entry;
				pending.insert(value);
				m_deques78[3][i] = m_deques78[3][m_deques78[3].size() - 1];
				m_deques78[3].pop_back();
				--i;
			}
			else if (q == 4)
			{
				entry->m_queue = 3;
				m_field20 += entry->slot38();
				m_deques78[entry->m_queue].push_back(m_deques78[4][i]);
				m_deques78[4][i] = m_deques78[4][m_deques78[4].size() - 1];
				m_deques78[4].pop_back();
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

	while (m_field20 >= m_field24 && pending.size() != 0)
	{
		Rva009EF0D0Element *entry = pending.begin()->second.m_entry;
		pending.erase(pending.begin());
		entry->m_queue = 4;
		m_field20 -= entry->slot38();
		m_deques78[entry->m_queue].push_back(entry);
		if (m_field20 < 0)
			m_field20 = 0;
	}

	for (Q1ReceiverPending::iterator it = pending.begin(); it != pending.end(); ++it)
		m_deques78[3].push_back(it->second.m_entry);

	for (int pass = 0; pass < 2; ++pass)
	{
		BfmeThingBVA keys;
		if (pass == 0)
		{
			keys = m_set1a4;
			((Rva009EC770Set *)&keys)->rva009EC770(*(Rva009EC770Set *)&m_set190);
			keys.m_tree.insert(m_set1b8.m_tree.begin(), m_set1b8.m_tree.end());
			keys.m_active = true;
		}
		else
		{
			keys = m_set190;
			((Rva009EC5B0Set *)&keys)->subtract(*(Rva009EC5B0Set *)&m_set1a4);
		}

		for (Rva001408C0Set::iterator it = keys.m_tree.begin(); it != keys.m_tree.end(); ++it)
		{
			Q1ReceiverAssetHash::iterator found = m_map44.find((int)*it);
			if (found != m_map44.end())
			{
				Rva009EF0D0Element *asset = (*found).second;
				if (asset->m_queue == 7)
				{
					unsigned int flags = asset->m_word & 0xff00ffff;
					asset->m_word = flags;
					asset->m_word = flags | 0x2000000;
					m_deques78[asset->m_queue].push_back(asset);
				}
			}
		}

		if (pass == 0)
			m_field1e0 = m_deques78[0].size() + m_deques78[1].size() +
				m_deques78[2].size();
		else
			m_field1e4 = m_deques78[0].size() + m_deques78[1].size() +
				m_deques78[2].size() - m_field1e0;
	}
}
