// cl: /EHs-c-
//
// Bounds pass at 0x00784090 over the APT queued item that 0x00785FD0's flush
// walks (element cleanup ILT 0x00049062 -> 0x00785300 reads the same layout):
// a pointer range at this+4/+8, each entry dispatching on its virtual type at
// slot 1 (types 0/1 -> 24-byte triangle list via slot 3, type 2 -> 16-byte
// record list via slot 4), and the six-float affine transform at this+0x10.
// Every transformed point widens [min, max]; the second output becomes the
// extent max - min.  Reached through ILT 0x0001B69E; owner name not recovered.

struct Rva00784090Point
{
	float x;
	float y;
};

struct Rva00784090Triangle
{
	Rva00784090Point p0;
	Rva00784090Point p1;
	Rva00784090Point p2;
};

struct Rva00784090Quad
{
	Rva00784090Point p0;
	Rva00784090Point p1;
};

struct Rva00784090TriangleList
{
	char pad[8];
	Rva00784090Triangle *begin;
	Rva00784090Triangle *end;
};

struct Rva00784090QuadList
{
	char pad[0xc];
	Rva00784090Quad *begin;
	Rva00784090Quad *end;
};

class Rva00784090Entry
{
public:
	virtual void slot0();
	virtual int type();
	virtual void slot2();
	virtual Rva00784090TriangleList *triangles();
	virtual Rva00784090QuadList *quads();
};

struct Rva00784090Affine
{
	float a;
	float b;
	float c;
	float d;
	float tx;
	float ty;

	__forceinline void apply(const Rva00784090Point &in, Rva00784090Point &out) const
	{
		out.x = in.x * a + in.y * c + tx;
		out.y = in.x * b + in.y * d + ty;
	}
};

class Rva00785FD0Item
{
public:
	void rva00784090Bounds(Rva00784090Point *minPt, Rva00784090Point *maxPt);

private:
	void *m_vtbl;
	Rva00784090Entry **m_begin;
	Rva00784090Entry **m_end;
	int m_pad;
	Rva00784090Affine m_xform;
};

void Rva00785FD0Item::rva00784090Bounds(Rva00784090Point *minPt, Rva00784090Point *maxPt)
{
	minPt->x = 99999.0f;
	minPt->y = 99999.0f;
	maxPt->x = -99999.0f;
	maxPt->y = -99999.0f;

	Rva00784090Point p;
	for (Rva00784090Entry **it = m_begin; it != m_end; ++it)
	{
		Rva00784090Entry *entry = *it;
		switch (entry->type())
		{
		case 0:
		case 1:
		{
			Rva00784090TriangleList *list = entry->triangles();
			if (list == 0)
				break;
			for (Rva00784090Triangle *t = list->begin; t != list->end; ++t)
			{
				const Rva00784090Point &v0 = t->p0;
				const Rva00784090Point &v1 = t->p1;
				const Rva00784090Point &v2 = t->p2;
				m_xform.apply(v0, p);
				if (p.x < minPt->x)
					minPt->x = p.x;
				else if (p.x > maxPt->x)
					maxPt->x = p.x;
				if (minPt->y > p.y)
					minPt->y = p.y;
				else if (maxPt->y < p.y)
					maxPt->y = p.y;
				m_xform.apply(v2, p);
				if (p.x < minPt->x)
					minPt->x = p.x;
				else if (p.x > maxPt->x)
					maxPt->x = p.x;
				if (minPt->y > p.y)
					minPt->y = p.y;
				else if (maxPt->y < p.y)
					maxPt->y = p.y;
				m_xform.apply(v1, p);
				if (p.x < minPt->x)
					minPt->x = p.x;
				else if (p.x > maxPt->x)
					maxPt->x = p.x;
				if (minPt->y > p.y)
					minPt->y = p.y;
				else if (maxPt->y < p.y)
					maxPt->y = p.y;
			}
			break;
		}
		case 2:
		{
			Rva00784090QuadList *list = entry->quads();
			if (list == 0)
				break;
			for (Rva00784090Quad *q = list->begin; q != list->end; ++q)
			{
				const Rva00784090Point &v1 = q->p1;
				m_xform.apply(v1, p);
				if (p.x < minPt->x)
					minPt->x = p.x;
				else if (p.x > maxPt->x)
					maxPt->x = p.x;
				if (minPt->y > p.y)
					minPt->y = p.y;
				else if (maxPt->y < p.y)
					maxPt->y = p.y;
				const Rva00784090Point &v0 = q->p0;
				m_xform.apply(v0, p);
				if (p.x < minPt->x)
					minPt->x = p.x;
				else if (p.x > maxPt->x)
					maxPt->x = p.x;
				if (minPt->y > p.y)
					minPt->y = p.y;
				else if (maxPt->y < p.y)
					maxPt->y = p.y;
			}
			break;
		}
		}
	}

	maxPt->x = maxPt->x - minPt->x;
	maxPt->y = maxPt->y - minPt->y;
}
