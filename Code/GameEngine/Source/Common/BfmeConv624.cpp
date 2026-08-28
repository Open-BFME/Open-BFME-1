struct BfmeTempCME
{
	BfmeTempCME();
	unsigned char m_bfmeHead[0x14];
	int m_bfmeResult;
};

class BfmeThingCME
{
public:
	void bfmeCallCME(void *what, float value, BfmeTempCME *out, int one, int two);
	int bfmeGoCME(void *what);
};

int BfmeThingCME::bfmeGoCME(void *what)
{
	BfmeTempCME tmp;
	bfmeCallCME(what, 10.0f, &tmp, 0, 0);
	return tmp.m_bfmeResult;
}
