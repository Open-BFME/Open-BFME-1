// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
// Mutex-guarded erase from one of three adjacent STLport string sets.

#define _STLP_NO_EXCEPTIONS 1
#include <set>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
};

bool operator<(const AsciiString &left, const AsciiString &right);

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

class Rva006B4260MutexGuard
{
public:
	Rva006B4260MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva006B4260MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

class Rva006B4260Owner
{
public:
	void erase006B4260(const AsciiString &key, int index);

private:
	char m_pad44[0x44];
	int m_state;
	char m_pad48[0x95c - 0x48];
	void *m_mutex;
	char m_pad960[0x998 - 0x960];
	_STL::set<AsciiString> m_sets[3];
};

void Rva006B4260Owner::erase006B4260(const AsciiString &key, int index)
{
	Rva006B4260MutexGuard guard(m_mutex);
	m_sets[index].erase(key);
}
