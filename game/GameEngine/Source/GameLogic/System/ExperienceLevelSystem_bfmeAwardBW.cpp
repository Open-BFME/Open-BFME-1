// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5 experience award, retail 0x00380110.
//
// Every callee here is a real retail body reached through a 5-byte ILT thunk:
//   0x000240D7 -> Rva0037FE30::record(Arg1*, ObjectView*, bool) 0x0037FE30
//   0x00026DF0 -> BfmeThingCF::bfmeSendCF(void*)                   0x00413FA0
//   0x00034D29 -> ExperienceTracker::bfmeSetCurrentExperience(Real) 0x001B2060
//   0x00003913 -> ExperienceTracker::bfmeSetScalarIndex(int)      0x001B2780
//   0x0002431B -> ExperienceTracker::bfmeSetScalarBaseCount(int)   0x001B27C0
// This TU previously spelled all five as bfme* members of invented
// BfmeSubBW / BfmeThingBW classes, which nothing defines, so the object did
// not link. Respelling to the defining names leaves each call's push sequence
// and ECX receiver exactly as before.
//
// Two shapes need explaining, both fixed without a byte change:
//  * record's third parameter is `bool`, but retail pushes the caller's
//    dword straight through (push eax at +0x12, no test/setne). The union
//    pun passes the slot's raw 4 bytes.
//  * The 0x001B2060 body is EA's ExperienceTracker::bfmeSetCurrentExperience(Real)
//    (symbols.csv records that pin at ILT 0x00034D29), which is why retail
//    materialises the argument with `fild dword ptr [edi+0x10]` /
//    `fstp dword ptr [esp]` (+0x30..+0x3A): an int widened to float on the x87
//    stack and stored into the pushed slot. A `float` parameter reproduces it.
// The receiver layout views (vtable depth, m_bfmeSubBW at +0x210,
// m_bfmeLevelBW at +0x10, m_bfmeExtraBW at +0xCC) keep their matched names
// because the ledger row for bfmeAwardBW mangles them.
class BfmeThingCF
{
public:
	void bfmeSendCF(void *at);
};

class ExperienceTracker
{
public:
	void bfmeSetScalarIndex(int value);
	void bfmeSetScalarBaseCount(int value);
	// Retail's ILT 0x00034D29 -> 0x001B2060. symbols.csv records this body as
	// EA's ExperienceTracker::bfmeSetCurrentExperience(Real), which is the only
	// name whose parameter shape (4 bytes of x87 store into the pushed slot)
	// matches retail.
	void bfmeSetCurrentExperience(float value);
};

class Arg1;
class ObjectView;

// Retail passes the caller's third argument through to record's bool
// parameter as a raw dword.
union RawBool
{
	void *pointer;
	bool flag;
};

class BfmeAgentBW
{
public:
	virtual void bfmeSlot00BW();
	virtual void bfmeSlot01BW();
	virtual void bfmeSlot02BW();
	virtual void bfmeSlot03BW();
	virtual void bfmeSlot04BW();
	virtual void bfmeSlot05BW();
	virtual void bfmeSlot06BW();
	virtual void bfmeSlot07BW();
	virtual void bfmeSlot08BW();
	virtual void bfmeSlot09BW();
	virtual BfmeThingCF *bfmeGetBW();

	unsigned char m_bfmeHeadBW[0x20c];
	ExperienceTracker *m_bfmeSubBW;
};

class BfmeInfoBW
{
public:
	unsigned char m_bfmeHeadBW[0x10];
	int m_bfmeLevelBW;
	unsigned char m_bfmeMidBW[0x64];
	unsigned char m_bfmeAtBW[4];
	unsigned char m_bfmeTailBW[0x50];
	void *m_bfmeExtraBW;
};

// Retail's 0x0037FE30 body; `record` is public non-virtual, so the direct
// call is what retail emits.
class Rva0037FE30
{
public:
	void record(Arg1 *info, ObjectView *agent, bool bonus);
};

class ExperienceLevelSystem
{
public:
	void bfmeAwardBW(BfmeInfoBW *info, BfmeAgentBW *agent, void *extra, char bonus);
};

void ExperienceLevelSystem::bfmeAwardBW(BfmeInfoBW *info, BfmeAgentBW *agent, void *extra, char bonus)
{
	if (agent == 0)
		return;

	RawBool raw;
	raw.pointer = extra;
	reinterpret_cast<Rva0037FE30 *>(this)->record((Arg1 *)info, (ObjectView *)agent, raw.flag);

	BfmeThingCF *t = agent->bfmeGetBW();

	if (t != 0)
		t->bfmeSendCF(info->m_bfmeAtBW);

	agent->m_bfmeSubBW->bfmeSetCurrentExperience((float)info->m_bfmeLevelBW);
	agent->m_bfmeSubBW->bfmeSetScalarIndex((int)info->m_bfmeExtraBW);

	if (bonus != 0)
		agent->m_bfmeSubBW->bfmeSetScalarBaseCount((int)info->m_bfmeExtraBW);
}