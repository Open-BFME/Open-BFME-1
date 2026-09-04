// ?note@Rva00517AF0Host@@QAEHHEE@Z
// partial score=0.9 date=2026-09-04
// cl: /O2 /Ob0
//
// thiscall @ 0x00517AF0, 84 bytes, ret 0xC. Same d_0050fec0 kind-0x15
// family as the 74B note leftover. Guard +0x3D8, type==1, marks&1, then
// switch +0x3A8 (1 / 4 / 9) to Rva00516690 or BfmeR1102::bfmeGo1102B(0).

class BfmeR1102
{
public:
	void bfmeGo1102B(int a);
};

void Rva00516690(void);

class Rva00517AF0Host
{
public:
	int note(int kind, unsigned char type, unsigned char marks);

private:
	char m_lead[0x3A8];
	int m_3A8;
	char m_mid[0x2C];
	unsigned char m_3D8;
};

// ?note@Rva00517AF0Host@@QAEHHEE@Z
int Rva00517AF0Host::note(int kind, unsigned char type, unsigned char marks)
{
	if (m_3D8)
		goto fail;
	if (kind != 0x15)
		goto fail;

	int t = type;
	t--;
	if (t)
		goto fail;
	if ((marks & 1) == 0)
		goto fail;

	switch (m_3A8) {
	case 4:
	case 9:
		((BfmeR1102 *)this)->bfmeGo1102B(0);
		return 1;
	case 1:
		Rva00516690();
		return 1;
	}
fail:
	return 0;
}
