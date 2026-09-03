// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x006AC030: lock the template-set owner and clear one of its three
// string sets.  The generated name is anonymous; the indexed array layout and
// the PlayerTemplateStore-related owner family identify this method.

#define _STLP_NO_EXCEPTIONS 1
#include <set>

class AsciiString
{
};

bool operator<(const AsciiString &left, const AsciiString &right);

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

class Rva006AC030MutexGuard
{
public:
	Rva006AC030MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva006AC030MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

class Rva006AC030Owner
{
public:
	void clear(int index);

private:
	char m_pad44[0x44];
	int m_state;
	char m_pad48[0x95c - 0x48];
	void *m_mutex;
	char m_pad960[0x998 - 0x960];
	_STL::set<AsciiString> m_sets[3];
};

void Rva006AC030Owner::clear(int index)
{
	Rva006AC030MutexGuard guard(m_mutex);
	m_sets[index].clear();
}
