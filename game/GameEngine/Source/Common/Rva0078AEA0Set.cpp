// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva0078AEA0
{
	unsigned char m_dirty;
	unsigned char m_pad[7];
	unsigned m_8;
};

void __fastcall rva0078AEA0(Rva0078AEA0 *p, unsigned v)
{
	if (p->m_8 != v)
	{
		p->m_8 = v;
		p->m_dirty = 1;
	}
}
