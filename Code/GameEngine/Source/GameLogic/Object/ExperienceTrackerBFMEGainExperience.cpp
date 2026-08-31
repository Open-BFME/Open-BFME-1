// Byte-matched BFME ExperienceTracker multi-level experience helper.

typedef bool Bool;
typedef int Int;
typedef float Real;

class Object;

class ExperienceLevelSystem
{
public:
	Int bfmeExperienceForNextLevel(Object *object, Int *outLevel);
};

extern ExperienceLevelSystem *TheExperienceLevelSystem;

class ExperienceTracker
{
public:
	Bool gainExpForLevel(
		Int levelsToGain,
		Bool canScaleForBonus,
		Bool provideFeedback);

	void addExperiencePoints(
		Real experienceGain,
		Bool canScaleForBonus,
		Bool isShared,
		Bool allowLevelGain,
		Bool provideFeedback);

private:
	void *m_vtable;
	Object *m_parent;
};

Bool ExperienceTracker::gainExpForLevel(
	Int levelsToGain,
	Bool canScaleForBonus,
	Bool provideFeedback)
{
	const Int levelCount = levelsToGain;
	if (levelCount <= 0)
		return false;

	Bool gainedLevel = false;
	Int i = 0;
	while (i < levelCount)
	{
		Int experience = TheExperienceLevelSystem->
			bfmeExperienceForNextLevel(m_parent, 0);
		if (experience <= 0)
			break;
		addExperiencePoints(
			experience,
			false,
			false,
			canScaleForBonus,
			provideFeedback);
		++i;
		gainedLevel = true;
	}

	return gainedLevel;
}
