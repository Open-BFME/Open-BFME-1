// cl: /DNDEBUG /MD /EHsc
// BFME retail body 0x00203180: PropagandaTowerBehavior::effectLogic.
// The BFME layout puts the required upgrade at behavior+0x2C, the recipient
// Object's BodyModule at +0x200, and its weapon-bonus bits at +0x2A0.

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef float Real;

class UpgradeTemplate;

class Player
{
public:
	Bool hasUpgradeComplete(const UpgradeTemplate *upgrade);
};

class BodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual Real getMaxHealth() const = 0;                    // vslot +0x18
};

extern void j_000189f3(void);

class Object
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual Bool attemptHealingFromSoleBenefactor(
		Real amount, const Object *source, UnsignedInt duration);  // vslot +0x44

	Player *getControllingPlayer() const;
	__forceinline Bool hasAnyDamageWeapon() const
	{
		typedef Bool (Object::*Predicate)() const;
		union { void (*raw)(void); Predicate member; } target;
		target.raw = j_000189f3;
		return (this->*target.member)();
	}

	Bool testWeaponBonusCondition(int condition) const
	{
		return (m_weaponBonusFlags & (1 << condition)) != 0;
	}

	void setWeaponBonusCondition(int condition)
	{
		m_weaponBonusFlags |= (1 << condition);
	}

	void clearWeaponBonusCondition(int condition)
	{
		m_weaponBonusFlags &= ~(1 << condition);
	}

	unsigned char m_pad004[0x1FC];
	BodyModuleInterface *m_body;                              // this+0x200
	unsigned char m_pad204[0x9C];
	UnsignedInt m_weaponBonusFlags;                           // this+0x2A0
};

// The official damage-weapon predicate is reached through retail ILT
// 0x000189F3. The local typed call preserves its const-thiscall ABI.

class PropagandaTowerBehaviorModuleData
{
	public:
	unsigned char m_pad00[0x0C];
	UnsignedInt m_scanDelayInFrames;                           // +0x0C
	Real m_autoHealPercentPerSecond;                           // +0x10
	unsigned char m_pad14[0x08];
	Real m_upgradedAutoHealPercentPerSecond;                   // +0x1C
};

class PropagandaTowerBehavior
{
protected:
	// Retail primary vtable 0x010A576C places effectLogic at slot 13.
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void effectLogic(Object *obj, Bool giving,
		const PropagandaTowerBehaviorModuleData *modData);

private:
	unsigned char m_pad04[0x04];
	Object *m_object;                                           // this+0x08
	unsigned char m_pad0c[0x20];
	const UpgradeTemplate *m_upgradeRequired;                 // this+0x2C
};

// Retail multiplies by the float 0.2 at VA 0x01080BBC on this path.
static const Real kLogicFramesReciprocal = 0.2f;

void PropagandaTowerBehavior::effectLogic(
	Object *obj, Bool giving,
	const PropagandaTowerBehaviorModuleData *modData)
{
	if (m_object == 0)
		return;

	Player *player = m_object->getControllingPlayer();
	if (player == 0)
		return;

	Bool effectUpgraded;
	if (m_upgradeRequired != 0)
		effectUpgraded = player->hasUpgradeComplete(m_upgradeRequired);
	else
		effectUpgraded = false;

	if (giving)
	{
		if (obj->hasAnyDamageWeapon() == true)
		{
			if (obj->testWeaponBonusCondition(8) == false)
				obj->setWeaponBonusCondition(8);

			if (effectUpgraded)
			{
				if (obj->testWeaponBonusCondition(15) == false)
					obj->setWeaponBonusCondition(15);
			}
		}

		BodyModuleInterface *body = obj->m_body;
		if (body)
		{
			Real healthPercent;
			if (effectUpgraded)
				healthPercent = modData->m_upgradedAutoHealPercentPerSecond;
			else
				healthPercent = modData->m_autoHealPercentPerSecond;

			Real amount = body->getMaxHealth() * healthPercent
				* kLogicFramesReciprocal;
			obj->attemptHealingFromSoleBenefactor(
				amount, m_object, modData->m_scanDelayInFrames);
		}
	}
	else
	{
		obj->clearWeaponBonusCondition(8);
		obj->clearWeaponBonusCondition(15);
	}
}
