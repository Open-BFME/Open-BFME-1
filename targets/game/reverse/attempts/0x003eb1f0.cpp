// ?snapClosestGoalPosition@Rva003EB1F0Pathfinder@@QAEXPAVObject@@PAUCoord3D@@@Z
// partial score=0.35 date=2026-09-17
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Retail 0x003EB1F0, 1678 bytes.  The carved boundary is the contiguous
// body ending in `ret 8` at +0x68b.  The SnapClosestGoalPosition strings and
// AIStates.cpp's named caller prove the Pathfinder goal-position role.  The
// canonical Pathfinder spelling is already occupied by the separate 0x3F89A0
// body, so this recovered address keeps the semantic method name while
// retaining the address in its owner identity.
//
// The seven calls below are deliberately made through the ILT names printed
// by `tools/callees.py 0x003EB1F0 1678`; no guessed callee identity is used.

typedef int Int;
typedef bool Bool;
typedef unsigned char UByte;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

enum Rva003EB1F0Layer
{
	Rva003EB1F0Ground = 1
};

class Object
{
public:
	char m_pad00[0x74];
	Int m_id;
};

class CRCParameterCheck
{
};

class Rva003FD060TerrainLogic
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual Real getGroundHeight(Real x, Real y, Int layer,
		void *normal, Bool unknown);
};

struct Rva003EB1F0PathfindCell
{
	void *m_info;
	Int m_unused04;
	Int m_unused08;
	unsigned int m_packed;
};

class Rva003EB1F0PathfindLayer
{
public:
	char m_pad00[4];
	Rva003EB1F0PathfindCell **m_cells;
	Int m_width;
	Int m_height;
	Int m_xOrigin;
	Int m_yOrigin;
	char m_tail[0x44 - 0x18];
};

class Rva003EB1F0Pathfinder
{
public:
	void snapClosestGoalPosition(Object *obj, Coord3D *pos);

	char m_prefix[0x10];
	Rva003EB1F0PathfindCell **m_map;
	Int m_extentLoX;
	Int m_extentLoY;
	Int m_extentHiX;
	Int m_extentHiY;
	char m_middle[0x85c - 0x24];
	Rva003EB1F0PathfindLayer m_layers[16];
};

extern void j_000105cd(void);
extern void j_000171e8(void);
extern void j_0001c675(void);
extern void j_0003a17a(void);
extern void j_000411d2(void);
extern void j_000461ff(void);
extern void j_00049f3f(void);

#define Rva003EB1F0DebugFlag (*(unsigned char *)0x012F0239)
#define Rva003EB1F0DebugSink (*(void **)0x012ED4FC)
#define Rva003EB1F0Terrain (*(Rva003FD060TerrainLogic **)0x012EF4CC)
#define Rva003EB1F0K1266C (*(const Real *)0x01075344)
#define Rva003EB1F0K1253 (*(const Real *)0x0107533C)
#define Rva003EB1F0DirectionWeight (*(const Real *)0x01075C74)
#define Rva003EB1F0CellBias (*(const double *)0x010EE498)
#define Rva003EB1F0CellScale (*(const double *)0x010EE488)

typedef void (__cdecl *Rva003EB1F0Log)(void *, const char *, ...);

static __forceinline UByte rva003eb1f0CheckDestination(
	Rva003EB1F0Pathfinder *self, Object *obj, Int x, Int y,
	Rva003EB1F0Layer layer, Int radius, Int center, void **checked)
{
	typedef UByte (Rva003EB1F0Pathfinder::*Call)(void *, void *, void *,
		void *, void *, void *, void **, Int);
	union
	{
		void (*raw)(void);
		Call member;
	} call;
	call.raw = ::j_00049f3f;
	return (self->*call.member)((void *)obj, (void *)x, (void *)y,
		(void *)(Int)layer, (void *)radius, (void *)(Int)center, checked, 0);
}

static __forceinline void rva003eb1f0GetRadius(
	Rva003EB1F0Pathfinder *self, const Object *obj, Int &radius,
	Bool &center)
{
	typedef void (Rva003EB1F0Pathfinder::*Call)(const Object *, Int &, Bool &);
	union
	{
		void (*raw)(void);
		Call member;
	} call;
	call.raw = ::j_000461ff;
	(self->*call.member)(obj, radius, center);
}

static __forceinline Rva003EB1F0Layer rva003eb1f0GetLayer(
	Rva003FD060TerrainLogic *terrain, Object *obj, const Coord3D *pos)
{
	typedef Rva003EB1F0Layer (Rva003FD060TerrainLogic::*Call)(
		Object *, const Coord3D *);
	union
	{
		void (*raw)(void);
		Call member;
	} call;
	call.raw = ::j_0001c675;
	return (terrain->*call.member)(obj, pos);
}

static __forceinline Bool rva003eb1f0WorldToCell(
	Rva003EB1F0Pathfinder *self, const Coord3D *pos, ICoord2D *cell)
{
	typedef Bool (Rva003EB1F0Pathfinder::*Call)(const Coord3D *, ICoord2D *);
	union
	{
		void (*raw)(void);
		Call member;
	} call;
	call.raw = ::j_000171e8;
	return (self->*call.member)(pos, cell);
}

static __forceinline void rva003eb1f0AdjustThunk(
	Rva003EB1F0Pathfinder *self, Int x, Int y, Bool center, Coord3D &pos,
	Rva003EB1F0Layer layer)
{
	typedef void (Rva003EB1F0Pathfinder::*Call)(Int, Int, Bool, Coord3D &,
		Rva003EB1F0Layer);
	union
	{
		void (*raw)(void);
		Call member;
	} call;
	call.raw = ::j_000411d2;
	(self->*call.member)(x, y, center, pos, layer);
}

static __forceinline Rva003EB1F0PathfindCell *rva003eb1f0LayerCell(
	Rva003EB1F0PathfindLayer *layer, Int x, Int y)
{
	typedef Rva003EB1F0PathfindCell *
		(Rva003EB1F0PathfindLayer::*Call)(Int, Int);
	union
	{
		void (*raw)(void);
		Call member;
	} call;
	call.raw = ::j_000105cd;
	return (layer->*call.member)(x, y);
}

static __forceinline Rva003EB1F0PathfindCell *rva003eb1f0CellAt(
	Rva003EB1F0Pathfinder *self, Rva003EB1F0Layer layer, Int x, Int y)
{
	Rva003EB1F0PathfindCell *cell;
	if (layer > 1 && layer <= 15)
	{
		cell = rva003eb1f0LayerCell(&self->m_layers[layer], x, y);
		if (cell != 0)
			return cell;
	}
	return self->m_map[x] + y;
}

static __forceinline void rva003eb1f0AdjustInline(
	Int x, Int y, Bool center, Coord3D *pos, Rva003EB1F0Layer layer)
{
	if (center)
	{
		pos->x = ((Real)x + Rva003EB1F0K1253) *
			Rva003EB1F0DirectionWeight;
		pos->y = ((Real)y + Rva003EB1F0K1253) *
			Rva003EB1F0DirectionWeight;
	}
	else
	{
		pos->x = ((Real)x + Rva003EB1F0CellBias) * Rva003EB1F0CellScale;
		pos->y = ((Real)y + Rva003EB1F0CellBias) * Rva003EB1F0CellScale;
	}
	Real groundHeight = Rva003EB1F0Terrain->getGroundHeight(
		pos->x, pos->y, (Int)layer, 0, 1);
	pos->z = groundHeight;
}

void Rva003EB1F0Pathfinder::snapClosestGoalPosition(Object *obj,
	Coord3D *pos)
{
	Int iRadius;
	Bool center;
	if (Rva003EB1F0DebugFlag && Rva003EB1F0DebugSink)
		((Rva003EB1F0Log)::j_0003a17a)(Rva003EB1F0DebugSink,
			(const char *)0x010EF008, pos->x, pos->y, pos->z);

	rva003eb1f0GetRadius(this, obj, iRadius, center);
	if (Rva003EB1F0DebugFlag && Rva003EB1F0DebugSink)
	{
		const char *centerName = center ? (const char *)0x0107FA58 :
			(const char *)0x01080180;
		((Rva003EB1F0Log)::j_0003a17a)(Rva003EB1F0DebugSink,
			(const char *)0x010EEFA8, iRadius, centerName);
	}

	ICoord2D cell;
	Coord3D adjustDest = *pos;
	Rva003EB1F0Layer layer;
	struct
	{
		void *result;
		Int pad;
	} checked;
	if (!center)
	{
		if (Rva003EB1F0DebugFlag && Rva003EB1F0DebugSink)
			((Rva003EB1F0Log)::j_0003a17a)(Rva003EB1F0DebugSink,
				(const char *)0x010EEF48);
		adjustDest.x += Rva003EB1F0K1266C;
		adjustDest.y += Rva003EB1F0K1266C;
	}

	layer = rva003eb1f0GetLayer(Rva003EB1F0Terrain, obj, pos);
	rva003eb1f0WorldToCell(this, &adjustDest, &cell);
	rva003eb1f0AdjustThunk(this, cell.x, cell.y,
		center, *pos,
		Rva003EB1F0Ground);

	if (Rva003EB1F0DebugFlag && Rva003EB1F0DebugSink)
	{
		const char *centerName = center ? (const char *)0x0107FA58 :
			(const char *)0x01080180;
		((Rva003EB1F0Log)::j_0003a17a)(Rva003EB1F0DebugSink,
			(const char *)0x010EEE90, cell.x, cell.y,
			(Int)layer, iRadius, centerName, pos->x, pos->y, pos->z);
	}

	Bool initialCheck = rva003eb1f0CheckDestination(this, obj,
		cell.x, cell.y, layer, iRadius, *(Int *)&center, &checked.result);
	if (initialCheck)
	{
		Bool initialEmpty = (checked.result == 0);
		if (initialEmpty)
		{
			if (Rva003EB1F0DebugFlag && Rva003EB1F0DebugSink)
				((Rva003EB1F0Log)::j_0003a17a)(Rva003EB1F0DebugSink,
					(const char *)0x010EEE20);
			return;
		}
	}

	if (Rva003EB1F0DebugFlag && Rva003EB1F0DebugSink)
		((Rva003EB1F0Log)::j_0003a17a)(Rva003EB1F0DebugSink,
			(const char *)0x010EEDB0);

	Int i;
	Int j;
	for (i = cell.x - 1; i < cell.x + 2; ++i)
	{
		for (j = cell.y - 1; j < cell.y + 2; ++j)
		{
			Bool neighbourCheck = rva003eb1f0CheckDestination(this, obj,
				i, j, layer, iRadius, *(Int *)&center, &checked.result);
			if (neighbourCheck)
			{
				Bool neighbourEmpty = (checked.result == 0);
				if (neighbourEmpty)
				{
					rva003eb1f0AdjustThunk(this, i, j, center, *pos, layer);
					if (Rva003EB1F0DebugFlag && Rva003EB1F0DebugSink)
					{
						const char *centerName = center ?
							(const char *)0x0107FA58 :
							(const char *)0x01080180;
						((Rva003EB1F0Log)::j_0003a17a)(
							Rva003EB1F0DebugSink,
							(const char *)0x010EEC90, i, j, (Int)layer,
						 iRadius, centerName, pos->x, pos->y, pos->z);
					}
					return;
				}
			}
		}
	}

	if (iRadius == 0)
	{
		for (i = cell.x - 1; i < cell.x + 2; ++i)
		{
			for (j = cell.y - 1; j < cell.y + 2; ++j)
			{
				Rva003EB1F0PathfindCell *newCell =
					rva003eb1f0CellAt(this, layer, i, j);
				if (newCell != 0)
				{
					void *info = newCell->m_info;
					Int goal = info == 0 ? 0 :
						*(Int *)((char *)info + 0x14);
					if (goal == 0 || goal == obj->m_id)
					{
						rva003eb1f0AdjustInline(i, j, center, pos, layer);
						if (Rva003EB1F0DebugFlag &&
							Rva003EB1F0DebugSink)
						{
							const char *centerName = center ?
								(const char *)0x0107FA58 :
								(const char *)0x01080180;
							((Rva003EB1F0Log)::j_0003a17a)(
								Rva003EB1F0DebugSink,
								(const char *)0x010EEBE0, i, j,
								(Int)layer, iRadius, centerName,
								pos->x, pos->y, pos->z);
						}
						return;
					}
				}
			}
		}

		for (i = cell.x - 1; i < cell.x + 2; ++i)
		{
			for (j = cell.y - 1; j < cell.y + 2; ++j)
			{
				Rva003EB1F0PathfindCell *newCell =
					rva003eb1f0CellAt(this, layer, i, j);
				if (newCell != 0 &&
					(newCell->m_packed & 0x38) != 0x18)
				{
				rva003eb1f0AdjustInline(i, j, center, pos, layer);
					if (Rva003EB1F0DebugFlag &&
						Rva003EB1F0DebugSink)
					{
						const char *centerName = center ?
							(const char *)0x0107FA58 :
							(const char *)0x01080180;
						((Rva003EB1F0Log)::j_0003a17a)(
							Rva003EB1F0DebugSink,
							(const char *)0x010EEB30, i, j,
							(Int)layer, iRadius, centerName,
								pos->x, pos->y, pos->z);
					}
					return;
				}
			}
		}
	}

	if (Rva003EB1F0DebugFlag && Rva003EB1F0DebugSink)
	((Rva003EB1F0Log)::j_0003a17a)(Rva003EB1F0DebugSink,
			(const char *)0x010EED40, iRadius, pos->x, pos->y, pos->z);
}
