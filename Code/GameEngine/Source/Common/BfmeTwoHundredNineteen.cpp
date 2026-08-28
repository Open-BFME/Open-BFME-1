// One more twice-emitted body, both copies converted here under their own
// names: the audio subsystem started or stopped once the run has gone far
// enough.

class ClientSubsystem
{
public:
	virtual void bfmeSpare000JZ(void) = 0;
	virtual void bfmeSpare001JZ(void) = 0;
	virtual void bfmeSpare002JZ(void) = 0;
	virtual void bfmeSpare003JZ(void) = 0;
	virtual void bfmeSpare004JZ(void) = 0;
	virtual void bfmeSpare005JZ(void) = 0;
	virtual void bfmeSpare006JZ(void) = 0;
	virtual void bfmeSpare007JZ(void) = 0;
	virtual void bfmeSpare008JZ(void) = 0;
	virtual void bfmeSpare009JZ(void) = 0;
	virtual void bfmeSpare010JZ(void) = 0;
	virtual void bfmeSpare011JZ(void) = 0;
	virtual void bfmeSpare012JZ(void) = 0;
	virtual void bfmeSpare013JZ(void) = 0;
	virtual void bfmeSpare014JZ(void) = 0;
	virtual void bfmeSpare015JZ(void) = 0;
	virtual void bfmeSpare016JZ(void) = 0;
	virtual void bfmeSpare017JZ(void) = 0;
	virtual void bfmeSpare018JZ(void) = 0;
	virtual void bfmeStopJZ(unsigned int mode) = 0;		///< retail slot 19, [vptr+0x4c]
	virtual void bfmeSpare020JZ(void) = 0;
	virtual void bfmeSpare021JZ(void) = 0;
	virtual void bfmeSpare022JZ(void) = 0;
	virtual void bfmeSpare023JZ(void) = 0;
	virtual void bfmeSpare024JZ(void) = 0;
	virtual void bfmeSpare025JZ(void) = 0;
	virtual void bfmeSpare026JZ(void) = 0;
	virtual void bfmeStartJZ(int one, int two, int three) = 0;	///< retail slot 27, [vptr+0x6c]
};

extern ClientSubsystem *TheAudioClientUpdate;	///< retail [0x012ED668]

struct BfmeItemJZ
{
	unsigned char m_bfmeHead[0x84];		// 0x00
	int m_bfmeFlag;				// 0x84
};


class BfmeThingJZ
{
public:
	void bfmeGoJZ(void);

private:
	unsigned char m_bfmeHead[0x14];		// 0x00
	BfmeItemJZ *m_bfmeItem;			// 0x14
	unsigned char m_bfmeGap[0x14];		// 0x18
	unsigned int m_bfmeMode;		// 0x2c
};

void BfmeThingJZ::bfmeGoJZ(void)
{
	ClientSubsystem *audio = TheAudioClientUpdate;

	if (audio == 0)
		return;

	unsigned int mode = m_bfmeMode;

	if (mode < 5)
		return;

	BfmeItemJZ *item = m_bfmeItem;

	if (item != 0 && item->m_bfmeFlag == 0)
	{
		audio->bfmeStartJZ(1, 1, 0);

		m_bfmeMode = 1;

		return;
	}

	audio->bfmeStopJZ(mode);

	m_bfmeMode = 1;
}


class BfmeThingKB
{
public:
	void bfmeGoKB(void);

private:
	unsigned char m_bfmeHead[0x14];		// 0x00
	BfmeItemJZ *m_bfmeItem;			// 0x14
	unsigned char m_bfmeGap[0x14];		// 0x18
	unsigned int m_bfmeMode;		// 0x2c
};

void BfmeThingKB::bfmeGoKB(void)
{
	ClientSubsystem *audio = TheAudioClientUpdate;

	if (audio == 0)
		return;

	unsigned int mode = m_bfmeMode;

	if (mode < 5)
		return;

	BfmeItemJZ *item = m_bfmeItem;

	if (item != 0 && item->m_bfmeFlag == 0)
	{
		audio->bfmeStartJZ(1, 1, 0);

		m_bfmeMode = 1;

		return;
	}

	audio->bfmeStopJZ(mode);

	m_bfmeMode = 1;
}
