// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/fullfade /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

typedef bool Bool;
typedef int Int;

struct CRITICAL_SECTION;
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION *lock);

class CriticalSectionLock
{
public:
	explicit CriticalSectionLock(CRITICAL_SECTION *lock) : m_lock(lock)
	{
		EnterCriticalSection(m_lock);
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class TransitionGroup
{
public:
	void init(void);
	void reset(void);
	void skip(void);
	void reverse(void);
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
	unsigned char m_padding[7];
	Int m_directionMultiplier;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class GameWindowTransitionsHandler
{
public:
	void setGroup(AsciiString groupName, Bool immediate);
private:
	TransitionGroup *findGroup(AsciiString groupName);
	unsigned char m_padding0[0x20];
	TransitionGroup *m_currentGroup;
	TransitionGroup *m_pendingGroup;
	unsigned char m_padding1[0x0c];
	unsigned char m_criticalSection;
};

void GameWindowTransitionsHandler::setGroup(AsciiString groupName, Bool immediate)
{
	CriticalSectionLock lockGuard(
		reinterpret_cast<CRITICAL_SECTION *>(&m_criticalSection));

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
