class BfmeVec3HN
{
public:
	float m_bfmeXHN;
	float m_bfmeYHN;
	float m_bfmeZHN;
};

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition() const;
};

class BfmeObjHN
{
public:
	unsigned char m_bfmeHeadHN[0x38];
	float m_bfme38HN;
	float m_bfme3cHN;
	float m_bfme40HN;
	unsigned char m_bfmeGap2HN[0x68];
	GeometryInfo m_bfmeGeomHN;
};

struct Rva003FD060TerrainLogic
{
	virtual void bfmeVt00HN();
	virtual void bfmeVt01HN();
	virtual void bfmeVt02HN();
	virtual void bfmeVt03HN();
	virtual void bfmeVt04HN();
	virtual void bfmeVt05HN();
	virtual void bfmeVt06HN();
	virtual void bfmeVt07HN();
	virtual void bfmeVt08HN();
	virtual void bfmeVt09HN();
	virtual void bfmeVt10HN();
	virtual void bfmeVt11HN();
	virtual void bfmeVt12HN();
	virtual void bfmeVt13HN();
	virtual void bfmeVt14HN();
	virtual bool bfmeReachHN(BfmeVec3HN *a, BfmeVec3HN *b);
};

// TheAI's pathfinder at +0x0C; ILT 0x00033E06 -> 0x003EE780 is the matched
// two-argument wrapper ?isAttackViewBlockedByObstacle@Pathfinder@@QAE_NPBVObject@@PBUCoord3D@@@Z
// (PathfinderAttackViewForwarders.cpp).
class Object;
struct Coord3D;

class Pathfinder
{
public:
	bool isAttackViewBlockedByObstacle(const Object *obj, const Coord3D *pos);
};

class AI
{
public:
	unsigned char m_bfmeHeadHN[0xc];
	Pathfinder *m_pathfinder;
};

// Retail 0x012EF4CC is EA's singleton; only its type spelling matters for the
// mangled name, so this TU declares it canonically and keeps its own TU-local
// view of the vtable for the members it touches.
class TerrainLogic;

extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;

class BfmeCheckHN
{
public:
	bool bfmeTestHN(BfmeVec3HN *p);

	unsigned char m_bfmeHeadHN[8];
	BfmeObjHN *m_bfme08HN;
};

bool BfmeCheckHN::bfmeTestHN(BfmeVec3HN *p)
{
	BfmeObjHN *o = m_bfme08HN;

	BfmeVec3HN a;

	a.m_bfmeXHN = o->m_bfme38HN;
	a.m_bfmeYHN = o->m_bfme3cHN;
	a.m_bfmeZHN = o->m_bfme40HN;

	BfmeVec3HN b;

	b.m_bfmeXHN = p->m_bfmeXHN;
	b.m_bfmeYHN = p->m_bfmeYHN;
	b.m_bfmeZHN = p->m_bfmeZHN;

	a.m_bfmeZHN = o->m_bfmeGeomHN.getMaxHeightAbovePosition() + a.m_bfmeZHN;

	if (!((Rva003FD060TerrainLogic *)TheTerrainLogic)->bfmeReachHN(&a, &b))
		return false;

	if (TheAI != 0)
	{
		Pathfinder *pathfinder = TheAI->m_pathfinder;

		if (pathfinder->isAttackViewBlockedByObstacle((const Object *)m_bfme08HN, (const Coord3D *)&b))
			return false;
	}

	return true;
}
