// ?add006B15A0@Rva006B15A0Owner@@QAEXABVAsciiString@@@Z
// partial score=0.91 date=2026-09-03
// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
// Record a non-empty audio name while holding the shared owner mutex.

class AsciiString
{
public:
	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		char m_data[1];
	};

	bool hasText() const
	{
		return m_data != 0 && m_data->m_length != 0;
	}


private:
	Header *m_data;
};

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
extern void j_00018d22();
extern void j_00024f00();
extern void j_00032317();

class Rva006B15A0MutexGuard
{
public:
	Rva006B15A0MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva006B15A0MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

struct Rva006B15A0Node
{
	char m_link[8];
	AsciiString m_name;
};

class Rva006B15A0Lookup
{
public:
	Rva006B15A0Node *find(const AsciiString &key);

private:
	char m_data[0x14];
};

class Rva006B15A0Records
{
public:
	void add(const AsciiString *name);

private:
	char m_data[0x0c];
};

class Rva006B15A0Names
{
public:
	void push_back(const AsciiString &name);

private:
	char m_data[0x0c];
};

class Rva006B15A0Owner
{
public:
    void add006B15A0(register const AsciiString &name);

private:
	char m_pad44[0x44];
	int m_state;
	char m_pad48[0x914];
	void *m_mutex;
	char m_pad960[0x0c];
	Rva006B15A0Lookup m_lookup;
	Rva006B15A0Records m_records;
	Rva006B15A0Names m_names;
};

void Rva006B15A0Owner::add006B15A0(register const AsciiString &name)
{
	register Rva006B15A0Owner *self = this;
	if (!name.hasText())
		return;

	{
		register void *handle = self->m_mutex;
		Rva006B15A0MutexGuard guard(handle);

		Rva006B15A0Node *node = self->m_lookup.find(name);
		if (node == 0)
		{
			self->m_names.push_back(name);
		}
		else if (node->m_name.hasText())
		{
			self->m_records.add(&node->m_name);
		}
	}
}
