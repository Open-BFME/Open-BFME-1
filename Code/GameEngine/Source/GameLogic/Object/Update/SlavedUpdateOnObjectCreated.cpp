// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;

enum ModelConditionFlagType
{
	MODELCONDITION_PACKING = 29
};

class ModelConditionFlags
{
public:
	bool test(ModelConditionFlagType condition) const
	{
		return (m_bits & (1u << condition)) != 0;
	}

	void set(ModelConditionFlagType condition)
	{
		m_bits |= 1u << condition;
	}

private:
	UnsignedInt m_bits;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlavedUpdate.h
class SlavedUpdateModuleData
{
private:
	unsigned char m_unreconstructed00[0x30];

public:
	float m_repairRatePerSecond;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setModelConditionState(ModelConditionFlagType condition)
	{
		if (!m_modelConditionFlags.test(condition))
		{
			m_modelConditionFlags.set(condition);
			notifyModelConditionChanged();
		}
	}

	void notifyModelConditionChanged();

private:
	unsigned char m_unreconstructed000[0x118];
	ModelConditionFlags m_modelConditionFlags;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlavedUpdate.h
class SlavedUpdate
{
public:
	virtual void onObjectCreated();

private:
	SlavedUpdateModuleData *m_moduleData;
	Object *m_object;
};

// ?onObjectCreated@SlavedUpdate@@UAEXXZ
void SlavedUpdate::onObjectCreated()
{
	if (m_moduleData->m_repairRatePerSecond > 0.0f)
		m_object->setModelConditionState(MODELCONDITION_PACKING);
}
