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

// The two source records the body copies raw bytes from. Neither address is
// named in dir32_addresses.csv, so both keep the address-derived name; the
// retail bytes are the NUL-terminated literals "GameChat" and "Buddy".
extern const Rva00511430OutElse g_011052B8;
extern const Rva00511430Out3 g_011052C4;

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
		d->m_00 = g_011052C4.m_00;
		d->m_04 = g_011052C4.m_04;
	}
	else
	{
		Rva00511430OutElse *d = (Rva00511430OutElse *)out;
		d->m_00 = g_011052B8.m_00;
		d->m_04 = g_011052B8.m_04;
		d->m_08 = g_011052B8.m_08;
	}
}
