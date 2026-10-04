// BuddyThreadClass constructor at retail RVA 0x0063C4F0.

namespace _STL
{

template <class Char>
class char_traits;

template <class Char>
class allocator;

template <class Char, class Traits, class Allocator>
class basic_string
{
public:
	basic_string();
	~basic_string();

private:
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

}

// Kept: the five member constructions below are compiler-generated, not a
// source-level call, so no spelling names the ILT directly. The union/member
// pointer recipe reaches ?j_0004048a@@YAXXZ but drops the per-call EH state
// stores and the member-init ordering, and an inline forwarding constructor
// would define the STLport ctor in this TU over the matched 0x004D4F40 body.
#pragma comment(linker, "/alternatename:??0?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ=?j_0004048a@@YAXXZ")

class BFMENetworkLock;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/thread.h
// The base of BuddyThreadClass is the WWLib thread base; its one-argument
// constructor is defined once, in ThreadClassLifecycle.cpp.
class ThreadClass
{
public:
	ThreadClass(const char *name);
	virtual ~ThreadClass();
	virtual void Execute();
	virtual void Thread_Function() = 0;

private:
	char m_name[0x40];
	void *m_auxHandle;
	void *m_liveHandle;
	int m_priority;
};

class CriticalSectionClass
{
public:
	CriticalSectionClass();
	~CriticalSectionClass();

	// The old BuddyOwnedLock slot at +0xa8 is a sentry LockClass: retail
	// stores a null pointer there in the constructor and the generated
	// destructor calls LockClass's own destructor on it.
	class LockClass
	{
	public:
		LockClass() : m_lock(0) {}
		LockClass(CriticalSectionClass &criticalSection);
		~LockClass();

		LockClass *m_lock;
	};

private:
	char m_body[8];
};

class BuddyThreadClass : public ThreadClass
{
public:
	BuddyThreadClass(BFMENetworkLock *lock);
	virtual void Thread_Function();

private:
	bool m_isNewAccount;
	bool m_isConnecting;
	bool m_isConnected;
	int m_profileID;
	int m_lastErrorCode;
	bool m_isDeleting;
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > m_nick;
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > m_email;
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > m_password;
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > m_status;
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > m_error;
	BFMENetworkLock *m_networkLock;
	CriticalSectionClass m_criticalSection;
	CriticalSectionClass::LockClass m_ownedLock;
};

BuddyThreadClass::BuddyThreadClass(BFMENetworkLock *lock) :
	ThreadClass(0),
	m_networkLock(lock),
	m_criticalSection()
{
	m_isNewAccount = m_isDeleting = m_isConnecting = m_isConnected = false;
	m_profileID = 0;
	m_lastErrorCode = 0;
	CriticalSectionClass::LockClass *ownedLock =
		new CriticalSectionClass::LockClass(m_criticalSection);
	CriticalSectionClass::LockClass *const oldLock = m_ownedLock.m_lock;
	if (ownedLock != oldLock)
	{
		if (oldLock)
			delete oldLock;
		m_ownedLock.m_lock = ownedLock;
	}
}
