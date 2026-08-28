struct BfmeLinkRW
{
	BfmeLinkRW *m_bfmeNext;
	BfmeLinkRW *m_bfmePrev;
	void *m_bfmeWhat;
};

void *bfmeAllocRW(unsigned int bytes);

class BfmeListRW
{
public:
	void bfmePushRW(void *what);
	unsigned char m_bfmeHead[0xc];
	BfmeLinkRW **m_bfmeRoot;
};

void BfmeListRW::bfmePushRW(void *what)
{
	BfmeLinkRW *end = *m_bfmeRoot;
	BfmeLinkRW *link = (BfmeLinkRW *)bfmeAllocRW(0xc);
	void **slot = &link->m_bfmeWhat;
	if (slot != 0)
		*slot = what;
	BfmeLinkRW *last = end->m_bfmePrev;
	link->m_bfmeNext = end;
	link->m_bfmePrev = last;
	last->m_bfmeNext = link;
	end->m_bfmePrev = link;
}
