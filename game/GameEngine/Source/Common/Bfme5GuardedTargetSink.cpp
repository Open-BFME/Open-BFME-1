#define BFME_TEN_VIRTUALS(PREFIX) \
	virtual void PREFIX##0(void); virtual void PREFIX##1(void); \
	virtual void PREFIX##2(void); virtual void PREFIX##3(void); \
	virtual void PREFIX##4(void); virtual void PREFIX##5(void); \
	virtual void PREFIX##6(void); virtual void PREFIX##7(void); \
	virtual void PREFIX##8(void); virtual void PREFIX##9(void)

enum CommandSourceType {};

// retail ILT 0x0001C882 -> 0x000D88D0 is the matched AICommandInterface::aiHunt row
class AICommandInterface
{
public:
	void aiHunt(CommandSourceType cmdSource);
};

// retail ILT 0x0003EEBE -> 0x001CEA50 is the matched Object::setWeaponLock row
class Object
{
public:
	void setWeaponLock(int a, int b);
};

class BfmeTargetSub
{
};

class BfmeTarget
{
public:
	BFME_TEN_VIRTUALS(v00);
	BFME_TEN_VIRTUALS(v10);
	BFME_TEN_VIRTUALS(v20);
	BFME_TEN_VIRTUALS(v30);
	BFME_TEN_VIRTUALS(v40);
	BFME_TEN_VIRTUALS(v50);
	BFME_TEN_VIRTUALS(v60);
	BFME_TEN_VIRTUALS(v70);
	BFME_TEN_VIRTUALS(v80);
	virtual void v90(void);
	virtual void v91(void);
	virtual void v92(void);
	virtual void v93(void);
	virtual void v94(void);
	virtual void v95(void);
	virtual bool bfmeTest(void);

	char m_bfmeFields[0x1C];
	BfmeTargetSub m_bfmeSub;
};

class BfmeTargetSink;

struct BfmeTargetContext
{
	char m_bfmeFields[0x6C];
	int m_bfmeValue;
};

class Gen_0028B440
{
public:
	int bfmeApply(BfmeTarget *target);

private:
	char m_bfmeFields[8];
	BfmeTargetSink *m_bfmeSink;
	char m_bfme0C[0x18];
	BfmeTargetContext *m_bfmeContext;
};

// ?bfmeApply@Gen_0028B440@@QAEHPAVBfmeTarget@@@Z
int Gen_0028B440::bfmeApply(BfmeTarget *target)
{
	BfmeTargetSink *sink = m_bfmeSink;

	if (target->bfmeTest())
		((AICommandInterface *)&target->m_bfmeSub)->aiHunt((CommandSourceType)2);

	((Object *)sink)->setWeaponLock(m_bfmeContext->m_bfmeValue, 1);
	return 1;
}

#undef BFME_TEN_VIRTUALS
