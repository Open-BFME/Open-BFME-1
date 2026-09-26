// cl: /O2 /Ob0

struct Rva00591200Blk
{
	int a;
	int b;
	int c;
	int d;
	int e;
	char f;
};

class Rva00591200
{
	Rva00591200Blk m;

public:
	Rva00591200 &set(const Rva00591200Blk *p);
};

Rva00591200 &Rva00591200::set(const Rva00591200Blk *p)
{
	m.a = p->a;
	m.c = p->c;
	m.d = p->d;
	m.e = p->e;
	m.f = p->f;
	return *this;
}
