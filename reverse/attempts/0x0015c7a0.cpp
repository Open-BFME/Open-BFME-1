// ?run@SelfR0015C7A0@@QAEHXZ
// partial score=0.55 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: address-derived recovery, retail 0x0015C7A0, 476 bytes.
//
// Draft reconstruction: an EHsc frame wraps a `new T(args)` (matches the
// documented U4NewThenInit shape), several lookups through two global
// singletons (0x012F0898, 0x012ED810), a three-way choice of Coord3D
// source, an early-exit guard on a `sub` lookup, a conditional call to a
// still-unconverted callee at 0x00004C37, and a tail pair of virtual calls.
// Identity of the owning class and most field types is unresolved; this is
// an address-derived name pending probe.py convergence.

typedef int Int;
typedef float Real;

struct Coord0015C7A0
{
	Real x, y, z;
};

class BfmeX1011R0015C7A0;
class TeamR0015C7A0;

class BfmeLook1011R0015C7A0
{
public:
	BfmeX1011R0015C7A0 *bfmeFind1011(Int id);
	char m_pad[0x3C];
	Int m_field3C;
};

class BfmeX1011R0015C7A0
{
public:
	char m_pad[0x38];
	Coord0015C7A0 m_coord;
};

class TeamR0015C7A0
{
public:
	Coord0015C7A0 *getEstimateTeamPosition_000EDCD0(Coord0015C7A0 *out) const;
};

class TeamFactoryR0015C7A0
{
public:
	void *find(Int id);
};

class LayerQueryR0015C7A0
{
public:
	Int getLayer(void) const;
};

class PolygonTriggerR0015C7A0
{
public:
	void getCenterPoint(Coord0015C7A0 *out) const;
};

struct FactorsR0015C7A0
{
	char m_pad[0x3C];
	Int m_field3C;
};

struct AIRootR0015C7A0
{
	char m_pad[0x14];
	FactorsR0015C7A0 *m_factors;
};

class TailR0015C7A0
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual Int v10Call(void);				// +0x10
};

class QR0015C7A0
{
public:
	char m_pad[0x1C];
	TailR0015C7A0 *m_tail;					// +0x1C
};

class QVtblR0015C7A0
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2C();
	virtual void v30();
	virtual void v34();
	virtual void v38Call(void *arg, Int flag);		// +0x38
	virtual Int v3CReserved();
};

extern "C" BfmeLook1011R0015C7A0 *g_bfmeClockBK;		// 0x012F0898
extern TeamFactoryR0015C7A0 *TheTeamFactoryR0015C7A0;		// 0x012ED810
extern "C" AIRootR0015C7A0 *TheAIParseDefinitionAI;		// 0x012EF214

extern bool bfmeCallENJ(void *a, void *b);
extern Real aiGetAdjustedVisionRangeForObjectR0015C7A0(void *object, Int flags);

class CtorTargetR0015C7A0
{
public:
	CtorTargetR0015C7A0(void *container, Int a, Int b, Int c, void *out);
	char m_body[0x54];
};

class SelfR0015C7A0
{
public:
	Int run(void);
};

// ?run@SelfR0015C7A0@@QAEHXZ
Int SelfR0015C7A0::run(void)
{
	char *self = reinterpret_cast<char *>(this);
	char *container = *reinterpret_cast<char **>(self + 0x1C);

	Int containerFlag = *reinterpret_cast<Int *>(container + 0x70);
	if (containerFlag == 1)
		return -1;

	BfmeX1011R0015C7A0 *r1 = g_bfmeClockBK->bfmeFind1011(
			*reinterpret_cast<Int *>(container + 0x44));
	void *teamRaw = TheTeamFactoryR0015C7A0->find(
			*reinterpret_cast<Int *>(container + 0x48));

	Coord0015C7A0 tmp;

	if (r1)
	{
		tmp = r1->m_coord;
	}
	else if (teamRaw)
	{
		reinterpret_cast<TeamR0015C7A0 *>(teamRaw)->getEstimateTeamPosition_000EDCD0(&tmp);
	}
	else
	{
		char *container2 = *reinterpret_cast<char **>(self + 0x1C);
		tmp = *reinterpret_cast<Coord0015C7A0 *>(container2 + 0x50);
	}

	container = *reinterpret_cast<char **>(self + 0x1C);
	BfmeX1011R0015C7A0 *sub = g_bfmeClockBK->bfmeFind1011(
			*reinterpret_cast<Int *>(container + 0x6C));
	if (!sub)
		return -1;

	LayerQueryR0015C7A0 *obj = *reinterpret_cast<LayerQueryR0015C7A0 **>(container + 0x10);

	if (obj->getLayer() != 1)
	{
		if (!bfmeCallENJ(obj, sub))
			return -1;
	}

	Real range = aiGetAdjustedVisionRangeForObjectR0015C7A0(obj, 3);

	char *c2 = *reinterpret_cast<char **>(self + 0x1C);
	PolygonTriggerR0015C7A0 *pt = *reinterpret_cast<PolygonTriggerR0015C7A0 **>(c2 + 0x4C);

	if (pt)
	{
		if (*reinterpret_cast<unsigned char *>(c2 + 0x68))
			tmp = *reinterpret_cast<Coord0015C7A0 *>(c2 + 0x5C);
		else
			pt->getCenterPoint(&tmp);
	}

	*reinterpret_cast<Coord0015C7A0 *>(self + 0x2C) = tmp;
	*reinterpret_cast<Real *>(self + 0x38) = range * tmp.x;

	*reinterpret_cast<Int *>(self + 0x3C) =
			g_bfmeClockBK->m_field3C + TheAIParseDefinitionAI->m_factors->m_field3C;
	*reinterpret_cast<Int *>(self + 0x28) = 7;

	CtorTargetR0015C7A0 *ctorResult =
			new CtorTargetR0015C7A0(container, 0, 1, 0, self + 0x24);
	*reinterpret_cast<void **>(self + 0x40) = ctorResult;

	QR0015C7A0 *q = reinterpret_cast<QR0015C7A0 *>(ctorResult);
	TailR0015C7A0 *tail = q->m_tail;
	reinterpret_cast<QVtblR0015C7A0 *>(tail)->v38Call(sub, -1);

	TailR0015C7A0 *finalObj = *reinterpret_cast<TailR0015C7A0 **>(self + 0x40);
	Int callResult = finalObj->v10Call();

	return callResult != 0 ? -1 : 0;
}
