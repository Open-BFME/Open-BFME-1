// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;

enum ModelConditionFlagType
{
	MODELCONDITION_DOOR_1_OPENING = 18,
	MODELCONDITION_DOOR_1_CLOSING,
	MODELCONDITION_DOOR_1_WAITING_OPEN,
	MODELCONDITION_DOOR_1_WAITING_TO_CLOSE,
	MODELCONDITION_DOOR_2_OPENING,
	MODELCONDITION_DOOR_2_CLOSING,
	MODELCONDITION_DOOR_2_WAITING_OPEN,
	MODELCONDITION_DOOR_2_WAITING_TO_CLOSE,
	MODELCONDITION_DOOR_3_OPENING,
	MODELCONDITION_DOOR_3_CLOSING,
	MODELCONDITION_DOOR_3_WAITING_OPEN,
	MODELCONDITION_DOOR_3_WAITING_TO_CLOSE,
	MODELCONDITION_DOOR_4_OPENING,
	MODELCONDITION_DOOR_4_CLOSING,
	MODELCONDITION_DOOR_4_WAITING_OPEN,
	MODELCONDITION_DOOR_4_WAITING_TO_CLOSE
};

static const ModelConditionFlagType theOpeningFlags[4] =
{
	MODELCONDITION_DOOR_1_OPENING,
	MODELCONDITION_DOOR_2_OPENING,
	MODELCONDITION_DOOR_3_OPENING,
	MODELCONDITION_DOOR_4_OPENING
};

static const ModelConditionFlagType theClosingFlags[4] =
{
	MODELCONDITION_DOOR_1_CLOSING,
	MODELCONDITION_DOOR_2_CLOSING,
	MODELCONDITION_DOOR_3_CLOSING,
	MODELCONDITION_DOOR_4_CLOSING
};

static const ModelConditionFlagType theWaitingOpenFlags[4] =
{
	MODELCONDITION_DOOR_1_WAITING_OPEN,
	MODELCONDITION_DOOR_2_WAITING_OPEN,
	MODELCONDITION_DOOR_3_WAITING_OPEN,
	MODELCONDITION_DOOR_4_WAITING_OPEN
};

struct GameLogic
{
	unsigned char m_padding[0x3c];
	UnsignedInt m_frame;
	UnsignedInt getFrame() const { return m_frame; }
};

extern GameLogic *TheGameLogic;

struct ProductionUpdateModuleData
{
	unsigned char m_padding[0x0c];
	UnsignedInt m_doorOpeningTime;
	UnsignedInt m_doorWaitOpenTime;
	UnsignedInt m_doorClosingTime;
};

struct BfmeDoorInfo
{
	UnsignedInt m_doorOpenedFrame;
	UnsignedInt m_doorWaitOpenFrame;
	UnsignedInt m_doorClosedFrame;
	Bool m_holdOpen;
	unsigned char m_padding[3];
};

struct BfmeModelConditionFlags
{
	UnsignedInt m_bits[10];

	void set(ModelConditionFlagType flag)
	{
		m_bits[(UnsignedInt)flag >> 5] |= 1 << ((UnsignedInt)flag & 31);
	}

	void set(ModelConditionFlagType flag, Bool value)
	{
		if (value)
			set(flag);
		else
			m_bits[(UnsignedInt)flag >> 5] &= ~(1 << ((UnsignedInt)flag & 31));
	}
};

class ProductionUpdate
{
public:
	const ProductionUpdateModuleData *getProductionUpdateModuleData() const
	{
		return m_moduleData;
	}

protected:
	void updateDoors();

private:
	void *m_vptr;
	ProductionUpdateModuleData *m_moduleData;
	unsigned char m_padding[0x34];
	BfmeDoorInfo m_doors[4];
	BfmeModelConditionFlags m_clearFlags;
	BfmeModelConditionFlags m_setFlags;
	Bool m_flagsDirty;
};

// ?updateDoors@ProductionUpdate@@IAEXXZ
void ProductionUpdate::updateDoors()
{
	const ProductionUpdateModuleData *d = getProductionUpdateModuleData();
	UnsignedInt now = TheGameLogic->getFrame();
	for (Int i = 0; i < 4; ++i)
	{
		if (m_doors[i].m_doorOpenedFrame)
		{
			if (now - m_doors[i].m_doorOpenedFrame > d->m_doorOpeningTime)
			{
				m_doors[i].m_doorOpenedFrame = 0;
				m_doors[i].m_doorWaitOpenFrame = now;
				m_clearFlags.set(theOpeningFlags[i], true);
				m_setFlags.set(theOpeningFlags[i], false);
				m_setFlags.set(theWaitingOpenFlags[i]);
				m_flagsDirty = 1;
			}
		}
		else if (m_doors[i].m_doorWaitOpenFrame)
		{
			if (now - m_doors[i].m_doorWaitOpenFrame > d->m_doorWaitOpenTime && !m_doors[i].m_holdOpen)
			{
				m_doors[i].m_doorWaitOpenFrame = 0;
				m_doors[i].m_doorClosedFrame = now;
				m_clearFlags.set(theWaitingOpenFlags[i], true);
				m_setFlags.set(theWaitingOpenFlags[i], false);
				m_setFlags.set(theClosingFlags[i]);
				m_flagsDirty = 1;
			}
		}
		else if (m_doors[i].m_doorClosedFrame && !m_doors[i].m_holdOpen)
		{
			if (now - m_doors[i].m_doorClosedFrame > d->m_doorClosingTime)
			{
				m_doors[i].m_doorClosedFrame = 0;
				m_clearFlags.set(theClosingFlags[i], true);
				m_setFlags.set(theClosingFlags[i], false);
				m_flagsDirty = 1;
			}
		}
	}
}
