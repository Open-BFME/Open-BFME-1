// ?eraseKey@Rva0069F540Owner@@QAEXPAX@Z
// partial score=0.6 date=2026-09-15
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
	Rva0069F540Pair *m_start;
	Rva0069F540Pair *m_finish;

	Rva0069F540Pair *begin(void) const { return m_start; }
	Rva0069F540Pair *end(void) const { return m_finish; }
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
	Rva0069F540Vec *vec = (Rva0069F540Vec *)(m_bytes + 0xadc);
	void *mutex = *(void **)(m_bytes + 0x95c);
	unsigned char held = 0;
	if (WaitForSingleObject(mutex, 0xFFFFFFFFu) != 0x102u)
		held = 1;

	Rva0069F540Pair *it = vec->begin();
	if (it != vec->end())
	{
		if (it->m_key != key)
		{
			Rva0069F540Pair *limit = vec->end();
			for (;;)
			{
				it = it + 1;
				if (it == limit)
					goto done;
				if (it->m_key == key)
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