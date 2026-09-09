// ?parseGeometryType@GeometryInfo@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.97 date=2026-09-09
// Canonical identity: GeometryInfo::parseGeometryType is registered by
// ThingTemplate's Geometry field and tail-calls GeometryInfo::calcBoundingStuff.

extern "C" const char *const GeometryNames[];

class INI
{
public:
	const char *getNextToken(const char *sep) throw();
	static int scanIndexList(const char *s, const char *const *list) throw();
};

struct BfmeElem60
{
	__forceinline BfmeElem60() throw()
	{
		m_00 = 0;
		m_04 = 1.0f;
		m_08 = 1.0f;
		m_0C = 1.0f;
		m_10 = 0;
		m_14 = 0;
		m_18 = 0;
		m_1C = 0;
		m_20 = 1;
	}

	__forceinline BfmeElem60(const BfmeElem60 &o) throw()
	{
		m_00 = o.m_00;
		m_04 = o.m_04;
		m_08 = o.m_08;
		m_0C = o.m_0C;
		m_10 = o.m_10;
		m_14 = o.m_14;
		m_18 = o.m_18;
		m_1C = o.m_1C;
		m_20 = o.m_20;
	}

	volatile int m_00;
	volatile float m_04;
	volatile float m_08;
	volatile float m_0C;
	volatile int m_10;
	volatile int m_14;
	volatile int m_18;
	volatile char *m_1C;
	unsigned char m_20;
};

class BfmeVec60
{
public:
	void resize(unsigned int n, BfmeElem60 e) throw();
	BfmeElem60 *m_begin;
	BfmeElem60 *m_end;
	BfmeElem60 *m_capacity;
};

class GeometryInfo
{
public:
	static void parseGeometryType(INI *, void *, void *, const void *);
	unsigned char m_head[0x2c];
	BfmeVec60 m_shapes;

private:
	void calcBoundingStuff() throw();
};

void GeometryInfo::parseGeometryType(INI *ini, void *, void *store, const void *)
{
	int idx = INI::scanIndexList(ini->getNextToken(0), GeometryNames);
	GeometryInfo *o = (GeometryInfo *)store;
	o->m_shapes.resize(1, BfmeElem60());
	o->m_shapes.m_begin->m_00 = idx;
	o->calcBoundingStuff();
}
