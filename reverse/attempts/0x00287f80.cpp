// ?d_00287f80@@YAXXZ
// partial score=0.85 date=2026-09-03
#define BFME_TEN_VIRTUALS(PREFIX) \
	virtual void PREFIX##0(void); virtual void PREFIX##1(void); \
	virtual void PREFIX##2(void); virtual void PREFIX##3(void); \
	virtual void PREFIX##4(void); virtual void PREFIX##5(void); \
	virtual void PREFIX##6(void); virtual void PREFIX##7(void); \
	virtual void PREFIX##8(void); virtual void PREFIX##9(void)

struct BfmeEffectRecord
{
	int m_bfmeValues[3];
};

class BfmeThingCOF
{
public:
	bool bfmeAskCOF(void);
	void bfmeRunCOF(void *record, void *a, void *b, void *c);
};

struct BfmeMaskSource
{
	char m_bfmeFields[8];
	unsigned int m_bfmeMask;
};

struct BfmeSelection
{
	char m_bfmeFields[0x10];
	unsigned int m_bfmeIndex;
};

class BfmeSelector
{
public:
	BFME_TEN_VIRTUALS(v00);
	virtual void v10(void);
	virtual void v11(void);
	virtual void v12(void);
	virtual void v13(void);
	virtual void v14(void);
	virtual BfmeSelection *bfmeGet(void);
};

struct BfmeEffectState
{
	void bfmeFill(void *source, int mode, BfmeEffectRecord *record, int enabled);

	char m_bfmeFields[0x200];
	BfmeSelector *m_bfmeSelector;
};

class Gen_00287F80
{
public:
	BFME_TEN_VIRTUALS(v00);
	virtual void v10(void);
	virtual void bfmeRefresh(void);

	void bfmeRun(BfmeThingCOF *effect, void *source);

private:
	BfmeMaskSource *m_bfmeMaskSource;
	BfmeEffectState *m_bfmeState;
	char m_bfme0C[0x620];
	unsigned int m_bfmeFlagIndex;
	unsigned char m_bfmeFlags[1];
};

// ?bfmeRun@Gen_00287F80@@QAEXPAVBfmeThingCOF@@PAX@Z
void Gen_00287F80::bfmeRun(BfmeThingCOF *effect, void *source)
{
	BfmeEffectRecord record;

	if (!m_bfmeFlags[m_bfmeFlagIndex])
		bfmeRefresh();

	BfmeSelection *selection = m_bfmeState->m_bfmeSelector->bfmeGet();
	BfmeMaskSource *maskSource = m_bfmeMaskSource;
	unsigned int bit = reinterpret_cast<unsigned int>(selection);
	if (selection != 0)
		bit = 1U << (selection->m_bfmeIndex - 1);

	if (maskSource->m_bfmeMask & bit) {
		m_bfmeState->bfmeFill(source, 0, &record, 0);
		if (effect != 0 && !effect->bfmeAskCOF())
			effect->bfmeRunCOF(&record, 0, 0, 0);
	}
}

#undef BFME_TEN_VIRTUALS
