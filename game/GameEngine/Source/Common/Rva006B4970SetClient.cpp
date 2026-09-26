// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Mutex-guarded client-setting helper in the 0x006B3C50 owner family.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

extern void __stdcall initializeRva006B3C50(void *buffer);
extern void j_00047f3c();

class Rva006B4970MutexGuard
{
public:
	Rva006B4970MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva006B4970MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

class Rva006B3C50ClientOwner
{
public:
	void set006B4970(int value);
	void set006B4A30(int value);
	void set006B4AF0(int value);
	void set006B4BB0(int value);
	void set006B4C70(int value);

private:
	char m_pad44[0x44];
	int m_state;
	char m_pad48[0x95c - 0x48];
	void *m_mutex;
};

void Rva006B3C50ClientOwner::set006B4970(int value)
{
	char buffer[8];
	Rva006B3C50ClientOwner *self = this;
	void *handle = self->m_mutex;
	Rva006B4970MutexGuard guard(handle);
	*reinterpret_cast<int *>(0x012BA12C) = value;
	typedef void (__cdecl *Rva006B4970Helper)(...);
	Rva006B4970Helper helper = reinterpret_cast<Rva006B4970Helper>(j_00047f3c);
	helper(0);
	self->m_state = 0;
	typedef void (Rva006B3C50ClientOwner::*RvaInit)(void *);
	union
	{
		void (__stdcall *freeInit)(void *);
		RvaInit memberInit;
	} init;
	init.freeInit = ::initializeRva006B3C50;
	(self->*init.memberInit)(buffer);
}

void Rva006B3C50ClientOwner::set006B4A30(int value)
{
	char buffer[8];
	Rva006B3C50ClientOwner *self = this;
	void *handle = self->m_mutex;
	Rva006B4970MutexGuard guard(handle);
	*reinterpret_cast<int *>(0x012BA130) = value;
	typedef void (__cdecl *Rva006B4970Helper)(...);
	Rva006B4970Helper helper = reinterpret_cast<Rva006B4970Helper>(j_00047f3c);
	helper(1);
	self->m_state = 0;
	typedef void (Rva006B3C50ClientOwner::*RvaInit)(void *);
	union
	{
		void (__stdcall *freeInit)(void *);
		RvaInit memberInit;
	} init;
	init.freeInit = ::initializeRva006B3C50;
	(self->*init.memberInit)(buffer);
}

void Rva006B3C50ClientOwner::set006B4AF0(int value)
{
	char buffer[8];
	Rva006B3C50ClientOwner *self = this;
	void *handle = self->m_mutex;
	Rva006B4970MutexGuard guard(handle);
	*reinterpret_cast<int *>(0x012BA134) = value;
	typedef void (__cdecl *Rva006B4970Helper)(...);
	Rva006B4970Helper helper = reinterpret_cast<Rva006B4970Helper>(j_00047f3c);
	helper(2);
	self->m_state = 0;
	typedef void (Rva006B3C50ClientOwner::*RvaInit)(void *);
	union
	{
		void (__stdcall *freeInit)(void *);
		RvaInit memberInit;
	} init;
	init.freeInit = ::initializeRva006B3C50;
	(self->*init.memberInit)(buffer);
}

void Rva006B3C50ClientOwner::set006B4BB0(int value)
{
	char buffer[8];
	Rva006B3C50ClientOwner *self = this;
	void *handle = self->m_mutex;
	Rva006B4970MutexGuard guard(handle);
	*reinterpret_cast<int *>(0x012BA13C) = value;
	typedef void (__cdecl *Rva006B4970Helper)(...);
	Rva006B4970Helper helper = reinterpret_cast<Rva006B4970Helper>(j_00047f3c);
	helper(4);
	self->m_state = 0;
	typedef void (Rva006B3C50ClientOwner::*RvaInit)(void *);
	union
	{
		void (__stdcall *freeInit)(void *);
		RvaInit memberInit;
	} init;
	init.freeInit = ::initializeRva006B3C50;
	(self->*init.memberInit)(buffer);
}

void Rva006B3C50ClientOwner::set006B4C70(int value)
{
	char buffer[8];
	Rva006B3C50ClientOwner *self = this;
	void *handle = self->m_mutex;
	Rva006B4970MutexGuard guard(handle);
	*reinterpret_cast<int *>(0x012BA138) = value;
	typedef void (__cdecl *Rva006B4970Helper)(...);
	Rva006B4970Helper helper = reinterpret_cast<Rva006B4970Helper>(j_00047f3c);
	helper(3);
	self->m_state = 0;
	typedef void (Rva006B3C50ClientOwner::*RvaInit)(void *);
	union
	{
		void (__stdcall *freeInit)(void *);
		RvaInit memberInit;
	} init;
	init.freeInit = ::initializeRva006B3C50;
	(self->*init.memberInit)(buffer);
}
