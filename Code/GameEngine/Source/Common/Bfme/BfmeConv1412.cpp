// Open-BFME5 conversions.

struct BfmeElemVLH
{
	char m_bfmePad[0x60];
};

class BfmeVecVLH
{
public:
	BfmeElemVLH *bfmeAtVLH(int i);
	int m_bfme00;
	BfmeElemVLH *volatile m_bfme04;
	BfmeElemVLH *volatile m_bfme08;
};

BfmeElemVLH *BfmeVecVLH::bfmeAtVLH(int i)
{
	if (i < 0)
		return 0;
	if ((unsigned)i >= (unsigned)(m_bfme08 - m_bfme04))
		return 0;
	BfmeElemVLH *p = m_bfme04;
	BfmeElemVLH *e = m_bfme08;
	int k = i;
	while (p != e)
	{
		if (k == 0)
			return p;
		++p;
		--k;
	}
	return 0;
}
