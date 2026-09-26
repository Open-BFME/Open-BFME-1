// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RousingSpeechUpdate::update, retail 0x00265030, 223 bytes.
// The update interface is reached through the secondary vtable at primary+0x10.
// The first entry sets a deadline using SpeechDuration and the current frame.
// CreateWave enables progression by WaveWidth, capped at BonusRadius. The
// original names of the behavior floats at +0xf4/+0xf8 remain unproven.
// Completion clears Object model-condition bit 0x10 and sleeps forever.

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class Object
{
public:
	void notifyModelConditionChanged();

private:
	unsigned char m_pad00[0x128];

public:
	unsigned int m_modelConditionFlags;
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	unsigned int m_frame;
};

extern GameLogic *TheBfmeGameLogic;

// Named factory 0x0011C6C0 reaches callback 0x00264AC0 and table
// RVA 0x00CB6BB8; the names below are witnessed at their exact offsets.
class RousingSpeechUpdateModuleData
{
private:
	unsigned char m_pad00[0x254];

public:
	float m_bonusRadius;
	unsigned int m_speechDuration;
	unsigned int m_updateInterval;
	unsigned char m_pad260[8];
	unsigned char m_createWave;
	unsigned char m_pad269[3];
	float m_waveWidth;
};

class RousingSpeechUpdatePrimary
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void onObjectCreated();
	virtual void slot14();
	virtual void slot15();

	RousingSpeechUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0c[0xdc];
	void *m_speechObjectList;
	unsigned int m_wakeDeadline;
	unsigned char m_hasWoken;
	unsigned char m_padf1[3];
	float m_0F4;
	float m_0F8;
};

class RousingSpeechUpdate
{
public:
	virtual UpdateSleepTime update();
};

extern void j_000087a6();
extern void j_0002191d();

// ?update@RousingSpeechUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime RousingSpeechUpdate::update()
{
	unsigned char *secondary = reinterpret_cast<unsigned char *>(this);
	RousingSpeechUpdatePrimary *primary =
		reinterpret_cast<RousingSpeechUpdatePrimary *>(secondary - 0x10);
	typedef void (RousingSpeechUpdatePrimary::*ClearCall)();
	union { void *asVoid; ClearCall asMember; } clearCast;
	clearCast.asVoid = (void *)j_000087a6;
	(primary->*clearCast.asMember)();

	if (secondary[0xe0] == 0)
	{
		primary->onObjectCreated();
		RousingSpeechUpdateModuleData *moduleData =
			*reinterpret_cast<RousingSpeechUpdateModuleData **>(secondary - 0x0c);
		*reinterpret_cast<unsigned int *>(secondary + 0xdc) =
			moduleData->m_speechDuration + TheBfmeGameLogic->m_frame;
		secondary[0xe0] = 1;
	}

	RousingSpeechUpdateModuleData *data =
		*reinterpret_cast<RousingSpeechUpdateModuleData **>(secondary - 0x0c);
	if (TheBfmeGameLogic->m_frame < *reinterpret_cast<unsigned int *>(secondary + 0xdc) &&
		!(*reinterpret_cast<float *>(secondary + 0xe4) >= data->m_bonusRadius))
	{
		if (data->m_createWave != 0)
		{
			*reinterpret_cast<float *>(secondary + 0xe4) =
				*reinterpret_cast<float *>(secondary + 0xe8);
			*reinterpret_cast<float *>(secondary + 0xe8) +=
				data->m_waveWidth;
			if (*reinterpret_cast<float *>(secondary + 0xe8) >
				data->m_bonusRadius)
				*reinterpret_cast<float *>(secondary + 0xe8) =
					data->m_bonusRadius;
		}
		primary->slot15();
		return (UpdateSleepTime)(*reinterpret_cast<RousingSpeechUpdateModuleData **>(secondary - 0x0c))->m_updateInterval;
	}

	Object *object = *reinterpret_cast<Object **>(secondary - 8);
	secondary[0xe0] = 0;
	if ((*(reinterpret_cast<unsigned char *>(object) + 0x128) & 0x10) != 0)
	{
		*(reinterpret_cast<unsigned int *>(reinterpret_cast<unsigned char *>(object) + 0x128))
			&= 0xffffffef;
		typedef void (Object::*NotifyCall)();
		union { void *asVoid; NotifyCall asMember; } notifyCast;
		notifyCast.asVoid = (void *)j_0002191d;
		(object->*notifyCast.asMember)();
	}
	return UPDATE_SLEEP_FOREVER;
}
