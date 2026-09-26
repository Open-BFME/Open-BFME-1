// Open-BFME5 conversions from the BFME experience/level helper family.

class ExperienceTracker
{
public:
	void addExperiencePoints(float experienceGain, bool canScaleForBonus,
		bool isShared, bool allowLevelGain, bool provideFeedback);
};

struct BfmeObjectD120
{
	unsigned char m_pad[0x210];
	ExperienceTracker *m_experienceTracker;
};

// ?bfmeRva0037D120AddExperience@@YAHPAVBfmeObjectD120@@H@Z
int bfmeRva0037D120AddExperience(BfmeObjectD120 *object, int experience)
{
	object->m_experienceTracker->addExperiencePoints(
		(float)experience, true, true, true, false);
	return 1;
}

class BfmeSub210_4B0
{
public:
	void apply(float value, int flags);
};

struct BfmeObjectD150
{
	unsigned char m_pad[0x210];
	BfmeSub210_4B0 *m_sub210;
};

// ?bfmeRva0037D150Apply@@YAHPAVBfmeObjectD150@@H@Z
int bfmeRva0037D150Apply(BfmeObjectD150 *object, int value)
{
	object->m_sub210->apply((float)value, 0);
	return 1;
}
