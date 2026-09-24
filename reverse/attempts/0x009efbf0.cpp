// ?Queue_Keys_009EFBF0@AssetRegistry@@QAEX_NABV?$set@PAURva001408C0Target@@U?$less@PAURva001408C0Target@@@_STL@@V?$allocator@PAURva001408C0Target@@@3@@_STL@@@Z
// partial score=0.99 date=2026-09-24
// ?Queue_Keys_009EFBF0@AssetRegistry@@QAEX_NABV?$set@PAURva001408C0Target@@U?$less@PAURva001408C0Target@@@_STL@@V?$allocator@PAURva001408C0Target@@@3@@_STL@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// A member of the registry g_theAssetRegistry (0x0134FAAC) points at, on the
// layout the landed constructor ??0Gen_dtor_009eb9e0@@QAE@XZ size-checks: the
// hash_map at +0x44, the seven deques at +0x78 (0x28 bytes each), the first
// set group at +0x190 and the two counters at +0x1E0/+0x1E4 that the matched
// Gen_009EBB60Target::bfmeForward (0x009EDE40) turns into a percentage. Both
// retail call sites (0x009F13C0, and 0x009F16E1 inside d_009f1510) hold the
// +0x60 lock and pass a bool and a local set group.
//
// For every key in the set, the entry the +0x44 map holds for it is queued
// when its state byte (bits 16-23 of +4) is 7: the state is cleared, bit 25
// is set, the entry goes on the deque that state byte selects (front or back
// by the bool, counted in +0x1E0 or +0x1E4) and the key is recorded in the
// +0x190 set. The entry's +4 word is shared with the worker thread
// (0x009EFA30 rewrites it under the same lock); retail re-reads it for every
// use and writes it as two whole-word stores, so the entry carries a
// volatile word view beside the bitfield view. The deque element is named for
// the push_back aux body it reaches, 0x009EF0D0 (push_front aux is
// 0x009EF140); both are byte-identical to deque<int>'s, per the ledger. The
// address token stays in the method name: nothing names this body beyond
// what it does.

#define _STLP_USE_STATIC_LIB 1

#include <deque>
#include <hash_map>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key> Rva001408C0Set;

struct Rva009F2140AssetSetGroup
{
	Rva001408C0Set m_tree;
	unsigned int m_count;
	bool m_active;
	unsigned char m_padding[3];
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

	union
	{
		volatile unsigned int m_word;
		struct
		{
			volatile unsigned int m_refCount : 16;
			volatile unsigned int m_state : 8;
			volatile unsigned int m_bits : 8;
		};
		struct
		{
			unsigned short m_refCountBytes;
			unsigned char m_stateByte;
			unsigned char m_bitsByte;
		};
	};
};

typedef _STL::hash_map<int, Rva009EF0D0Element *> AssetHash;
typedef _STL::deque<Rva009EF0D0Element *> AssetQueue;

class AssetRegistry
{
public:
	void Queue_Keys_009EFBF0(bool front, const Rva001408C0Set &keys);

private:
	unsigned char m_unmodelled_000[0x44];
	AssetHash m_map44;
	unsigned char m_unmodelled_058[0x20];
	AssetQueue m_deques78[7];
	Rva009F2140AssetSetGroup m_set190;
	unsigned char m_unmodelled_1a4[0x3c];
	unsigned int m_field1e0;
	unsigned int m_field1e4;
};

typedef char AssetRegistryQueueLayoutCheck[
	sizeof(AssetRegistry) == 0x1e8 ? 1 : -1];

void AssetRegistry::Queue_Keys_009EFBF0(bool front, const Rva001408C0Set &keys)
{
	for (Rva001408C0Set::const_iterator it = keys.begin(); it != keys.end(); ++it)
	{
		AssetHash::const_iterator found = m_map44.find((int)*it);
		if (found != m_map44.end())
		{
			Rva009EF0D0Element *asset = (*found).second;
			if (asset->m_state == 7)
			{
				unsigned int flags = asset->m_word & 0xff00ffff;
				asset->m_word = flags;
				asset->m_word = flags | 0x2000000;
				if (front)
				{
					m_deques78[asset->m_state].push_front(asset);
					++m_field1e0;
				}
				else
				{
					m_deques78[asset->m_state].push_back(asset);
					++m_field1e4;
				}
				m_set190.m_tree.insert(*it);
			}
		}
	}
}
