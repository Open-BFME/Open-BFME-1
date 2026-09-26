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
		m_words[0] = 0;
		m_words[1] = 0;
		m_words[2] = 0;
		m_words[3] = 0;
		m_words[4] = 0;
		m_words[5] = 0;
		m_words[6] = 0;
		m_words[7] = 0;
	}

	int m_words[8];
	unsigned char m_firstFlag;
	unsigned char m_secondFlag;
	unsigned short m_mode;
};

class BfmeRequestOwner
{
public:
	void forwardEmptyRequest(int selector);
	void forwardRequest(int selector, BfmeNineWordRequest request);
};

void BfmeRequestOwner::forwardEmptyRequest(int selector)
{
	BfmeRequestOwner *self = this;
	BfmeNineWordRequest request;
	self->forwardRequest(selector, request);
}
