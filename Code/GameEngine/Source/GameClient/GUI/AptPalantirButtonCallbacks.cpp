class AptPalantir
{
public:
	void showSpellStore();
	void showOptions();
	void upgradeSkill();
};

extern AptPalantir *TheAptPalantir;

// ?aptPalantirOnButtonSpellStore@@YAXXZ
void aptPalantirOnButtonSpellStore()
{
	TheAptPalantir->showSpellStore();
}

// ?aptPalantirOnButtonOptions@@YAXXZ
void aptPalantirOnButtonOptions()
{
	TheAptPalantir->showOptions();
}

// ?aptPalantirOnButtonSkillUpgrade@@YAXXZ
void aptPalantirOnButtonSkillUpgrade()
{
	TheAptPalantir->upgradeSkill();
}
