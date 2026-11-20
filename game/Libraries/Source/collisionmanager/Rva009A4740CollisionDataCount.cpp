// ?rva009A4740@Rva009A45A0CollisionData@@QAEXXZ
// cl: /O2 /G6 /MD /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /DBFME_STLP_NODE_ALLOC=1
// stlport
// BFME1 retail 0x009A4740 (750 B, thiscall, EH); ported from Open-BFME-2 0x0075A1A0 (byte-identical).
// Walks both collision bucket tables and counts each node's two sub-object pointers
// in a local map<Rva009A2FE0Sub *, unsigned>. The unsigned maximum is scanned
// (result unused), and the map is cleared between tables.
// Codegen: no /arch:SSE; /EHs retains the retail destructor shape; the retail
// tree insert layout define reproduces the map helpers at 0x009A34A0,
// 0x009A3520, 0x009A4010, 0x009A4130, 0x009A41E0, 0x009A4350,
// 0x009A46A0 and 0x009A46C0. Retail has one identity per body, without ICF.
// Identity evidence: targets/game/reverse/identity_evidence/009a4740-collision-count-map-family.md
// The sub-object type stays address-derived because its original name is unproven.

struct Rva009A2FE0Node;

struct Rva009A2FE0Sub
{
	unsigned char m_pad0[4];
	unsigned m_bfme04;
	unsigned char m_pad8[8];
	unsigned m_bfme10;
};

struct Rva009A2FE0Node
{
	Rva009A2FE0Sub *m_bfme00;
	Rva009A2FE0Sub *m_bfme04;
	unsigned char m_pad8[8];
	unsigned m_bfme10;
	unsigned char m_pad14[0x18];
	Rva009A2FE0Node **m_backSlot;
	Rva009A2FE0Node *m_next;
};

class Rva009A45A0CollisionData
{
public:
	void bfmeOneCGD();
	void bfmeTwoCGD();
	void bfmeGoCGD();
	void rva009A4740();
	Rva009A2FE0Node *nextNode();
	Rva009A2FE0Node *nextNode2();
	void *m_bfmeFirst;
	unsigned char m_bfmeGap[0x18 - 4];
	Rva009A2FE0Node *m_buckets2[0x2b7b];
	Rva009A2FE0Node *m_active2;
	int m_index2;
	Rva009A2FE0Node *m_cur2;
	Rva009A2FE0Node *m_buckets[0x493];
	Rva009A2FE0Node *m_active;
	int m_index;
	Rva009A2FE0Node *m_cur;
	unsigned char m_bfmeGap1[0xc06d - 0xc068];
	bool m_bfmeBusy;
};



// The BFME2 twin is 0x0075A1A0; WorldBuilder's 0x018062E0 adds
// "collisionmanager_stat" / "Contacts:" / "max on obj " debug output.
// BFME1 walks the tables through +0xC060/+0xC064 and +0xAE08/+0xAE0C,
// counts each node's pointers at +0 and +4, and destroys the map at exit.

#include <map>

typedef _STL::map<Rva009A2FE0Sub *, unsigned int> Rva0075A1A0Counts;

inline Rva009A2FE0Node *Rva009A45A0CollisionData::nextNode()
{
	while (m_cur == 0)
	{
		int i = m_index + 1;

		if (i == 0x493)
			return 0;
		m_index = i;
		m_cur = m_buckets[i];
	}
	Rva009A2FE0Node *n = m_cur;
	m_cur = m_cur->m_next;
	return n;
}

// ?Rva009A45A0CollisionData::nextNode2 absent-from-retail (inlined into rva009A4740; no standalone retail body)
inline Rva009A2FE0Node *Rva009A45A0CollisionData::nextNode2()
{
	while (m_cur2 == 0)
	{
		int i = m_index2 + 1;

		if (i == 0x2b7b)
			return 0;
		m_index2 = i;
		m_cur2 = m_buckets2[i];
	}
	Rva009A2FE0Node *n = m_cur2;
	m_cur2 = m_cur2->m_next;
	return n;
}

static inline void rva009A4740Count(Rva0075A1A0Counts &counts, Rva009A2FE0Sub *const &key)
{
	Rva0075A1A0Counts::iterator it = counts.find(key);
	if (it == counts.end())
		counts[key] = 1;
	else
		++(*it).second;
}

static inline unsigned int rva009A4740Max(Rva0075A1A0Counts &counts)
{
	unsigned int most = 0;
	for (Rva0075A1A0Counts::iterator it = counts.begin(); it != counts.end(); ++it)
		if ((*it).second > most)
			most = (*it).second;
	return most;
}

void Rva009A45A0CollisionData::rva009A4740()
{
	Rva0075A1A0Counts counts;
	Rva009A2FE0Node *n;

	m_index = 0;
	m_cur = m_buckets[0];
	while ((n = nextNode()) != 0)
	{
		rva009A4740Count(counts, n->m_bfme00);
		rva009A4740Count(counts, n->m_bfme04);
	}
	{
		unsigned int most = 0;
		for (Rva0075A1A0Counts::iterator it = counts.begin(); it != counts.end(); ++it)
			if ((*it).second > most)
				most = (*it).second;
	}
	counts.clear();

	m_index2 = 0;
	m_cur2 = m_buckets2[0];
	while ((n = nextNode2()) != 0)
	{
		rva009A4740Count(counts, n->m_bfme00);
		rva009A4740Count(counts, n->m_bfme04);
	}
	rva009A4740Max(counts);
}
