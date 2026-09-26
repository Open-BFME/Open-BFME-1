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
	BfmeStrTQ &currentName = m_bfmeNameTQ;

	if (name.bfmeDiffersTQ(currentName))
	{
		BfmeHandleTQ *eventInfoHandle = m_bfmeHandleTQ;

		if (eventInfoHandle != 0)
		{
			long remainingRefs = BfmeDecTQ(&eventInfoHandle->m_bfmeRefTQ);

			if (remainingRefs <= 0 && m_bfmeHandleTQ != 0)
				m_bfmeHandleTQ->bfmeCloseTQ(1);

			m_bfmeHandleTQ = 0;
		}

		currentName.bfmeSetTQ(name);
	}
}
