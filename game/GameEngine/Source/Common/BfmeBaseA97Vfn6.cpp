// cl: /DNDEBUG /MD /EHsc
// stlport
// Retail 0x002DA9D0 (256 B): vftable 0x010CE8FC slot 6 through ILT 0x000060AA.

#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>

class PartitionManager;
extern PartitionManager *ThePartitionManager;

// BfmeWideResult descriptor: vector start/end/capacity, cursor at +0x0c and
// reference count at +0x10; entries are eight bytes.
struct BfmeIterEntry
{
	void *object;
	unsigned int unknown04;
};
struct BfmeObjectIterator
{
	std::vector<BfmeIterEntry> entries;
	BfmeIterEntry *current;
	int references;
};
struct BfmeWideResult
{
	BfmeObjectIterator *m_value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &);
	~BfmeWideResult()
	{
		if (--m_value->references == 0)
			delete m_value;
	}
	void *next()
	{
		if (m_value->current == m_value->entries.end())
			return 0;
		return (m_value->current++)->object;
	}
};
class BfmeWideForwardA
{
public:
	BfmeWideResult bfmeForwardWideA(int, int, int, int);
};

class BfmeBaseA97
{
public:
	virtual void v0();
	virtual bool vfn1(void *a, void *b);
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void vfn6(void *a, void *b_sub38);
	unsigned char pad[0x60 - 4];
	float m_f60;
	void handleMatch(void *a, void *b);
};

// ?vfn6@BfmeBaseA97@@UAEXPAX0@Z
void BfmeBaseA97::vfn6(void *a, void *b_sub38)
{
	float radius = m_f60 > 1.0f ? m_f60 : 1.0f;
	BfmeWideResult iter = ((BfmeWideForwardA *)ThePartitionManager)->
		bfmeForwardWideA((int)b_sub38, *(int *)&radius, 3, 0);
	while (void *obj = iter.next()) {
		if (vfn1(a, obj))
			handleMatch(a, obj);
	}
}
