// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class DisplayString;

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	char m_body[4];
};

class AsciiString
{
public:
	~AsciiString();

private:
	char m_body[4];
};

class UnicodeString
{
public:
	~UnicodeString();

private:
	char m_body[4];
};

class CursorInfo
{
public:
	~CursorInfo();

private:
	char m_body[0x54];
};

class DisplayStringManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void freeDisplayString(DisplayString *string);
};

extern DisplayStringManager *TheDisplayStringManager;

class Mouse : public SubsystemInterface
{
public:
	virtual ~Mouse(void);

private:
	CursorInfo m_cursorInfo[50];
	AsciiString m_tooltipFontName;
	char m_pad0[0x10fc - 0x1074];
	UnicodeString m_tooltipState;
	UnicodeString m_tooltipString;
	UnicodeString m_cursorText;
	char m_pad1[0x4dac - 0x1108];
	DisplayString *m_cursorTextDisplayString;
};

Mouse::~Mouse(void)
{
	if (m_cursorTextDisplayString)
		TheDisplayStringManager->freeDisplayString(m_cursorTextDisplayString);
	m_cursorTextDisplayString = 0;
}
