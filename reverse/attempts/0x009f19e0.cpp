// ?m009F19E0@Q1Receiver0134FAAC@@QAEXH@Z
// partial score=0.88 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Q1Receiver0134FAAC::m009F19E0, retail 0x009F19E0, 117 bytes.

struct Q1ReceiverState
{
	unsigned char m_lock[0x1C];
	unsigned char m_unmodelled[0x114];
};

struct Q1ReceiverRecord
{
	unsigned char m_unmodelled_000[0x0C];
	volatile int m_value;
	bool m_active;

	void copy_from(const Q1ReceiverRecord *source);
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	void *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	void *lock);

class Q1Receiver0134FAAC
{
public:
	void m009F19E0(Q1ReceiverRecord &source);
	void refresh(void);

	private:
	unsigned char m_unmodelled_000[0x60];
	Q1ReceiverState m_state;
	Q1ReceiverRecord m_record;
};

class Q1ReceiverLockGuard
{
public:
	explicit Q1ReceiverLockGuard(void *state) : m_state(state)
	{
		EnterCriticalSection(m_state);
	}
	~Q1ReceiverLockGuard()
	{
		LeaveCriticalSection(m_state);
	}

	void *m_state;
};

void Q1Receiver0134FAAC::m009F19E0(Q1ReceiverRecord &source)
{
	Q1ReceiverRecord *source_pointer = &source;
	void *state = &m_state;
	Q1ReceiverLockGuard lock(state);
	Q1ReceiverRecord *record = &m_record;

	if (record != source_pointer)
	{
		record->copy_from(source_pointer);
		record->m_active = true;
		record->m_value = source_pointer->m_value;
		this->refresh();
	}
}
