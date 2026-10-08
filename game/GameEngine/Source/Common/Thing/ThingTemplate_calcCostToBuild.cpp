// cl: /DNDEBUG /MD /EHsc
// ?calcCostToBuild@ThingTemplate@@QBEHPBVPlayer@@H@Z
//
// Retail RVA 0x0013E390 (131 bytes), reached through ILT 0xDA8A from the
// matched UpgradeTemplate::calcCostToBuild (0x0010A850) and
// Player::canAffordBuild (0x000C99D0, base cost -1). A base cost of -1 reads
// the final override's build cost. Without a player the base cost is
// returned unscaled; otherwise it is scaled by the faction modifier, the
// owner-list modifier and the BUILDCOST handicap.

typedef float Real;

class AsciiString;
class ThingTemplate;

class Handicap
{
public:
	enum HandicapType { BUILDCOST = 0 };
	Real getHandicap(HandicapType t, const ThingTemplate *tmpl) const;
};

class Rva000D6030Owner
{
public:
	Real rva000d6030(const ThingTemplate *tmpl);
};

class Player
{
public:
	Real getProductionCostChangePercent(const AsciiString &buildTemplateName) const;
	char m_pad00[0xC];
	Handicap m_handicap; // +0x0C
};

class Overridable
{
public:
	Overridable *friend_getFinalOverride();
	Overridable *getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}
	void *m_vtbl;
	Overridable *m_nextOverride; // +0x04
};

extern const Real BfmeSubdualCapERD;

class ThingTemplate : public Overridable
{
public:
	int calcCostToBuild(const Player *player, int baseCost) const;
	unsigned short getBuildCost() const
	{
		const ThingTemplate *tmpl = m_nextOverride ? (const ThingTemplate *)m_nextOverride->getFinalOverride() : this;
		if (!tmpl)
			tmpl = this;
		return tmpl->m_buildCost;
	}
	char m_pad08[0x18];
	char m_nameString[4]; // +0x20
	char m_pad24[0x456];
	unsigned short m_buildCost; // +0x47A
};

int ThingTemplate::calcCostToBuild(const Player *player, int baseCost) const
{
	int cost = (baseCost == -1) ? getBuildCost() : baseCost;
	if (!player)
		return cost;

	Real factionModifier = BfmeSubdualCapERD + player->getProductionCostChangePercent(*(const AsciiString *)m_nameString);
	factionModifier *= ((Rva000D6030Owner *)player)->rva000d6030(this);
	Real buildCost = cost;
	return (int)(buildCost * player->m_handicap.getHandicap(Handicap::BUILDCOST, this) * factionModifier);
}
