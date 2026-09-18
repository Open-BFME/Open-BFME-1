// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned char UnsignedByte;

class Object;
class Player;

class ExperienceTracker
{
public:
	Int getExperienceValue(const Object *killer) const;
	Real bfmeScaleLivingWorldExperience(Real amount) const;
};

class BfmeOtherCGG
{
};

class BfmeThingCGG
{
public:
	void *bfmeGoCGG(BfmeOtherCGG *other, Bool flag);
};

class Object
{
public:
	Player *getControllingPlayer() const;

	ExperienceTracker *getExperienceTracker() const
	{
		return m_experienceTracker;
	}

private:
	unsigned char m_unreconstructed[0x210];
	ExperienceTracker *m_experienceTracker;
};

class Player
{
public:
	Bool addSkillPoints(Real delta, Bool fromScript);
	Bool addSkillPointsForKill(const Object *killer, const Object *victim);
};

Bool Player::addSkillPointsForKill(const Object *killer, const Object *victim)
{
	if (!killer || !victim)
		return false;

	if ((*(const UnsignedByte *)((const char *)victim + 0x90) & 4) != 0)
		return false;

	Real skillValue;
	if (victim->getControllingPlayer() == this)
	{
		skillValue = victim->getExperienceTracker()->getExperienceValue(killer);
	}
	else
	{
		skillValue = (Int)reinterpret_cast<BfmeThingCGG *>(
			victim->getExperienceTracker())->bfmeGoCGG(
			(BfmeOtherCGG *)killer, false);
		skillValue = killer->getExperienceTracker()->bfmeScaleLivingWorldExperience(
			skillValue);
	}

	return addSkillPoints(skillValue, true);
}
