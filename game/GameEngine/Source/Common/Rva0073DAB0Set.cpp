// cl: /O2 /Ob0

struct Rva0073DAB0Blk
{
	int a;
	int b;
	int c;
	char d;
};

class Rva0073DAB0
{
	Rva0073DAB0Blk m;

public:
	Rva0073DAB0 &set(const Rva0073DAB0Blk *p);
};

Rva0073DAB0 &Rva0073DAB0::set(const Rva0073DAB0Blk *p)
{
	m.a = p->a;
	m.b = p->b;
	m.c = p->c;
	m.d = p->d;
	return *this;
}
