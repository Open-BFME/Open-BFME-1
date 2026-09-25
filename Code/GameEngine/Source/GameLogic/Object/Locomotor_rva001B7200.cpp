// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc-
// Retail 0x001B7200, 467 bytes, thiscall RET 8.  The receiver is the
// locomotor: it is passed as the second argument of the Path method at
// 0x003FD7D0, where the matched AIUpdateInterface::needToRotate (0x00271390)
// passes its current locomotor, and it is the receiver of the 0x001B49E0
// transform setter.  No caller, vtable slot or string names the method, so
// it keeps its address.  Object+0x1FC m_contain, Thing+0x38 m_cachedPos and
// AIUpdateInterface+0x140 m_path are layout-witnessed; the contain module's
// getHordeContainInterface is vtable slot 26 (+0x68) as in the landed
// AIHordeExitState_rva0016FB20.cpp.
//
// The by-value Coord3D copies with a member-wise copy constructor and the
// in-place sub() are what keep the object's z on the frame while x and y are
// forwarded into the x87 subtraction; the inline accessors in the path
// conditional are what keep its jmp / xor edi,edi join.

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Coord3D() {}
	Coord3D(const Coord3D &that) { x = that.x; y = that.y; z = that.z; }
	void sub(const Coord3D *that) { x -= that->x; y -= that->y; z -= that->z; }
	Real GetLengthSqrd() const;
};

class Object;
class Rva001B7200Locomotor;

// 36-byte out record of the Path method at 0x003FD7D0.
struct Rva001B7200PathPoint
{
	Real m_real00;
	Coord3D m_coord04;
	Real m_real10[3];
	PathfindLayerEnum m_layer;
	Int m_int20;
};

class Path
{
public:
	void Rva003FDCF0(Coord3D &out);
	void computePointOnPath(Object *object, Rva001B7200Locomotor *locomotor,
		Rva001B7200PathPoint *out, Bool flag);
	void bfmeAdvanceCachedPoint(Coord3D &point);
};

class AIUpdateInterface
{
public:
	Path *getPath() { return m_path; }

	char m_pad000[0x140];
	Path *m_path;
};

#define RVA001B7200_SLOT(n) virtual void slot##n() = 0;

class HordeContainInterface
{
public:
	RVA001B7200_SLOT(00) RVA001B7200_SLOT(01) RVA001B7200_SLOT(02)
	RVA001B7200_SLOT(03) RVA001B7200_SLOT(04) RVA001B7200_SLOT(05)
	RVA001B7200_SLOT(06) RVA001B7200_SLOT(07) RVA001B7200_SLOT(08)
	RVA001B7200_SLOT(09) RVA001B7200_SLOT(10) RVA001B7200_SLOT(11)
	RVA001B7200_SLOT(12) RVA001B7200_SLOT(13) RVA001B7200_SLOT(14)
	RVA001B7200_SLOT(15) RVA001B7200_SLOT(16) RVA001B7200_SLOT(17)
	RVA001B7200_SLOT(18) RVA001B7200_SLOT(19) RVA001B7200_SLOT(20)
	RVA001B7200_SLOT(21) RVA001B7200_SLOT(22) RVA001B7200_SLOT(23)
	RVA001B7200_SLOT(24) RVA001B7200_SLOT(25) RVA001B7200_SLOT(26)
	RVA001B7200_SLOT(27) RVA001B7200_SLOT(28) RVA001B7200_SLOT(29)
	RVA001B7200_SLOT(30) RVA001B7200_SLOT(31) RVA001B7200_SLOT(32)
	RVA001B7200_SLOT(33) RVA001B7200_SLOT(34) RVA001B7200_SLOT(35)
	RVA001B7200_SLOT(36) RVA001B7200_SLOT(37) RVA001B7200_SLOT(38)
	RVA001B7200_SLOT(39) RVA001B7200_SLOT(40) RVA001B7200_SLOT(41)
	RVA001B7200_SLOT(42) RVA001B7200_SLOT(43) RVA001B7200_SLOT(44)
	RVA001B7200_SLOT(45) RVA001B7200_SLOT(46) RVA001B7200_SLOT(47)
	RVA001B7200_SLOT(48) RVA001B7200_SLOT(49) RVA001B7200_SLOT(50)
	RVA001B7200_SLOT(51) RVA001B7200_SLOT(52) RVA001B7200_SLOT(53)
	RVA001B7200_SLOT(54) RVA001B7200_SLOT(55) RVA001B7200_SLOT(56)
	RVA001B7200_SLOT(57) RVA001B7200_SLOT(58) RVA001B7200_SLOT(59)
	RVA001B7200_SLOT(60) RVA001B7200_SLOT(61) RVA001B7200_SLOT(62)
	RVA001B7200_SLOT(63) RVA001B7200_SLOT(64) RVA001B7200_SLOT(65)
	RVA001B7200_SLOT(66) RVA001B7200_SLOT(67) RVA001B7200_SLOT(68)
	RVA001B7200_SLOT(69) RVA001B7200_SLOT(70) RVA001B7200_SLOT(71)
	RVA001B7200_SLOT(72) RVA001B7200_SLOT(73) RVA001B7200_SLOT(74)
	RVA001B7200_SLOT(75) RVA001B7200_SLOT(76) RVA001B7200_SLOT(77)
	RVA001B7200_SLOT(78) RVA001B7200_SLOT(79) RVA001B7200_SLOT(80)
	RVA001B7200_SLOT(81) RVA001B7200_SLOT(82) RVA001B7200_SLOT(83)
	RVA001B7200_SLOT(84) RVA001B7200_SLOT(85) RVA001B7200_SLOT(86)
	RVA001B7200_SLOT(87) RVA001B7200_SLOT(88) RVA001B7200_SLOT(89)
	RVA001B7200_SLOT(90) RVA001B7200_SLOT(91) RVA001B7200_SLOT(92)
	RVA001B7200_SLOT(93) RVA001B7200_SLOT(94) RVA001B7200_SLOT(95)
	RVA001B7200_SLOT(96) RVA001B7200_SLOT(97) RVA001B7200_SLOT(98)
	RVA001B7200_SLOT(99) RVA001B7200_SLOT(100)
	virtual void slot101(Coord3D *point, Real *reals, Int value,
		PathfindLayerEnum layer) = 0;
	RVA001B7200_SLOT(102) RVA001B7200_SLOT(103) RVA001B7200_SLOT(104)
	virtual Bool slot105() = 0;
};

class ContainModuleInterface
{
public:
	RVA001B7200_SLOT(00) RVA001B7200_SLOT(01) RVA001B7200_SLOT(02)
	RVA001B7200_SLOT(03) RVA001B7200_SLOT(04) RVA001B7200_SLOT(05)
	RVA001B7200_SLOT(06) RVA001B7200_SLOT(07) RVA001B7200_SLOT(08)
	RVA001B7200_SLOT(09) RVA001B7200_SLOT(10) RVA001B7200_SLOT(11)
	RVA001B7200_SLOT(12) RVA001B7200_SLOT(13) RVA001B7200_SLOT(14)
	RVA001B7200_SLOT(15) RVA001B7200_SLOT(16) RVA001B7200_SLOT(17)
	RVA001B7200_SLOT(18) RVA001B7200_SLOT(19) RVA001B7200_SLOT(20)
	RVA001B7200_SLOT(21) RVA001B7200_SLOT(22) RVA001B7200_SLOT(23)
	RVA001B7200_SLOT(24) RVA001B7200_SLOT(25)
	virtual HordeContainInterface *getHordeContainInterface() = 0;
};

#undef RVA001B7200_SLOT

class Thing
{
public:
	const Coord3D *getPosition() const { return &m_cachedPos; }
	void setPosition(const Coord3D *pos);

	char m_pad000[0x38];
	Coord3D m_cachedPos;
};

class Object : public Thing
{
public:
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	void setLayer(PathfindLayerEnum layer);

	char m_pad044[0x1fc - 0x44];
	ContainModuleInterface *m_contain;
	char m_pad200[4];
	AIUpdateInterface *m_ai;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
	UnsignedInt getFrame() { return m_frame; }

	char m_pad000[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;
extern Real g_bfmeScaleBC;

void *Rva001B4750Get(void *object);

// The first argument of the retail body: an object ID sits at +0xA8.
class Rva001B7200IdRecord
{
public:
	char m_pad000[0xa8];
	Int m_int0A8;
};

class Rva001B49E0Owner
{
public:
	void setPosition(const Coord3D *position);
};

class Rva001B7200Locomotor : public Rva001B49E0Owner
{
public:
	Bool rva001B7200(Object *object, Rva001B7200IdRecord *record);

	char m_pad000[0x60];
	UnsignedInt m_dword60;
};

Bool Rva001B7200Locomotor::rva001B7200(Object *object, Rva001B7200IdRecord *record)
{
	Int id = record->m_int0A8;
	if (id == 0)
		return false;
	if (TheGameLogic->findObjectByID(id) == 0)
		return false;

	ContainModuleInterface *contain = object->getContain();
	if (contain == 0 || contain->getHordeContainInterface() == 0)
		return false;

	HordeContainInterface *horde = contain->getHordeContainInterface();
	AIUpdateInterface *ai = object->getAIUpdateInterface();
	Path *path = ai ? ai->getPath() : 0;
	if (path == 0)
		return false;

	Coord3D pathPos;
	path->Rva003FDCF0(pathPos);
	Rva001B7200PathPoint point;
	path->computePointOnPath(object, this, &point, false);

	Coord3D pointPos = point.m_coord04;
	Coord3D delta = *object->getPosition();
	delta.sub(&pathPos);
	if (delta.GetLengthSqrd() > g_bfmeScaleBC)
	{
		object->setPosition(&pathPos);
		setPosition(&pathPos);
		object->setLayer(point.m_layer);
		horde->slot101(&pointPos, point.m_real10, point.m_int20, point.m_layer);
		m_dword60 = TheGameLogic->getFrame() + 0x3c;
		return true;
	}

	if (!horde->slot105() && TheGameLogic->getFrame() <= m_dword60)
		return true;

	Path *cached = static_cast<Path *>(Rva001B4750Get(object));
	if (cached == 0)
		return false;

	cached->bfmeAdvanceCachedPoint(delta);
	cached->bfmeAdvanceCachedPoint(delta);
	cached->bfmeAdvanceCachedPoint(delta);
	cached->computePointOnPath(object, this, &point, false);
	if (point.m_int20 == 0x7fffffff)
		return false;
	cached->bfmeAdvanceCachedPoint(delta);
	return false;
}
