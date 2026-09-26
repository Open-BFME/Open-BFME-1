// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva0013F690
{
	unsigned m_0;

public:
	Rva0013F690 *mask();
};

Rva0013F690 *Rva0013F690::mask()
{
	m_0 = (~m_0) & 0x1FFFFFFF;
	return this;
}
