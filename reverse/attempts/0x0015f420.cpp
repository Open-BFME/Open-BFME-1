// ?run@SelfR0015F420@@QAEHXZ
// partial score=0.45 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: address-derived recovery, retail 0x0015F420, 527 bytes.
//
// Draft reconstruction, sibling in shape to the body at 0x0015C7A0: an EHsc
// frame, several lookups through the same two global singletons
// (0x012F0898, 0x012EF214), a query-object fallback chain guarded by three
// niladic vtable calls at +0x3C, a weapon-based scale-up of an int factor,
// and the identical `new(0x54)` + constructor-thunk + two-vtable-call tail
// seen at 0x0015C7A0. Identity of the owning class and most field types is
// unresolved; this is an address-derived name pending probe.py convergence.

typedef int Int;
typedef float Real;

struct Coord0015F420
{
	Real x, y, z;
};

class BfmeX1011R0015F420;

class BfmeLook1011R0015F420
{
public:
	BfmeX1011R0015F420 *bfmeFind1011(Int id);
	char m_pad[0x3C];
	Int m_field3C;
};

class BfmeSubBIAR0015F420
{
public:
	Int ask(void);
};

class FlagsObjR0015F420
{
public:
	char m_pad0[4];
	BfmeSubBIAR0015F420 *m_field4;
	char m_pad1[0xD4 - 8];
	Int m_field0xD4;
};

class BfmeX1011R0015F420
{
public:
	char m_pad0[4];
	FlagsObjR0015F420 *m_field4;
	char m_pad1[0x74 - 8];
	Int m_field74;
};

class QueryResultR0015F420
{
public:
	char m_pad0[8];
	Int m_field8;
	char m_pad1[0x10 - 0xC];
	Int m_field0x10;
};

class QueryVtblR0015F420
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
	virtual void v38();
	virtual QueryResultR0015F420 *v3CCall(void);
};

class Weapon0015F420;

class ObjectR0015F420
{
public:
	Int getRelationship(void *other) const;
	bool bfmeAskAIA(Int what) const;
	Weapon0015F420 *getCurrentWeapon(Int slot);

	char m_pad0[0x200];
	QueryVtblR0015F420 *m_field0x200;
};

class Weapon0015F420
{
public:
	char m_pad0[4];
	void *m_field4;
};

class ContainerR0015F420
{
public:
	char m_pad0[0x10];
	ObjectR0015F420 *m_field0x10;
	char m_pad1[0x44 - 0x14];
	Int m_field44;
	Int m_field48;
	Int m_field4C;
	Int m_field50;
};

struct FactorsR0015F420
{
	char m_pad[0x3C];
	Int m_field3C;
};

struct AIRootR0015F420
{
	char m_pad[0x14];
	FactorsR0015F420 *m_factors;
};

class TailR0015F420
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual Int v10Call(void);
};

class QR0015F420
{
public:
	char m_pad[0x1C];
	TailR0015F420 *m_tail;
};

class QVtblR0015F420
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
	virtual void v38Call(void *arg, Int flag);
};

extern "C" BfmeLook1011R0015F420 *g_bfmeClockBK;		// 0x012F0898
extern "C" AIRootR0015F420 *TheAIParseDefinitionAI;		// 0x012EF214

extern Int j_00046e98(void *self);
extern bool j_00028f74(void *arg);
extern Real aiGetAdjustedVisionRangeForObjectR0015F420(void *object, Int flags);
extern Real __stdcall thunk8da5R0015F420(void *arg);

class CtorTargetR0015F420
{
public:
	CtorTargetR0015F420(void *container, Int a, Int b, Int c, void *out);
	char m_body[0x54];
};

class SelfR0015F420
{
public:
	Int run(void);
};

// ?run@SelfR0015F420@@QAEHXZ
Int SelfR0015F420::run(void)
{
	char *self = reinterpret_cast<char *>(this);
	ContainerR0015F420 *cont = *reinterpret_cast<ContainerR0015F420 **>(self + 0x1C);
	ObjectR0015F420 *obj = cont->m_field0x10;

	*reinterpret_cast<Int *>(self + 0x44) = 0;

	BfmeX1011R0015F420 *r1 = g_bfmeClockBK->bfmeFind1011(cont->m_field50);
	QueryVtblR0015F420 *q = obj->m_field0x200;

	if (!r1)
	{
		if (!q)
			return -1;

		QueryResultR0015F420 *res = q->v3CCall();
		if (!res->m_field8)
			return -1;

		res = q->v3CCall();
		if (res->m_field0x10 == 7)
			return -1;

		QueryVtblR0015F420 *q2 = obj->m_field0x200;
		QueryResultR0015F420 *res2 = q2->v3CCall();
		Int candidate = res2->m_field8;

		r1 = g_bfmeClockBK->bfmeFind1011(candidate);
		if (!r1)
			return -1;

		Int rel = obj->getRelationship(r1);
		if (rel == 0)
		{
			ContainerR0015F420 *contReload = *reinterpret_cast<ContainerR0015F420 **>(self + 0x1C);
			contReload->m_field50 = candidate;
		}
	}

	FlagsObjR0015F420 *flagsObj = r1->m_field4;
	if (flagsObj)
	{
		if (flagsObj->m_field4)
			flagsObj->m_field4->ask();
	}

	if (flagsObj->m_field0xD4 & 0x1000)
	{
		if (!obj->bfmeAskAIA(0x6c))
		{
			*reinterpret_cast<Int *>(self + 0x44) = r1->m_field74;

			Int thunkResult = j_00046e98(self);
			if (!thunkResult)
				return -2;

			BfmeX1011R0015F420 *thunkObj = reinterpret_cast<BfmeX1011R0015F420 *>(thunkResult);
			ContainerR0015F420 *contReload2 = *reinterpret_cast<ContainerR0015F420 **>(self + 0x1C);
			contReload2->m_field50 = thunkObj->m_field74;
		}
	}

	ContainerR0015F420 *contFinal = *reinterpret_cast<ContainerR0015F420 **>(self + 0x1C);

	Coord0015F420 temp;
	*reinterpret_cast<Int *>(&temp.x) = contFinal->m_field44;
	*reinterpret_cast<Int *>(&temp.y) = contFinal->m_field48;
	*reinterpret_cast<Int *>(&temp.z) = contFinal->m_field4C;

	Real range = aiGetAdjustedVisionRangeForObjectR0015F420(obj, 3);

	Int factor = TheAIParseDefinitionAI->m_factors->m_field3C;

	Weapon0015F420 *weapon = obj->getCurrentWeapon(0);
	if (weapon)
	{
		weapon = obj->getCurrentWeapon(0);
		if (j_00028f74(weapon->m_field4))
			factor = factor + (factor >> 1);
	}

	temp.y = range;

	*reinterpret_cast<Coord0015F420 *>(self + 0x2C) = temp;

	*reinterpret_cast<Int *>(self + 0x3C) = g_bfmeClockBK->m_field3C + factor;

	Real extra = thunk8da5R0015F420(obj);
	Real sum = extra + temp.x;

	*reinterpret_cast<Int *>(self + 0x28) = 7;
	*reinterpret_cast<Real *>(self + 0x38) = sum * sum;

	CtorTargetR0015F420 *ctorResult =
			new CtorTargetR0015F420(contFinal, 0, 1, 0, 0);
	*reinterpret_cast<void **>(self + 0x40) = ctorResult;

	QR0015F420 *tailQ = reinterpret_cast<QR0015F420 *>(ctorResult);
	TailR0015F420 *tail = tailQ->m_tail;
	reinterpret_cast<QVtblR0015F420 *>(tail)->v38Call(r1, -1);

	TailR0015F420 *finalObj = *reinterpret_cast<TailR0015F420 **>(self + 0x40);
	Int callResult = finalObj->v10Call();

	return callResult != 0 ? -1 : 0;
}
