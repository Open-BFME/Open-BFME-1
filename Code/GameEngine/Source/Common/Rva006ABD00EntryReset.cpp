// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x006ABD00: mutex-guarded reset of one 0x1c4-byte entry.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

class Rva006ABD00MutexGuard
{
public:
	Rva006ABD00MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva006ABD00MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

class Rva006ABB80
{
public:
	void reset();

private:
	char m_data[0x1c4];
};

class Rva006ABD00Owner
{
public:
	void resetEntry(int index);

private:
	char m_pad44[0x44];
	int m_state;
	char m_pad48[0xb8 - 0x48];
	Rva006ABB80 m_entries[4];
	char m_padend[0x95c - (0xb8 + 4 * 0x1c4)];
	void *m_mutex;
};

void Rva006ABD00Owner::resetEntry(int index)
{
	Rva006ABD00Owner *self = this;
	void *handle = self->m_mutex;
	Rva006ABD00MutexGuard guard(handle);
	self->m_entries[index].reset();
}
