// ?eraseKey@Rva0069F540Owner@@QAEXPAX@Z
// partial score=0.55 date=2026-09-04
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Mutex-guarded walk of 8-byte pairs at +0xADC; on key match erase via vec.

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
	Rva0069F540Pair *m_begin;
	Rva0069F540Pair *m_end;
	void erase(Rva0069F540Pair *it);
};

class Rva0069F540Owner
{
public:
	void eraseKey(void *key);

	char m_bytes[0xae4];
};

void Rva0069F540Owner::eraseKey(void *key)
{
	void *mutex = *(void **)(m_bytes + 0x95c);
	unsigned char held = 0;
	if (WaitForSingleObject(mutex, 0xFFFFFFFFu) != 0x102u)
		held = 1;

	Rva0069F540Vec *vec = (Rva0069F540Vec *)(m_bytes + 0xadc);
	Rva0069F540Pair *it = vec->m_begin;
	if (it != vec->m_end)
	{
		void *want = key;
		if (it->m_key != want)
		{
			Rva0069F540Pair *limit = vec->m_end;
			for (;;)
			{
				it = (Rva0069F540Pair *)((char *)it + 8);
				if (it == limit)
					goto done;
				if (it->m_key == want)
					break;
			}
		}
		vec->erase(it);
		m_bytes[0x636] = 1;
	}
done:
	if (held)
		ReleaseMutex(mutex);
}
