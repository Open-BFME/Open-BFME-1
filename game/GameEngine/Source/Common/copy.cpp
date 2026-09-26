// cl: /O2 /Ob0

struct Rva00222540Ten
{
	int x[10];
};

struct Rva00222540Obj
{
	int a;
	Rva00222540Ten t;
};

void copy(Rva00222540Obj *dst, const Rva00222540Obj *src)
{
	if (dst)
	{
		dst->a = src->a;
		dst->t = src->t;
	}
}
