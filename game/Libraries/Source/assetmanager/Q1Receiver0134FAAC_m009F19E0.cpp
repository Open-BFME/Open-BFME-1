// ?m009F19E0@Q1Receiver0134FAAC@@QAEXH@Z
// cl: /DNDEBUG /MD /EHsc

struct Q1ReceiverState
{
	unsigned char m_lock[0x1C];
	unsigned char m_unmodelled[0x114];
};

class BfmeThingBVA
{
	public:
	unsigned char m_unmodelled_000[0x0C];
	int m_value;
	bool m_active;

	void bfmeStepBVA(BfmeThingBVA *other);
	void set_value(int value)
	{
		m_value = value;
	}
};

struct CRITICAL_SECTION;
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	CRITICAL_SECTION *lock);

class Q1Receiver0134FAAC
{
public:
	void m009F19E0(int source);
	void refresh(void);

private:
	unsigned char m_unmodelled_000[0x60];
	Q1ReceiverState m_state;
	BfmeThingBVA m_record;
};

class CriticalSectionLock
{
public:
	explicit CriticalSectionLock(int state) : m_state(state)
	{
		EnterCriticalSection((CRITICAL_SECTION *)m_state);
	}
	~CriticalSectionLock()
	{
		LeaveCriticalSection((CRITICAL_SECTION *)m_state);
	}

	int m_state;
};

typedef void (Q1Receiver0134FAAC::*Q1ReceiverRefreshMethod)(void);

void Q1Receiver0134FAAC::m009F19E0(int source)
{
	CriticalSectionLock lock((int)&m_state);
	BfmeThingBVA *record = &m_record;
	BfmeThingBVA &source_record = *(BfmeThingBVA *)(unsigned int)source;

	if (record != &source_record)
	{
		record->bfmeStepBVA(&source_record);
		record->m_active = true;
		record->set_value(source_record.m_value);
	}
	this->refresh();
}
