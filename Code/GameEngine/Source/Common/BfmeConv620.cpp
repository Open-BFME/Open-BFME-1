class BfmeSubCLE;

class BfmeXCLE
{
public:
	bool bfmeRunCLE(BfmeSubCLE *sub, void *what, int value);
};

class BfmeSubCLE
{
public:
	BfmeXCLE *bfmeAskCLE(int value);
};

class BfmeThingCLE
{
public:
	bool bfmeGoCLE(void *what);
	unsigned char m_bfmeHead[0xc];
	BfmeSubCLE *m_bfmeSub;
};

bool BfmeThingCLE::bfmeGoCLE(void *what)
{
	if (m_bfmeSub->bfmeAskCLE(0) == 0)
		return true;
	return m_bfmeSub->bfmeAskCLE(0)->bfmeRunCLE(m_bfmeSub, what, 0);
}
