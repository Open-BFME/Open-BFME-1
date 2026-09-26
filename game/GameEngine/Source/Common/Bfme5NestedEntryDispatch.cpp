#define BFME_TEN_VIRTUALS(PREFIX) \
	virtual void PREFIX##0(void); virtual void PREFIX##1(void); \
	virtual void PREFIX##2(void); virtual void PREFIX##3(void); \
	virtual void PREFIX##4(void); virtual void PREFIX##5(void); \
	virtual void PREFIX##6(void); virtual void PREFIX##7(void); \
	virtual void PREFIX##8(void); virtual void PREFIX##9(void)

struct BfmeEntry
{
	char m_bfmeFields[4];
	unsigned char m_bfmeKind;
};

class BfmeEntrySink
{
public:
	void bfmeApply(BfmeEntry *entry, unsigned char kind, int active,
		int mode, int enabled);
};

class BfmeSinkProvider
{
public:
	BFME_TEN_VIRTUALS(v00);
	virtual BfmeEntrySink *bfmeSink(void);
};

struct BfmeEntryGroup
{
	void *m_bfmeKey;
	BfmeEntry **m_bfmeBegin;
	BfmeEntry **m_bfmeEnd;
};

struct BfmeGroupVector
{
	BfmeEntryGroup **m_bfmeBegin;
	BfmeEntryGroup **m_bfmeEnd;
};

struct BfmeEntryState
{
	char m_bfmeFields[0x24];
	BfmeGroupVector m_bfmeGroups;
};

class Gen_00283790
{
public:
	void bfmeDispatch(void *key);

private:
	char m_bfmeFields[4];
	BfmeEntryState *m_bfmeState;
	BfmeSinkProvider *m_bfmeProvider;
};

// ?bfmeDispatch@Gen_00283790@@QAEXPAX@Z
void Gen_00283790::bfmeDispatch(void *key)
{
	BfmeSinkProvider *provider = m_bfmeProvider;
	if (provider == 0)
		return;

	BfmeEntrySink *sink = provider->bfmeSink();
	if (sink == 0)
		return;

	BfmeEntryState *state = m_bfmeState;
	BfmeGroupVector *groups = &state->m_bfmeGroups;
	for (unsigned int outer = 0;
		outer < static_cast<unsigned int>(groups->m_bfmeEnd - groups->m_bfmeBegin);
		++outer) {
		BfmeEntryGroup *group = groups->m_bfmeBegin[outer];
		if (group->m_bfmeKey == key) {
			for (unsigned int inner = 0;
				inner < static_cast<unsigned int>(group->m_bfmeEnd - group->m_bfmeBegin);
				++inner) {
				BfmeEntry *entry = group->m_bfmeBegin[inner];
				sink->bfmeApply(entry, entry->m_bfmeKind, 1, 0, 0);
			}
		}
	}
}

#undef BFME_TEN_VIRTUALS
