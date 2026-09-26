// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG /DWIN32 /D_WINDOWS

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#define TEN_SLOTS(P) \
	virtual void slot_##P##_0(); virtual void slot_##P##_1(); \
	virtual void slot_##P##_2(); virtual void slot_##P##_3(); \
	virtual void slot_##P##_4(); virtual void slot_##P##_5(); \
	virtual void slot_##P##_6(); virtual void slot_##P##_7(); \
	virtual void slot_##P##_8(); virtual void slot_##P##_9()

class FlaggedReferenceTarget
{
public:
	virtual void dispose();
	TEN_SLOTS(0); TEN_SLOTS(1); TEN_SLOTS(2); TEN_SLOTS(3); TEN_SLOTS(4);
	TEN_SLOTS(5); TEN_SLOTS(6); TEN_SLOTS(7); TEN_SLOTS(8);
	virtual void slot_9_0(); virtual void slot_9_1(); virtual void slot_9_2();
	virtual void slot_9_3(); virtual void slot_9_4(); virtual void slot_9_5();
	virtual void slot_9_6(); virtual void slot_9_7(); virtual void slot_9_8();
	virtual void applyFlag(int flag);

	int m_refCount;
};

class FlaggedReferenceSource
{
public:
	TEN_SLOTS(a); TEN_SLOTS(b); TEN_SLOTS(c);
	virtual void slot_d_0(); virtual void slot_d_1(); virtual void slot_d_2();
	virtual FlaggedReferenceTarget *getTarget(int zero, void *context);
};

#undef TEN_SLOTS

class FlaggedReferenceApplicator
{
public:
	void apply(FlaggedReferenceSource *source, unsigned char flag);

private:
	unsigned char m_unreconstructed00[8];
	void *m_context;
};

void FlaggedReferenceApplicator::apply(
	FlaggedReferenceSource *source, unsigned char flag)
{
	unsigned char shown = flag;
	// This compiler-only branch is present in retail before the source guard.
	if (!shown)
		_ReadWriteBarrier();

	if (source)
	{
		FlaggedReferenceTarget *target = source->getTarget(0, m_context);
		if (target)
		{
			target->applyFlag(shown);
			if (--target->m_refCount == 0)
				target->dispose();
		}
	}
}
