// cl: /DNDEBUG /MD /EHsc

typedef int Bool;

enum ModelConditionFlagType
{
	MODELCONDITION_BIT_20 = 20
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class Object
{
public:
	Bool bfmeHasSignificantPreferredLocomotorHeight() const;
	void notifyModelConditionChanged();

	unsigned char m_pad[0x120];
	class ModelConditionFlags
	{
	public:
		bool test(ModelConditionFlagType bit) const { return (m_word & (1u << bit)) != 0; }
		void clear(ModelConditionFlagType bit) { m_word &= ~(1u << bit); }
		void set(ModelConditionFlagType bit) { m_word |= 1u << bit; }

		unsigned int m_word;
	} m_modelCondition;
};

class DeflectSpecialPower
{
public:
	virtual UpdateSleepTime update();

private:
	unsigned char m_pad[0x28];
	bool m_deflecting;
	bool m_wasDeflecting;
};

// ?update@DeflectSpecialPower@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime DeflectSpecialPower::update()
{
	if (!m_deflecting && !m_wasDeflecting)
		return UPDATE_SLEEP_FOREVER;
	if ((unsigned char)(*(Object **)((char *)this - 8))->bfmeHasSignificantPreferredLocomotorHeight())
	{
		if (m_deflecting)
		{
			Object *object = *(Object **)((char *)this - 8);
			m_deflecting = false;
			if (object->m_modelCondition.test(MODELCONDITION_BIT_20))
			{
				object->m_modelCondition.clear(MODELCONDITION_BIT_20);
				object->notifyModelConditionChanged();
			}
			return UPDATE_SLEEP_FOREVER;
		}
	}
	else if (m_wasDeflecting)
	{
		if (!m_deflecting)
		{
			Object *object = *(Object **)((char *)this - 8);
			m_wasDeflecting = false;
			m_deflecting = true;
			if (!object->m_modelCondition.test(MODELCONDITION_BIT_20))
			{
				object->m_modelCondition.set(MODELCONDITION_BIT_20);
				object->notifyModelConditionChanged();
			}
		}
	}
	return UPDATE_SLEEP_NONE;
}
