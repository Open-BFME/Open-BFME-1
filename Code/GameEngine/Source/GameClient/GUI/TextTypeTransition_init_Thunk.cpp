// cl: /DNDEBUG /MD /EHsc
// readable body of ?init@TextTypeTransition@@UAEXPAVGameWindow@@@Z: Code/GameEngine/Source/GameClient/GUI/GameWindowTransitionsStyles.cpp
typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString();
	UnicodeString(const UnicodeString &source);
	~UnicodeString();
	void set(const UnicodeString &source);
	UnicodeString &operator=(const UnicodeString &source)
	{
		set(source);
		return *this;
	}
	Int getLength() const
	{
		return m_data ? *reinterpret_cast<const unsigned short *>(
			reinterpret_cast<const unsigned char *>(m_data) + 4) : 0;
	}
private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	Int winGetSize(Int *width, Int *height);
	Int winGetScreenPosition(Int *x, Int *y);
};

class DisplayString;
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayStringManager.h
class DisplayStringManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual DisplayString *newDisplayString();
};
extern DisplayStringManager *TheDisplayStringManager;

UnicodeString GadgetStaticTextGetText(GameWindow *window);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class TextTypeTransition
{
public:
	virtual ~TextTypeTransition();
	virtual void init(GameWindow *window);
	virtual void update(Int frame);
private:
	Int m_frameLength;
	bool m_isFinished;
	bool m_isForward;
	unsigned char m_pad0a[2];
	GameWindow *m_win;
	Int m_startFrame;
	Int m_endFrame;
	ICoord2D m_pos;
	ICoord2D m_size;
	Int m_drawState;
	UnicodeString m_fullText;
	UnicodeString m_partialText;
	DisplayString *m_dStr;
};

void TextTypeTransition::init(GameWindow *window)
{
	if (window)
	{
		m_win = window;
		m_win->winGetSize(&m_size.x, &m_size.y);
		m_win->winGetScreenPosition(&m_pos.x, &m_pos.y);
	}
	m_isForward = false;
	update(m_startFrame);
	m_isFinished = false;
	m_isForward = true;
	m_dStr = TheDisplayStringManager->newDisplayString();
	m_fullText = GadgetStaticTextGetText(m_win);
	Int length = m_fullText.getLength();
	m_frameLength = length < m_endFrame ? length : m_endFrame;
}
