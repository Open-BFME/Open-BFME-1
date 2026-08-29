// Open-BFME5 conversions.

struct BfmeVec945A
{
	int m_bfmeX;
	int m_bfmeY;
	int m_bfmeZ;
};


struct BfmeNode946
{
	BfmeNode946 *m_bfmeNext;
	BfmeNode946 *m_bfmePrev;
	BfmeVec945A m_bfmeVec;
};

void *bfmeAlloc946(unsigned int n);

BfmeNode946 **__stdcall bfmeGo946A(BfmeNode946 **out, BfmeNode946 *pos, BfmeVec945A *val)
{
	BfmeNode946 *n = (BfmeNode946 *)bfmeAlloc946(0x14);
	BfmeVec945A *dst = &n->m_bfmeVec;
	if (dst) {
		dst->m_bfmeX = val->m_bfmeX;
		dst->m_bfmeY = val->m_bfmeY;
		dst->m_bfmeZ = val->m_bfmeZ;
	}
	BfmeNode946 *prev = pos->m_bfmePrev;
	n->m_bfmeNext = pos;
	n->m_bfmePrev = prev;
	prev->m_bfmeNext = n;
	pos->m_bfmePrev = n;
	*out = n;
	return out;
}

BfmeNode946 **__stdcall bfmeGo946B(BfmeNode946 **out, BfmeNode946 *pos, BfmeVec945A *val)
{
	BfmeNode946 *n = (BfmeNode946 *)bfmeAlloc946(0x14);
	BfmeVec945A *dst = &n->m_bfmeVec;
	if (dst) {
		dst->m_bfmeX = val->m_bfmeX;
		dst->m_bfmeY = val->m_bfmeY;
		dst->m_bfmeZ = val->m_bfmeZ;
	}
	BfmeNode946 *prev = pos->m_bfmePrev;
	n->m_bfmeNext = pos;
	n->m_bfmePrev = prev;
	prev->m_bfmeNext = n;
	pos->m_bfmePrev = n;
	*out = n;
	return out;
}
