// Open-BFME5 conversions.

class BfmeS1176
{
public:
	void bfmeAssign1176(char *s);
};

class BfmeW1176
{
public:
	BfmeS1176 *bfmeGetText1176(BfmeS1176 *ret);
	void bfmeTouch1176(void);
	char m_bfmePad[0x58];
	char m_bfme58;
};

BfmeS1176 *BfmeW1176::bfmeGetText1176(BfmeS1176 *ret)
{
	volatile int x = 0;

	bfmeTouch1176();
	ret->bfmeAssign1176(&m_bfme58);

	return ret;
}
