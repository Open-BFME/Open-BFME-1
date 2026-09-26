// cl: /O2 /Ob0

struct Rva00193660Src
{
	unsigned short a;
	unsigned short b;
	unsigned short c;
	unsigned short d;
	int e;
	unsigned short *ref;
};

class Rva00193660
{
	unsigned short a;
	unsigned short b;
	unsigned short c;
	unsigned short d;
	int e;
	unsigned short *ref;

public:
	Rva00193660 &set(const Rva00193660Src *p);
};

Rva00193660 &Rva00193660::set(const Rva00193660Src *p)
{
	a = p->a;
	b = p->b;
	c = p->c;
	d = p->d;
	e = p->e;
	unsigned short *r = p->ref;
	ref = r;
	if (r)
		++*r;
	return *this;
}
