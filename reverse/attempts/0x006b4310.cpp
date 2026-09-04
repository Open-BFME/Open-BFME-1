// ?update006B4310@Rva006B4310Owner@@QAEXABVAsciiString@@HH@Z
// partial score=0.97 date=2026-09-03
// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Mutex-guarded three-argument entry update in the 0x006B3C50 owner family.
// Best: 157/156, sub esp 8 + C6 stack-owned match clear006B44A0 Guard shape.
// Wall: mutex in eax not edi; 3 args steal callee-saved so ReleaseMutex reloads
// from stack after pops (+1B). Same MutexGuard lands 2-arg siblings.

class AsciiString;

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

class Rva006B4310MutexGuard
{
public:
	explicit Rva006B4310MutexGuard(void *handle)
		: m_handle(handle), m_owned(0)
	{
		if (WaitForSingleObject(m_handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva006B4310MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

class Rva006B4310Entry
{
public:
	void initialize(const AsciiString &first, int second);

private:
	char m_data[0x1c4];
};

class Rva006B4310Owner
{
public:
	void update006B4310(const AsciiString &first, int second, int index);
	void finalize(const AsciiString &first, int second, int third);

private:
	char m_padb8[0xb8];
	Rva006B4310Entry m_entries[4];
	char m_padend[0x95c - (0xb8 + 4 * 0x1c4)];
	void *m_mutex;
};

void Rva006B4310Owner::update006B4310(
	const AsciiString &first, int second, int index)
{
	Rva006B4310Owner *self = this;
	register void *handle = self->m_mutex;
	Rva006B4310MutexGuard guard(handle);
	register int indexLocal = index;
	register int secondLocal = second;
	register const AsciiString *firstLocal = &first;
	self->m_entries[indexLocal].initialize(*firstLocal, secondLocal);
	self->finalize(*firstLocal, secondLocal, indexLocal);
}
