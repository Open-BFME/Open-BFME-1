// ?onEnter@AIIdleState@@UAE?AW4StateReturnType@@XZ
// partial score=0.55 date=2026-09-10
// Complete BFME reconstruction banked after the focused 198-byte probe.

struct BfmeAIIdleOnEnterState
{
	unsigned char m_pad000[0x1C];
	StateMachine *m_machine;
	unsigned char m_pad020[4];
	UnsignedShort m_initialSleepOffset;
	Bool m_shouldLookForTargets;
	Bool m_inited;
};

struct BfmeAIIdleOnEnterObject;

struct BfmeAIIdleOnEnterMachine
{
	unsigned char m_pad000[0x10];
	BfmeAIIdleOnEnterObject *m_owner;
};

struct BfmeAIIdleOnEnterOverride
{
	void *m_vtable;
	BfmeAIIdleOnEnterOverride *m_nextOverride;
};

struct BfmeAIIdleOnEnterTemplate
{
	void *m_vtable;
	BfmeAIIdleOnEnterOverride *m_nextOverride;
	unsigned char m_pad008[0x20 - 8];
	char *m_nameData;
	unsigned char m_pad024[0x4CD - 0x24];
	UnsignedByte m_bfmeIdleFlag;
};

struct BfmeAIIdleOnEnterFiringTracker
{
	unsigned char m_pad000[0x20];
	UnsignedInt m_field020;
};

struct BfmeAIIdleOnEnterObject
{
	unsigned char m_pad000[4];
	BfmeAIIdleOnEnterTemplate *m_template;
	unsigned char m_pad008[0x38 - 8];
	Coord3D m_position;
	unsigned char m_pad044[0x74 - 0x44];
	UnsignedInt m_id;
	unsigned char m_pad078[0x1EC - 0x78];
	BfmeAIIdleOnEnterFiringTracker *m_firingTracker;
	unsigned char m_pad1F0[0x204 - 0x1F0];
	AIUpdateInterface *m_ai;
};

extern void *g_012ED4FC;
extern void j_000022bb(void);
extern void j_0003a17a(void);
extern void j_00001bae(void);
class CRCParameterCheck;
typedef void (__cdecl *BfmeAIIdleCritterDesyncLog)(
	CRCParameterCheck *, const char *, ...);
typedef int (__cdecl *BfmeAIIdleRandomValue)(int, int, char *, int);
typedef BfmeAIIdleOnEnterOverride *(__fastcall *BfmeAIIdleGetFinalOverride)(
	BfmeAIIdleOnEnterOverride *);

StateReturnType AIIdleState::onEnter()
{
	BfmeAIIdleOnEnterState *self = (BfmeAIIdleOnEnterState *)this;
	BfmeAIIdleOnEnterObject *obj =
		((BfmeAIIdleOnEnterMachine *)self->m_machine)->m_owner;
	AIUpdateInterface *ai = obj->m_ai;
	if (ai)
		ai->resetNextMoodCheckTime();
	self->m_inited = true;

	BfmeAIIdleOnEnterTemplate *templateObject = obj->m_template;
	if (templateObject && templateObject->m_nextOverride)
	{
		BfmeAIIdleOnEnterTemplate *finalTemplate =
			(BfmeAIIdleOnEnterTemplate *)((BfmeAIIdleGetFinalOverride)j_000022bb)(
				templateObject->m_nextOverride);
		if (finalTemplate->m_bfmeIdleFlag)
		{
			BfmeAIIdleOnEnterFiringTracker *tracker = obj->m_firingTracker;
			if (tracker)
				tracker->m_field020 = 0;
		}
	}

	CRCParameterCheck *crc = (CRCParameterCheck *)g_012ED4FC;
	if (crc)
	{
		UnsignedInt id = obj->m_id;
		const char *name = (const char *)0x0107388B;
		templateObject = obj->m_template;
		if (templateObject && templateObject->m_nextOverride)
		{
			BfmeAIIdleOnEnterTemplate *finalTemplate =
				(BfmeAIIdleOnEnterTemplate *)((BfmeAIIdleGetFinalOverride)j_000022bb)(
					templateObject->m_nextOverride);
			if (finalTemplate->m_nameData)
				name = finalTemplate->m_nameData + 8;
		}
		((BfmeAIIdleCritterDesyncLog)j_0003a17a)(crc,
			"AIIdleState::onEnter() called for object %s(%d) at location %g,%g,%g.",
			name, id, (double)obj->m_position.x,
			(double)obj->m_position.y, (double)obj->m_position.z);
	}

	self->m_initialSleepOffset = (UnsignedShort)((BfmeAIIdleRandomValue)j_00001bae)(
		0, 10, (char *)0x0109769C, 0x7A2);
	return STATE_CONTINUE;
}
