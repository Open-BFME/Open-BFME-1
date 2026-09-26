// cl: /DNDEBUG /MD /EHsc

// The named bfmeStepXJ caller reaches this method through its existing
// ?bfmeApplyXJ@BfmeOwnerXJ@@QAEXPAXPAVBfmeThingXJ@@@Z ILT.  The target is a
// small damage-record application wrapper.  Its local constructor is the
// compact BFME DamageInfo constructor at 0x0002C9D5, whose retail body proves
// the offsets used below: damage type +0x10, death type +0x1c, and clipped
// output +0x54 in a 0x5c-byte object.

extern const float BfmeZeroRange;

class DamageInfo
{
public:
	DamageInfo();

private:
	unsigned char m_bfmeStorage[0x5c];

public:
	int &damageType()
	{
		return *(int *)(m_bfmeStorage + 0x10);
	}

	int &deathType()
	{
		return *(int *)(m_bfmeStorage + 0x1c);
	}

	float &actualDamageClipped()
	{
		return *(float *)(m_bfmeStorage + 0x54);
	}
};

class BfmeThingXJ
{
public:
	virtual void bfmeV00XJ() = 0;
	virtual void bfmeV01XJ() = 0;
	virtual void bfmeV02XJ() = 0;
	virtual void bfmeV03XJ() = 0;
	virtual void bfmeV04XJ() = 0;
	virtual void bfmeV05XJ() = 0;
	virtual void bfmeV06XJ() = 0;
	virtual void bfmeV07XJ() = 0;
	virtual void bfmeV08XJ() = 0;
	virtual void bfmeV09XJ() = 0;
	virtual void bfmeV10XJ() = 0;
	virtual void bfmeV11XJ() = 0;
	virtual void bfmeV12XJ() = 0;
	virtual void bfmeV13XJ(DamageInfo *damage) = 0;
	virtual void bfmeV14XJ() = 0;
	virtual void bfmeV15XJ() = 0;
	virtual void bfmeV16XJ(int deathType, BfmeThingXJ *thing) = 0;
};

class BfmeOwnerXJ
{
public:
	unsigned char bfmeApplyXJ(void *a, BfmeThingXJ *thing);
};

extern void j_000384f6(void);

class BfmeOwnerXJApplyCall
{
public:
	bool apply(void *a, BfmeThingXJ *thing, DamageInfo *damage);
};

static __forceinline bool callBfmeOwnerXJApply(BfmeOwnerXJ *owner,
	void *a, BfmeThingXJ *thing, DamageInfo *damage)
{
	typedef bool (BfmeOwnerXJApplyCall::*Function)(void *, BfmeThingXJ *,
		DamageInfo *);
	union
	{
		void (*raw)(void);
		Function member;
	} fn;
	fn.raw = j_000384f6;
	return (reinterpret_cast<BfmeOwnerXJApplyCall *>(owner)->*fn.member)(
		a, thing, damage);
}

unsigned char BfmeOwnerXJ::bfmeApplyXJ(void *a, BfmeThingXJ *thing)
{
	DamageInfo damage;
	if (callBfmeOwnerXJApply(this, a, thing, &damage) == true)
	{
		if (damage.damageType() == 7)
			thing->bfmeV16XJ(damage.deathType(), thing);
		else
			thing->bfmeV13XJ(&damage);
	}

	return damage.actualDamageClipped() > BfmeZeroRange;
}
