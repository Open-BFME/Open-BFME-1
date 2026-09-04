// Open-BFME5 conversions.

void __cdecl operator delete(void *block);

class BfmeStrVVA
{
public:
	~BfmeStrVVA() { bfmeClearVVA(); }
	char *m_bfme00;

private:
	void bfmeClearVVA();
};

class BfmeTexVVA
{
public:
	void bfmeReleaseRefVVA();
};

class BfmeHolderVVA
{
public:
	~BfmeHolderVVA()
	{
		if (m_bfme00 != 0)
			m_bfme00->bfmeReleaseRefVVA();
	}

	BfmeTexVVA *m_bfme00;
};

class BfmeOwnVVA
{
public:
	~BfmeOwnVVA();
	virtual void bfmeSlot0VVA();
	BfmeStrVVA m_bfme04;
	BfmeStrVVA m_bfme08;
	char m_bfmePad0c[0x20];
	BfmeHolderVVA *m_bfme2c;
};

BfmeOwnVVA::~BfmeOwnVVA()
{
	delete m_bfme2c;
}
