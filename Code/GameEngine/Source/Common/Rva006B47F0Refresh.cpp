// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Mutex-guarded refresh helper in the 0x006B3C50 owner family.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

extern void __stdcall initializeRva006B3C50(void *buffer);
extern void j_0002fbbc();

class Rva006B47F0MutexGuard
{
public:
	Rva006B47F0MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva006B47F0MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

class Rva006B47F0Owner
{
public:
	void refresh006B47F0();
	void refresh006B48B0();

private:
	char m_pad44[0x44];
	int m_state;
	char m_pad48[0x95c - 0x48];
	void *m_mutex;
};

void Rva006B47F0Owner::refresh006B47F0()
{
	char buffer[8];
	Rva006B47F0Owner *self = this;
	void *handle = self->m_mutex;
	Rva006B47F0MutexGuard guard(handle);
	if (*reinterpret_cast<unsigned char *>(
			reinterpret_cast<unsigned char *>(*reinterpret_cast<void **>(0x012ED5C8)) + 0xA94))
	{
		*reinterpret_cast<unsigned char *>(0x012BA144) = 0;
		::j_0002fbbc();
		self->m_state = 0;
		typedef void (Rva006B47F0Owner::*RvaInit)(void *);
		union
		{
			void (__stdcall *freeInit)(void *);
			RvaInit memberInit;
		} init;
		init.freeInit = ::initializeRva006B3C50;
		(self->*init.memberInit)(buffer);
	}
}

void Rva006B47F0Owner::refresh006B48B0()
{
	char buffer[8];
	Rva006B47F0Owner *self = this;
	void *handle = self->m_mutex;
	Rva006B47F0MutexGuard guard(handle);
	if (*reinterpret_cast<unsigned char *>(
			reinterpret_cast<unsigned char *>(*reinterpret_cast<void **>(0x012ED5C8)) + 0xA94))
	{
		*reinterpret_cast<unsigned char *>(0x012BA144) = 1;
		::j_0002fbbc();
		self->m_state = 0;
		typedef void (Rva006B47F0Owner::*RvaInit)(void *);
		union
		{
			void (__stdcall *freeInit)(void *);
			RvaInit memberInit;
		} init;
		init.freeInit = ::initializeRva006B3C50;
		(self->*init.memberInit)(buffer);
	}
}
