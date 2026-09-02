// cl: /EHs-c-

class Gen0052AD00
{
public:
	bool bfmeFlushFlags(void);
	void bfmeFlush11(void);
	void bfmeFlush14(void);
	void bfmeFlush15(void);
	void bfmeFlush10(void);
	void bfmeFlush12(void);
	void bfmeFlush13(void);

private:
	unsigned char m_unmodelled[0x10];
	bool m_flag10;
	bool m_flag11;
	bool m_flag12;
	bool m_flag13;
	bool m_flag14;
	bool m_flag15;
	bool m_enabled;
};

// Clear each pending flag and dispatch its corresponding refresh operation.
// ?bfmeFlushFlags@Gen0052AD00@@QAE_NXZ
bool Gen0052AD00::bfmeFlushFlags(void)
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
		bfmeFlush14();
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
		bfmeFlush13();
		changed = true;
	}
	return changed;
}
