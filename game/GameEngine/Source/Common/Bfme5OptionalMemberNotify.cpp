#include "../GameLogic/command_source_type.h"

#define BFME_TEN_VIRTUALS(PREFIX) \
	virtual void PREFIX##0(void); virtual void PREFIX##1(void); \
	virtual void PREFIX##2(void); virtual void PREFIX##3(void); \
	virtual void PREFIX##4(void); virtual void PREFIX##5(void); \
	virtual void PREFIX##6(void); virtual void PREFIX##7(void); \
	virtual void PREFIX##8(void); virtual void PREFIX##9(void)

class BfmeNotifyTarget
{
public:
	BFME_TEN_VIRTUALS(v00);
	BFME_TEN_VIRTUALS(v10);
	virtual void v20(void);
	virtual void v21(void);
	virtual void v22(void);
	virtual void v23(void);
	virtual void v24(void);
	virtual void v25(void);
	virtual void v26(void);
	virtual void bfmeApply(int value);
	virtual void v28(void);
	virtual void v29(void);
	virtual void v30(void);
	virtual void bfmeBefore(void);
};

// ILT 0x00024D70 reaches the canonical aiIdle body at RVA 0x000D87E0.
// It is a non-virtual thiscall with one CommandSourceType stack argument.
class AICommandInterface
{
public:
	void aiIdle(CommandSourceType source);
};

struct BfmeOptionalSub
{
	char m_bfmeFields[0x20];
	AICommandInterface m_bfmeInner;
};

struct BfmeOptionalState
{
	char m_bfmeFields[0x1FC];
	BfmeNotifyTarget *m_bfmeTarget;
	char m_bfme200[4];
	BfmeOptionalSub *m_bfmeSub;
};

class Gen_0027DE90
{
public:
	void bfmeNotify(void *before, int value);

private:
	char m_bfmeFields[8];
	BfmeOptionalState *m_bfmeState;
};

// ?bfmeNotify@Gen_0027DE90@@QAEXPAXH@Z
void Gen_0027DE90::bfmeNotify(void *before, int value)
{
	BfmeNotifyTarget *target = m_bfmeState->m_bfmeTarget;

	if (target != 0) {
		if (before != 0)
			target->bfmeBefore();

		BfmeOptionalSub *sub = m_bfmeState->m_bfmeSub;
		if (sub != 0)
			sub->m_bfmeInner.aiIdle(static_cast<CommandSourceType>(value));

		target->bfmeApply(value);
	}
}

#undef BFME_TEN_VIRTUALS
