// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Glo00EF3330::h004893E0, retail 0x004893E0, 31 bytes.
//
// A counter bumped under the object's own critical section: the section is at
// this+0x34 and the count at this+0x30, and both calls go through the import
// table, so they are indirect.
//
// The increment is scheduled between the two calls, and its address is kept in
// edi across both because the same pointer is the argument to each.

struct BfmeCriticalSection
{
	unsigned char m_unmodelled_000[0x18];			// sizeof(CRITICAL_SECTION)
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(BfmeCriticalSection *cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(BfmeCriticalSection *cs);

extern void j_00043c57(void);

typedef int Int;

class Glo00EF3330
{
public:
	void h004893E0(void);
	void h00489410(void);

private:
	unsigned char m_unmodelled_000[0x30];
	Int m_count;						// this+0x30
	BfmeCriticalSection m_section;				// this+0x34
};

void Glo00EF3330::h004893E0(void)
{
	EnterCriticalSection(&m_section);
	++m_count;
	LeaveCriticalSection(&m_section);
}

class CriticalSectionLock
{
public:
	explicit CriticalSectionLock(BfmeCriticalSection *section) : m_section(section)
	{
		EnterCriticalSection(m_section);
	}

	~CriticalSectionLock()
	{
		LeaveCriticalSection(m_section);
	}

private:
	BfmeCriticalSection *m_section;
};

void Glo00EF3330::h00489410(void)
{
	CriticalSectionLock lockGuard(&m_section);
	if (--m_count <= 0)
		j_00043c57();
}
