// cl: /DNDEBUG /MD /EHsc

typedef float Real;

struct RandomSoundSelectorSound
{
	char m_value[4];
};

struct RandomSoundSelectorClientBehaviorModuleDataView
{
	char m_pad000[8];
	RandomSoundSelectorSound *m_indexedSounds[109];
	char m_pad1BC[12];
	Real m_chance;
	unsigned int m_selectedValue;
	bool m_selectedFlag;

	RandomSoundSelectorSound *getIndexedSound(unsigned int index) const
	{
		return m_indexedSounds[index];
	}
};

class RandomSoundSelectorPrimary
{
public:
	virtual void anchor();
	RandomSoundSelectorClientBehaviorModuleDataView *m_moduleData;
	void *m_drawable;
};

class SoundSelectorInterface
{
public:
	virtual RandomSoundSelectorSound *getIndexedSound(unsigned int index) = 0;
	virtual void *findMappedSound(unsigned int key) = 0;
	virtual bool getSelectedValue(unsigned int *value) = 0;
};

class RandomSoundSelectorClientBehavior : public RandomSoundSelectorPrimary, public SoundSelectorInterface
{
public:
	virtual RandomSoundSelectorSound *getIndexedSound(unsigned int index);
	virtual void *findMappedSound(unsigned int key);
	virtual bool getSelectedValue(unsigned int *value);

private:
	void reroll();
	Real m_randomSelection;
	unsigned int m_lastFrame;
};

RandomSoundSelectorSound *RandomSoundSelectorClientBehavior::getIndexedSound(unsigned int index)
{
	RandomSoundSelectorClientBehaviorModuleDataView *data = m_moduleData;
	reroll();
	if (m_randomSelection >= data->m_chance)
		return 0;
	if (data->getIndexedSound(index) == 0)
		return 0;
	return data->getIndexedSound(index) + 1;
}

bool RandomSoundSelectorClientBehavior::getSelectedValue(unsigned int *value)
{
	RandomSoundSelectorClientBehaviorModuleDataView *data = m_moduleData;
	reroll();
	if (m_randomSelection >= data->m_chance)
		return false;
	*value = data->m_selectedValue;
	return data->m_selectedFlag;
}
