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

// Retail ILT 0x000391C6 reaches the matched five-argument sink at 0x004135C0.
class AsciiString;
class S4Sink004135C0
{
public:
	void invoke(const AsciiString &name, int kind, int active, int mode, int enabled);
};

class BfmeSinkProvider
{
public:
	BFME_TEN_VIRTUALS(v00);
	virtual S4Sink004135C0 *bfmeSink(void);
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
	// Retail zero-extends the byte argument with XOR/MOV rather than MOVZX.
	typedef void (S4Sink004135C0::*SinkEntry)(const AsciiString &, int, int, int, int);
	typedef void (S4Sink004135C0::*SinkCall)(const AsciiString &, unsigned char, int, int, int);
	union { SinkEntry entry; SinkCall call; } invoke = { &S4Sink004135C0::invoke };

	BfmeSinkProvider *provider = m_bfmeProvider;
	if (provider == 0)
		return;

	S4Sink004135C0 *sink = provider->bfmeSink();
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
				(sink->*invoke.call)(
					*reinterpret_cast<const AsciiString *>(entry), entry->m_bfmeKind, 1, 0, 0);
			}
		}
	}
}

#undef BFME_TEN_VIRTUALS
