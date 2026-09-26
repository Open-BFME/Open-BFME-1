// ?updateAt003FA5B0@Pathfinder@@QAEXPAVObject@@HH@Z
// partial score=0.05 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc
// Probe symbol: ?updateAt003FA5B0@BfmePathfinder003FA5B0@@QAEXPAVBfmeObject003FA5B0@@HH@Z
// The address-qualified types intentionally avoid claiming unwitnessed BFME layouts.

typedef unsigned char Bool;

class BfmeSubBIA;

class BfmeObject003FA5B0
{
public:
	virtual void bfmeSlot00(void);
	virtual void bfmeSlot04(void);
	virtual void bfmeSlot08(void);
	virtual void bfmeSlot0C(void);
	virtual void bfmeSlot10(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeSlot1C(void);
	virtual void bfmeSlot20(void);
	virtual void bfmeSlot24(void);
	virtual BfmeSubBIA *bfmeSlot28(void);

	Bool bfmeAskAIA(int kind) const;
	Bool bfmeAskCSA(void) const;
	float bfmeAt0038(void) const;
};

class BfmeSubBIA
{
public:
	void method0041BAC0(void);
	void bfmeOnRemove(void);
	unsigned bfmeFlags00C8(void) const;
	float bfmeRange0398(void) const;
	Bool bfmeQueryRegion(void *region) const;
};

class BfmePathfinder003FA5B0
{
public:
	void updateAt003FA5B0(BfmeObject003FA5B0 *object, int add, int flags);
	void classifyFence003F7D10(BfmeObject003FA5B0 *object, Bool add);
	void removePos003E3F70(BfmeObject003FA5B0 *object);
	void removeGoal003E3D20(BfmeObject003FA5B0 *object);
	void classifyWorker003F9310(BfmeObject003FA5B0 *object, Bool add);
};

extern Bool bfmeQueryGlobal004C4D40(int value);

void BfmePathfinder003FA5B0::updateAt003FA5B0(
	BfmeObject003FA5B0 *object,
	int add,
	int flags)
{
	double alignedWorkspaceValue;
	__declspec(align(8)) unsigned char workspace[0x148];
	BfmeSubBIA *sub = object->bfmeSlot28();
	if (sub != 0)
	{
		if (add)
			sub->method0041BAC0();
		else
			sub->bfmeOnRemove();
	}

	if (sub != 0 && (sub->bfmeFlags00C8() & 0x02000000) != 0)
		return;
	if (sub != 0 && (sub->bfmeFlags00C8() & 0x01000000) != 0)
		return;
	if (object->bfmeAskAIA(0x94))
		return;

	if (sub != 0 && sub->bfmeRange0398() > 0.0f && !object->bfmeAskAIA(0x3c))
	{
		classifyFence003F7D10(object, (Bool)add);
		return;
	}

	if (!add)
	{
		removePos003E3F70(object);
		removeGoal003E3D20(object);
	}

	if (!object->bfmeAskAIA(7))
		return;
	if (object->bfmeAskCSA())
		return;

	Bool special = object->bfmeAskAIA(0x3b);
	if (special)
	{
		if (object->bfmeAskAIA(0x95))
			special = sub != 0 && sub->bfmeQueryRegion(workspace);
		else if (bfmeQueryGlobal004C4D40(0x4c))
			special = 0;
	}

	alignedWorkspaceValue = object->bfmeAt0038();
	if (alignedWorkspaceValue >= 0.0f && !special)
		return;

	classifyWorker003F9310(object, (Bool)add);
}
