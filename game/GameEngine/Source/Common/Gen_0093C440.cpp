// Clean reconstruction of the guarded release and optional cleanup at retail
// RVA 0x0093C440.  Its first three fields share the observed layout of the
// related release body at 0x0093C400.

// Retail imports GDI32 at VA 0x013590FC, 0x013590C8 and 0x013590C4.
extern "C" __declspec(dllimport) void *__stdcall SelectObject(void *, void *);
extern "C" __declspec(dllimport) int __stdcall DeleteObject(void *);
extern "C" __declspec(dllimport) int __stdcall DeleteDC(void *);

void __cdecl operator delete(void *);

class Gen_0093C440
{
public:
	Gen_0093C440 *process(int flags);

private:
	unsigned char m_pad[4];
	void *m_first;
	void *m_second;
	unsigned char m_gap[4];
	void *m_third;
};

Gen_0093C440 *Gen_0093C440::process(int flags)
{
	if (m_second != 0) {
		SelectObject(m_third, m_first);
		DeleteObject(m_second);
		m_second = 0;
	}
	if (m_third != 0) {
		DeleteDC(m_third);
		m_third = 0;
	}
	if ((flags & 1) != 0)
		operator delete(this);
	return this;
}
