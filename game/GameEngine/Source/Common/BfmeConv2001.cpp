extern "C" void *bfmeVftAEVK[];
extern "C" void *bfmeVftBEVK[];
extern "C" void *bfmeVftCEVK[];

class BfmeHostEVK;

class BfmeSubEVK
{
public:
	void bfmeInitBEVK(BfmeSubEVK *src);

	void *volatile m_bfmeVftCEVK;
	unsigned char m_bfmePadCEVK[0xc];
};

class BfmeHostEVK
{
public:
	BfmeHostEVK(BfmeHostEVK *other);
	void bfmeInitAEVK(BfmeHostEVK *other);

	void *volatile m_bfmeVftAEVK;
	int m_bfmePadAEVK;
	void *volatile m_bfmeVftBEVK;
	int m_bfmePadBEVK;
	BfmeSubEVK m_bfmeSubEVK;
	char m_bfmeFlagEVK;
};

BfmeHostEVK::BfmeHostEVK(BfmeHostEVK *other)
{
	bfmeInitAEVK(other);
	m_bfmeSubEVK.bfmeInitBEVK(other != 0 ? &other->m_bfmeSubEVK : 0);

	m_bfmeVftAEVK = bfmeVftAEVK;
	m_bfmeVftBEVK = bfmeVftBEVK;
	m_bfmeSubEVK.m_bfmeVftCEVK = bfmeVftCEVK;

	m_bfmeFlagEVK = other->m_bfmeFlagEVK;
}
