class BfmeAgentBI;

struct BfmeInfoBI
{
	unsigned char m_bfmeFlagBI;
	unsigned char m_bfmeLevelBI;
};

class BfmeAgentBI
{
public:
	virtual void bfmeSlot00BI();
	virtual char bfmeReadingBI();
	virtual void bfmeSlot02BI();
	virtual void bfmeSlot03BI();
	virtual void bfmeSlot04BI();
	virtual void bfmeSlot05BI();
	virtual void bfmeSlot06BI();
	virtual void bfmeSlot07BI();
	virtual void bfmeSlot08BI();
	virtual void bfmeSlot09BI();
	virtual void bfmeFillBI(BfmeInfoBI *info);
	virtual void bfmeSlot11BI();
	virtual void bfmeSlot12BI();
	virtual void bfmeSlot13BI();
	virtual void bfmeSlot14BI();
	virtual void bfmeSlot15BI();
	virtual void bfmeSlot16BI();
	virtual void bfmeSlot17BI();
	virtual void bfmeSlot18BI();
	virtual void bfmeSlot19BI();
	virtual void bfmeSlot20BI();
	virtual void bfmeSlot21BI();
	virtual void bfmeSlot22BI();
	virtual void bfmeSlot23BI();
	virtual void bfmeSlot24BI();
	virtual void bfmeSlot25BI();
	virtual void bfmeSlot26BI();
	virtual void bfmeSlot27BI();
	virtual void bfmeSlot28BI();
	virtual void bfmeSlot29BI();
	virtual void bfmeSlot30BI();
	virtual void bfmeSlot31BI();
	virtual void bfmeSlot32BI();
	virtual void bfmeSlot33BI();
	virtual void bfmeSlot34BI();
	virtual void bfmeByteBI(unsigned char *dst);
};

struct Rva005A00B0AudioClient
{
	virtual void bfmeSlot00AD();
	virtual void bfmeSlot01AD();
	virtual void bfmeSlot02AD();
	virtual void bfmeSlot03AD();
	virtual void bfmeSlot04AD();
	virtual void bfmeSlot05AD();
	virtual void bfmeSlot06AD();
	virtual void bfmeSlot07AD();
	virtual void bfmeSlot08AD();
	virtual void bfmeSlot09AD();
	virtual void bfmeSlot10AD();
	virtual void bfmeSlot11AD();
	virtual void bfmeSlot12AD();
	virtual void bfmeSlot13AD();
	virtual void bfmeSlot14AD();
	virtual void bfmeSlot15AD();
	virtual void bfmeSlot16AD();
	virtual void bfmeSlot17AD();
	virtual void bfmeSlot18AD();
	virtual void bfmeSlot19AD();
	virtual void bfmeSlot20AD();
	virtual void bfmeSlot21AD();
	virtual void bfmeSlot22AD();
	virtual void bfmeSlot23AD();
	virtual void bfmeSlot24AD();
	virtual void bfmeSlot25AD();
	virtual void bfmeSlot26AD();
	virtual void bfmeSlot27AD();
	virtual void bfmeSlot28AD();
	virtual void bfmeSlot29AD();
	virtual void bfmeSlot30AD();
	virtual void bfmeSlot31AD();
	virtual unsigned int bfmeNewBI();
	virtual void bfmeSlot33AD();
	virtual void bfmeSlot34AD();
	virtual void bfmeSlot35AD();
	virtual void bfmeSlot36AD();
	virtual void bfmeSlot37AD();
	virtual void bfmeSlot38AD();
	virtual void bfmeSlot39AD();
	virtual void bfmeSlot40AD();
	virtual void bfmeSlot41AD();
	virtual void bfmeSlot42AD();
	virtual void bfmeSlot43AD();
	virtual void bfmeSlot44AD();
	virtual void bfmeSlot45AD();
	virtual void bfmeSlot46AD();
	virtual void bfmeSlot47AD();
	virtual void bfmeSlot48AD();
	virtual void bfmeSlot49AD();
	virtual void bfmeSlot50AD();
	virtual void bfmeSlot51AD();
	virtual void bfmeSlot52AD();
	virtual void bfmeSlot53AD();
	virtual void bfmeSlot54AD();
	virtual void bfmeSlot55AD();
	virtual void bfmeSlot56AD();
	virtual void bfmeSlot57AD();
	virtual void bfmeSlot58AD();
	virtual void bfmeSlot59AD();
	virtual void bfmeSlot60AD();
	virtual void bfmeSlot61AD();
	virtual void bfmeSlot62AD();
	virtual void bfmeSlot63AD();
	virtual void bfmeSlot64AD();
	virtual void bfmeSlot65AD();
	virtual void bfmeSlot66AD();
	virtual void bfmeSlot67AD();
	virtual void bfmeSlot68AD();
	virtual void bfmeSlot69AD();
	virtual void bfmeSlot70AD();
	virtual void bfmeSlot71AD();
	virtual void bfmeSlot72AD();
	virtual void bfmeSlot73AD();
	virtual void bfmeSlot74AD();
	virtual void bfmeSlot75AD();
	virtual void bfmeSlot76AD();
	virtual void bfmeSlot77AD();
	virtual void bfmeSlot78AD();
	virtual void bfmeSlot79AD();
	virtual void bfmeSlot80AD();
	virtual void bfmeSlot81AD();
	virtual void bfmeAudioBI(BfmeAgentBI *ag, void *dst);
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

class BfmeHostBI
{
public:
	void bfmeSaveBI(BfmeAgentBI *ag);
	void bfmeResetBI();

	unsigned char m_bfmeHeadBI[0x2c];
	unsigned int m_bfmeHandleBI;
	unsigned char m_bfmeSlotABI;
	unsigned char m_bfmeSlotBBI;
	unsigned char m_bfmeSlotCBI;
};

void BfmeHostBI::bfmeSaveBI(BfmeAgentBI *ag)
{
	BfmeInfoBI info;

	info.m_bfmeFlagBI = 1;
	info.m_bfmeLevelBI = 1;
	ag->bfmeFillBI(&info);

	if (ag->bfmeReadingBI() != 0)
		bfmeResetBI();

	TheAudioClientUpdate->bfmeAudioBI(ag, &m_bfmeHandleBI);

	ag->bfmeByteBI(&m_bfmeSlotABI);
	ag->bfmeByteBI(&m_bfmeSlotBBI);
	ag->bfmeByteBI(&m_bfmeSlotCBI);

	unsigned char live = (m_bfmeHandleBI >= 5);

	ag->bfmeByteBI(&live);

	if (ag->bfmeReadingBI() != 0 && live != 0 && m_bfmeHandleBI < 5)
		m_bfmeHandleBI = TheAudioClientUpdate->bfmeNewBI();
}
