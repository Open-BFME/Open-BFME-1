// cl: /DNDEBUG /MD /EHs-c-
// Retail 0x008A0C60: const member reading this+4/this+8 as a pointer pair and
// this+0x12B0 as the wrap adjustment; pointer-difference/20 count with wrap add.

struct Rva008A0C60Elem
{
	int m_v[5];
};

struct Rva008A0C60Owner
{
	int m_0;
	Rva008A0C60Elem *m_begin;
	Rva008A0C60Elem *m_end;
	char m_pad[0x12b0 - 12];
	int m_wrap;
	int getCount() const;
};

// ?getCount@Rva008A0C60Owner@@QBEHXZ
int Rva008A0C60Owner::getCount() const
{
	int n = m_end - m_begin;
	if (n >= 0)
		return n;
	return n + m_wrap;
}
