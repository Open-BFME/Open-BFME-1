// Open-BFME5 conversions from the BFME experience/level helper family.

class ExperienceTracker
{
public:
};

struct BfmeObjectD120
{
	unsigned char m_pad[0x210];
	ExperienceTracker *m_experienceTracker;
};

extern "C" void __cdecl __identifier("?j_00010096@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_000326f5@@YAXXZ")();

// ?bfmeRva0037D120AddExperience@@YAHPAVBfmeObjectD120@@H@Z
int bfmeRva0037D120AddExperience(BfmeObjectD120 *object, int experience)
{
	union { void (*raw)(); void (ExperienceTracker::*member)(float, bool, bool, bool, bool); }
		add = { __identifier("?j_00010096@@YAXXZ") };
	(object->m_experienceTracker->*add.member)(
		(float)experience, true, true, true, false);
	return 1;
}

class BfmeSub210_4B0
{
public:
};

struct BfmeObjectD150
{
	unsigned char m_pad[0x210];
	BfmeSub210_4B0 *m_sub210;
};

// ?bfmeRva0037D150Apply@@YAHPAVBfmeObjectD150@@H@Z
int bfmeRva0037D150Apply(BfmeObjectD150 *object, int value)
{
	union { void (*raw)(); void (BfmeSub210_4B0::*member)(float, int); }
		apply = { __identifier("?j_000326f5@@YAXXZ") };
	(object->m_sub210->*apply.member)((float)value, 0);
	return 1;
}
