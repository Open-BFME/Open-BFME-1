// cl: /O2 /Ob1

struct BfmeElem340
{
	unsigned char bfmePred(void); // retail ILT 0x0003C5B0; called via j_0003c5b0 below
	char m_bfmeBytes[0xEC];
};

extern void j_0003c5b0();
typedef unsigned char (BfmeElem340::*BfmeElem340PredCall)(void);

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
		union { void (*raw)(); BfmeElem340PredCall member; } call;
		call.raw = j_0003c5b0;
		if ((cursor->*call.member)())
			return 1;

		++cursor;
	}
	while (cursor != m_bfmeFinish);

	return 0;
}
