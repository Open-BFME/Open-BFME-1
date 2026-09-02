#define BFME_TEN_VIRTUALS(PREFIX) \
	virtual void PREFIX##0(void); virtual void PREFIX##1(void); \
	virtual void PREFIX##2(void); virtual void PREFIX##3(void); \
	virtual void PREFIX##4(void); virtual void PREFIX##5(void); \
	virtual void PREFIX##6(void); virtual void PREFIX##7(void); \
	virtual void PREFIX##8(void); virtual void PREFIX##9(void)

struct BfmeEffectRecord8030 { int m_values[3]; };

struct BfmeSelection8030
{
	char m_fields[0x10];
	unsigned int m_index;
};

class BfmeSelector8030
{
public:
	BFME_TEN_VIRTUALS(v00);
	virtual void v10(void); virtual void v11(void); virtual void v12(void);
	virtual void v13(void); virtual void v14(void);
	virtual BfmeSelection8030 *bfmeGet(void);
};

class BfmeEffectState8030
{
public:
	void bfmeFill(void *source, int mode, BfmeEffectRecord8030 *record, int enabled);
	char m_fields[0x200];
	BfmeSelector8030 *m_selector;
};

class BfmeThing8030
{
public:
	void bfmeRun(BfmeEffectState8030 *state, BfmeEffectRecord8030 *record,
		int a, int b);
};

struct BfmeMaskSource8030
{
	char m_fields[0x48C];
	unsigned int m_mask;
};

class Gen_00288030
{
public:
	BFME_TEN_VIRTUALS(v00);
	virtual void v10(void);
	virtual void bfmeRefresh(void);
	void bfmeDispatch(BfmeThing8030 *effect, void *source);

private:
	BfmeMaskSource8030 *m_maskSource;
	BfmeEffectState8030 *m_state;
	char m_fields[0x620];
	unsigned int m_flagIndex;
	unsigned char m_flags[1];
};

// ?bfmeDispatch@Gen_00288030@@QAEXPAVBfmeThing8030@@PAX@Z
void Gen_00288030::bfmeDispatch(BfmeThing8030 *effect, void *source)
{
	BfmeEffectRecord8030 record;
	if (!m_flags[m_flagIndex])
		bfmeRefresh();

	BfmeMaskSource8030 *maskSource = m_maskSource;
	BfmeSelection8030 *selection = m_state->m_selector->bfmeGet();
	if (selection == 0 ||
		(maskSource->m_mask & (1U << (selection->m_index - 1))) != 0) {
		BfmeEffectState8030 *state = m_state;
		state->bfmeFill(source, 0, &record, 0);
		if (effect != 0)
			effect->bfmeRun(state, &record, 0, 0);
	}
}

#undef BFME_TEN_VIRTUALS
