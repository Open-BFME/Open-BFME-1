// cl: /DNDEBUG /MD /O2 /Ob2
// Retail RVA 0x0024F810. The owner class and its field names remain unknown.
// The ILT at 0x0001E0AB names the game-logic predicate, and the ILT at
// 0x0004A12E names the ExperienceTracker-compatible three-argument call.

class GameLogicPortraitShim
{
public:
	bool isInMultiplayerOrSkirmishGame(void);
};

#define TheGameLogic (*(GameLogicPortraitShim **)0x012F0898)

class ExperienceTracker
{
public:
	bool gainExpForLevel(int levelsToGain, bool canScaleForBonus,
		bool provideFeedback);
};

class Rva0024F810Inner
{
public:
	unsigned char m_head[0x28];
	int m_start;
};

class Rva0024F810State
{
public:
	unsigned char m_head[0x210];
	Rva0024F810Inner *m_inner;
};

class Rva0024F810Thing
{
public:
	unsigned char m_head[8];
	int m_time;
	char m_flag;
};

class Rva0024F810Owner
{
public:
	void apply(void);
};

void Rva0024F810Owner::apply(void)
{
	char *base = (char *)this;

	if ((*(Rva0024F810Thing **)(base - 0xc))->m_flag != 0
		&& TheGameLogic->isInMultiplayerOrSkirmishGame() == 0)
		return;

	Rva0024F810State *state = *(Rva0024F810State **)((char *)this - 8);
	Rva0024F810Thing *owner = *(Rva0024F810Thing **)((char *)this - 0xc);
	Rva0024F810Inner *inner = state->m_inner;
	int now = owner->m_time;
	int start = inner->m_start;

	reinterpret_cast<ExperienceTracker *>(inner)->gainExpForLevel(
		now - start, false, false);
}
