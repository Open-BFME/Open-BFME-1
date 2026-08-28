// cl: /DNDEBUG /MD /EHsc

class BehaviorModule;

struct BFMESpecialPowerRechargeShim
{
	virtual void bfmeSlot00() = 0;
	virtual void bfmeSlot01() = 0;
	virtual void bfmeSlot02() = 0;
	virtual void bfmeSlot03() = 0;
	virtual void bfmeSlot04() = 0;
	virtual void bfmeSlot05() = 0;
	virtual void bfmeSlot06() = 0;
	virtual void bfmeSlot07() = 0;
	virtual void bfmeSlot08() = 0;
	virtual void bfmeSlot09() = 0;
	virtual void bfmeSlot10() = 0;
	virtual void bfmeSlot11() = 0;
	virtual void bfmeSlot12() = 0;
	virtual void bfmeSlot13() = 0;
	virtual void bfmeSlot14() = 0;
	virtual void bfmeSlot15() = 0;
	virtual void startPowerRecharge() = 0; // +0x40
};

struct BFMEBehaviorSpecialPowerShim
{
	virtual void bfmeSlot0() = 0;
	virtual void bfmeSlot1() = 0;
	virtual void bfmeSlot2() = 0;
	virtual void bfmeSlot3() = 0;
	virtual void bfmeSlot4() = 0;
	virtual void bfmeSlot5() = 0;
	virtual void bfmeSlot6() = 0;
	virtual BFMESpecialPowerRechargeShim *getSpecialPower() = 0; // +0x1C
};

struct BFMEObjectBehaviorsField
{
	unsigned char pad[0x1f0];
	BehaviorModule *const *behaviors;
};

class Object
{
public:
	void bfmeStartAllSpecialPowerRecharges() const;
};

// The original method spelling is unrecovered.  RespawnUpdate reaches this
// fan-out through the retail ILT before restoring spellbook powers.
void Object::bfmeStartAllSpecialPowerRecharges() const
{
	BehaviorModule *const *behaviors =
		reinterpret_cast<const BFMEObjectBehaviorsField *>(this)->behaviors;

	for (BehaviorModule *const *m = behaviors; *m; ++m)
	{
		char *adjusted =
			reinterpret_cast<char *>(const_cast<BehaviorModule *>(*m)) + 0x0c;
		BFMESpecialPowerRechargeShim *sp =
			reinterpret_cast<BFMEBehaviorSpecialPowerShim *>(adjusted)->getSpecialPower();
		if (!sp)
			continue;

		sp->startPowerRecharge();
	}
}
