// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00537740Cursor
{
	unsigned char *m_0;
	unsigned m_4;
};

unsigned char *rva00537740(Rva00537740Cursor *p)
{
	--p->m_4;
	unsigned char *cur = p->m_0;
	p->m_0 = cur + 1;
	return cur;
}
