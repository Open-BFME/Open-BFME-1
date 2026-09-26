// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// BFMETransitionGroup destructor at retail 0x0048AB20. The constructor at
// 0x0048AAD0 and setName at 0x00489B60 identify the group and its list.

// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>

struct AsciiStringData
{
	int m_refCount;
	int m_length;
	char m_text[1];
};

class AsciiString;

template <typename T> class StringBase
{
private:
	friend class AsciiString;
	~StringBase();

	AsciiStringData *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	~AsciiString() {}
};

class Transition
{
public:
	virtual ~Transition();
	virtual void init(void *);
	virtual void update(int);
	virtual void reverse(void);
	virtual void draw(void);
	virtual void skip(void);

protected:
	int m_frameLength;
	bool m_isFinished;
	bool m_isForward;
	bool m_isReversed;
	void *m_win;
};

class TransitionWindow
{
public:
	~TransitionWindow()
	{
		m_win = 0;
		if (m_transition)
			delete m_transition;
		m_transition = 0;
	}

private:
	AsciiString m_winName;
	int m_frameDelay;
	unsigned int m_winID;
	void *m_win;
	Transition *m_transition;
	int m_currentFrameDelay;
};

class BFMETransitionGroup
{
public:
	~BFMETransitionGroup();

private:
	bool m_fireOnce;
	unsigned char m_padding[3];
	_STL::list<TransitionWindow *> m_transitionWindowList;
	int m_directionMultiplier;
	int m_currentFrame;
	AsciiString m_name;
};

// ??1BFMETransitionGroup@@QAE@XZ
BFMETransitionGroup::~BFMETransitionGroup()
{
	_STL::list<TransitionWindow *>::iterator it = m_transitionWindowList.begin();
	while (it != m_transitionWindowList.end())
	{
		TransitionWindow *tWin = *it;
		delete tWin;
		it = m_transitionWindowList.erase(it);
	}
}
