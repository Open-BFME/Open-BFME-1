// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /ICode/Libraries/Source/WWVegas/WWLib
// Mutex-guarded named-entry update and follow-up in the 0x006B3C50 owner family.

#include "ascii_string.h"

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
extern void j_0002c7af();
extern void j_00023d21();

class Rva006B4310MutexGuard
{
public:
	Rva006B4310MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		unsigned long status = WaitForSingleObject(handle, 0xFFFFFFFF);
		if (status != 0x102)
			m_owned = 1;
	}

	~Rva006B4310MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

class Rva006B4310Entry
{
public:
	void initialize(const AsciiString &first, float second);

private:
	char m_data[0x1c4];
};

class Rva006B4310Owner
{
public:
	void update006B4310(const AsciiString &first, float second, int index);
	void finalize(const AsciiString &first, float second, int third);

private:
	char m_padb8[0xb8];
	Rva006B4310Entry m_entries[4];
	char m_padend[0x95c - (0xb8 + 4 * 0x1c4)];
	void *m_mutex;
};

// Retail 0x006B4310 (156B). The guard is the family's inline mutex lock
// (out-of-line release at 0x006915E0); the entry call reaches 0x006ACE90
// through ILT 0x0002C7AF and the follow-up reaches 0x006B24D0 through ILT
// 0x00023D21, the same (name, float, index) callee 0x006B44A0 passes -1.0f.
void Rva006B4310Owner::update006B4310(
	const AsciiString &first, float second, int index)
{
	Rva006B4310MutexGuard guard(m_mutex);
	{
		typedef void (Rva006B4310Entry::*Initialize)(const AsciiString &, float);
		union
		{
			void (__cdecl *freeInitialize)();
			Initialize memberInitialize;
		} initialize;
		initialize.freeInitialize = ::j_0002c7af;
		(m_entries[index].*initialize.memberInitialize)(first, second);
	}
	{
		typedef void (Rva006B4310Owner::*Finalize)(const AsciiString &, float, int);
		union
		{
			void (__cdecl *freeFinalize)();
			Finalize memberFinalize;
		} finalize;
		finalize.freeFinalize = ::j_00023d21;
		(this->*finalize.memberFinalize)(first, second, index);
	}
}
