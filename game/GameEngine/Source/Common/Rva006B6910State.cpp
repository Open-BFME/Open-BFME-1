// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Mutex-guarded state change in the 0x006B3C50 owner family.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
extern void j_00045f0c();
extern void j_0000c30b();
extern void __stdcall initializeRva006B3C50(void *buffer);

class Rva006B6910MutexGuard
{
public:
	Rva006B6910MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva006B6910MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

class Rva006B6910Owner
{
public:
	void set006B6910(int value);

private:
	char m_pad44[0x44];
	int m_state;
	char m_pad48[0x604 - 0x48];
	int m_value;
	char m_pad608[0x631 - 0x608];
	char m_changed;
	char m_pad632[0x95c - 0x632];
	void *m_mutex;
	char m_pad960[0xb54 - 0x960];
	void *m_callback;
};

void Rva006B6910Owner::set006B6910(int value)
{
	Rva006B6910Owner *self = this;
	void *handle = self->m_mutex;
	Rva006B6910MutexGuard guard(handle);
	if (value != self->m_value)
	{
		self->m_value = value;
		void *callback = self->m_callback;
		self->m_changed = 1;
		typedef void (Rva006B6910Owner::*Notify)(void *);
		union
		{
			void (__cdecl *freeNotify)();
			Notify memberNotify;
		} notify;
		notify.freeNotify = ::j_00045f0c;
		(self->*notify.memberNotify)(callback);
		typedef void (Rva006B6910Owner::*Update)();
		union
		{
			void (__cdecl *freeUpdate)();
			Update memberUpdate;
		} update;
		update.freeUpdate = ::j_0000c30b;
		(self->*update.memberUpdate)();
		char buffer[8];
		self->m_state = 0;
		typedef void (Rva006B6910Owner::*Initialize)(void *);
		union
		{
			void (__stdcall *freeInitialize)(void *);
			Initialize memberInitialize;
		} initialize;
		initialize.freeInitialize = ::initializeRva006B3C50;
		(self->*initialize.memberInitialize)(buffer);
	}
}
