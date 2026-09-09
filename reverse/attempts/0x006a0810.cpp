// ?bfmeEraseAAR@BfmeTableAAR@@QAEXPAPAUBfmeNodeAAR@@@Z
// partial score=0.8 date=2026-09-08
namespace _STL
{

class __node_alloc
{
public:
	static void _M_deallocate(void *p, unsigned int n);
};

}

struct BfmeKeyAAR
{
	unsigned char m_bfmeHeadAAR[8];
	unsigned int m_bfmeHashAAR;
};

struct BfmeNodeAAR
{
	BfmeNodeAAR *m_bfmeNextAAR;
	BfmeKeyAAR *m_bfmeKeyAAR;
};

class BfmeTableAAR
{
public:
	void bfmeEraseAAR(BfmeNodeAAR **it);

	unsigned char m_bfmeHeadTAAR[4];
	BfmeNodeAAR **m_bfmeBucketsAAR;
	BfmeNodeAAR **m_bfmeEndAAR;
	unsigned char m_bfmeGapAAR[4];
	int m_bfmeSizeAAR;
};

void BfmeTableAAR::bfmeEraseAAR(BfmeNodeAAR **it)
{
	BfmeNodeAAR *n = *it;

	if (n == 0)
		return;

	BfmeKeyAAR *key = n->m_bfmeKeyAAR;
	unsigned int h = (unsigned int)key;

	if (key != 0)
		h = key->m_bfmeHashAAR;

	register BfmeNodeAAR **buckets = m_bfmeBucketsAAR;
	register BfmeNodeAAR **end = m_bfmeEndAAR;
	unsigned int idx = h % (unsigned int)(end - buckets);
	BfmeNodeAAR **slot = buckets + idx;
	BfmeNodeAAR *cur = *slot;

	if (cur == n)
	{
		*slot = cur->m_bfmeNextAAR;
		_STL::__node_alloc::_M_deallocate(cur, 8);
		--m_bfmeSizeAAR;
		return;
	}

	while (cur != 0)
	{
		BfmeNodeAAR *nx = cur->m_bfmeNextAAR;

		if (nx == 0)
			return;

		if (nx == n)
		{
			cur->m_bfmeNextAAR = nx->m_bfmeNextAAR;
			_STL::__node_alloc::_M_deallocate(nx, 8);
			--m_bfmeSizeAAR;
			return;
		}

		cur = nx;
	}
}
