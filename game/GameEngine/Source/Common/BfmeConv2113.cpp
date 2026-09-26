typedef int Int;

class Glo012F1024Item
{
public:
	void bfmeEnter(void);

	char m_bfmeBodyZU[0xDC];
};

class Glo012F1028Sub
{
public:
	void bfmeNotify(void);
};

class Glo012F1028Type
{
public:
	char m_bfmeHeadZU[0x28];
	Glo012F1028Sub *m_bfmeSub;
};

extern Glo012F1028Type *Glo012F1028;

class BfmeRewindZU
{
public:
	void bfmeRewindZU(void);

private:
	char m_bfmeHeadAZU[0x08];
	Int m_bfmeIndexZU;
	Glo012F1024Item *m_bfmeItemsZU;
	char m_bfmeHeadBZU[0x18 - 0x10];
	Int m_bfmeLimitZU;
};

void BfmeRewindZU::bfmeRewindZU(void)
{
	Int index = 0;
	Int limit = m_bfmeLimitZU;

	m_bfmeIndexZU = index;

	if (index > limit)
	{
		m_bfmeIndexZU = limit;
		Glo012F1028->m_bfmeSub->bfmeNotify();
	}
	else
	{
		m_bfmeItemsZU[index].bfmeEnter();
		Glo012F1028->m_bfmeSub->bfmeNotify();
	}
}
