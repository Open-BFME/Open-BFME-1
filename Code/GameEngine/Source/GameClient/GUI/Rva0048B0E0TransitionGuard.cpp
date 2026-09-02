// cl: /DNDEBUG /DWIN32 /MD /EHsc

typedef bool Bool;

struct Rva0048B0E0CriticalSection
{
	unsigned char data[24];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	Rva0048B0E0CriticalSection *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	Rva0048B0E0CriticalSection *section);

class Rva0048B0E0Lock
{
public:
	explicit Rva0048B0E0Lock(Rva0048B0E0CriticalSection *section) :
		m_section(section)
	{
		EnterCriticalSection(m_section);
	}

	~Rva0048B0E0Lock()
	{
		LeaveCriticalSection(m_section);
	}

private:
	Rva0048B0E0CriticalSection *m_section;
};

class Rva0048B0E0TransitionHandler
{
public:
	void update(void);
	void waitForTransition(void);

private:
	unsigned char m_padding0[0x34];
	Rva0048B0E0CriticalSection m_section;
	unsigned char m_padding1[8];
	Bool m_updating;
};

void Rva0048B0E0TransitionHandler::update(void)
{
	Rva0048B0E0Lock lock(&m_section);
	if (!m_updating)
	{
		m_updating = true;
		waitForTransition();
		m_updating = false;
	}
}
