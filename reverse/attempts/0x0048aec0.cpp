// ?reverse@GameWindowTransitionsHandler@@QAEXVAsciiString@@@Z
// partial score=0.97 date=2026-09-01
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/asciistringsetoutofline /Ireference/shims/fullfade /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4

#include "PreRTS.h"
#include "GameClient/GameWindowTransitions.h"

class BFMETransitionGroupView
{
public:
	void init();
	void reset();
	void reverse();
	void skip();
};

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &);
	~BfmeStringArgBase();
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}
	~BfmeAsciiStringArg();

private:
	char *m_text;
};

class BFMETransitionHandler
{
public:
	TransitionGroup *findGroup(BfmeAsciiStringArg groupName);
};

class BFMETransitionLock
{
	public:
	explicit BFMETransitionLock(CRITICAL_SECTION &lock) : m_lock(lock)
	{
		EnterCriticalSection(&m_lock);
	}

	~BFMETransitionLock()
	{
		LeaveCriticalSection(&m_lock);
	}

	private:
	CRITICAL_SECTION &m_lock;
};

void GameWindowTransitionsHandler::reverse(AsciiString groupName)
{
	unsigned char *rawThis = reinterpret_cast<unsigned char *>(this);
	TransitionGroup *&currentGroup = *reinterpret_cast<TransitionGroup **>(rawThis + 0x20);
	TransitionGroup *&pendingGroup = *reinterpret_cast<TransitionGroup **>(rawThis + 0x24);

	BFMETransitionLock guard(*reinterpret_cast<CRITICAL_SECTION *>(rawThis + 0x34));
	TransitionGroup *group = reinterpret_cast<BFMETransitionHandler *>(this)->findGroup(groupName);
	if (group && currentGroup == group)
	{
		reinterpret_cast<BFMETransitionGroupView *>(currentGroup)->reverse();
	}
	else if (group && pendingGroup == group)
	{
		reinterpret_cast<BFMETransitionGroupView *>(pendingGroup)->reset();
		pendingGroup = NULL;
	}
	else if (group)
	{
		if (currentGroup)
		{
			reinterpret_cast<BFMETransitionGroupView *>(currentGroup)->skip();
			reinterpret_cast<BFMETransitionGroupView *>(currentGroup)->reset();
		}
		if (pendingGroup)
		{
			reinterpret_cast<BFMETransitionGroupView *>(pendingGroup)->skip();
			reinterpret_cast<BFMETransitionGroupView *>(pendingGroup)->reset();
			pendingGroup = NULL;
		}

		currentGroup = group;
		reinterpret_cast<BFMETransitionGroupView *>(currentGroup)->init();
		reinterpret_cast<BFMETransitionGroupView *>(currentGroup)->skip();
		reinterpret_cast<BFMETransitionGroupView *>(currentGroup)->reverse();
	}
}
