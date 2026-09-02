// ?forwardEmptyRequest@BfmeRequestOwner@@QAEXH@Z
// partial score=0.68 date=2026-09-02
// cl: /O2

// Open-BFME5: build an all-zero nine-dword request record and forward it by
// value together with the caller's request selector.

struct BfmeNineWordRequest
{
	__forceinline BfmeNineWordRequest()
	{
		m_firstFlag = 0;
		m_secondFlag = 0;
		m_mode = 0;
		for (int i = 0; i < 8; ++i)
			m_words[i] = 0;
	}

	unsigned char m_firstFlag;
	unsigned char m_secondFlag;
	unsigned short m_mode;
	int m_words[8];
};

class BfmeRequestOwner
{
public:
	void forwardEmptyRequest(int selector);
	void forwardRequest(int selector, BfmeNineWordRequest request);
};

void BfmeRequestOwner::forwardEmptyRequest(int selector)
{
	BfmeNineWordRequest request;
	forwardRequest(selector, request);
}
