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

// Retail spells this accessor ?getFinalOverride@Overridable@@QBEPBV1@XZ
// (public const, upstream Overridable.h); the TU-local stand-in carries the
// template layout the bodies read, so it takes the defining class/member name.
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	unsigned char m_bfmeHeadYY[4];
	Overridable *m_nextOverride;
	unsigned char m_bfmeMidYY[0x43c];
	int m_bfme444YY;
	unsigned char m_bfmeMid2YY[0x84];
	char m_bfme4CCYY;
};

class Gen_0026f940
{
public:
	int m();
};

class Object
{
public:
	bool bfmeIsComputerControlled() const;

	unsigned char m_bfmeHeadYY[4];
	Overridable *m_nextOverride;
	unsigned char m_bfmeMidYY[0x1fc];
	Gen_0026f940 *m_bfme204YY;
};

class Rva003DB760Config
{
public:
	unsigned char m_bfmeHeadYY[0x10];
	int m_bfme10YY;
};

static __forceinline Overridable *bfmeFinalYY(Overridable *p)
{
	if (p == 0)
		return 0;

	if (p->m_nextOverride == 0)
		return p;

	return const_cast<Overridable *>( p->m_nextOverride->getFinalOverride() );
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

class Rva003DB760Context
{
public:
	Rva003DB760Context(void *a, Object *o, Rva003DB760Config *c, char d, char e);

	void *m_bfme00YY;
	Object *m_nextOverride;
	Rva003DB760Config *m_bfme08YY;
	BfmeMovementPositionInfo m_bfme0CYY;
	char m_bfme18YY;
	char m_bfme19YY;
	char m_bfme1AYY;
	char m_bfme1BYY;
	char m_bfme1CYY;
};

Rva003DB760Context::Rva003DB760Context(void *a, Object *o, Rva003DB760Config *c, char d, char e)
{
	m_bfme00YY = a;
	m_nextOverride = o;
	m_bfme08YY = c;

	int n = bfmeFinalYY(o->m_nextOverride)->m_bfme444YY;
	char f = bfmeFinalYY(o->m_nextOverride)->m_bfme4CCYY;
	m_bfme0CYY.set(c->m_bfme10YY, f, o->bfmeIsComputerControlled(), n);
	m_bfme18YY = 0;
	m_bfme19YY = d;
	m_bfme1AYY = 1;
	m_bfme1BYY = 0;
	m_bfme1CYY = e;
}

// Retail 0x003DB820 (175 bytes): a second, wider context built the same way.
// Its only caller (0x003E6EE0, through ILT 0x00049EE0) passes eight
// arguments; the same 12-byte BfmeMovementPositionInfo record now sits at
// +0x04, and +0x20 caches the Object's +0x204 sub-object's +0x164 dword
// (Gen_0026f940::m) or zero when that sub-object is missing.
class Rva003DB820Context
{
public:
	Rva003DB820Context(void *a, Rva003DB760Config *c, char d, int e, Object *o,
		char f, int g, int h);

	void *m_bfme00YY;
	BfmeMovementPositionInfo m_nextOverride;
	char m_bfme10YY;
	char m_bfme11YY;
	int m_bfme14YY;
	Object *m_bfme18YY;
	int m_bfme1CYY;
	int m_bfme20YY;
	unsigned char m_bfme24YY[8];
	int m_bfme2CYY;
};

Rva003DB820Context::Rva003DB820Context(void *a, Rva003DB760Config *c, char d,
	int e, Object *o, char f, int g, int h)
{
	m_bfme00YY = a;

	int n = bfmeFinalYY(o->m_nextOverride)->m_bfme444YY;
	char flag = bfmeFinalYY(o->m_nextOverride)->m_bfme4CCYY;
	m_nextOverride.set(c->m_bfme10YY, flag, o->bfmeIsComputerControlled(), n);
	m_bfme10YY = d;
	m_bfme11YY = f;
	m_bfme14YY = e;
	m_bfme18YY = o;
	m_bfme1CYY = g;
	m_bfme2CYY = h;
	m_bfme20YY = o->m_bfme204YY != 0 ? o->m_bfme204YY->m() : 0;
}
