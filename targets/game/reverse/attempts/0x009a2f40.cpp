// ?isEqual@Rva009A2F40Box@@QAEEPBV1@@Z
// partial score=0.68 date=2026-09-28
// SYMBOL: ?isEqual@Rva009A2F40Box@@QAEEPBV1@@Z
// SYMBOL: ?getKey@Rva009A2F40Box@@QBEIXZ
// SIZE: 44
// cl: /DNDEBUG /MD /G6 /EHsc
class Rva009A2F40Box
{
public:
	int m_pad0;
	int m_pad4;
	int m_a;
	int m_b;
	unsigned char isEqual(const Rva009A2F40Box *o);
	unsigned int getKey() const;
};
unsigned char Rva009A2F40Box::isEqual(const Rva009A2F40Box *o)
{
	if (m_a == o->m_a)
	{
		if (m_b == o->m_b)
			goto yes;
		goto no;
	}
no:
	return 0;
yes:
	return 1;
}
unsigned int Rva009A2F40Box::getKey() const
{
	return ((unsigned int)m_a << 16) + (unsigned int)m_b;
}
