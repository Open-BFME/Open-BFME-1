// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LevelGrantSpecialPower scalar deleting destructor.
class __declspec(novtable) SpecialAbilityUpdate
{
public:
	virtual ~SpecialAbilityUpdate();
};

class LevelGrantSpecialPower : public SpecialAbilityUpdate
{
	friend void forceLevelGrantSpecialPowerDeletingDestructorCopy(const LevelGrantSpecialPower &that);
protected:
	__declspec(noinline) virtual ~LevelGrantSpecialPower();
};

// ~LevelGrantSpecialPower is matched out of line (SpecialAbilityUpdateDestructor.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceLevelGrantSpecialPowerDeletingDestructorCopy(const LevelGrantSpecialPower &that)
{
	LevelGrantSpecialPower value(that);
}
