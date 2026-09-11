// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: Energy::adjustPower, retail 0x000C7ED0 (138 bytes).
//
// Identity: Object::onDisabledEdge calls Energy::adjustPower through ILT
// 0x00041A56, and the canonical upstream Energy declaration gives this exact
// (Int, Bool) operation.  The matching sibling Energy bodies use the BFME
// layout below: production at +4, consumption at +8, owner at +0xc.

class Player
{
public:
	void onPowerBrownOutChange(bool brownOut);
};

class Energy
{
public:
	void adjustPower(int powerDelta, bool adding);

private:
	void *m_vptrPad;
	int m_energyProduction;
	int m_energyConsumption;
	Player *m_owner;

	void addProduction(int amount)
	{
		m_energyProduction += amount;
		if (m_owner == 0)
			return;
		m_owner->onPowerBrownOutChange(m_energyProduction < m_energyConsumption);
	}

	void addConsumption(int amount)
	{
		m_energyConsumption += amount;
		if (m_owner == 0)
			return;
		m_owner->onPowerBrownOutChange(m_energyProduction < m_energyConsumption);
	}
};

// ?adjustPower@Energy@@QAEXH_N@Z
void Energy::adjustPower(int powerDelta, bool adding)
{
	if (powerDelta == 0)
		return;

	if (powerDelta > 0)
	{
		if (adding)
			addProduction(powerDelta);
		else
			addProduction(-powerDelta);
	}
	else
	{
		if (adding)
			addConsumption(-powerDelta);
		else
			addConsumption(powerDelta);
	}
}
