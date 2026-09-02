// ?rva00B00260RotateVec3Array@@YAXPAURva00B00260Vec3@@PBU1@PBURva00B00260Mat3D@@H@Z
// partial score=0.93 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c-
// Array rotate: 3x4 Matrix3D times Vec3, translation column unused.

struct Rva00B00260Vec3
{
	float x;
	float y;
	float z;
};

struct Rva00B00260Mat3D
{
	float m[3][4];
};

void rva00B00260RotateVec3Array(Rva00B00260Vec3 *out, const Rva00B00260Vec3 *in,
	const Rva00B00260Mat3D *mtx, int count)
{
	int n = count;
	Rva00B00260Vec3 *d = out;
	const Rva00B00260Mat3D *m = mtx;
	const Rva00B00260Vec3 *s = in;

	if (n <= 0)
		return;

	while (n--)
	{
		d->x = s->z * m->m[0][2] + s->y * m->m[0][1] + s->x * m->m[0][0];
		d->y = s->x * m->m[1][0] + s->z * m->m[1][2] + s->y * m->m[1][1];
		d->z = s->z * m->m[2][2] + s->y * m->m[2][1] + s->x * m->m[2][0];
		++s;
		++d;
	}
}
