// ?bfmeConsiderEZ@BfmeHostEZ@@QAEXPAVBfmeNodeEZ@@PBVBfmeVec2EZ@@@Z
// Retail RVA 0x001A3280, 167 bytes.

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum ObjectID
{
	OBJECT_ID_NONE = 0
};

class Object
{
public:
	unsigned char m_bfmeHeadEZ[0x38];
	Coord3D m_bfmePosEZ;
};

class Pathfinder
{
public:
	bool slowDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to, ObjectID id);
	bool worldLineNoHit(const Coord3D *from, const Coord3D *to);
};

class AI
{
public:
	unsigned char m_bfmeHeadEZ[0xc];
	Pathfinder *m_bfmePathEZ;
};

extern AI *TheAI;

class BfmeNodeEZ
{
public:
	Coord3D m_bfmePosEZ;
	int m_bfmeTagEZ;
};

class BfmeVec2EZ
{
public:
	float x;
	float y;
};

class BfmeHostEZ
{
public:
	void bfmeConsiderEZ(BfmeNodeEZ *n, const BfmeVec2EZ *p);

	Coord3D m_bfmePosEZ;
	int m_bfmeTagEZ;
	float m_bfmeBestEZ;
	BfmeNodeEZ *m_bfmeNodeEZ;
	Object *m_bfmeObjEZ;
};

void BfmeHostEZ::bfmeConsiderEZ(BfmeNodeEZ *n, const BfmeVec2EZ *p)
{
	volatile float padding[3];
	(void)padding;
	float py = *(const volatile float *)&p->y;
	float px = *(const volatile float *)&p->x;
	padding[0] = px - n->m_bfmePosEZ.x;
	float dy = py - n->m_bfmePosEZ.y;
	float *dxp = (float *)&padding[0];
	float d2 = dy * dy + dxp[0] * dxp[0];
	if (m_bfmeTagEZ != 0 && d2 >= m_bfmeBestEZ)
		return;

	Pathfinder *path = TheAI->m_bfmePathEZ;
	if (!path->slowDoesPathExist(m_bfmeObjEZ,
		&m_bfmeObjEZ->m_bfmePosEZ, &n->m_bfmePosEZ, OBJECT_ID_NONE))
		return;

	Pathfinder *path2 = TheAI->m_bfmePathEZ;
	if (!path2->worldLineNoHit(&m_bfmeObjEZ->m_bfmePosEZ,
		&n->m_bfmePosEZ))
		return;

	m_bfmeTagEZ = n->m_bfmeTagEZ;
	m_bfmePosEZ = n->m_bfmePosEZ;
	m_bfmeBestEZ = d2;
	m_bfmeNodeEZ = n;
}
