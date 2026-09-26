// cl: /O2 /Ob0

struct Rva00422F80Obj
{
	int a;
	int b;
	int c;
	int d;
	int e;
	char f;
};

void copy(Rva00422F80Obj *dst, const Rva00422F80Obj *src)
{
	if (dst)
	{
		dst->a = src->a;
		dst->b = src->b;
		dst->c = src->c;
		dst->d = src->d;
		dst->e = src->e;
		dst->f = src->f;
	}
}
