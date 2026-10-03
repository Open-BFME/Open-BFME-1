class BfmeAudioGG
{
public:
	virtual void bfmeSlot00GG(void);
	virtual void bfmeSlot01GG(void);
	virtual void bfmeSlot02GG(void);
	virtual void bfmeSlot03GG(void);
	virtual void bfmeSlot04GG(void);
	virtual void bfmeSlot05GG(void);
	virtual void bfmeSlot06GG(void);
	virtual void bfmeSlot07GG(void);
	virtual void bfmeSlot08GG(void);
	virtual void bfmeSlot09GG(void);
	virtual void bfmeSlot10GG(void);
	virtual void bfmeSlot11GG(void);
	virtual void bfmeSlot12GG(void);
	virtual void bfmeSlot13GG(void);
	virtual void bfmeSlot14GG(void);
	virtual void bfmeSlot15GG(void);
	virtual void bfmeSlot16GG(void);
	virtual void bfmeSlot17GG(void);
	virtual void bfmeSlot18GG(void);
	virtual void bfmeNotifyGG(int value);
};

// Retail's AudioManager singleton (0x012ED668); the TU-local view above only
// names the slot this body calls.
class AudioManager;

extern AudioManager *TheAudio;

static inline BfmeAudioGG *localBfmeAudioGG()
{
	return (BfmeAudioGG *)TheAudio;
}

class BfmeOwnerGG
{
public:
	unsigned char m_bfmeHeadGG[0x10];
	char m_bfmeFlagGG;
};

class Object;
enum UpdateSleepTime;

// The call at the tail of this body is retail's ILT thunk 0x000157DA, whose
// target is UpdateModule::setWakeFrame(Object *, UpdateSleepTime) at
// 0x002B2040 (game/GameEngine/Source/GameLogic/Object/Update/UpdateModule.cpp);
// symbols.csv pins that real name at the thunk address, so spelling the real
// protected member keeps the call displacement and lets the body resolve at
// link. The definition lives in
// game/GameEngine/Include/GameLogic/Module/UpdateModule.h, which this TU does
// not include (its prefix view keeps retail's offsets local to this file), so
// the declaration below carries the same signature and access.
class UpdateModule
{
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);

	friend class BfmeSecondGG;
};

class BfmeSecondGG
{
public:
	void bfmeGoGG(int unused);

	unsigned char m_bfmeHeadGG[4];
	int m_bfmeValueGG;
};

void BfmeSecondGG::bfmeGoGG(int unused)
{
	char *base = (char *)this;

	if ((*(BfmeOwnerGG **)(base - 0x24))->m_bfmeFlagGG == 0)
		return;

	if (TheAudio != 0)
	{
		localBfmeAudioGG()->bfmeNotifyGG(m_bfmeValueGG);
		m_bfmeValueGG = 1;
	}

	((UpdateModule *)(base - 0x28))->setWakeFrame(*(Object **)(base - 0x20), (UpdateSleepTime)0x3fffffff);
}
