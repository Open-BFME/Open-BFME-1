// ?d_003e8e10@@YAXXZ
// partial score=0.04 date=2026-09-19
//
// The caller at 0x0016D5F0 supplies (source, melee-context, the locomotor
// block at source-AI+0x1A8, output position, target).  Its member-pointer
// typedef calls this Pathfinder-area helper "FindMeleeEngagementLocation".
// The owner class is not proved, so this source deliberately keeps the RVA
// token in its class name.  The only callee spellings used here are the ILT
// names printed by tools/callees.py.

typedef int Int;
typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Rva003E8E10CellPair
{
	Int x;
	Int y;
};

class Rva003E8E10Object
{
public:
	void getUnitDirectionVector2D(Coord3D &direction);
	void getPosition(Coord3D *position);

	char m_pad00[0x38];
	Coord3D m_position;
};

class Rva003E8E10Weapon
{
public:
	Bool isGoalPosWithinAttackRange(const Rva003E8E10Object *source,
		const Coord3D *goal, const Rva003E8E10Object *target,
		const Coord3D *targetPosition, Int flags) const;
};

class Rva003E8E10Pathfinder
{
public:
	Bool findMeleeEngagementLocation(Rva003E8E10Object *source,
		void *meleeContext, void *locomotorBlock, Coord3D *result,
		Rva003E8E10Object *target);

	Bool targetPositionIsUsable(Rva003E8E10Object *source,
		Rva003E8E10Object *target);
	void getRadiusAndCenter(const Rva003E8E10Object *object, Int &radius,
		Bool &center);
	Bool convertPosition(const Coord3D *position,
		Rva003E8E10CellPair *cell);
};

class Rva003E8E10Terrain
{
public:
	Int getLayerForDestination(Rva003E8E10Object *object);
};

class Rva003E8E10Coord
{
public:
	void normalize();
};

extern void j_0003a4e5(void);
extern void j_00036089(void);
extern void j_000461ff(void);
extern void j_00005ee3(void);
extern void j_0002bd82(void);
extern void j_00027bc9(void);
extern void j_000171e8(void);
extern void j_0001c675(void);

static float *const g_directionWeight = (float *)0x01075C74;
static float *const g_cellBias = (float *)0x01075344;

Bool Rva003E8E10Pathfinder::findMeleeEngagementLocation(
	Rva003E8E10Object *source, void *meleeContext, void *locomotorBlock,
	Coord3D *result, Rva003E8E10Object *target)
{
	Rva003E8E10Weapon *weapon = (Rva003E8E10Weapon *)meleeContext;
	Coord3D sourcePosition = source->m_position;
	Coord3D targetPosition = target->m_position;

	union
	{
		void *raw;
		Bool (Rva003E8E10Weapon::*member)(
			const Rva003E8E10Object *, const Coord3D *,
			const Rva003E8E10Object *, const Coord3D *, Int) const;
	} goalCheck;
	goalCheck.raw = (void *)j_0003a4e5;

	union
	{
		void *raw;
		Bool (Rva003E8E10Pathfinder::*member)(
			Rva003E8E10Object *, Rva003E8E10Object *);
	} viewCheck;
	viewCheck.raw = (void *)j_00036089;

	if ((weapon->*goalCheck.member)(source, &sourcePosition, target,
		&targetPosition, 0) && (this->*viewCheck.member)(source, target))
	{
		*result = targetPosition;
		return true;
	}

	union
	{
		void *raw;
		void (Rva003E8E10Object::*member)(Coord3D &);
	} directionCall;
	directionCall.raw = (void *)j_00005ee3;

	Coord3D direction;
	(source->*directionCall.member)(direction);
	direction.x *= *g_directionWeight;
	direction.y *= *g_directionWeight;

	Coord3D delta;
	delta.x = targetPosition.x + direction.x - sourcePosition.x;
	delta.y = targetPosition.y + direction.y - sourcePosition.y;
	delta.z = targetPosition.z - sourcePosition.z;

	union
	{
		void *raw;
		void (Rva003E8E10Coord::*member)();
	} normalizeCall;
	normalizeCall.raw = (void *)j_0002bd82;
	(((Rva003E8E10Coord *)&delta)->*normalizeCall.member)();

	Int radius;
	Bool center;
	union
	{
		void *raw;
		void (Rva003E8E10Pathfinder::*member)(
			const Rva003E8E10Object *, Int &, Bool &);
	} radiusCall;
	radiusCall.raw = (void *)j_000461ff;
	(this->*radiusCall.member)(source, radius, center);

	Coord3D candidate = targetPosition;
	Rva003E8E10CellPair cell;
	union
	{
		void *raw;
		Bool (Rva003E8E10Pathfinder::*member)(
			const Coord3D *, Rva003E8E10CellPair *);
	} convertCall;
	convertCall.raw = (void *)j_000171e8;

	union
	{
		void *raw;
		Int (Rva003E8E10Terrain::*member)(Rva003E8E10Object *);
	} layerCall;
	layerCall.raw = (void *)j_0001c675;

	Rva003E8E10Terrain *terrain =
		*(Rva003E8E10Terrain **)0x012EF4CC;
	Int layer = (terrain->*layerCall.member)(source);
	(void)layer;
	(void)locomotorBlock;

	for (Int attempt = 0; attempt != 2; ++attempt)
	{
		candidate.x += delta.x * (attempt ? 0.5f : 0.0f);
		candidate.y += delta.y * (attempt ? 0.5f : 0.0f);
		candidate.x += *g_cellBias;
		candidate.y += *g_cellBias;

		if (!(this->*convertCall.member)(&candidate, &cell))
			continue;

		if (cell.x < -1 || cell.x > 0x7fff ||
			cell.y < -1 || cell.y > 0x7fff)
			continue;

		if ((weapon->*goalCheck.member)(source, &candidate, target,
			&targetPosition, attempt) &&
			(this->*viewCheck.member)(source, target))
		{
			*result = candidate;
			return true;
		}
	}

	(void)radius;
	(void)center;
	return false;
}
