// ?bfmeSetZN@BfmeHostZN@@QAEXI@Z
// partial score=0.95 date=2026-09-09
// ?bfmeSetZN@BfmeHostZN@@QAEXI@Z
class BfmeOwnerVNI
{
public:
	void bfmeApply1VNI();
};

class BfmeHostZN : public BfmeOwnerVNI
{
public:
	void bfmeSetZN(unsigned int bit);

	unsigned char m_bfmeHeadZN[0x110];
	unsigned int m_bfmeBitsZN[8];
};

void BfmeHostZN::bfmeSetZN(unsigned int bit)
{
	unsigned int i = bit >> 5;
	unsigned int m = 1 << (bit & 0x1f);
	unsigned int *w = &m_bfmeBitsZN[i];
	unsigned int c = *w;

	if (m & c)
		return;

	*w = c | m;
	bfmeApply1VNI();
}
