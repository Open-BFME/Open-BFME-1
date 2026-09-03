// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x006AE060: mutex-guarded insertion into an indexed string set and
// invalidation of the entry cache when a new non-default-scale key is added.

#define _STLP_NO_EXCEPTIONS 1
#include <set>

class AsciiString
{
private:
	void *m_data;
};

bool operator<(const AsciiString &left, const AsciiString &right);

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

class Rva006AE060MutexGuard
{
public:
	Rva006AE060MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva006AE060MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

struct Rva006AE060Entry
{
	char m_pad9c[0x9c];
	float m_scale;
	_STL::set<AsciiString> m_strings;
	char m_padac[0x188 - 0xac];
	char m_cache[0x30];
	char m_tail[0x1c4 - 0x1b8];
};

class Rva006AE060Owner
{
public:
	void insert(const AsciiString &key, int index);

private:
	char m_padb8[0xb8];
	Rva006AE060Entry m_entries[4];
	char m_padend[0x95c - (0xb8 + 4 * 0x1c4)];
	void *m_mutex;
};

void Rva006AE060Owner::insert(const AsciiString &key, int index)
{
	Rva006AE060MutexGuard guard(m_mutex);
	Rva006AE060Entry *entry = &m_entries[index];
	if (entry->m_strings.insert(key).second && entry->m_scale != 1.0f)
	{
		for (unsigned int offset = 0; offset < sizeof(entry->m_cache); ++offset)
			entry->m_cache[offset] = 2;
	}
}
