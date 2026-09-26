void __cdecl operator delete(void *block);

class BfmeStringYJ
{
public:
	~BfmeStringYJ()
	{
		bfmeReleaseYJ();
	}

	void bfmeReleaseYJ();

	void *m_bfmeDataYJ;
};

class BfmeChildYJ
{
public:
	void bfmeCleanYJ();
};

class BfmeOwnerYJ
{
public:
	~BfmeOwnerYJ();

	BfmeStringYJ m_bfmeTextYJ;
	unsigned char m_bfmePadYJ[0x38];
	BfmeChildYJ *m_bfmeChildYJ;
};

BfmeOwnerYJ::~BfmeOwnerYJ()
{
	BfmeChildYJ *child = m_bfmeChildYJ;

	if (child != 0)
	{
		child->bfmeCleanYJ();
		operator delete(child);
	}
}
