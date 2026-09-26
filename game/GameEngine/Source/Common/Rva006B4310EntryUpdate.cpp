// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /Igame/Libraries/Source/WWVegas/WWLib
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
	// Callee 0x006ACE90; the ledger names it Rva006ACE90Owner::addNamedRoom.
	void rva006ACE90(const AsciiString &first, float second);

private:
	char m_data[0x1c4];
};

class Rva006B4310Owner
{
public:
	void update006B4310(const AsciiString &first, float second, int index);

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
		typedef void (Rva006B4310Entry::*Rva006ACE90Call)(const AsciiString &, float);
		union
		{
			void (__cdecl *free006ACE90)();
			Rva006ACE90Call member006ACE90;
		} call006ACE90;
		call006ACE90.free006ACE90 = ::j_0002c7af;
		(m_entries[index].*call006ACE90.member006ACE90)(first, second);
	}
	{
		typedef void (Rva006B4310Owner::*Rva006B24D0Call)(const AsciiString &, float, int);
		union
		{
			void (__cdecl *free006B24D0)();
			Rva006B24D0Call member006B24D0;
		} call006B24D0;
		call006B24D0.free006B24D0 = ::j_00023d21;
		(this->*call006B24D0.member006B24D0)(first, second, index);
	}
}
