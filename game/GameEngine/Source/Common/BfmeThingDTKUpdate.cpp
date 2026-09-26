// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct BfmeThingDTKConfig
{
	unsigned char m_pad0[0x294];
	unsigned char m_enabled;
};

class BfmeThingDTK
{
public:
	virtual void slot00(void) = 0; virtual void slot04(void) = 0;
	virtual void slot08(void) = 0; virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0; virtual void slot14(void) = 0;
	virtual void slot18(void) = 0; virtual void slot1C(void) = 0;
	virtual void slot20(void) = 0; virtual void slot24(void) = 0;
	virtual void slot28(void) = 0; virtual void slot2C(void) = 0;
	virtual void slot30(void) = 0; virtual void slot34(void) = 0;
	virtual void slot38(void) = 0; virtual void slot3C(void) = 0;
	virtual void slot40(void) = 0; virtual void slot44(void) = 0;
	virtual void slot48(void) = 0; virtual void slot4C(void) = 0;
	virtual void slot50(void) = 0; virtual void slot54(void) = 0;
	virtual void slot58(void) = 0; virtual void slot5C(void) = 0;
	virtual void slot60(void) = 0; virtual void slot64(void) = 0;
	virtual void slot68(void) = 0;

	void update(void);
	void bfmeTailDTK(void);

private:
	unsigned char m_pad4[8];
	BfmeThingDTKConfig *m_config;
	unsigned char m_active;
	unsigned char m_pad11[3];
	int m_startCountdown;
	unsigned char m_pad18[0x0C];
	int m_periodicCountdown;
};

void BfmeThingDTK::update(void)
{
	if (!m_config->m_enabled)
		return;

	if (!m_active && --m_startCountdown <= 0) {
		m_active = 1;
		m_periodicCountdown = 0;
	}

	if (--m_periodicCountdown < 1) {
		bfmeTailDTK();
		if (m_active)
			slot68();
		m_periodicCountdown = 25;
	}
}
