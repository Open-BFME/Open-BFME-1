// Player::hasUpgradeComplete(const UpgradeTemplate *) const: ilt_oracle
// CONFIRMS ?hasUpgradeComplete@Player@@QBE_NPBVUpgradeTemplate@@@Z at
// 0x000D5930 (ILT 0x000235BF).
// Two more: another bit test taken from the argument and a clamp between two
// bounds.

class UpgradeTemplate
{
public:
	int m_bfmeHead[8];					// +0x00
	unsigned int m_bfmeIndex;				// +0x20
};

class Player
{
public:
	bool hasUpgradeComplete(const UpgradeTemplate *thing) const;

private:
	int m_bfmeHead[35];					// +0x00
	unsigned int m_upgradesCompleted[8];				// +0x8C
};

// ?hasUpgradeComplete@Player@@QBE_NPBVUpgradeTemplate@@@Z
bool Player::hasUpgradeComplete(const UpgradeTemplate *thing) const
{
	if (thing == 0)
		return false;

	unsigned int index = thing->m_bfmeIndex;

	return (m_upgradesCompleted[index >> 5] & (1 << (index & 31))) != 0;
}

class Gen_000B2860
{
public:
	void bfmeClamp(float low, float high);

private:
	int m_bfmeHead[21];					// +0x00
	float m_bfmeValue;					// +0x54
};

// ?bfmeClamp@Gen_000B2860@@QAEXMM@Z
void Gen_000B2860::bfmeClamp(float low, float high)
{
	float value = m_bfmeValue;

	m_bfmeValue = value < low ? low : (value > high ? high : value);
}
