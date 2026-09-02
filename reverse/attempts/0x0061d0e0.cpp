// ?bfmeConfigure@BfmeConfigureRect@@QAEXHHHHH@Z
// partial score=0.34 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

class BfmeConfigureRect
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeApply(void);

	void bfmeConfigure(int left, int right, int top, int bottom, int value);

private:
	unsigned char m_beforeMode[0x20];
	int m_mode;
	int m_unused28;
	int m_width;
	int m_zero30;
	int m_left;
	int m_right;
	int m_top;
	int m_bottom;
	int m_zero44;
	int m_value;
};

void BfmeConfigureRect::bfmeConfigure(
	int left, int right, int top, int bottom, int value)
{
	m_value = value;
	m_right = right;
	m_top = top;
	int width = right - left;
	m_left = left;
	m_mode = 3;
	m_zero44 = 0;
	m_bottom = bottom;
	m_width = width;
	m_zero30 = 0;
	bfmeApply();
}
