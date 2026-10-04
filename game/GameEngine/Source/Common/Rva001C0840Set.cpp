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

// Retail vtable VA 0x01085DBC: the table is emitted elsewhere under its own
// class name, so it is referenced by that name rather than through a stand-in
// plus a linker alias.
extern "C" const char __identifier("??_7DamageInfoOutput@@6B@")[];

Rva001C0840 &Rva001C0840::set(const Rva001C0840Blk *p)
{
	m.vptr = (void *)__identifier("??_7DamageInfoOutput@@6B@");
	m.a = p->a;
	m.b = p->b;
	m.c = p->c;
	return *this;
}
