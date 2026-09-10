// ?move@Rva001B7200Locomotor@@QAE_NPAVObject@@PAVRva001B7200TerrainResult@@@Z
// partial score=0.94 date=2026-09-10
// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc-
// Retail 0x001B7200 is the Bool helper called by the appearance-6 mover at
// 0x001BB530.  The caller supplies the Object and the terrain/path result
// returned by the BFME TerrainLogic query; the fields and callee ABIs below
// are taken from the complete retail body and its caller.

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned UnsignedInt;

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Real GetLengthSqrd() const;
};

struct Rva001B7200Delta
{
	Real x;
	Real y;
	Real z;

	Real GetLengthSqrd() const;
};

class Object;
class Rva001B7200Locomotor;
class Rva001B7200Path;

class GameLogic
{
public:
	Object *findObjectByID(Int id);

	char m_pad000[0x3c];
	UnsignedInt m_frame;
};

class Rva001B7200TerrainResult
{
public:
	char m_pad000[0xa8];
	Int m_objectID;
};

struct Rva001B7200PointInfo
{
	Real m_distance;
	Coord3D m_position;
	Real m_unknown10;
	Real m_unknown14;
	Real m_unknown18;
	Int m_layer;
	Int m_objectID;
};

class Rva001B7200Path
{
public:
	void getPathPosition(Coord3D *position);
	void computePointOnPath(Object *object, Rva001B7200Locomotor *locomotor,
		Rva001B7200PointInfo *point, Bool useCache);
	void advanceCachedPoint(Coord3D *position);
};

class Rva001B7200AIUpdate
{
public:
	char m_pad000[0x140];
	Rva001B7200Path *m_path;
};

class Rva001B7200HordeContain
{
public:
#define BFME_SLOT(n) virtual void slot##n() = 0;
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03);
	BFME_SLOT(04); BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07);
	BFME_SLOT(08); BFME_SLOT(09); BFME_SLOT(10); BFME_SLOT(11);
	BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14); BFME_SLOT(15);
	BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23);
	BFME_SLOT(24); BFME_SLOT(25); BFME_SLOT(26); BFME_SLOT(27);
	BFME_SLOT(28); BFME_SLOT(29); BFME_SLOT(30); BFME_SLOT(31);
	BFME_SLOT(32); BFME_SLOT(33); BFME_SLOT(34); BFME_SLOT(35);
	BFME_SLOT(36); BFME_SLOT(37); BFME_SLOT(38); BFME_SLOT(39);
	BFME_SLOT(40); BFME_SLOT(41); BFME_SLOT(42); BFME_SLOT(43);
	BFME_SLOT(44); BFME_SLOT(45); BFME_SLOT(46); BFME_SLOT(47);
	BFME_SLOT(48); BFME_SLOT(49); BFME_SLOT(50); BFME_SLOT(51);
	BFME_SLOT(52); BFME_SLOT(53); BFME_SLOT(54); BFME_SLOT(55);
	BFME_SLOT(56); BFME_SLOT(57); BFME_SLOT(58); BFME_SLOT(59);
	BFME_SLOT(60); BFME_SLOT(61); BFME_SLOT(62); BFME_SLOT(63);
	BFME_SLOT(64); BFME_SLOT(65); BFME_SLOT(66); BFME_SLOT(67);
	BFME_SLOT(68); BFME_SLOT(69); BFME_SLOT(70); BFME_SLOT(71);
	BFME_SLOT(72); BFME_SLOT(73); BFME_SLOT(74); BFME_SLOT(75);
	BFME_SLOT(76); BFME_SLOT(77); BFME_SLOT(78); BFME_SLOT(79);
	BFME_SLOT(80); BFME_SLOT(81); BFME_SLOT(82); BFME_SLOT(83);
	BFME_SLOT(84); BFME_SLOT(85); BFME_SLOT(86); BFME_SLOT(87);
	BFME_SLOT(88); BFME_SLOT(89); BFME_SLOT(90); BFME_SLOT(91);
	BFME_SLOT(92); BFME_SLOT(93); BFME_SLOT(94); BFME_SLOT(95);
	BFME_SLOT(96); BFME_SLOT(97); BFME_SLOT(98); BFME_SLOT(99);
	BFME_SLOT(100);
	virtual void submit(Coord3D *point, Real *unknown,
		Int objectID, Int layer) = 0;
	BFME_SLOT(102); BFME_SLOT(103); BFME_SLOT(104);
	virtual Bool isBusy() = 0;
#undef BFME_SLOT
};

class Rva001B7200ContainModule
{
public:
#define BFME_SLOT(n) virtual void slot##n() = 0;
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03);
	BFME_SLOT(04); BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07);
	BFME_SLOT(08); BFME_SLOT(09); BFME_SLOT(10); BFME_SLOT(11);
	BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14); BFME_SLOT(15);
	BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23);
	BFME_SLOT(24); BFME_SLOT(25);
	virtual Rva001B7200HordeContain *getHordeContainInterface() = 0;
#undef BFME_SLOT
};

class Object
{
public:
	char m_pad000[0x38];
	Coord3D m_position;
	char m_pad044[0x1fc - 0x44];
	Rva001B7200ContainModule *m_contain;
	char m_pad200[4];
	Rva001B7200AIUpdate *m_ai;

	void setPosition(const Coord3D *position);
	void setLayer(Int layer);
};

class Rva001B7200Locomotor
{
public:
	Bool move(Object *object, Rva001B7200TerrainResult *result);
	void updatePosition(const Coord3D *position);

	char m_pad000[0x60];
	UnsignedInt m_stamp;
};

extern GameLogic *TheBfmeGameLogic;
#define BfmeScaleBC (*(const Real *)0x0107fac4)

#pragma comment(linker, "/alternatename:?findObjectByID@GameLogic@@QAEPAVObject@@H@Z=?j_0001f253@@YAXXZ")
#pragma comment(linker, "/alternatename:?getPathPosition@Rva001B7200Path@@QAEXPAVCoord3D@@@Z=?j_0002e2a3@@YAXXZ")
#pragma comment(linker, "/alternatename:?computePointOnPath@Rva001B7200Path@@QAEXPAVObject@@PAVRva001B7200Locomotor@@PAURva001B7200PointInfo@@_N@Z=?j_00008a9e@@YAXXZ")
#pragma comment(linker, "/alternatename:?advanceCachedPoint@Rva001B7200Path@@QAEXPAVCoord3D@@@Z=?j_0000711c@@YAXXZ")
#pragma comment(linker, "/alternatename:?GetLengthSqrd@Rva001B7200Delta@@QBEMXZ=?j_0002e339@@YAXXZ")
#pragma comment(linker, "/alternatename:?setPosition@Object@@QAEXPBUCoord3D@@@Z=?j_0003a1a7@@YAXXZ")
#pragma comment(linker, "/alternatename:?setLayer@Object@@QAEXH@Z=?j_00035e0e@@YAXXZ")
#pragma comment(linker, "/alternatename:?updatePosition@Rva001B7200Locomotor@@QAEXPBUCoord3D@@@Z=?j_0000c1b7@@YAXXZ")
#pragma comment(linker, "/alternatename:_Rva001B7200GetPath=?j_0000b8a7@@YAXXZ")

extern "C" void *Rva001B7200GetPath(Object *object);

// ?move@Rva001B7200Locomotor@@QAE_NPAVObject@@PAVRva001B7200TerrainResult@@@Z
Bool Rva001B7200Locomotor::move(Object *object, Rva001B7200TerrainResult *result)
{
	Int objectID = result->m_objectID;
	if (objectID == 0)
		return false;
	if (TheBfmeGameLogic->findObjectByID(objectID) == 0)
		return false;

	Rva001B7200ContainModule *contain = object->m_contain;
	if (contain == 0)
		return false;
	if (contain->getHordeContainInterface() == 0)
		return false;

	Rva001B7200HordeContain *horde = contain->getHordeContainInterface();
	Rva001B7200Path *path;
	if (object->m_ai)
		path = object->m_ai->m_path;
	else
		path = 0;
	if (path == 0)
		return false;

	char scratch[0x44];
	Rva001B7200Delta *delta = reinterpret_cast<Rva001B7200Delta *>(scratch + 4);
	Coord3D *currentPosition = reinterpret_cast<Coord3D *>(scratch + 0x10);
	Coord3D *newPosition = reinterpret_cast<Coord3D *>(scratch + 0x1c);
	Rva001B7200PointInfo *point =
		reinterpret_cast<Rva001B7200PointInfo *>(scratch + 0x28);
	Coord3D *cachedPosition = reinterpret_cast<Coord3D *>(scratch + 4);

	path->getPathPosition(currentPosition);
	path->computePointOnPath(object, this, point, false);

	newPosition->x = point->m_position.x;
	newPosition->y = point->m_position.y;
	newPosition->z = point->m_position.z;
	delta->x = object->m_position.x - currentPosition->x;
	delta->y = object->m_position.y - currentPosition->y;
	delta->z = object->m_position.z - currentPosition->z;
	if (delta->GetLengthSqrd() > BfmeScaleBC)
	{
		object->setPosition(currentPosition);
		updatePosition(currentPosition);
		object->setLayer(point->m_layer);
		horde->submit(newPosition, &point->m_unknown10,
			point->m_objectID, point->m_layer);
		m_stamp = TheBfmeGameLogic->m_frame + 0x3c;
		return true;
	}

	if (!horde->isBusy() && TheBfmeGameLogic->m_frame <= m_stamp)
		return true;

	Rva001B7200Path *cachedPath =
		static_cast<Rva001B7200Path *>(Rva001B7200GetPath(object));
	if (cachedPath == 0)
		return false;

	cachedPath->advanceCachedPoint(cachedPosition);
	cachedPath->advanceCachedPoint(cachedPosition);
	cachedPath->advanceCachedPoint(cachedPosition);
	cachedPath->computePointOnPath(object, this, point, false);
	if (point->m_objectID == 0x7fffffff)
		return false;
	cachedPath->advanceCachedPoint(cachedPosition);
	return false;
}
