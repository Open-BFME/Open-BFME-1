// ?calc@Rva00064410Catmull@@YAXPAURva00064410Point@@PBURva00064410Point@@11M@Z
// Retail 0x00064410. Evaluates each coordinate of a four-point Catmull-Rom curve.
// cl: /DNDEBUG /MD /EHsc

struct Rva00064410Point
{
	float x;
	float y;
	float z;
};

class Rva00064410Catmull
{
public:
	static float evaluate(float p0, float p1, float p2, float p3, float t);
};

#pragma comment(linker, "/alternatename:?evaluate@Rva00064410Catmull@@SAMMMMMM@Z=?j_0003757e@@YAXXZ")

__declspec(noinline) float Rva00064410Catmull::evaluate(
	float p0, float p1, float p2, float p3, float t)
{
	return p0 + p1 + p2 + p3 + t;
}

void calc(
	Rva00064410Point *out,
	const Rva00064410Point *p0,
	const Rva00064410Point *p1,
	const Rva00064410Point *p2,
	const Rva00064410Point *p3,
	float t)
{
	volatile float z = Rva00064410Catmull::evaluate(p0->z, p1->z, p2->z, p3->z, t);
	volatile float y = Rva00064410Catmull::evaluate(p0->y, p1->y, p2->y, p3->y, t);
	float x = Rva00064410Catmull::evaluate(p0->x, p1->x, p2->x, p3->x, t);
	out->x = x;
	out->y = y;
	out->z = z;
}
