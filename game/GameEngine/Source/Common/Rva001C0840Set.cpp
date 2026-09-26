// cl: /O2 /Ob0

struct Rva001C0840Blk
{
	void *vptr;
	int a;
	int b;
	char c;
};

class Rva001C0840
{
	Rva001C0840Blk m;

public:
	Rva001C0840 &set(const Rva001C0840Blk *p);
};

Rva001C0840 &Rva001C0840::set(const Rva001C0840Blk *p)
{
	m.vptr = (void *)0x01085DBC;
	m.a = p->a;
	m.b = p->b;
	m.c = p->c;
	return *this;
}
