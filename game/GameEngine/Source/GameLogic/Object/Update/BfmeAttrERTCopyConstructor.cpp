// ??0BfmeAttrERT@@QAE@ABV0@@Z
// cl: /DNDEBUG /MD /EHsc
// stlport

#include <vector>

typedef int Int;
typedef bool Bool;

struct BfmeLegendStringVec
{
	BfmeLegendStringVec(const BfmeLegendStringVec &other);
	~BfmeLegendStringVec();

	void *m_start;
	void *m_finish;
	void *m_end;
};

class Gen_ve_0039d5d0
{
};

typedef _STL::vector<Gen_ve_0039d5d0 *> BfmePointerVector;

struct BfmeAttributePlainBlock
{
	Int m_values[6];
};

class BfmeAttrERT
{
public:
	BfmeAttrERT(const BfmeAttrERT &other);

private:
	BfmeLegendStringVec m_names;
	BfmeLegendStringVec m_values;
	BfmePointerVector m_list0;
	BfmePointerVector m_list1;
	BfmePointerVector m_list2;
	BfmePointerVector m_list3;
	BfmeAttributePlainBlock m_firstPlain;
	BfmeAttributePlainBlock m_secondPlain;
	Int m_kind;
	Int m_index;
	Bool m_enabled;
	unsigned char m_pad[3];
	Int m_useCount;
};

BfmeAttrERT::BfmeAttrERT(const BfmeAttrERT &other)
	: m_names(other.m_names)
	, m_values(other.m_values)
	, m_list0(other.m_list0)
	, m_list1(other.m_list1)
	, m_list2(other.m_list2)
	, m_list3(other.m_list3)
	, m_firstPlain(other.m_firstPlain)
	, m_secondPlain(other.m_secondPlain)
{
	m_kind = other.m_kind;
	m_index = other.m_index;
	m_enabled = other.m_enabled;
	m_useCount = other.m_useCount;
}
