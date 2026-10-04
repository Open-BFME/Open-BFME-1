// AudioLoopUpgrade::upgradeImplementation at retail 0x002D33E0: slot 9 of the UpgradeMux table
// 0x010CBD08, reached only through ILT 0x0004617D. AudioLoopUpgrade's registered
// constructor 0x002D32B0 stores that table. Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md
// The stack event this TU builds and destroys leaves through the ILT thunks
// 0x00008E86 and 0x00026F35, which reach 0x000B4440 and 0x000B31F0 -- the
// AudioEventInfoRef/ObjectID constructor and the scalar AudioEventRTS
// destructor owned by Audio/AudioEventRTSThinExtraCtor.cpp and
// Audio/AudioEventRTSCopyAndLifetime.cpp. The names below are the ones the
// ledger defines at those addresses; nothing else spells them.
struct AudioEventInfoRef
{
	void *ptr;
};

enum ObjectID
{
	INVALID_ID = 0
};

// Audio/AudioEventRTSCopyAndLifetime.cpp defines the scalar destructor
// (??1AudioEventRTS@@QAE@XZ, retail 0x000B31F0); the virtual one at 0x000CFA40
// is a separate row, so this view models the destructor non-virtually, as
// retail's own caller view does.
class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventInfoRef &eventInfo, ObjectID ownerID);
	~AudioEventRTS();

	unsigned char m_bfmeBodyERR[0x70]; // the leading dword is the vptr retail writes
};

// The wake-up call leaves through ILT 0x000157DA -> 0x002B2040, the real body of
// UpdateModule::setWakeFrame(Object *, UpdateSleepTime) in
// GameLogic/Object/Update/UpdateModule.cpp. That member is protected, so the
// mangled name carries IAE and AudioLoopUpgrade is befriended here rather than
// inventing a base relationship at this-0x20.
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 0
};

class AudioLoopUpgrade;

class UpdateModule
{
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);

	friend class AudioLoopUpgrade;
};

class BfmeAudioERR
{
public:
	virtual void bfmeSlot00ERR();
	virtual void bfmeSlot01ERR();
	virtual void bfmeSlot02ERR();
	virtual void bfmeSlot03ERR();
	virtual void bfmeSlot04ERR();
	virtual void bfmeSlot05ERR();
	virtual void bfmeSlot06ERR();
	virtual void bfmeSlot07ERR();
	virtual void bfmeSlot08ERR();
	virtual void bfmeSlot09ERR();
	virtual void bfmeSlot10ERR();
	virtual void bfmeSlot11ERR();
	virtual void bfmeSlot12ERR();
	virtual void bfmeSlot13ERR();
	virtual void bfmeSlot14ERR();
	virtual void bfmeSlot15ERR();
	virtual void bfmeSlot16ERR();
	virtual int bfmeSlot17ERR(AudioEventRTS *buf);
	virtual void bfmeSlot18ERR();
	virtual void bfmeSlot19ERR(int handle);
};

// Retail global at 0x012ED668 is AudioManager *TheAudio (GameAudio.cpp);
// this TU only needs two slots of it, so it keeps its own view.
class AudioManager;

extern AudioManager *TheAudio;

class BfmeXERR
{
public:
	unsigned char m_bfmeHeadERR[0x74];
	void *m_bfmeValueERR;
};

class BfmeNodeERR
{
public:
	unsigned char m_bfmeHeadERR[8];
	unsigned char m_bfmePayloadERR[4];
	unsigned int m_bfmeCountERR;
};

class AudioLoopUpgrade
{
protected:
	virtual void upgradeImplementation();
public:
	unsigned char m_bfmeHeadERR[0x8]; // +0x04, after the vptr
	int m_bfmeHandleERR;
};

void AudioLoopUpgrade::upgradeImplementation()
{
	BfmeAudioERR *audio = (BfmeAudioERR *)TheAudio;
	BfmeNodeERR *node = *(BfmeNodeERR **)((char *)this - 0x1c);

	if (audio != 0)
	{
		int handle = m_bfmeHandleERR;

		if (handle != 1)
			audio->bfmeSlot19ERR(handle);

		BfmeXERR *owner = *(BfmeXERR **)((char *)this - 0x18);
		void *value = owner->m_bfmeValueERR;
		AudioEventRTS buf(*(const AudioEventInfoRef *)&node->m_bfmePayloadERR,
			static_cast<ObjectID>(reinterpret_cast<int>(value)));
		AudioEventRTS *arg = &buf;

		m_bfmeHandleERR = ((BfmeAudioERR *)TheAudio)->bfmeSlot17ERR(arg);
	}

	if (node->m_bfmeCountERR > 0)
		((UpdateModule *)((char *)this - 0x20))->setWakeFrame(
			*(Object **)((char *)this - 0x18),
			static_cast<UpdateSleepTime>(node->m_bfmeCountERR));
}
