// ?reset@Rva007DCAF0@@QAEHXZ
// partial score=0.88 date=2026-09-02
// cl: /O2
// 0x007DCAF0: thiscall reset. C-style COM Release on six pointer slots, a
// five-argument cdecl helper, then return 1.

struct Rva007DCAF0UnkVtbl
{
	void *QueryInterface;
	void *AddRef;
	unsigned long (__stdcall *Release)(void *self);
};

struct Rva007DCAF0Unk
{
	Rva007DCAF0UnkVtbl *lpVtbl;
};

void *Rva007DCAF0Helper(void *a, void *b, void *c, char *d, int e);

class Rva007DCAF0
{
public:
	int reset();

private:
	char m_pad[4];
	Rva007DCAF0Unk *m_04;
	Rva007DCAF0Unk *m_08;
	char m_pad0C[0x28];
	void *m_34;
	void *m_38;
	char m_pad3C[4];
	Rva007DCAF0Unk *m_40;
	Rva007DCAF0Unk *m_44;
	char m_pad48[4];
	Rva007DCAF0Unk *m_4C;
	Rva007DCAF0Unk *m_50;
};

int Rva007DCAF0::reset()
{
	char tmp;
	int zero = 0;
	if (m_04)
		m_04->lpVtbl->Release(m_04);
	if (m_08)
		m_08->lpVtbl->Release(m_08);
	m_38 = Rva007DCAF0Helper((m_04 = 0, m_08 = 0, m_38),
		m_38, m_34, &tmp, zero);
	if (m_4C)
		m_4C->lpVtbl->Release(m_4C);
	m_4C = 0;
	if (m_40)
		m_40->lpVtbl->Release(m_40);
	m_40 = 0;
	if (m_50)
		m_50->lpVtbl->Release(m_50);
	m_50 = 0;
	if (m_44)
		m_44->lpVtbl->Release(m_44);
	m_44 = 0;
	return 1;
}
