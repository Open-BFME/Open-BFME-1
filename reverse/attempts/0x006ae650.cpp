// Scratch reconstruction for retail RVA 0x006AE650.
// partial score=0.9 date=2026-09-16
__declspec(dllimport) void __stdcall bfmeClose1012(void *h);
__declspec(dllimport) int __stdcall bfmeWait1012(void *h, int t);

class BfmeLockTM
{
public:
	BfmeLockTM(void *h)
	{
		m_bfmeOkTM = 0;
		m_bfmeHandleTM = h;

		if (bfmeWait1012(h, -1) != 0x102)
			m_bfmeOkTM = 1;
	}

	~BfmeLockTM()
	{
		if (m_bfmeOkTM)
			bfmeClose1012(m_bfmeHandleTM);
	}

	void *m_bfmeHandleTM;
	char m_bfmeOkTM;
};

template <typename T> class StringBase
{
	void *m_data;
};

class Rva006AEE00Tree
{
public:
	struct InsertResult
	{
		void *m_iterator;
		bool m_inserted;
	};

	void insert_unique(InsertResult *out, const StringBase<char> &key);

	unsigned char m_body[0xc];
};

class Rva006AE650Owner
{
public:
	virtual void bfmeSlot00TM();
	virtual void bfmeSlot01TM();
	virtual void bfmeSlot02TM();
	virtual void bfmeSlot03TM();
	virtual void bfmeSlot04TM();
	virtual void bfmeSlot05TM();
	virtual void bfmeSlot06TM();
	virtual void bfmeSlot07TM();
	virtual void bfmeSlot08TM();
	virtual void bfmeSlot09TM();
	virtual void bfmeSlot10TM();
	virtual void bfmeSlot11TM();
	virtual void bfmeSlot12TM();
	virtual void bfmeSlot13TM();
	virtual void bfmeSlot14TM();
	virtual void bfmeSlot15TM();
	virtual void bfmeSlot16TM();
	virtual void bfmeSlot17TM();
	virtual void bfmeStepTM(int a, int b) throw();

	void rva006AE650(int a, int b);

	unsigned char m_bfmeHeadTM[0x958];
	void *m_bfmeMutexTM;
	char m_bfmeGapTM[0x38];
	Rva006AEE00Tree m_bfmeArrTM[4];
};

void Rva006AE650Owner::rva006AE650(int a, int b)
{
	BfmeLockTM lock(m_bfmeMutexTM);

	bfmeStepTM(a, b);

	Rva006AEE00Tree::InsertResult out;
	m_bfmeArrTM[b].insert_unique(&out,
		*reinterpret_cast<StringBase<char> *>(*(volatile int *)&a));
}
