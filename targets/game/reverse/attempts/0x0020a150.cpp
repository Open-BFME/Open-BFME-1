// ?onDie@SlowDeathBehavior@@UAEXPBVDamageInfo@@@Z
// partial score=0.9952 date=2026-10-30
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// SlowDeathBehavior::onDie (retail 0x0020A150, 842 B).  Clean C++ conversion
// of the former __emit lift in
// game/GameEngine/Source/GameLogic/Object/Behavior/SlowDeathBehavior_onDie_Thunk.cpp.
//
// The receiver is the DieModuleInterface subobject at complete-object +0x20
// (object pointer at this-0x18, SlowDeathBehaviorInterface at this+4, whose
// slot 2 is the landed isDieApplicable 0x001F7080).  BFME replaces Zero
// Hour's two-pass roll with a weighted rejection loop: every applicable
// SlowDeathBehaviorInterface and its probability go into two STLport
// vectors, a roll picks one, and a pick that no longer accepts the death
// (isDieApplicable, then BFME's fourth interface slot +0x0C) is removed by
// swapping in the last entry, until one begins its slow death.  BFME 2
// (Open-BFME-2 Code/GameEngine/Source/GameLogic/Object/Behavior/
// SlowDeathBehaviorUpdate.cpp, 0x0045E6B8) has the same loop; BFME 1 adds
// the selectable-when-dead test on ThingTemplate +0x4CA and passes
// file/line to the random call.  Like SlowDeathBehavior_beginSlowDeath.cpp,
// this TU keeps the BFME1 layout as compact local views; the Zero Hour
// layout of SlowDeathBehavior.cpp cannot hold this body.

#include <vector>

typedef int Int;
typedef bool Bool;

class DamageInfo;

template<class T> inline T &at(void *p, unsigned off) { return *(T *)((char *)p+off); }
template<class T> inline const T &at(const void *p, unsigned off) { return *(const T *)((const char *)p+off); }

// Overridable: final override resolved inline one level, recursing through
// the out-of-line body (0x00087A80).
class Overridable
{
public:
	virtual void slot00();
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}
	Overridable *m_nextOverride;
};
class ThingTemplate : public Overridable {};

class AIUpdateInterface
{
public:
	Bool isAiInDeadState() const { return at<Bool>(this, 0x32b); }	// m_isAiDead
	void markAsDead();
};

class SlowDeathBehaviorInterface
{
public:
	virtual void beginSlowDeath(const DamageInfo *damageInfo) = 0;
	virtual Int getProbabilityModifier(const DamageInfo *damageInfo) const = 0;
	virtual Bool isDieApplicable(const DamageInfo *damageInfo) const = 0;
	virtual Bool slot0C() = 0;	// BFME-only slot, identity unproven
};

class BehaviorModuleInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
	virtual void slot50(); virtual void slot54();
	virtual SlowDeathBehaviorInterface *getSlowDeathBehaviorInterface();
};
class BehaviorModule
{
public:
	char pad00[0x0c];
	BehaviorModuleInterface m_interface;	// +0x0C
};

// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Override.h
template <class T> class OVERRIDE
{
public:
	const T *operator*() const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}
	operator const T *() const { return operator*(); }
private:
	const T *m_overridable;
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	AIUpdateInterface *getAIUpdateInterface() { return at<AIUpdateInterface *>(this, 0x204); }
	BehaviorModule **getBehaviorModules() const { return at<BehaviorModule **>(this, 0x1f0); }
	void setSelectable(bool selectable);
private:
	virtual void slot00();
	OVERRIDE<ThingTemplate> m_template;	// +0x04
};

class GameLogic
{
public:
	void deselectObject(Object *obj, unsigned short playerMask, bool affectClient);
};
extern GameLogic *TheGameLogic;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class UpdateModule
{
public:
	virtual void slot00();
protected:
	Object *getObject() const { return m_object; }
	const void *m_moduleData;
	Object *m_object;	// +0x08
	char pad0c[0x14];
};
class DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo) = 0;
};

class SlowDeathBehavior : public UpdateModule, public DieModuleInterface, public SlowDeathBehaviorInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo);
	virtual void beginSlowDeath(const DamageInfo *damageInfo);
	virtual Int getProbabilityModifier(const DamageInfo *damageInfo) const;
	virtual Bool isDieApplicable(const DamageInfo *damageInfo) const;
	virtual Bool slot0C();
};

void SlowDeathBehavior::onDie( const DamageInfo *damageInfo )
{
	if (!isDieApplicable(damageInfo))
		return;

	AIUpdateInterface *ai = getObject()->getAIUpdateInterface();
	if (ai)
	{
		// has another AI already handled us. (hopefully another SlowDeathBehavior)
		if (ai->isAiInDeadState())
			return;
		ai->markAsDead();
	}

	// deselect this unit for all players.
	TheGameLogic->deselectObject(getObject(), 0xffff, true);

	Object *obj = getObject();
	if (obj->getTemplate() && !at<Bool>(obj->getTemplate(), 0x4ca))
		obj->setSelectable(false);

	Int total = 0;
	std::vector<Int> probabilities;
	std::vector<SlowDeathBehaviorInterface *> behaviors;
	for (BehaviorModule** update = getObject()->getBehaviorModules(); *update; ++update)
	{
		SlowDeathBehaviorInterface* sdu = (*update)->m_interface.getSlowDeathBehaviorInterface();
		if (sdu != 0 && sdu->isDieApplicable(damageInfo))
		{
			Int probability = sdu->getProbabilityModifier( damageInfo );
			total += probability;
			probabilities.push_back(probability);
			behaviors.push_back(sdu);
		}
	}

	while (!behaviors.empty())
	{
#line 813 "F:\\\\bfme\\\\Code\\\\gameengine\\\\Source\\\\GameLogic\\\\Object\\\\Behavior\\\\SlowDeathBehavior.cpp"
		Int roll = GetGameLogicRandomValue(0, total - 1, __FILE__, __LINE__);
		std::vector<Int>::iterator it = probabilities.begin();
		for (; it != probabilities.end(); ++it)
		{
			if (roll < *it)
				break;
			roll -= *it;
		}
		total -= *it;
		Int index = it - probabilities.begin();

		SlowDeathBehaviorInterface *sdu = behaviors[index];
		if (sdu && sdu->isDieApplicable(damageInfo) && sdu->slot0C())
		{
			sdu->beginSlowDeath(damageInfo);
			return;
		}

		behaviors[index] = behaviors.back();
		behaviors.pop_back();
		probabilities[index] = probabilities.back();
		probabilities.pop_back();
	}
}
