extern "C" void *bfmeVftAEVJ[];
extern "C" void *bfmeVftBEVJ[];
extern "C" void *bfmeVftCEVJ[];

class BfmeHostEVJ;

class BfmeSubEVJ
{
public:
	void bfmeInitBEVJ(BfmeSubEVJ *src);

	void *volatile m_bfmeVftCEVJ;
	unsigned char m_bfmePadCEVJ[8];
};

class BfmeHostEVJ
{
public:
	BfmeHostEVJ(BfmeHostEVJ *other);
	void bfmeInitAEVJ(BfmeHostEVJ *other);

	void *volatile m_bfmeVftAEVJ;
	int m_bfmePadAEVJ;
	void *volatile m_bfmeVftBEVJ;
	int m_bfmePadBEVJ;
	BfmeSubEVJ m_bfmeSubEVJ;
	char m_bfmeFlagEVJ;
};

BfmeHostEVJ::BfmeHostEVJ(BfmeHostEVJ *other)
{
	bfmeInitAEVJ(other);
	m_bfmeSubEVJ.bfmeInitBEVJ(other != 0 ? &other->m_bfmeSubEVJ : 0);

	m_bfmeVftAEVJ = bfmeVftAEVJ;
	m_bfmeVftBEVJ = bfmeVftBEVJ;
	m_bfmeSubEVJ.m_bfmeVftCEVJ = bfmeVftCEVJ;

	m_bfmeFlagEVJ = other->m_bfmeFlagEVJ;
}
