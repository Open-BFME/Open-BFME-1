class BfmeSubDDA
{
public:
	int bfmeTailDDA();
	unsigned char m_bfmeHead[0x39];
	bool m_bfmeFlag;
};

class BfmeThingDDA
{
public:
	int bfmeGoDDA();
	unsigned char m_bfmeHead[0x68];
	BfmeSubDDA *m_bfmeSub;
};

int BfmeThingDDA::bfmeGoDDA()
{
	BfmeSubDDA *s = m_bfmeSub;
	if (s != 0 && s->m_bfmeFlag)
		return s->bfmeTailDDA();
	return 0;
}
