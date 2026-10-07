// cl: /O2 /Ob0

enum ScienceType
{
	SCIENCE_PLACEHOLDER = 0
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	bool hasScience(ScienceType science) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;
	void notifyModelConditionChanged();

	char m_lead[0x134];
	unsigned int m_flags;
};

class DataRva002CF610
{
public:
	char m_lead[0x14];
	int m_value;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_PLACEHOLDER = 0
};

// Retail calls 0x2AC7F -> 0x002CCEC0, the matched DockUpdate::update; this
// body extends it (base-qualified, non-virtual call).
class DockUpdate
{
public:
	virtual UpdateSleepTime update();
};

class Rva002CF610
{
public:
	int apply();
};

int Rva002CF610::apply()
{
	int result = reinterpret_cast<DockUpdate *>(this)->DockUpdate::update();
	Object *obj = *(Object **)((char *)this - 8);
	if (!(obj->m_flags & 0x800))
	{
		DataRva002CF610 *data = *(DataRva002CF610 **)((char *)this - 0xC);
		if (obj->getControllingPlayer()->hasScience((ScienceType)data->m_value))
		{
			if (!(obj->m_flags & 0x800))
			{
				obj->m_flags |= 0x800;
				obj->notifyModelConditionChanged();
			}
		}
	}
	return result;
}
