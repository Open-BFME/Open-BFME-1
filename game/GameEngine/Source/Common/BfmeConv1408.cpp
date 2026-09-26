// Open-BFME5 conversions.

class BfmeBlockVKQ
{
public:
	char bfmeAnyVKQ(const BfmeBlockVKQ &o);
	char bfmeCmpVKQ(const BfmeBlockVKQ &o);
	int m_bfmeArr[10];
};

class BfmeThingVKQ
{
public:
	char bfmeTestVKQ(BfmeBlockVKQ &f);
	int m_bfme00;
	BfmeBlockVKQ m_bfme04;
	BfmeBlockVKQ m_bfme2c;
};

char BfmeThingVKQ::bfmeTestVKQ(BfmeBlockVKQ &f)
{
	if (f.bfmeAnyVKQ(m_bfme2c))
		return false;
	BfmeBlockVKQ tmp = f;
	for (int i = 0; i < 10; ++i)
		tmp.m_bfmeArr[i] &= m_bfme04.m_bfmeArr[i];
	return !m_bfme04.bfmeCmpVKQ(tmp);
}
