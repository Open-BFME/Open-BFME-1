// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LevelGrantSpecialPower scalar deleting destructor.

class SpecialAbilityUpdate
{
protected:
	virtual ~SpecialAbilityUpdate();
};

class LevelGrantSpecialPower : public SpecialAbilityUpdate
{
protected:
	__declspec(noinline) virtual ~LevelGrantSpecialPower();
};

LevelGrantSpecialPower::~LevelGrantSpecialPower()
{
}
