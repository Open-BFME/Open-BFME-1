// ?getCount@Rva008A0C60Owner@@QBEHXZ
// partial score=0.8 date=2026-09-06
struct Rva008A0C60Elem { int m_v[5]; };
struct Rva008A0C60Owner {
	int m_0; Rva008A0C60Elem* m_begin; Rva008A0C60Elem* m_end; char m_pad[0x12b0 - 12]; int m_wrap;
	int getCount() const;
};
int Rva008A0C60Owner::getCount() const
{
	int n = m_end - m_begin;
	if (n < 0)
		n += m_wrap;
	return n;
}
