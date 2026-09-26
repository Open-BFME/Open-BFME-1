// cl: /O2 /Ob0

struct Rva00422890Blk
{
	int a;
	int b;
	int c;
	int d;
	int e;
	char f;
};

class Rva00422890
{
	Rva00422890Blk m;

public:
	Rva00422890 &set(const Rva00422890Blk *p);
};

Rva00422890 &Rva00422890::set(const Rva00422890Blk *p)
{
	m.a = p->a;
	m.b = p->b;
	m.c = p->c;
	m.d = p->d;
	m.e = p->e;
	m.f = p->f;
	return *this;
}
