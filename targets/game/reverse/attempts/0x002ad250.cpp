// ?update002AD250@StealthUpdate@@QAEXXZ
// partial score=0.82 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
//
// StealthUpdate::update002AD250, retail RVA 0x002AD250 (238 bytes).
// The ILT at 0x000272AF and the matched AIGroup::groupStealthIdle caller
// establish this as a StealthUpdate member helper.  The neutral RVA-derived
// method name is retained until a stronger retail symbol is recovered.

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;

enum DisabledType
{
	DisabledTypeStealth = 3
};

class Object
{
public:
	void clearModelConditionState(int condition);
	void notifyModelConditionChanged();
	void setDisabledUntil(DisabledType type, UnsignedInt frame);

	unsigned char m_pad00[0x12C];
	UnsignedInt m_status;
};

class BfmeItemRY
{
public:
	void bfmeDoRY(void *first, void *second);
};

class BfmeObjE10
{
public:
	void actionA(int action);
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheBfmeGameLogic;

class StealthUpdateModuleData
{
private:
	unsigned char m_pad00[0x310];

public:
	UnsignedInt m_stealthDelay;
	UnsignedInt m_detectionDelay;
	UnsignedInt m_enableState;
	UnsignedInt m_disableState;
	UnsignedInt m_blackMarketCheckFrames;
};

class UpdateModule
{
public:
	virtual void unused() = 0;

protected:
	const void *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x20 - 0x0C];
};

class StealthUpdate : public UpdateModule
{
protected:
	const StealthUpdateModuleData *getStealthUpdateModuleData() const
	{
		return (const StealthUpdateModuleData *)m_moduleData;
	}

	Object *getObject()
	{
		return m_object;
	}

public:
	void update002AD250();

private:
	UnsignedInt m_stealthAllowedFrame;
	UnsignedInt m_detectionExpiresFrame;
	UnsignedInt m_nextBlackMarketCheckFrame;
	Bool m_enabled;
	Bool m_xferRestoreDisguise;
};

// ?update002AD250@StealthUpdate@@QAEXXZ
void StealthUpdate::update002AD250()
{
	Object *object = getObject();
	const StealthUpdateModuleData *data = getStealthUpdateModuleData();
	UnsignedInt now = TheBfmeGameLogic->m_frame;

	if (!data->m_enableState && !data->m_blackMarketCheckFrames)
		return;
	if (!m_xferRestoreDisguise)
	{
		if (now < m_nextBlackMarketCheckFrame)
			return;

		m_stealthAllowedFrame = data->m_stealthDelay + now;
		m_detectionExpiresFrame = 0;
		object->clearModelConditionState(0x10);

		if (object->m_status & 0x01000000)
		{
			object->m_status &= 0xFEFFFFFF;
			object->notifyModelConditionChanged();
		}
		if (!(object->m_status & 0x00040000))
		{
			object->m_status |= 0x00040000;
			object->notifyModelConditionChanged();
		}

		((BfmeItemRY *)object)->bfmeDoRY(
			(void *)0xF9, (void *)data->m_enableState);
		object->setDisabledUntil(DisabledTypeStealth, m_stealthAllowedFrame);
		((BfmeObjE10 *)object)->actionA(0x1C);
		m_xferRestoreDisguise = 1;
		return;
	}

restore_state:
	((BfmeItemRY *)object)->bfmeDoRY(
		(void *)0xFA, (void *)data->m_disableState);
	m_detectionExpiresFrame = data->m_detectionDelay + now;
}
