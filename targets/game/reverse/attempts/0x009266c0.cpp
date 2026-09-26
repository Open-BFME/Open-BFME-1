// ?lessXYZ@@YAHPBURva009266C0Point@@0@Z
// partial score=0.9 date=2026-09-06
struct Rva009266C0Point { int x; int y; int z; };
int lessXYZ(const Rva009266C0Point* a, const Rva009266C0Point* b)
{
	int ax = a->x;
	if (b->x > ax) return 1;
	else if (b->x < ax) return 0;
	else {
		int ay = a->y;
		if (b->y > ay) return 1;
		else if (b->y < ay) return 0;
		else if (a->z < b->z) return 1;
		else return 0;
	}
}
