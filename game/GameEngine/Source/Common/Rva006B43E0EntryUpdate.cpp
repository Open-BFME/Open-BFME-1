// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /Igame/Libraries/Source/WWVegas/WWLib
// Mutex-guarded keyed entry update and follow-up in the 0x006B3C50 owner family.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
extern void j_0000afc9();
extern void j_00023d21();

class Rva006B43E0MutexGuard
{
public:
	Rva006B43E0MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		unsigned long status = WaitForSingleObject(handle, 0xFFFFFFFF);
		if (status != 0x102)
			m_owned = 1;
	}

	~Rva006B43E0MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

struct Gen_t_006af670_k4
{
	int a[1];
};

class Rva006B43E0Tree
{
public:
	void insert(const Gen_t_006af670_k4 &value);

private:
	char m_data[0x0c];
};

class Rva006B43E0Entry
{
public:
	Rva006B43E0Tree m_tree;

private:
	char m_pad[0x1c4 - 0x0c];
};

class Rva006B43E0Owner
{
public:
	void update006B43E0(const Gen_t_006af670_k4 &first, int index);
	void finalize(const Gen_t_006af670_k4 &first, float second, int third);

private:
	char m_padb8[0x270];
	Rva006B43E0Entry m_entries[3];
	char m_padend[0x95c - (0x270 + 3 * 0x1c4)];
	void *m_mutex;
};

// Retail 0x006B43E0 (153B). Same guard family as 0x006B4310: the wait
// status goes through a named local so the mutex stays in EDI; the keyed
// insert reaches 0x006AF670 through ILT 0x0000AFC9 and the follow-up passes
// -1.0f through ILT 0x00023D21.
void Rva006B43E0Owner::update006B43E0(
	const Gen_t_006af670_k4 &first, int index)
{
	Rva006B43E0MutexGuard guard(m_mutex);
	{
		typedef void (Rva006B43E0Tree::*InsertCall)(const Gen_t_006af670_k4 &);
		union
		{
			void (__cdecl *freeInsert)();
			InsertCall memberInsert;
		} callInsert;
		callInsert.freeInsert = ::j_0000afc9;
		((m_entries[index].m_tree).*callInsert.memberInsert)(first);
	}
	{
		typedef void (Rva006B43E0Owner::*FinalizeCall)(const Gen_t_006af670_k4 &, float, int);
		union
		{
			void (__cdecl *freeFinalize)();
			FinalizeCall memberFinalize;
		} callFinalize;
		callFinalize.freeFinalize = ::j_00023d21;
		(this->*callFinalize.memberFinalize)(first, -1.0f, index);
	}
}
