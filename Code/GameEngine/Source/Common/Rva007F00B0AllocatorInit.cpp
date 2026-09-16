// Address-derived reconstruction of retail 0x007F00B0 (98 bytes).
// The caller and the neighbouring FESL allocator bodies establish a three-
// pointer interface object: vptr, acquire callback, release callback.

struct Rva007F00B0Allocator
{
	void *m_vtable;
	void *m_allocate;
	void *m_release;
};

typedef void *(__cdecl *Rva007F00B0Allocate)(unsigned int, int);

extern Rva007F00B0Allocator *g_Rva0130A5B0;

void *operator new(unsigned int size);

void Rva007F00B0(void *allocate, void *release)
{
	Rva007F00B0Allocator *p;

	if (g_Rva0130A5B0)
		return;

	if (allocate)
	{
		p = (Rva007F00B0Allocator *)((Rva007F00B0Allocate)allocate)(12, 0);
		if (p)
			p->m_allocate = allocate;
		else
			goto clear;
	}
	else
	{
		p = (Rva007F00B0Allocator *)::operator new(12);
		if (p)
			p->m_allocate = (void *)0x00BEFFE0;
		else
			goto clear;
	}

	p->m_vtable = (void *)0x0112A5C4;
	if (!release)
		release = (void *)0x00BEFFF0;
	p->m_release = release;
	g_Rva0130A5B0 = p;
	return;

clear:
	g_Rva0130A5B0 = 0;
}
