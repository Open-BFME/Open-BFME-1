// ??0Rva008D9EC0Owner@@QAE@PAURva008D9EC0Vec3@@000@Z
// partial score=0.85 date=2026-09-06
// ??0Rva008D9EC0Owner@@QAE@PAURva008D9EC0Vec3@@000@Z
struct Rva008D9EC0Vec3 { float x; float y; float z; };
struct Rva008D9EC0Owner {
	bool m_flag;
	int m_count;
	int m_index;
	int m_field_c;
	float m_diff1[3];
	float m_diff2[3];
	Rva008D9EC0Vec3* m_pA;
	Rva008D9EC0Vec3* m_pC;
	Rva008D9EC0Owner(Rva008D9EC0Vec3* a, Rva008D9EC0Vec3* b, Rva008D9EC0Vec3* c, Rva008D9EC0Vec3* d);
};
Rva008D9EC0Owner::Rva008D9EC0Owner(Rva008D9EC0Vec3* a, Rva008D9EC0Vec3* b, Rva008D9EC0Vec3* c, Rva008D9EC0Vec3* d)
{
	m_flag = true;
	m_pC = c;
	m_index = -1;
	m_count = 0;
	m_field_c = 0;
	m_pA = a;
	m_diff1[0] = c->x - a->x;
	m_diff1[1] = c->y - a->y;
	m_diff1[2] = c->z - a->z;
	m_diff2[0] = d->x - b->x;
	m_diff2[1] = d->y - b->y;
	m_diff2[2] = d->z - b->z;
}
