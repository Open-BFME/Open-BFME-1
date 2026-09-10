// ?bfmeStepYD@BfmeThingYD@@QAEXXZ
// partial score=0.18 date=2026-09-10
struct BfmeClockYD
{
	unsigned char m_bfmeHead[0x3c];
	int m_bfmeNow;
};

extern BfmeClockYD *g_bfmeClockYD;

struct BfmeCoordYD
{
	float x;
	float y;
	float z;
};

// The receiver at this+0x0c is an Object-shaped owner.  Only the retail
// offsets consumed by bfmeStepYD are named here; the rest stays opaque.
struct BfmeOwnerYD
{
	unsigned char m_bfmePrefix[0x38];
	BfmeCoordYD m_bfmePosition;
	float m_bfmeRadius;
	unsigned char m_bfmeTail[0x1b8];
};

struct BfmeQueryNodeYD
{
	void *m_bfmeObject;
	unsigned char m_bfmePad[4];
	BfmeQueryNodeYD *m_bfmeNext;
};

struct BfmeQueryYD
{
	BfmeQueryNodeYD *m_bfmeFirst;
	BfmeQueryNodeYD *m_bfmeCurrent;
	BfmeQueryNodeYD *m_bfmeEnd;
	unsigned int m_bfmeCount;
};

struct BfmeFilterYD
{
	unsigned int m_bfmeVptr;
	BfmeFilterYD *m_bfmeNext;
	const void *m_bfmeObject;
	int m_bfmeArg0;
	int m_bfmeArg1;
};

// The query callee's retail target and ABI are not proven yet.  Keep this as
// a declaration-only placeholder in the research snapshot; it is not a
// production identity claim or a fallback implementation.
extern BfmeQueryYD bfmeUnresolvedPartitionQueryYD(const BfmeCoordYD *, float,
	BfmeFilterYD *);

class BfmeThingYD
{
public:
	virtual void bfmeSpareYDa0();
	virtual void bfmeSpareYDa1();
	virtual void bfmeSpareYDa2();
	virtual void bfmeSpareYDa3();
	virtual void bfmeSpareYDa4();
	virtual void bfmeSpareYDa5();
	virtual bool bfmeAskTwoYD();
	virtual void bfmeSpareYDb0();
	virtual void bfmeSpareYDb1();
	virtual void bfmeSpareYDb2();
	virtual bool bfmeAskOneYD();
	void bfmeStepYD();
	void bfmeSetYD(int what);
	void bfmeGoYD();
	unsigned char m_bfmePrefix[4];
	BfmeOwnerYD *m_bfmeOwner;
	unsigned char m_bfmeHead[0x18];
	bool m_bfmeFlag;
	unsigned char m_bfmeGapOne[3];
	int m_bfmeCount;
	unsigned char m_bfmeGapTwo[4];
	int m_bfmeStamp;
};

void BfmeThingYD::bfmeStepYD()
{
	BfmeOwnerYD *owner = m_bfmeOwner;
	if (!owner)
		return;

	BfmeCoordYD center = owner->m_bfmePosition;
	center.x += owner->m_bfmePosition.x;
	center.y += owner->m_bfmePosition.y;
	center.z += owner->m_bfmePosition.z;

	BfmeFilterYD first = { 0x010860A0, 0, owner, 0, 0 };
	BfmeFilterYD second = { 0x010860B0, 0, owner, 0x3B, 0x67 };
	BfmeFilterYD third = { 0x01083B80, 0, owner, 0x58, 2 };
	BfmeFilterYD fourth = { 0x01083B5C, 0, owner, 0, 0 };
	fourth.m_bfmeNext = &third;
	BfmeFilterYD *filters = &fourth;
	third.m_bfmeNext = &second;
	second.m_bfmeNext = &first;

	BfmeQueryYD query = bfmeUnresolvedPartitionQueryYD(&center, 30.0f, filters);
	while (query.m_bfmeCurrent != query.m_bfmeEnd)
	{
		BfmeQueryNodeYD *node = query.m_bfmeCurrent;
		query.m_bfmeCurrent = node->m_bfmeNext;
		void *object = node->m_bfmeObject;
		if (!object)
			continue;

		unsigned char *ai = *(unsigned char **)((unsigned char *)object + 0x204);
		if (ai)
		{
			// The retail loop forwards the owner and the mode value through the
			// AI subobject.  Keep this operation neutral until those two ABI
			// targets receive independently proven names.
			(void)ai;
		}
	}
}

void BfmeThingYD::bfmeGoYD()
{
	if (!bfmeAskOneYD())
		return;
	if (!bfmeAskTwoYD())
		return;
	bfmeStepYD();
	bfmeSetYD(2);
	m_bfmeFlag = false;
	m_bfmeCount = 0;
	m_bfmeStamp = g_bfmeClockYD->m_bfmeNow;
}
