// cl: /O2 /Ob0

struct Rva0075B710Obj
{
	char pad[0xC8];
	int m_C8;
};

void set(Rva0075B710Obj *p, int x)
{
	if (p)
		p->m_C8 = x;
}
