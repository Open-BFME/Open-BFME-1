// ?lookup2A8@Rva00801340Owner@@QAEPAXPAX@Z
// partial score=0.9 date=2026-09-04
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Table lookup via bfmeLookRH at base+0x2A8 into pointer array at +0x34.
// Near-miss: 50/51 — base lands in eax not ecx so add not lea edx,[ecx+imm].

int __stdcall bfmeLookRH(void *table, void *key);

class Rva00801340Owner
{
public:
	void *lookup2A8(void *key);

	char m_pad0[4];
	char *m_base;
	char m_pad8[0x34 - 8];
	void **m_arr34;
};

void *Rva00801340Owner::lookup2A8(void *key)
{
	if (m_arr34)
	{
		char *base = m_base;
		int idx = bfmeLookRH(base + 0x2a8, key);
		if (idx != -1)
			return m_arr34[idx];
	}
	return 0;
}
