// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	int x;
	int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const char *);
	~AsciiString();

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	int winGetSize(int *, int *);
	int winGetScreenPosition(int *, int *);
};

class Image;

class MappedImageCollection
{
public:
	const Image *findImageByName(const AsciiString &);
};

extern MappedImageCollection *TheMappedImageCollection;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class Transition
{
public:
	virtual ~Transition();
	virtual void init(GameWindow *) = 0;
	virtual void update(int) = 0;
	virtual void reverse() = 0;
	virtual void draw() = 0;
	virtual void skip() = 0;

protected:
	int m_frameLength;
	bool m_isFinished;
	bool m_isForward;
	bool m_isReversed;
	unsigned char m_pad0b;
	GameWindow *m_win;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class ButtonFlashTransition : public Transition
{
public:
	virtual void init(GameWindow *);

protected:
	ICoord2D m_pos;
	ICoord2D m_size;
	int m_drawState;
	const Image *m_gradient;
};

// ?init@ButtonFlashTransition@@UAEXPAVGameWindow@@@Z
void ButtonFlashTransition::init(GameWindow *win)
{
	if (win) {
		m_win = win;
		m_win->winGetSize(&m_size.x, &m_size.y);
		m_win->winGetScreenPosition(&m_pos.x, &m_pos.y);
	}
	m_isForward = false;
	update(0);
	m_isFinished = false;
	m_isForward = true;
	AsciiString gradient("Gradient");
	m_gradient = TheMappedImageCollection->findImageByName(gradient);
}
