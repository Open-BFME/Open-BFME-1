class BfmeReqCR;
class BfmeSrcCR;

class BfmeSrcCR
{
public:
	void *m_bfmeHeadCR;
};

class BfmeReqCR
{
public:
	BfmeReqCR(BfmeSrcCR *src, int mode);
	~BfmeReqCR();

	unsigned char m_bfmePadCR[0x70];
};

struct Rva005A00B0AudioClient
{
	virtual void bfmeSlot00CR();
	virtual void bfmeSlot01CR();
	virtual void bfmeSlot02CR();
	virtual void bfmeSlot03CR();
	virtual void bfmeSlot04CR();
	virtual void bfmeSlot05CR();
	virtual void bfmeSlot06CR();
	virtual void bfmeSlot07CR();
	virtual void bfmeSlot08CR();
	virtual void bfmeSlot09CR();
	virtual void bfmeSlot10CR();
	virtual void bfmeSlot11CR();
	virtual void bfmeSlot12CR();
	virtual void bfmeSlot13CR();
	virtual void bfmeSlot14CR();
	virtual void bfmeSlot15CR();
	virtual void bfmeSlot16CR();
	virtual void bfmeSendCR(BfmeReqCR *req);
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

void __stdcall bfmeQueueCR(BfmeSrcCR *src)
{
	if (src->m_bfmeHeadCR != 0)
	{
		BfmeReqCR req(src, 1);

		TheAudioClientUpdate->bfmeSendCR(&req);
	}
}
