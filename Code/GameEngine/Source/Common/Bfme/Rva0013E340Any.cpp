// cl: /O2 /Ob1

struct BfmeElem340
{
	unsigned char bfmePred(void);
	char m_bfmeBytes[0xEC];
};

class Gen_0013E340
{
public:
	unsigned char bfmeAny(void);

private:
	char m_bfmePad[0x2F8];
	BfmeElem340 *m_bfmeStart;
	BfmeElem340 *m_bfmeFinish;
};

unsigned char Gen_0013E340::bfmeAny(void)
{
	BfmeElem340 *cursor = m_bfmeStart;

	if (cursor == m_bfmeFinish)
		return 0;

	do
	{
		if (cursor->bfmePred())
			return 1;

		++cursor;
	}
	while (cursor != m_bfmeFinish);

	return 0;
}
