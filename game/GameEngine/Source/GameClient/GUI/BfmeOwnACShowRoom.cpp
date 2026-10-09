// cl: /MD /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

class BfmeStrDataAC
{
public:
	unsigned char m_bfmeHeadAC[4];
	short m_bfmeLenAC;
};

class BfmeRoomAC
{
public:
	BfmeRoomAC(const BfmeRoomAC &other);
	~BfmeRoomAC();

	// ?bfmeHasTextAC@BfmeRoomAC@@QBEHXZ absent-from-retail
	int bfmeHasTextAC(void) const
	{
		return m_bfmeDataAC != 0 && m_bfmeDataAC->m_bfmeLenAC != 0;
	}

	BfmeStrDataAC *m_bfmeDataAC;
};

class Display
{
public:
	virtual void bfmeDpSlot00AC(void);
	virtual void bfmeDpSlot01AC(void);
	virtual void bfmeDpSlot02AC(void);
	virtual void bfmeDpSlot03AC(void);
	virtual void bfmeDpSlot04AC(void);
	virtual void bfmeDpSlot05AC(void);
	virtual void bfmeDpSlot06AC(void);
	virtual void bfmeDpSlot07AC(void);
	virtual void bfmeDpSlot08AC(void);
	virtual void bfmeDpSlot09AC(void);
	virtual void bfmeDpSlot10AC(void);
	virtual void bfmeDpSlot11AC(void);
	virtual void bfmeDpSlot12AC(void);
	virtual void bfmeDpSlot13AC(void);
	virtual void bfmeDpSlot14AC(void);
	virtual void bfmeDpSlot15AC(void);
	virtual void bfmeDpSlot16AC(void);
	virtual void bfmeDpSlot17AC(void);
	virtual void bfmeDpSlot18AC(void);
	virtual void bfmeDpSlot19AC(void);
	virtual void bfmeDpSlot20AC(void);
	virtual void bfmeDpSlot21AC(void);
	virtual void bfmeDpSlot22AC(void);
	virtual void bfmeDpSlot23AC(void);
	virtual void bfmeDpSlot24AC(void);
	virtual void bfmeDpSlot25AC(void);
	virtual void bfmeDpSlot26AC(void);
	virtual void bfmeDpSlot27AC(void);
	virtual void bfmeDpSlot28AC(void);
	virtual void bfmeDpSlot29AC(void);
	virtual void bfmeDpSlot30AC(void);
	virtual void bfmeDpSlot31AC(void);
	virtual void bfmeDpSlot32AC(void);
	virtual void bfmeDpSlot33AC(void);
	virtual void bfmeDpSlot34AC(void);
	virtual void bfmeDpSlot35AC(void);
	virtual void bfmeDpSlot36AC(void);
	virtual void bfmeDpSlot37AC(void);
	virtual void bfmeDpSlot38AC(void);
	virtual void bfmeDpSlot39AC(void);
	virtual void bfmeDpSlot40AC(void);
	virtual void bfmeDpSlot41AC(void);
	virtual void bfmeDpSlot42AC(void);
	virtual void bfmeDpSlot43AC(void);
	virtual void bfmeDpSlot44AC(void);
	virtual void bfmeDpSlot45AC(void);
	virtual void bfmeDpSlot46AC(void);
	virtual void bfmeDpSlot47AC(void);
	virtual void bfmeDpSlot48AC(void);
	virtual void bfmeDpSlot49AC(void);
	virtual void bfmeDpSlot50AC(void);
	virtual void bfmeDpSlot51AC(void);
	virtual void bfmeDpSlot52AC(void);
	virtual void bfmeDpSlot53AC(void);
	virtual void bfmeDpSlot54AC(void);
	virtual void bfmeDpSlot55AC(void);
	virtual void bfmeDpSlot56AC(void);
	virtual void bfmeDpSlot57AC(void);
	virtual void bfmeDpSlot58AC(void);
	virtual void bfmeDpSlot59AC(void);
	virtual void bfmeDpSlot60AC(void);
	virtual void bfmeDpSlot61AC(void);
	virtual void bfmeDpSlot62AC(void);
	virtual bool bfmeShowAC(AsciiString name, int flags);

	unsigned char m_bfmeHeadAC[0x104];
	char m_bfmeShownAC;
};

class ClientSubsystem
{
public:
	virtual void bfmeCsSlot00AC(void);
	virtual void bfmeCsSlot01AC(void);
	virtual void bfmeCsSlot02AC(void);
	virtual void bfmeCsSlot03AC(void);
	virtual void bfmeCsSlot04AC(void);
	virtual void bfmeStopAC(void);
	virtual void bfmeCsSlot06AC(void);
	virtual void bfmeCsSlot07AC(void);
	virtual void bfmeCsSlot08AC(void);
	virtual void bfmeCsSlot09AC(void);
	virtual void bfmeCsSlot10AC(void);
	virtual void bfmeCsSlot11AC(void);
	virtual void bfmeCsSlot12AC(void);
	virtual void bfmeCsSlot13AC(void);
	virtual void bfmeCsSlot14AC(void);
	virtual void bfmeSetModeAC(int mode);
};

extern Display *TheDisplay;
extern ClientSubsystem *TheAudioClientUpdate;

class BfmeOwnAC
{
public:
	void bfmeShowRoomAC(void *unused);

	unsigned char m_bfmeHeadAC[0x14];
	AsciiString m_bfmeRoomAC;
};

void BfmeOwnAC::bfmeShowRoomAC(void *unused)
{
	if (!((const BfmeRoomAC *)&m_bfmeRoomAC)->bfmeHasTextAC())
		return;

	if (TheDisplay)
		TheDisplay->bfmeShowAC(m_bfmeRoomAC, 0x800014);

	TheDisplay->m_bfmeShownAC = 1;
	TheAudioClientUpdate->bfmeSetModeAC(2);
	TheAudioClientUpdate->bfmeStopAC();
}
