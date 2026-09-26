extern "C" void *bfmeVtblEVD[];

class Rva0048EC80Manager
{
public:
	virtual void bfmeSlot00EVD();
	virtual void bfmeSlot01EVD();
	virtual void bfmeSlot02EVD();
	virtual void bfmeSlot03EVD();
	virtual void bfmeSlot04EVD();
	virtual void bfmeSlot05EVD();
	virtual void bfmeSlot06EVD();
	virtual void bfmeSlot07EVD();
	virtual void bfmeSlot08EVD();
	virtual void bfmeSlot09EVD();
	virtual void bfmeReleaseEVD(void *item);
};

extern Rva0048EC80Manager *Rva0048EC80TheManager;

class BfmeBaseEVD
{
public:
	~BfmeBaseEVD();

	void *volatile m_bfmeVfptrEVD;
	unsigned char m_bfmeHeadEVD[0x20];
};

class BfmeEntryEVD : public BfmeBaseEVD
{
public:
	~BfmeEntryEVD();

	void *m_bfmeSlotsEVD[3];
	volatile int m_bfmeCountEVD;
};

BfmeEntryEVD::~BfmeEntryEVD()
{
	m_bfmeVfptrEVD = bfmeVtblEVD;

	for (int i = 0; i < m_bfmeCountEVD; i++)
	{
		Rva0048EC80TheManager->bfmeReleaseEVD(m_bfmeSlotsEVD[i]);
		m_bfmeSlotsEVD[i] = 0;
	}
}
