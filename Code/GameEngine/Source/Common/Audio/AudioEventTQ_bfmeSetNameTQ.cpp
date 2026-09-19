// cl: /Oa
class BfmeStrTQ
{
public:
	~BfmeStrTQ();

	int bfmeDiffersTQ(const BfmeStrTQ &other) const;
	void bfmeSetTQ(const BfmeStrTQ &other);

	void *m_bfmeDataTQ;
};

extern "C" __declspec(dllimport) long __stdcall BfmeDecTQ(long *p);

class BfmeHandleTQ
{
public:
	virtual void bfmeCloseTQ(int mode);

	long m_bfmeRefTQ;
};

class AudioEventTQ
{
public:
	void bfmeSetNameTQ(BfmeStrTQ name);

	unsigned char m_bfmeHeadTQ[8];
	BfmeHandleTQ *m_bfmeHandleTQ;
	unsigned char m_bfmePadTQ[8];
	BfmeStrTQ m_bfmeNameTQ;
};

void AudioEventTQ::bfmeSetNameTQ(BfmeStrTQ name)
{
	BfmeStrTQ &n = m_bfmeNameTQ;

	if (name.bfmeDiffersTQ(n))
	{
		BfmeHandleTQ *h = m_bfmeHandleTQ;

		if (h != 0)
		{
			long r = BfmeDecTQ(&h->m_bfmeRefTQ);

			if (r <= 0 && m_bfmeHandleTQ != 0)
				m_bfmeHandleTQ->bfmeCloseTQ(1);

			m_bfmeHandleTQ = 0;
		}

		n.bfmeSetTQ(name);
	}
}
