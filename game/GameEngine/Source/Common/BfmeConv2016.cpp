extern "C" void *bfmeVftEAZ[];

class BfmeStrEAZ
{
public:
	~BfmeStrEAZ();

	void *m_bfmeDataEAZ;
};

class Rva0048EC80Manager
{
public:
	virtual void bfmeSlot00EAZ();
	virtual void bfmeSlot01EAZ();
	virtual void bfmeSlot02EAZ();
	virtual void bfmeSlot03EAZ();
	virtual void bfmeSlot04EAZ();
	virtual void bfmeSlot05EAZ();
	virtual void bfmeSlot06EAZ();
	virtual void bfmeSlot07EAZ();
	virtual void bfmeSlot08EAZ();
	virtual void bfmeSlot09EAZ();
	virtual void bfmeReleaseEAZ(void *item);
};

extern Rva0048EC80Manager *Rva0048EC80TheManager;

class BfmeHostEAZ
{
public:
	~BfmeHostEAZ();

	void *volatile m_bfmeVftEAZ;
	unsigned char m_bfmeHeadEAZ[0x184];
	BfmeStrEAZ m_bfmeS0EAZ;
	BfmeStrEAZ m_bfmeS1EAZ;
	BfmeStrEAZ m_bfmeS2EAZ;
	BfmeStrEAZ m_bfmeS3EAZ;
	int m_bfmePadEAZ;
	void *m_bfmeAEAZ;
	void *m_bfmeBEAZ;
	int m_bfmeCEAZ;
};

BfmeHostEAZ::~BfmeHostEAZ()
{
	m_bfmeVftEAZ = bfmeVftEAZ;

	void *a = *(void *volatile *)&m_bfmeAEAZ;

	if (a != 0)
		Rva0048EC80TheManager->bfmeReleaseEAZ(a);

	if (m_bfmeBEAZ != 0)
		Rva0048EC80TheManager->bfmeReleaseEAZ(m_bfmeBEAZ);

	m_bfmeCEAZ = 0;
}
