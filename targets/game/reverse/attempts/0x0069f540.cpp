// ?eraseKey@Rva0069F540Owner@@QAEXPAX@Z
// partial score=0.4717 date=2026-10-29
// ?eraseKey@Rva0069F540Owner@@QAEXPAX@Z
// Rewrite 2026-10-29 (claude-opus-5-5): natural for(begin;!=end();++it) loop with erase+flag+break
// gives retail's 106B and instruction stream; only residue is VC7.1 saving EBP around the loop
// region (push at +0x37 / pop at +0x58) where retail saves it in the prologue. Inert: while/do,
// function-scope it, it++/key==, continue form, key const local, inline find/remove helpers (worse),
// member mutex without local (worse), lock struct with dtor (EH frame, 172B).
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *hHandle, unsigned long dwMilliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *hMutex);
struct Rva0069F540Pair
{
	void *m_key;
	char m_rest[4];
};
struct Rva0069F540Vec
{
	Rva0069F540Pair *m_start;
	Rva0069F540Pair *m_finish;
	Rva0069F540Pair *begin(void) const { return m_start; }
	Rva0069F540Pair *end(void) const { return m_finish; }
	Rva0069F540Pair *erase(Rva0069F540Pair *it);
};
class Rva0069F540Owner
{
public:
	void eraseKey(void *key);
	char m_bytes[0x636];
	bool m_dirty;
	char m_pad1[0x95c - 0x637];
	void *m_mutex;
	char m_pad2[0xadc - 0x960];
	Rva0069F540Vec m_vec;
};
void Rva0069F540Owner::eraseKey(void *key)
{
	void *mutex = m_mutex;
	bool held = false;
	if (WaitForSingleObject(mutex, 0xFFFFFFFFu) != 0x102u)
		held = true;
	for (Rva0069F540Pair *it = m_vec.begin(); it != m_vec.end(); ++it)
	{
		if (it->m_key == key)
		{
			m_vec.erase(it);
			m_dirty = true;
			break;
		}
	}
	if (held)
		ReleaseMutex(mutex);
}
