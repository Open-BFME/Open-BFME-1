// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME5: the dynamic-name builder at retail 0x0036E370, 88 bytes.
// The caller supplies the string to fill; the name is taken from the last
// node of a chain, and the id is read before the walk so it survives it.

#include <vector>
#include "ascii_string.h"

class StringBaseNarrowAA
{
public:
	void __cdecl format(class AsciiStringAA text, ...);

protected:
	StringBaseNarrowAA(void)
	{
		m_bfmeNarrowAA = 0;
	}

	StringBaseNarrowAA(const char *text);

	StringBaseNarrowAA(const StringBaseNarrowAA &other);

	~StringBaseNarrowAA(void);

	char *m_bfmeNarrowAA;
};

class AsciiStringAA : public StringBaseNarrowAA
{
public:
	AsciiStringAA(void)
	{
	}

	AsciiStringAA(const char *text) : StringBaseNarrowAA(text)
	{
	}

	AsciiStringAA(const AsciiStringAA &other) : StringBaseNarrowAA(other)
	{
	}

	~AsciiStringAA(void)
	{
	}

	const char *bfmeTextAA(void) const
	{
		return (m_bfmeNarrowAA != 0) ? m_bfmeNarrowAA + 8 : "";
	}
};

// The chain walk is retail's ?getFinalOverride@Overridable@@QBEPBV1@XZ at
// 0x00087A80 (reached through ILT 0x000022BB), so the reference carries that
// spelling.  No real header declares Overridable, and only the declaration is
// needed to name the call.
class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

class BfmeNodeAA
{
public:
	char m_bfmePadAAA[4];
	BfmeNodeAA *m_bfmeNextAA;
	char m_bfmePadBAA[24];
	AsciiStringAA m_bfmeNameAA;
};

class BfmePartAA
{
public:
	char m_bfmePadCAA[4];
	BfmeNodeAA *m_bfmeNodeAA;
	char m_bfmePadDAA[108];
	int m_bfmeIdAA;
};

struct Gen_t_00372510_m4pod
{
	int a[1];
};

struct Rva0018EDB0Node
{
	void *m_owner;
	Rva0018EDB0Node *m_next;
};

void rva0018EDB0Insert(Rva0018EDB0Node *node);

class Rva0018F030PairSlot
{
public:
	void set(int first, int second);
};

extern void j_000103b6();

class Matrix3D;

class Rva0018F660
{
public:
	void transformPoints(const Matrix3D *matrix);
};

struct Rva00375060Entry
{
	Rva0018EDB0Node m_node;
	AsciiStringAA m_name;
};

class BfmeOwnerAA
{
public:
	void bfmeMakeNameAA(AsciiStringAA &out, int index);
	void rva00375060(Rva00375060Entry *entry);

	char m_bfmePadEAA[8];
	BfmePartAA *m_bfmePartAA;
	char m_rva00375060Gap[0xdc];
	_STL::vector<Gen_t_00372510_m4pod> m_rva00375060Vector;
};

void BfmeOwnerAA::bfmeMakeNameAA(AsciiStringAA &out, int index)
{
	BfmePartAA *part = m_bfmePartAA;

	if (part == 0)
		return;

	int id = part->m_bfmeIdAA;

	BfmeNodeAA *node = part->m_bfmeNodeAA;

	if (node != 0 && node->m_bfmeNextAA != 0)
		node = (BfmeNodeAA *)((const Overridable *)node->m_bfmeNextAA)
			->getFinalOverride();

	out.format(AsciiStringAA("Dynamic_%s_of_id_%d_at_index_%d"),
			node->m_bfmeNameAA.bfmeTextAA(), id, index);
}

void BfmeOwnerAA::rva00375060(Rva00375060Entry *entry)
{
	if (entry == 0)
		return;

	((Rva0018F030PairSlot *)entry)->set((int)j_000103b6, (int)this);
	((Rva0018F660 *)entry)->transformPoints(
		(const Matrix3D *)((const char *)m_bfmePartAA + 8));
	m_rva00375060Vector.push_back(
		*(const Gen_t_00372510_m4pod *)&entry);

	AsciiStringAA name;
	bfmeMakeNameAA(name, m_rva00375060Vector.size());
	const StringBase<char> *sourceName = (const StringBase<char> *)&name;
	StringBase<char> *targetName = (StringBase<char> *)&entry->m_name;
	targetName->set(*sourceName);
	rva0018EDB0Insert(&entry->m_node);
}
