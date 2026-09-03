// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	float getUpgradeCostChange() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	int calcCostToBuild(const Player *player, int baseCost) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
public:
	int calcCostToBuild(
		Player *player,
		const ThingTemplate *thingTemplate) const;

private:
	char m_bfmeBase[4];
	int m_type;
	char m_bfmeLayout08[0x14];
	int m_cost;
	char m_bfmeLayout20[0xfd];
	bool m_ignorePlayerCostChange;
};

int UpgradeTemplate::calcCostToBuild(
	Player *player,
	const ThingTemplate *thingTemplate) const
{
	int cost = m_cost;
	if (!player)
		return cost;

	float multiplier = 1.0f;
	if (m_type == 1 && !m_ignorePlayerCostChange)
		multiplier = 1.0f + player->getUpgradeCostChange();
	cost = (int)(cost * multiplier);

	if (thingTemplate)
		cost = thingTemplate->calcCostToBuild(player, cost);
	return cost;
}
