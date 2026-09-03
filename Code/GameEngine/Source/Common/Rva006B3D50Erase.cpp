// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
// Mutex-guarded erase and cache invalidation in the 0x006B3C50 owner family.

#define _STLP_NO_EXCEPTIONS 1
#include <set>

class AsciiString
{
};

bool operator<(const AsciiString &left, const AsciiString &right);

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
extern void __stdcall initializeRva006B3C50(void *buffer);

class Rva006B3D50MutexGuard
{
public:
	Rva006B3D50MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva006B3D50MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

struct Rva006B3D50Entry
{
	char m_pad9c[0x9c];
	float m_kind;
	_STL::set<AsciiString> m_strings;
	char m_padac[0x188 - 0xac];
	char m_cache[0x30];
	char m_tail[0x1c4 - 0x1b8];
};

class Rva006B3D50Owner
{
public:
	void erase006B3D50(const AsciiString &key, int index);

private:
	char m_padb8[0xb8];
	Rva006B3D50Entry m_entries[4];
	char m_padend[0x95c - (0xb8 + 4 * 0x1c4)];
	void *m_mutex;
};

void Rva006B3D50Owner::erase006B3D50(const AsciiString &key, int index)
{
	Rva006B3D50Owner *self = this;
	void *handle = self->m_mutex;
	Rva006B3D50MutexGuard guard(handle);
	Rva006B3D50Entry *entry = &self->m_entries[index];
	if (entry->m_strings.erase(key) > 0 && entry->m_kind != 1.0f)
	{
		char *cache = entry->m_cache;
		for (unsigned int offset = 0; offset < sizeof(entry->m_cache); ++offset)
			cache[offset] = 2;
	}
}
