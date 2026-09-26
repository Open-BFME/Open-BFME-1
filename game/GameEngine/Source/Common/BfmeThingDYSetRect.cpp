// cl: /DNDEBUG /MD /EHsc

class BfmeThingDY
{
public:
	virtual void bfmeSpare000DY(void) = 0;
	virtual void bfmeSpare001DY(void) = 0;
	virtual void bfmeSpare002DY(void) = 0;
	virtual void bfmeDoDY(void) = 0;

	void bfmeSetRectDY(int left, int right, int top, int bottom, int value);

private:
	unsigned char m_bfmeHead[0x20];
	int m_bfmeFirst;
	unsigned char m_bfmeGap[4];
	int m_bfmeWhat;
	int m_bfmeNone;
	int m_bfmeLeft;
	int m_bfmeRight;
	int m_bfmeTop;
	int m_bfmeBottom;
	int m_bfmeSecond;
	int m_bfmeHow;
};

void BfmeThingDY::bfmeSetRectDY(int left, int right, int top, int bottom, int value)
{
	int v = value;
	int l = left;
	int t = top;
	int r = right;
	m_bfmeHow = v;
	m_bfmeRight = r;
	int width = r - l;
	m_bfmeLeft = l;
	m_bfmeFirst = 3;
	m_bfmeSecond = 0;
	m_bfmeTop = t;
	int b = bottom;
	m_bfmeBottom = b;
	m_bfmeWhat = width;
	m_bfmeNone = 0;
	bfmeDoDY();
}
