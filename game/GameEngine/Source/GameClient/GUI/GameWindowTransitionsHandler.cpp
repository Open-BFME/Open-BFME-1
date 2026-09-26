// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/fullfade /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

// The four GameWindowTransitionsHandler methods that move a transition group
// in or out of play. They sit together in the image -- 0x0048A320, 0x0048AD80,
// 0x0048AEC0, 0x0048AFE0 -- and every one of them opens by taking the same
// critical section and then works on the same two group pointers:
//
//   update    0x0048A320  300 B  QAE
//   setGroup  0x0048AD80  249 B  QAE
//   reverse   0x0048AEC0  230 B  QAE
//   remove    0x0048AFE0  202 B  QAE
//
// Four files, four handlers. Three of them stopped the object at the critical
// section and called the twelve bytes in front of it m_padding1; the fourth
// named those twelve as m_drawGroup, m_secondaryDrawGroup and four more, and
// then carried on past the lock to the flags at +0x4C. Nothing contradicted
// anything -- the merged run is simply every statement at once:
//
//   +0x20 current group   +0x28 draw group      +0x34 critical section
//   +0x24 pending group   +0x2c secondary draw  +0x4c ... +0x55 the flags
//
// The critical section is 0x18 anonymous bytes here rather than a real
// CRITICAL_SECTION: only one of the four files included <windows.h> for it,
// the other three forward-declared the struct and cast, and the cast is what
// all four now do -- same address, one fewer system header.
//
// findGroup stays PRIVATE here and stays in its own TU, and that is not
// tidiness. Its body is pinned as ?findGroup@...@@QAE... at 0x0048A520, but
// retail's callers reach it through the ILT thunk at 0x00024172, which
// targets/game/reverse/symbols.csv pins under the PRIVATE spelling ?findGroup@...@@AAE...
// So the definition needs the public spelling and these three call sites need
// the private one: one TU cannot supply both, and merging it in would break
// whichever half lost.
//
// That is worth stating next to its opposite, because the two look identical
// until you read the pins and they come out the other way round:
//
//   InGameUI::destroyPlacementIcons  body row IAE at 0x0043AF00
//                                    thunk    QAE at 0x0001EC3B
//     -> MERGES with its caller. The extra spelling is on the THUNK, so the
//        definition keeps the row's own spelling and the call site resolves
//        through the other one. Both halves get what they need.
//        (GameClient/InGameUIBodies.cpp holds the pair.)
//
//   GameWindowTransitionsHandler::findGroup   body row QAE at 0x0048A520
//                                             thunk    AAE at 0x00024172
//     -> DOES NOT merge. The extra spelling is on the BODY side of what the
//        callers need: the definition must be QAE to exist at all, but a
//        caller in the same TU then emits QAE too and resolves to the body
//        address, where retail's displacement points at the thunk.
//
// Same shape, opposite answers, and the discriminator is which SIDE the extra
// spelling sits on -- not whether one exists. Read both pins before merging a
// callee into its caller's TU.

typedef bool Bool;
typedef int Int;

struct CRITICAL_SECTION;
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION *lock);

// Both constructors are real. Three of the four bodies hand the lock over as a
// pointer and take it with EnterCriticalSection(m_lock); reverse hands it over
// as a reference and takes it with EnterCriticalSection(&lock), and that is not
// a spelling difference -- built through the pointer form, reverse parks the
// lock address in ebp where retail uses ebx, and every push and reload around
// it shifts with it. Each call site keeps the form its own bytes prove.
class CriticalSectionLock
{
public:
	explicit CriticalSectionLock(CRITICAL_SECTION *lock) : m_lock(lock)
	{
		EnterCriticalSection(m_lock);
	}
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

template <typename T> class StringBase
{
friend class AsciiString;
private:
	StringBase(const StringBase<T> &other);
	void releaseBuffer(void);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->StringBase<char>::releaseBuffer();
	}
	Bool isEmpty(void) const
	{
		return m_data == 0 || *(unsigned short *)(m_data + 4) == 0;
	}
private:
	char *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class TransitionGroup
{
public:
	void init(void);
	void reset(void);
	void skip(void);
	void reverse(void);
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
	Bool m_fireOnce;					// +0x00
	unsigned char m_pad[3];
	void *m_windows;					// +0x04
	Int m_directionMultiplier;				// +0x08
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
	virtual void *appendMessage(unsigned int type) = 0;	// slot 13, vtable+0x34
};

extern MessageStream *TheMessageStream;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class GameWindowTransitionsHandler
{
public:
	void update(void);
	void setGroup(AsciiString groupName, Bool immediate);
	void reverse(AsciiString groupName);
	void remove(AsciiString groupName, Bool skipPending);

private:
	// Private on purpose -- see the note at the top.
	TransitionGroup *findGroup(AsciiString groupName);

	unsigned char m_padding0[0x20];
	TransitionGroup *m_currentGroup;			// +0x20
	TransitionGroup *m_pendingGroup;			// +0x24
	TransitionGroup *m_drawGroup;				// +0x28
	TransitionGroup *m_secondaryDrawGroup;			// +0x2c
	unsigned char m_pad30[4];
	unsigned char m_criticalSection[0x18];			// +0x34
	bool m_unknown4C;					// +0x4c
	bool m_notifyWhenIdle;					// +0x4d
	int m_unknown50;					// +0x50
	bool m_unknown54;					// +0x54
	bool m_holdFireOnce;					// +0x55
};

// ?update@GameWindowTransitionsHandler@@QAEXXZ
// Retail 0x0048A320, 300 bytes. ZH twin plus BFME's critical section, the
// reset-on-discard of the secondary draw group, the +0x55 fireOnce hold and
// the MessageStream(0x6D) it appends when it goes idle.
void GameWindowTransitionsHandler::update(void)
{
	TransitionGroup *current;
	CriticalSectionLock lockGuard(
		reinterpret_cast<CRITICAL_SECTION *>(m_criticalSection));

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

// ?setGroup@GameWindowTransitionsHandler@@QAEXVAsciiString@@_N@Z
// Retail 0x0048AD80, 249 bytes.
void GameWindowTransitionsHandler::setGroup(AsciiString groupName, Bool immediate)
{
	CriticalSectionLock lockGuard(
		reinterpret_cast<CRITICAL_SECTION *>(m_criticalSection));

	if (groupName.isEmpty() && immediate)
	{
		if (m_currentGroup)
		{
			m_currentGroup->reset();
			m_currentGroup = 0;
		}
	}
	if (immediate && m_currentGroup)
	{
		m_currentGroup->skip();
		m_currentGroup = findGroup(groupName);
		if (m_currentGroup)
			m_currentGroup->init();
		return;
	}

	if (m_currentGroup)
	{
		if (!m_currentGroup->isFireOnce() && !m_currentGroup->isReversed())
			m_currentGroup->reverse();
		m_pendingGroup = findGroup(groupName);
		if (m_pendingGroup)
			m_pendingGroup->init();
		return;
	}

	m_currentGroup = findGroup(groupName);
	if (m_currentGroup)
		m_currentGroup->init();
}

// ?reverse@GameWindowTransitionsHandler@@QAEXVAsciiString@@@Z
// Retail 0x0048AEC0, 230 bytes.
void GameWindowTransitionsHandler::reverse(AsciiString groupName)
{
	TransitionGroup *group;
	CriticalSectionLock lockGuard(
		*reinterpret_cast<CRITICAL_SECTION *>(&m_criticalSection));

	group = findGroup(groupName);
	if (group && m_currentGroup == group)
	{
		m_currentGroup->reverse();
	}
	else if (group && m_pendingGroup == group)
	{
		m_pendingGroup->reset();
		m_pendingGroup = 0;
	}
	else if (group)
	{
		if (m_currentGroup)
		{
			m_currentGroup->skip();
			m_currentGroup->reset();
		}
		if (m_pendingGroup)
		{
			m_pendingGroup->skip();
			m_pendingGroup->reset();
			m_pendingGroup = 0;
		}

		m_currentGroup = group;
		m_currentGroup->init();
		m_currentGroup->skip();
		m_currentGroup->reverse();
	}
}

// ?remove@GameWindowTransitionsHandler@@QAEXVAsciiString@@_N@Z
// Retail 0x0048AFE0, 202 bytes.
void GameWindowTransitionsHandler::remove(AsciiString groupName, Bool skipPending)
{
	CriticalSectionLock lockGuard(
		reinterpret_cast<CRITICAL_SECTION *>(m_criticalSection));

	TransitionGroup *g = findGroup(groupName);
	if (g)
	{
		if (m_pendingGroup == g)
		{
			if (skipPending)
				m_pendingGroup->skip();
			m_pendingGroup->reset();
			m_pendingGroup = 0;
		}
		if (m_currentGroup == g)
		{
			m_currentGroup->skip();
			m_currentGroup->reset();
			m_currentGroup = 0;
			if (m_pendingGroup)
				m_currentGroup = m_pendingGroup;
		}
	}
}
