// ?m009F0CC0@Q1Receiver0134FAAC@@QAEXH@Z
// cl: /DNDEBUG /MD /EHsc

struct Q1ReceiverState009F0CC0
{
	unsigned char m_lock[0x1C];
	unsigned char m_unmodelled[0x13C];
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
	void m009F0CC0(int source);
	void refresh(void);

private:
	unsigned char m_unmodelled_000[0x60];
	Q1ReceiverState009F0CC0 m_state;
	BfmeThingBVA m_record;
};

class CriticalSectionLock009F0CC0
{
public:
	explicit CriticalSectionLock009F0CC0(int state) : m_state(state)
	{
		EnterCriticalSection((CRITICAL_SECTION *)m_state);
	}
	~CriticalSectionLock009F0CC0()
	{
		LeaveCriticalSection((CRITICAL_SECTION *)m_state);
	}

	int m_state;
};

void Q1Receiver0134FAAC::m009F0CC0(int source)
{
	CriticalSectionLock009F0CC0 lock((int)&m_state);
	BfmeThingBVA *record = &m_record;
	BfmeThingBVA &source_record =
		*(BfmeThingBVA *)(unsigned int)source;

	if (record != &source_record)
	{
		record->bfmeStepBVA(&source_record);
		record->m_active = true;
		record->set_value(source_record.m_value);
	}
	this->refresh();
}
