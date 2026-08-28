struct BfmeRefCGA
{
	unsigned char m_bfmeHead[4];
	int m_bfmeCount;
};

struct BfmeSrcCGA
{
	BfmeRefCGA *m_bfmeRef;
	void *m_bfmeVal;
};

class BfmeThingCGA
{
public:
	void bfmeBaseCGA(void *what);
	BfmeThingCGA *bfmeInitCGA(void *what, BfmeSrcCGA *src);
	unsigned char m_bfmeHead[4];
	BfmeRefCGA *m_bfmeRef;
	void *m_bfmeVal;
};

BfmeThingCGA *BfmeThingCGA::bfmeInitCGA(void *what, BfmeSrcCGA *src)
{
	bfmeBaseCGA(what);
	BfmeRefCGA *ref = src->m_bfmeRef;
	m_bfmeRef = ref;
	if (ref != 0)
		++ref->m_bfmeCount;
	m_bfmeVal = src->m_bfmeVal;
	return this;
}
