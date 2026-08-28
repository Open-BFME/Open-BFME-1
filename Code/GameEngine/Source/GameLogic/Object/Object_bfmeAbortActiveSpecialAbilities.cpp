// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

class CommandButton;

class BFMESpecialPowerUpdateInterface
{
public:
	virtual void slot00();
	virtual Bool isSpecialAbility() const;
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual Bool isPowerCurrentlyInUse(const CommandButton *command) const;
};

class BFMEBehaviorSpecialPowerInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual BFMESpecialPowerUpdateInterface *getSpecialPowerUpdateInterface();
};

class BehaviorModule;

class SpecialAbilityUpdate
{
public:
	void bfmeAbortAbility();
};

class Object
{
public:
	void bfmeAbortActiveSpecialAbilities() const;

private:
	unsigned char m_pad[0x1f0];
	BehaviorModule **m_behaviors;
};

void Object::bfmeAbortActiveSpecialAbilities() const
{
	for (BehaviorModule **module = m_behaviors; *module; ++module)
	{
		BFMEBehaviorSpecialPowerInterface *behavior =
			reinterpret_cast<BFMEBehaviorSpecialPowerInterface *>(
				reinterpret_cast<char *>(*module) + 0x0c);
		BFMESpecialPowerUpdateInterface *specialPower =
			behavior->getSpecialPowerUpdateInterface();
		if (specialPower && specialPower->isSpecialAbility())
		{
			SpecialAbilityUpdate *update = reinterpret_cast<SpecialAbilityUpdate *>(
				reinterpret_cast<char *>(specialPower) - 0x20);
			specialPower = reinterpret_cast<BFMESpecialPowerUpdateInterface *>(
				reinterpret_cast<char *>(update) + 0x20);
			if (specialPower->isPowerCurrentlyInUse(0))
				update->bfmeAbortAbility();
		}
	}
}
