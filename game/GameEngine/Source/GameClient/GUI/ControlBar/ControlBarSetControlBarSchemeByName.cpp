// cl: /DNDEBUG /MD /EHsc
// Clean reconstruction of the BFME ControlBar scheme selector.

template <typename T> class StringBase
{
private:
	StringBase(const StringBase<T> &other);
	~StringBase();
	void *m_data;
	friend class AsciiString;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class ControlBarSchemeManager
{
public:
	void setControlBarScheme(AsciiString name);
};

enum RecorderModeType { RECORDERMODE_PLAYBACK = 1 };

class RecorderClass
{
public:
	RecorderModeType getMode();
};

extern RecorderClass *TheRecorder;

class ControlBar
{
public:
	void setControlBarSchemeByName(const AsciiString &name);

protected:
	void setDefaultControlBarConfig();

private:
	unsigned char m_unmodelled[0x30];
	ControlBarSchemeManager *m_controlBarSchemeManager;
};

void ControlBar::setControlBarSchemeByName(const AsciiString &name)
{
	if (m_controlBarSchemeManager != 0) {
		m_controlBarSchemeManager->setControlBarScheme(name);

		if (TheRecorder == 0 || TheRecorder->getMode() != RECORDERMODE_PLAYBACK)
			setDefaultControlBarConfig();
	}
}
