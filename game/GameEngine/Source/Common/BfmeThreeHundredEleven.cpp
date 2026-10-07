// 0x00469980 calls retail 0x00887B60, the matched narrow StringBase copy
// constructor, to copy-construct the leading string member in place.
template <class T> class StringBase
{
	friend class BfmeThingRD;
private:
	StringBase(const StringBase &source);
	void *m_data;
};

struct BfmeRefRD
{
	unsigned char m_bfmeHead[4];
	int m_bfmeCount;
};

class BfmeThingRD
{
public:
	BfmeThingRD *bfmeCopyRD(BfmeThingRD *from);
	unsigned char m_bfmeHead[4];
	BfmeRefRD *m_bfmeRef;
	int m_bfmeMore;
};

BfmeThingRD *BfmeThingRD::bfmeCopyRD(BfmeThingRD *from)
{
	((StringBase<char> *)this)->StringBase<char>::StringBase<char>(*(StringBase<char> *)from);
	BfmeRefRD *ref = from->m_bfmeRef;
	m_bfmeRef = ref;
	if (ref != 0)
		++ref->m_bfmeCount;
	m_bfmeMore = from->m_bfmeMore;
	return this;
}
