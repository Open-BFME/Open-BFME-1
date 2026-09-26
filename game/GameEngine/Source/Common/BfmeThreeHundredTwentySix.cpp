struct BfmeLinkRX
{
	BfmeLinkRX *m_bfmeNext;
	BfmeLinkRX *m_bfmePrev;
	unsigned short m_bfmeWhat;
};

void *bfmeAllocRX(unsigned int bytes);

class BfmeListRX
{
public:
	void bfmePushRX(unsigned short *what);
	BfmeLinkRX *m_bfmeEnd;
};

void BfmeListRX::bfmePushRX(unsigned short *what)
{
	BfmeLinkRX *end = m_bfmeEnd;
	BfmeLinkRX *link = (BfmeLinkRX *)bfmeAllocRX(0xc);
	unsigned short *slot = &link->m_bfmeWhat;
	if (slot != 0)
		*slot = *what;
	BfmeLinkRX *last = end->m_bfmePrev;
	link->m_bfmeNext = end;
	link->m_bfmePrev = last;
	last->m_bfmeNext = link;
	end->m_bfmePrev = link;
}
