// cl: /EHs-c-

class SkirmishScreenOwner
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1C(void) = 0;
	virtual void slot20(void) = 0;
	virtual bool bfmeAccept(void *value) = 0;
};

class BfmeThingBPF
{
public:
	void bfmeGoBPF(void *value, void *context);
};

class SkirmishScreenState
{
public:
	bool flushPendingUpdates(void);
	void bfmeFlush11(void);
	void refreshAllPlayerControls(void);
	void bfmeFlush15(void);
	void bfmeFlush10(void);
	void bfmeFlush12(void);
	void applySecondaryGame(void);

private:
	unsigned char m_unmodelled00[4];
	SkirmishScreenOwner *m_owner;
	void *m_first;
	void *m_second;
	bool m_flag10;
	bool m_flag11;
	bool m_flag12;
	bool m_flag13;
	bool m_flag14;
	bool m_flag15;
	bool m_enabled;
	unsigned char m_unmodelled17[0x11];
	BfmeThingBPF m_bpf;
};

// Clear each pending flag and dispatch its corresponding refresh operation.
// ?flushPendingUpdates@SkirmishScreenState@@QAE_NXZ
bool SkirmishScreenState::flushPendingUpdates(void)
{
	bool changed = false;
	if (m_enabled)
		return changed;

	if (m_flag11)
	{
		m_flag11 = false;
		bfmeFlush11();
		changed = true;
	}
	if (m_flag14)
	{
		m_flag14 = false;
		refreshAllPlayerControls();
		changed = true;
	}
	if (m_flag15)
	{
		m_flag15 = false;
		bfmeFlush15();
		changed = true;
	}
	if (m_flag10)
	{
		m_flag10 = false;
		bfmeFlush10();
		changed = true;
	}
	if (m_flag12)
	{
		m_flag12 = false;
		bfmeFlush12();
		changed = true;
	}
	if (m_flag13)
	{
		m_flag13 = false;
		applySecondaryGame();
		changed = true;
	}
	return changed;
}

// Validate the two pending objects and forward the surviving secondary object
// through the embedded BPF helper.
// ?applySecondaryGame@SkirmishScreenState@@QAEXXZ
void SkirmishScreenState::applySecondaryGame(void)
{
	if (m_first && !m_owner->bfmeAccept(m_first))
		m_first = 0;

	if (m_second && !m_owner->bfmeAccept(m_second))
		m_second = 0;

	if (m_second)
		m_bpf.bfmeGoBPF(m_second, 0);
}
