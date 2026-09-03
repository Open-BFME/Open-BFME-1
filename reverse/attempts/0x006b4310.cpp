// ?update006B4310@Rva006B4310Owner@@QAEXABVAsciiString@@HH@Z
// partial score=0.86 date=2026-09-03
// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Mutex-guarded three-argument entry update in the 0x006B3C50 owner family.

class AsciiString;

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

class Rva006B4310MutexGuard
{
public:
	Rva006B4310MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
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
	void *handle = self->m_mutex;
	Rva006B4310MutexGuard guard(handle);

	self->m_entries[index].initialize(first, second);
	self->finalize(first, second, index);
}
