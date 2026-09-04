// ?refresh@Rva002AD250@@QAEXXZ
// partial score=0.55 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x002AD250.  BFME keeps the state transition used by the stealth
// update in a small non-virtual helper.  The module-data tail and the runtime
// fields are deliberately laid out at their retail offsets.

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;

class GameLogic
{
public:
	UnsignedInt getFrame() const
	{
		return *(const UnsignedInt *)((const char *)this + 0x3C);
	}
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	void clearModelConditionState(int condition);
	void notifyModelConditionChanged();
	void setDisabledUntil(int type, UnsignedInt frame);
	unsigned char m_pad00[0x12C];
	UnsignedInt m_status;
};

class BfmeItemRY
{
public:
	void bfmeDoRY(void *one, void *two);
};

class BfmeObjE10
{
public:
	void actionA(int code);
};

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

class Rva002AD250Base
{
public:
	virtual void unused() = 0;

protected:
	StealthUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x20 - 0x0C];
};

class Rva002AD250 : public Rva002AD250Base
{
public:
	void refresh();

private:
	UnsignedInt m_stealthAllowedFrame;
	UnsignedInt m_detectionExpiresFrame;
	UnsignedInt m_nextBlackMarketCheckFrame;
	unsigned char m_pad2C[1];
	Bool m_xferRestoreDisguise;
};

// ?refresh@Rva002AD250@@QAEXXZ
void Rva002AD250::refresh()
{
	StealthUpdateModuleData *data = m_moduleData;
	GameLogic *logic = TheGameLogic;
	UnsignedInt now = logic->getFrame();

	if (!data->m_enableState)
	{
		if (!data->m_blackMarketCheckFrames)
			return;
		if (!m_xferRestoreDisguise)
		{
			if (now < m_nextBlackMarketCheckFrame)
				return;

			m_stealthAllowedFrame = data->m_stealthDelay;
			m_detectionExpiresFrame = 0;
			Object *object = m_object;
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
	((BfmeItemRY *)object)->bfmeDoRY((void *)0xF9, (void *)data->m_enableState);
	object->setDisabledUntil(3, m_stealthAllowedFrame);
	((BfmeObjE10 *)object)->actionA(0x1C);
			m_xferRestoreDisguise = 1;
			return;
		}
	}

restore_state:
	Object *object = m_object;
	((BfmeItemRY *)object)->bfmeDoRY((void *)0xFA, (void *)data->m_disableState);
	m_detectionExpiresFrame = data->m_detectionDelay + now;
}
