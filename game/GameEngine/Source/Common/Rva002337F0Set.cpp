// cl: /O2 /Ob0

struct Rva002337F0Blk
{
	int a;
	int b;
	int c;
	int d;
	char e;
	int f;
	int g;
};

class Rva002337F0
{
	Rva002337F0Blk m;

public:
	Rva002337F0 &set(const Rva002337F0Blk *p);
};

Rva002337F0 &Rva002337F0::set(const Rva002337F0Blk *p)
{
	m.a = p->a;
	m.b = p->b;
	m.c = p->c;
	m.d = p->d;
	m.e = p->e;
	m.f = p->f;
	m.g = p->g;
	return *this;
}
