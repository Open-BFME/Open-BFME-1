class BfmeThingBS;
class BfmeAgentBS;
class BfmeInfoBS;

class BfmeSubBS
{
public:
	void bfmeSetBS(float level);
};

class BfmeAgentBS
{
public:
	virtual void bfmeSlot00BS();
	virtual void bfmeSlot01BS();
	virtual void bfmeSlot02BS();
	virtual void bfmeSlot03BS();
	virtual void bfmeSlot04BS();
	virtual void bfmeSlot05BS();
	virtual void bfmeSlot06BS();
	virtual void bfmeSlot07BS();
	virtual void bfmeSlot08BS();
	virtual void bfmeSlot09BS();
	virtual BfmeThingBS *bfmeGetBS();

	unsigned char m_bfmeHeadBS[0x20c];
	BfmeSubBS *m_bfmeSubBS;
};

class BfmeInfoBS
{
public:
	unsigned char m_bfmeHeadBS[0x10];
	int m_bfmeLevelBS;
	unsigned char m_bfmeMidBS[0x64];
	unsigned char m_bfmeAtBS[4];
	unsigned char m_bfmeTailBS[0x50];
	void *m_bfmeExtraBS;
};

// Retail calls route through ILTs 0x240D7, 0x26DF0 and 0x3913 to
// the existing providers at 0x37FE30, 0x413FA0 and 0x1B2780. Their
// receiver is unchanged; stack cleanup is respectively ret 12, ret 4,
// ret 4. The record flag is a byte in a dword argument; the final scalar
// index is an integer, despite the original pointer-shaped local view.
class ExperienceLevelSystem;
class Arg1;
class ObjectView;
class Rva0037FE30
{
public:
	void record(Arg1 *info, ObjectView *agent, bool flag);
};

class BfmeThingCF
{
public:
	void bfmeSendCF(void *at);
};

class ExperienceTracker
{
public:
	void bfmeSetScalarIndex(int index);
};

extern ExperienceLevelSystem *TheExperienceLevelSystem;

int __cdecl bfmeApplyBS(BfmeAgentBS *a, BfmeInfoBS *b)
{
	if (a != 0)
	{
		((Rva0037FE30 *)TheExperienceLevelSystem)->record(
			(Arg1 *)b, (ObjectView *)a, true);

		BfmeThingBS *t = a->bfmeGetBS();

		if (t != 0)
			((BfmeThingCF *)t)->bfmeSendCF(b->m_bfmeAtBS);

		a->m_bfmeSubBS->bfmeSetBS((float)b->m_bfmeLevelBS);
		((ExperienceTracker *)a->m_bfmeSubBS)->bfmeSetScalarIndex(
			(int)b->m_bfmeExtraBS);
	}

	return 1;
}
