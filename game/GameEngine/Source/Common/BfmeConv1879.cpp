extern "C" void *bfmeVft0ZL[];
extern "C" void *bfmeVft1ZL[];
extern "C" void *bfmeVft2ZL[];

class BfmeBase0ZL
{
public:
	BfmeBase0ZL(BfmeBase0ZL *other);

	void *m_bfmeVft0ZL;
	unsigned char m_bfmePad0ZL[4];
	void *m_bfmeVft1ZL;
};

class BfmeMidZL
{
public:
	BfmeMidZL(BfmeMidZL *other);

	void *m_bfmeVft2ZL;
	unsigned char m_bfmePad1ZL[0x40];
};

class BfmeDerivedZL : public BfmeBase0ZL, public BfmeMidZL
{
public:
	BfmeDerivedZL(BfmeDerivedZL *other);

	int m_bfmeAZL;
	int m_bfmeBZL;
	int m_bfmeCZL;
};

BfmeDerivedZL::BfmeDerivedZL(BfmeDerivedZL *other)
	: BfmeBase0ZL(other), BfmeMidZL(other)
{
	m_bfmeVft0ZL = bfmeVft0ZL;
	m_bfmeVft1ZL = bfmeVft1ZL;
	m_bfmeVft2ZL = bfmeVft2ZL;

	m_bfmeAZL = other->m_bfmeAZL;
	m_bfmeBZL = other->m_bfmeBZL;
	m_bfmeCZL = other->m_bfmeCZL;
}
