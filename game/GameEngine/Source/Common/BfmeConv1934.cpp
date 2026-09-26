class BfmeReqDA;

class BfmeSlotDA
{
public:
	void *m_bfmeHeadDA;
};

class BfmeReqDA
{
public:
	BfmeReqDA(BfmeSlotDA *slot, int mode);
	~BfmeReqDA();

	unsigned char m_bfmePadDA[0x70];
};

struct Rva005A00B0AudioClient
{
	virtual void bfmeSlot00DA();
	virtual void bfmeSlot01DA();
	virtual void bfmeSlot02DA();
	virtual void bfmeSlot03DA();
	virtual void bfmeSlot04DA();
	virtual void bfmeSlot05DA();
	virtual void bfmeSlot06DA();
	virtual void bfmeSlot07DA();
	virtual void bfmeSlot08DA();
	virtual void bfmeSlot09DA();
	virtual void bfmeSlot10DA();
	virtual void bfmeSlot11DA();
	virtual void bfmeSlot12DA();
	virtual void bfmeSlot13DA();
	virtual void bfmeSlot14DA();
	virtual void bfmeSlot15DA();
	virtual void bfmeSlot16DA();
	virtual void bfmeSendDA(BfmeReqDA *req);
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

class BfmeHostDA
{
public:
	void bfmeStopDA();

	unsigned char m_bfmeHeadDA[0xf8];
	BfmeSlotDA m_bfmeSlotDA;
	unsigned char m_bfmeMidDA[0x18c];
	unsigned char m_bfmeADA;
	unsigned char m_bfmePadDA[0xb];
	unsigned char m_bfmeBDA;
};

void BfmeHostDA::bfmeStopDA()
{
	m_bfmeADA = 1;
	m_bfmeBDA = 0;

	if (TheAudioClientUpdate != 0)
	{
		BfmeSlotDA *slot = &m_bfmeSlotDA;

		if (slot->m_bfmeHeadDA != 0)
		{
			BfmeReqDA req(slot, 1);

			TheAudioClientUpdate->bfmeSendDA(&req);
		}
	}
}
