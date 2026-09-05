// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/fullfade /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

typedef bool Bool;

#include <windows.h>

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
private:
	char *m_data;
};

class TransitionGroup
{
public:
	void skip(void);
	void reset(void);
};

class GameWindowTransitionsHandler
{
public:
	void remove(AsciiString groupName, Bool skipPending);
private:
	TransitionGroup *findGroup(AsciiString groupName);
	unsigned char m_padding0[0x20];
	TransitionGroup *m_currentGroup;
	TransitionGroup *m_pendingGroup;
	unsigned char m_padding1[0x0c];
	CRITICAL_SECTION m_criticalSection;
};

void GameWindowTransitionsHandler::remove(AsciiString groupName, Bool skipPending)
{
	CriticalSectionLock lockGuard(
		&m_criticalSection);

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
