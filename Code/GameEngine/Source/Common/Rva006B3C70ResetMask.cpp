// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Three masked entry resets in the 0x006B3C50 owner family.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
extern void j_00011748();
extern void __stdcall initializeRva006B3C50(void *buffer);

class Rva006B3C70MutexGuard
{
public:
	Rva006B3C70MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva006B3C70MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

class Rva006B3C70Entry
{
public:
	void reset(int value);

private:
	char m_data[0x1c4];
};

class Rva006B3C70Owner
{
public:
	void reset006B3C70(int value, int mask);

private:
	char m_pad44[0x44];
	int m_state;
	char m_pad48[0x70];
	Rva006B3C70Entry m_entries[4];
	char m_pad78c[0x95c - (0xb8 + 4 * 0x1c4)];
	void *m_mutex;
};

void Rva006B3C70Owner::reset006B3C70(int value, int mask)
{
	Rva006B3C70Owner *self = this;

	void *handle = self->m_mutex;
	Rva006B3C70MutexGuard guard(handle);

	int index = 0;
	Rva006B3C70Entry *entry = self->m_entries;
	while (index < 3)
	{
		if (mask & (1 << index))
		{
			typedef void (Rva006B3C70Entry::*Reset)(int);
			union
			{
				void (__cdecl *freeReset)();
				Reset memberReset;
			} reset;
			reset.freeReset = ::j_00011748;
			(entry->*reset.memberReset)(value);
		}
		++index;
		++entry;
	}

	char buffer[8];
	self->m_state = 0;
	typedef void (Rva006B3C70Owner::*Initialize)(void *);
	union
	{
		void (__stdcall *freeInitialize)(void *);
		Initialize memberInitialize;
	} initialize;
	initialize.freeInitialize = ::initializeRva006B3C50;
	(self->*initialize.memberInitialize)(buffer);
}
