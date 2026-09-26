// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x006AC0F0: lock the owner, reset the vector subobject at +0x70
// using the indexed value offset by eight, and invalidate the ready flag.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

class Rva006A78C0Vector
{
public:
	void reset(int value);
};

class Rva006AC0F0MutexGuard
{
public:
	Rva006AC0F0MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva006AC0F0MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

class Rva006AC0F0Owner
{
public:
	void resetVector(int index);

private:
	char m_pad70[0x70];
	char m_pad630[0x630 - 0x70];
	unsigned char m_ready;
	char m_pad631[0x95c - 0x631];
	void *m_mutex;
};

void Rva006AC0F0Owner::resetVector(int index)
{
	Rva006AC0F0Owner *self = this;
	void *handle = self->m_mutex;
	Rva006AC0F0MutexGuard guard(handle);
	Rva006A78C0Vector *vector = reinterpret_cast<Rva006A78C0Vector *>(
		reinterpret_cast<char *>(self) + 0x70);
	vector->reset(index + 8);
	self->m_ready = 0;
}
