// ?rva008d6450@@YAXPAUElem16@@0@Z
// partial score=0.85 date=2026-09-06
// ?rva008d6450@@YAXPAUElem16@@0@Z

struct Elem16
{
	float x;
	float y;
	int i;
	int j;
};

struct Temp2
{
	int i;
	int j;
};

void __cdecl rva008d6450(Elem16 *a, Elem16 *b)
{
	Temp2 t;
	t.i = a->i;
	float ax = a->x;
	t.j = a->j;
	float ay = a->y;

	a->x = b->x;
	a->y = b->y;
	a->i = b->i;
	a->j = b->j;

	b->x = ax;
	b->y = ay;
	b->i = t.i;
	b->j = t.j;
}
