// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RousingSpeechUpdate::onObjectCreated, retail 0x00264EA0.
// The RousingSpeechUpdate vtable at 0x010B6D90 routes slot 13 through ILT
// 0x000211DE to this body.  Its base onObjectCreated call uses ILT 0x00020AF9.

class RousingObject
{
public:
	void notifyModelConditionChanged();

private:
	unsigned char m_pad[0x128];

public:
	union
	{
		unsigned int m_modelConditionFlags;
		unsigned char m_modelConditionFlagsByte;
	};
};

class RousingFXList
{
public:
	void doFXObj(const RousingObject *primary, const RousingObject *secondary) const;
};

class RousingThingCOF
{
public:
	bool bfmeAskCOF();
};

// Named factory 0x0011C6C0 reaches callback 0x00264AC0 and table
// RVA 0x00CB6BB8: BonusRadius/+254, LeaderFX/+260, CreateWave/+268,
// and WaveWidth/+26c. Behavior floats retain offset-qualified names.
class RousingSpeechUpdateModuleData
{
private:
	unsigned char m_pad00[0x254];

public:
	float m_bonusRadius;

private:
	unsigned char m_pad258[8];

public:
	RousingFXList *m_leaderFX;

private:
	unsigned char m_pad264[4];

public:
	unsigned char m_createWave;

private:
	unsigned char m_pad269[3];

public:
	float m_waveWidth;
};

class RousingSpeechUpdateBase
{
	virtual void onObjectCreated();

protected:
	RousingSpeechUpdateModuleData *m_moduleData;
	RousingObject *m_object;
	unsigned char m_pad0c[0xe8];

	unsigned int m_0F4;
	float m_0F8;
};

class RousingSpeechUpdate : public RousingSpeechUpdateBase
{
public:
	virtual void onObjectCreated();
};

extern void j_00020af9();
extern void j_0002191d();
extern void j_00022bba();
extern void j_00011f77();

void RousingSpeechUpdate::onObjectCreated()
{
	j_00020af9();

	RousingObject *object = m_object;
	if ((object->m_modelConditionFlagsByte & 0x10) == 0)
	{
		object->m_modelConditionFlags |= 0x10;
		typedef void (RousingObject::*NotifyCall)();
		union { void *asVoid; NotifyCall asMember; } notifyCast;
		notifyCast.asVoid = (void *)j_0002191d;
		(object->*notifyCast.asMember)();
	}

	RousingSpeechUpdateModuleData *data = m_moduleData;
	RousingFXList *fxList = data->m_leaderFX;
	if (fxList != 0)
	{
		RousingObject *fxObject = m_object;
		RousingThingCOF *cof = reinterpret_cast<RousingThingCOF *>(fxList);
		typedef bool (RousingThingCOF::*AskCall)();
		union { void *asVoid; AskCall asMember; } askCast;
		askCast.asVoid = (void *)j_00011f77;
		if (!(cof->*askCast.asMember)())
		{
			typedef void (RousingFXList::*FXCall)(const RousingObject *, const RousingObject *) const;
			union { void *asVoid; FXCall asMember; } fxCast;
			fxCast.asVoid = (void *)j_00022bba;
			(fxList->*fxCast.asMember)(fxObject, 0);
		}
	}

	m_0F4 = 0;
	if (data->m_createWave)
	{
		m_0F8 = data->m_waveWidth;
		if (m_0F8 > data->m_bonusRadius)
			m_0F8 = data->m_bonusRadius;
	}
	else
	{
		m_0F8 = data->m_bonusRadius;
	}
}
