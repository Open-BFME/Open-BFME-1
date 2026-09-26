// cl: /O2 /Ob0
//
// thiscall @ 0x00511430, 80 bytes, ret 0xC.
// If the first pointer or the flag byte is set, return. Else if this+0x25C
// is 3, copy a dword+short from 0x011052C4; otherwise dword+dword+byte
// from 0x011052B8. Same +0x25C host as the 74B note body in this dump.

class Rva00511430Host
{
public:
	void fill(void *guard, void *out, unsigned char flag);

private:
	char m_lead[0x25C];
	int m_25C;
};

struct Rva00511430Out3
{
	int m_00;
	unsigned short m_04;
};

struct Rva00511430OutElse
{
	int m_00;
	int m_04;
	char m_08;
};

// ?fill@Rva00511430Host@@QAEXPAX0E@Z
void Rva00511430Host::fill(void *guard, void *out, unsigned char flag)
{
	if (guard)
		return;
	if (flag)
		return;
	if (m_25C == 3)
	{
		Rva00511430Out3 *d = (Rva00511430Out3 *)out;
		d->m_00 = *(int *)0x011052C4;
		d->m_04 = *(unsigned short *)0x011052C8;
	}
	else
	{
		Rva00511430OutElse *d = (Rva00511430OutElse *)out;
		d->m_00 = *(int *)0x011052B8;
		d->m_04 = *(int *)0x011052BC;
		d->m_08 = *(char *)0x011052C0;
	}
}
