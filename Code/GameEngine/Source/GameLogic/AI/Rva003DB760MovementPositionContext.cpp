// cl: /DNDEBUG /MD
//
// Retail 0x003DB760 (143 bytes): constructor of a Pathfinder-side movement
// context.  The only caller (0x003F5E20) passes the Pathfinder, the moving
// Object, a record whose +0x10 dword is copied, and two flag bytes.
//
// +0x0C..+0x17 is the same 12-byte record Pathfinder::validMovementPosition
// (0x003DB520, PathfinderValidMovementPosition.cpp) builds on its stack from
// the same template reads (+0x444 minus one, +0x4CC == 0) and the same
// Object::bfmeIsComputerControlled call (ILT 0x00010EA1).  Retail reads +0x10
// after that call and issues every store after all three calls; an inlined
// setter on the record, whose arguments MSVC evaluates right to left,
// reproduces that order.

class LocomotorOverridable
{
public:
	LocomotorOverridable *friend_getFinalOverride();

	unsigned char m_bfmeHeadYY[4];
	LocomotorOverridable *m_bfme04YY;
	unsigned char m_bfmeMidYY[0x43c];
	int m_bfme444YY;
	unsigned char m_bfmeMid2YY[0x84];
	char m_bfme4CCYY;
};

class Object
{
public:
	bool bfmeIsComputerControlled() const;

	unsigned char m_bfmeHeadYY[4];
	LocomotorOverridable *m_bfme04YY;
};

class BfmeCfgYY
{
public:
	unsigned char m_bfmeHeadYY[0x10];
	int m_bfme10YY;
};

static __forceinline LocomotorOverridable *bfmeFinalYY(LocomotorOverridable *p)
{
	if (p == 0)
		return 0;

	if (p->m_bfme04YY == 0)
		return p;

	return p->m_bfme04YY->friend_getFinalOverride();
}

// Layout and field names as landed at 0x003DB520.
struct BfmeMovementPositionInfo
{
	unsigned int m_surfaces;
	unsigned char m_allowAircraftGoal;
	unsigned char m_computerControlled;
	unsigned char m_pad06[2];
	int m_maxLayer;

	void set(unsigned int surfaces, char aircraftGoalFlag,
		bool computerControlled, int maxLayer)
	{
		m_surfaces = surfaces;
		m_allowAircraftGoal = aircraftGoalFlag == 0;
		m_computerControlled = computerControlled;
		m_maxLayer = maxLayer - 1;
	}
};

class BfmeCtxYY
{
public:
	BfmeCtxYY(void *a, Object *o, BfmeCfgYY *c, char d, char e);

	void *m_bfme00YY;
	Object *m_bfme04YY;
	BfmeCfgYY *m_bfme08YY;
	BfmeMovementPositionInfo m_bfme0CYY;
	char m_bfme18YY;
	char m_bfme19YY;
	char m_bfme1AYY;
	char m_bfme1BYY;
	char m_bfme1CYY;
};

BfmeCtxYY::BfmeCtxYY(void *a, Object *o, BfmeCfgYY *c, char d, char e)
{
	m_bfme00YY = a;
	m_bfme04YY = o;
	m_bfme08YY = c;

	int n = bfmeFinalYY(o->m_bfme04YY)->m_bfme444YY;
	char f = bfmeFinalYY(o->m_bfme04YY)->m_bfme4CCYY;
	m_bfme0CYY.set(c->m_bfme10YY, f, o->bfmeIsComputerControlled(), n);
	m_bfme18YY = 0;
	m_bfme19YY = d;
	m_bfme1AYY = 1;
	m_bfme1BYY = 0;
	m_bfme1CYY = e;
}
