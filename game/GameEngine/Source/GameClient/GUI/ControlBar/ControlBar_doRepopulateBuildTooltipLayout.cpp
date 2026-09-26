// cl: /O2 /Ob2 /GR- /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// BFME-layout reconstruction of ControlBar::doRepopulateBuildTooltipLayout.

template <typename T>
class StringBase
{
friend class UnicodeString;

public:
	void *m_data;

private:
	void releaseBuffer();
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>()
	{
		m_data = 0;
	}

	~UnicodeString()
	{
		((StringBase<unsigned short> *)this)->releaseBuffer();
	}
};

class BfmeTooltipWindow
{
public:
	virtual ~BfmeTooltipWindow();
	virtual void slot01();
	virtual void slot02();
	virtual void collectText(UnicodeString &, UnicodeString &, UnicodeString &, UnicodeString &);
	virtual void setVisible(bool);
};

class BfmeTooltipLayout
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void setVisible(bool);
};

class Rva005929E0
{
public:
	void replace(const UnicodeString &, const UnicodeString &, const UnicodeString &, const UnicodeString &);
};

class Glo012F4B98Type
{
public:
	char m_padding[0x488];
	Rva005929E0 m_bfmeSub;
};

extern Glo012F4B98Type *Glo012F4B98;

class ControlBar
{
public:
	void doRepopulateBuildTooltipLayout();

private:
	char m_padding[0x278];
	BfmeTooltipLayout *m_layout;
	char m_paddingAfterLayout[0x2F4 - 0x27C];
	BfmeTooltipWindow *m_window;
};

void ControlBar::doRepopulateBuildTooltipLayout()
{
	if (m_layout == 0 || m_window == 0)
		return;
	BfmeTooltipWindow *window = m_window;

	UnicodeString name;
	UnicodeString cost;
	UnicodeString description;
	UnicodeString requirements;

	window->collectText(name, cost, description, requirements);
	m_layout->setVisible(false);

	if (Glo012F4B98)
		Glo012F4B98->m_bfmeSub.replace(name, cost, description, requirements);
}
