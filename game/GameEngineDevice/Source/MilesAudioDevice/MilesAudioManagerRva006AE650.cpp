// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x006AE650, 150 bytes, ret 8.  Miles audio vtable 0x0111C0C0 slot
// 38 (+0x98) routes through ILT 0x000142CC to this body; slot 39 (+0x9C,
// ILT 0x0000B50F) is the landed 0x006AC030 set clear on the same +0x998
// AsciiString sets.  No caller or string names the method, so it keeps the
// address token.
//
// Under the manager mutex (+0x95C, as in the landed siblings) it forwards
// both arguments to vtable slot 18 (+0x48, ILT 0x000474AB -> 0x006A9CE0)
// and then inserts the string into the set the index selects.  The guard
// is the family's (unwind funclet -> out-of-line release at 0x006915E0);
// the WaitForSingleObject status goes through a named local as in the
// landed 0x006A5E60 guard, which keeps the handle in ebp and reloads the
// name argument after the virtual call.  ReleaseMutex is an extern "C"
// import, so under /EHsc no unwind state reset precedes the inlined
// destructor.

#define _STLP_NO_EXCEPTIONS 1
#include <set>

#include "ascii_string.h"

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

class Rva006AE650MutexGuard
{
public:
	Rva006AE650MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		unsigned long status = WaitForSingleObject(handle, 0xFFFFFFFF);
		if (status != 0x102)
			m_owned = 1;
	}

	~Rva006AE650MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

class MilesAudioManager
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04(); virtual void vslot05(); virtual void vslot06(); virtual void vslot07();
	virtual void vslot08(); virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
	virtual void vslot12(); virtual void vslot13(); virtual void vslot14(); virtual void vslot15();
	virtual void vslot16(); virtual void vslot17();
	virtual void rva006A9CE0(const AsciiString &name, int index);
	virtual void vslot19();
	virtual void vslot20(); virtual void vslot21(); virtual void vslot22(); virtual void vslot23();
	virtual void vslot24(); virtual void vslot25(); virtual void vslot26(); virtual void vslot27();
	virtual void vslot28(); virtual void vslot29(); virtual void vslot30(); virtual void vslot31();
	virtual void vslot32(); virtual void vslot33(); virtual void vslot34(); virtual void vslot35();
	virtual void vslot36(); virtual void vslot37();
	virtual void rva006AE650(const AsciiString &name, int index);

private:
	char m_pad004[0x95c - 0x4];
	void *m_mutex;
	char m_pad960[0x998 - 0x960];
	_STL::set<AsciiString> m_sets[3];
};

void MilesAudioManager::rva006AE650(const AsciiString &name, int index)
{
	Rva006AE650MutexGuard guard(m_mutex);
	rva006A9CE0(name, index);
	m_sets[index].insert(name);
}
