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

// Retail vtable VA 0x01085DBC; the alternate name defines no table.
extern "C" void *bfmeVftDamageInfoOutput[];
#pragma comment(linker, "/alternatename:_bfmeVftDamageInfoOutput=??_7DamageInfoOutput@@6B@")

Rva001C0840 &Rva001C0840::set(const Rva001C0840Blk *p)
{
	m.vptr = bfmeVftDamageInfoOutput;
	m.a = p->a;
	m.b = p->b;
	m.c = p->c;
	return *this;
}
