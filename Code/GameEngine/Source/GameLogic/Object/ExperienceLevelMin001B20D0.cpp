// cl: /O2 /Ob1 /DNDEBUG /MD
// BFME retail 0x001B20D0: clamp a floating threshold to an experience value.

extern void j_00027953();

class ExperienceLevelSystem
{
};

typedef int (ExperienceLevelSystem::*BfmeExperienceMethod)(void *, int, int);

union BfmeExperienceCall
{
	void (*freeFunction)();
	BfmeExperienceMethod memberFunction;
};

extern ExperienceLevelSystem *TheExperienceLevelSystem;

class BfmeExperienceOwner001B20D0
{
public:
	float getMinimumExperience(float minimum, int level) const;

private:
	unsigned char m_head[4];
	void *m_tracker;
};

float BfmeExperienceOwner001B20D0::getMinimumExperience(
	float minimum, int level) const
{
	BfmeExperienceCall call;
	call.freeFunction = j_00027953;
	int experience = (TheExperienceLevelSystem->*call.memberFunction)(
		m_tracker, level, 0);
	float converted = (float)experience;
	float *selected;
	if (converted < minimum)
		selected = &converted;
	else
		selected = &minimum;
	return *selected;
}
