// cl: /O2 /Ob0

enum ScienceType
{
	SCIENCE_PLACEHOLDER = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	bool hasScience(ScienceType science) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
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

class Rva002CF610
{
public:
	int apply();
	int inner();
};

int Rva002CF610::apply()
{
	int result = inner();
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
