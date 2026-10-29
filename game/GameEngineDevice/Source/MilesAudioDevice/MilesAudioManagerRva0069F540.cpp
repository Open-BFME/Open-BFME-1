// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva0069F540@MilesAudioManager@@UAEXPAX@Z
// Retail 0x0069F540, 106 bytes (ret 4 at +0x67): MilesAudioManager vtable
// 0x0111C0C0 slot 88 (ILT 0x000165EF). Under the +0x95C mutex, erase the
// first 8-byte record of the vector at +0xADC whose first word is the
// argument and set the byte flag at +0x636. The method name is not
// recoverable, so it keeps the address.
//
// The erase is the out-of-line STLport vector<Gen_p8pod>::erase at
// 0x0069DE00 (ILT 0x0001698C); the explicit specialization declaration keeps
// VC7.1 from inlining it here. Releasing the mutex inside the found branch and
// returning (VC7.1 tail-merges the two releases) is what saves EBP in the
// prologue as retail does; a break out of the loop saves it around the loop.
#include <vector>

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *hHandle, unsigned long dwMilliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *hMutex);

struct Gen_p8pod
{
	void *m_key;
	char m_rest[4];
};

template <> _STL::vector<Gen_p8pod>::iterator _STL::vector<Gen_p8pod>::erase(_STL::vector<Gen_p8pod>::iterator position);

class MilesAudioManager
{
public:
	virtual void rva0069F540(void *key);

	char m_bytes[0x636 - 4];
	bool m_dirty;					// +0x636
	char m_pad637[0x95c - 0x637];
	void *m_mutex;					// +0x95c
	char m_pad960[0xadc - 0x960];
	_STL::vector<Gen_p8pod> m_vec;	// +0xadc
};

void MilesAudioManager::rva0069F540(void *key)
{
	void *mutex = m_mutex;
	bool held = false;
	if (WaitForSingleObject(mutex, 0xFFFFFFFFu) != 0x102u)
		held = true;
	for (_STL::vector<Gen_p8pod>::iterator it = m_vec.begin(); it != m_vec.end(); ++it)
	{
		if (it->m_key == key)
		{
			m_vec.erase(it);
			m_dirty = true;
			if (held)
				ReleaseMutex(mutex);
			return;
		}
	}
	if (held)
		ReleaseMutex(mutex);
}
