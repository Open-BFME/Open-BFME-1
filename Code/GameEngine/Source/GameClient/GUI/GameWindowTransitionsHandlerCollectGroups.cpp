// cl: /DNDEBUG /DWIN32 /MD /EHsc
// BFME GameWindowTransitionsHandler list collector at retail 0x0048B690.
// The caller at 0x0059FF70 passes a temporary list head; the receiver is the
// TheTransitionHandler object and its four group pointers are at +0x20..+0x2c.
// The group helper is kept as a TU-local ABI declaration.  Its retail call is
// the existing ILT 0x0000BE97, whose verified body candidate is 0x0048B390.

typedef bool Bool;

struct CRITICAL_SECTION;
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	CRITICAL_SECTION *lock);

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

class TransitionGroup
{
public:
	// Address-derived ABI name: the body copies this group's TransitionWindow
	// list into the caller-owned list head.  Its ILT route is pin-checked.
	void rva0048B390(void *destination);

private:
	Bool m_fireOnce;
	unsigned char m_padding[3];
	void *m_windows;
	int m_directionMultiplier;
};

class GameWindowTransitionsHandler
{
public:
	// Address-derived neutral name; retail has no surviving public declaration
	// for this BFME helper.  The receiver and four source groups are proven by
	// the 0x0059FF70 caller and the handler layout used by sibling methods.
	void rva0048B690(void *destination);

private:
	unsigned char m_padding0[0x20];
	TransitionGroup *m_currentGroup;
	TransitionGroup *m_pendingGroup;
	TransitionGroup *m_drawGroup;
	TransitionGroup *m_secondaryDrawGroup;
	unsigned char m_padding30[4];
	unsigned char m_criticalSection[0x18];
};

// ?rva0048B690@GameWindowTransitionsHandler@@QAEXPAX@Z
void GameWindowTransitionsHandler::rva0048B690(void *destination)
{
	CriticalSectionLock lockGuard(
		reinterpret_cast<CRITICAL_SECTION *>(m_criticalSection));

	if (m_currentGroup)
		m_currentGroup->rva0048B390(destination);
	if (m_pendingGroup)
		m_pendingGroup->rva0048B390(destination);
	if (m_drawGroup)
		m_drawGroup->rva0048B390(destination);
	if (m_secondaryDrawGroup)
		m_secondaryDrawGroup->rva0048B390(destination);
}
