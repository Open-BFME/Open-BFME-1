// cl: /DNDEBUG /DWIN32 /MD /EHsc
// GameWindowTransitionsHandler::update. ZH twin plus BFME critical section,
// reset-on-discard, +0x55 fireOnce guard, +0x4D MessageStream(0x6D).

typedef bool Bool;
typedef int Int;

struct CRITICAL_SECTION;
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION *lock);

class CriticalSectionLock
{
public:
	explicit CriticalSectionLock(CRITICAL_SECTION &lock) : m_lock(&lock)
	{
		EnterCriticalSection(&lock);
	}
	~CriticalSectionLock()
	{
		LeaveCriticalSection(m_lock);
	}
private:
	CRITICAL_SECTION *m_lock;
};

class TransitionGroup
{
public:
	void reset(void);
	void update(void);
	Bool isFinished(void);
	Bool isFireOnce(void) const
	{
		return m_fireOnce;
	}
	Bool isReversed(void) const
	{
		return m_directionMultiplier < 0;
	}
private:
	Bool m_fireOnce;
	unsigned char m_pad[3];
	void *m_windows;
	Int m_directionMultiplier;
};

class MessageStream
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void *appendMessage(unsigned int type) = 0;
};

extern MessageStream *TheMessageStream;

class GameWindowTransitionsHandler
{
public:
	void update(void);
private:
	unsigned char m_padding0[0x20];
	TransitionGroup *m_currentGroup;
	TransitionGroup *m_pendingGroup;
	TransitionGroup *m_drawGroup;
	TransitionGroup *m_secondaryDrawGroup;
	unsigned char m_pad30[4];
	unsigned char m_criticalSection[0x18];
	bool m_unknown4C;
	bool m_notifyWhenIdle;
	int m_unknown50;
	bool m_unknown54;
	bool m_holdFireOnce;
};

void GameWindowTransitionsHandler::update(void)
{
	TransitionGroup *current;
	CriticalSectionLock lockGuard(
		*reinterpret_cast<CRITICAL_SECTION *>(m_criticalSection));

	if (m_drawGroup != m_currentGroup)
	{
		if (m_secondaryDrawGroup)
			m_secondaryDrawGroup->reset();
		m_secondaryDrawGroup = m_drawGroup;
	}
	else
	{
		if (m_secondaryDrawGroup)
		{
			m_secondaryDrawGroup->reset();
			m_secondaryDrawGroup = 0;
		}
	}

	current = m_currentGroup;
	m_drawGroup = current;
	if (current && !current->isFinished())
		current->update();

	current = m_currentGroup;
	if (current && current->isFinished() && current->isFireOnce())
	{
		if (!m_pendingGroup)
		{
			if (m_holdFireOnce)
				return;
			current->reset();
			m_currentGroup = 0;
		}
	}

	current = m_currentGroup;
	if (current && m_pendingGroup && current->isFinished())
	{
		current->reset();
		m_currentGroup = m_pendingGroup;
		m_pendingGroup = 0;
	}

	if (!m_currentGroup && m_pendingGroup)
	{
		m_currentGroup = m_pendingGroup;
		m_pendingGroup = 0;
	}

	current = m_currentGroup;
	if (current && current->isFinished() && current->isReversed())
		m_currentGroup = 0;

	if (m_notifyWhenIdle && !m_currentGroup && !m_pendingGroup)
	{
		TheMessageStream->appendMessage(0x6D);
		m_notifyWhenIdle = 0;
	}
}
