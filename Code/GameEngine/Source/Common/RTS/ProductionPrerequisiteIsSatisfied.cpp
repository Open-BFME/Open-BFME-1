// cl: /DNDEBUG /MD /EHsc
// stlport

#include <vector>

class Player;
class ThingTemplate;

enum ScienceType
{
};

enum UpgradeType
{

    UPGRADE_TYPE_PLAYER,
    UPGRADE_TYPE_OBJECT
};

class UpgradeTemplate
{
public:
    virtual ~UpgradeTemplate();

    UpgradeType getUpgradeType() const
    {
        return m_type;
    }

private:
    UpgradeType m_type;
};

class ProductionPrerequisite
{
public:
    bool isSatisfied(const Player *player) const;

private:
    struct PrereqUnitRec
    {
        const ThingTemplate *unit;
        int flags;
        void *name;
    };

    int calcNumPrereqUnitsOwned(const Player *player, int counts[32]) const;

    std::vector<PrereqUnitRec> m_prereqUnits;
    std::vector<ScienceType> m_prereqSciences;
    std::vector<UpgradeTemplate *> m_prereqUpgrades;
};

class Player
{
public:
    bool hasScience(ScienceType science) const;
    bool hasUpgradeComplete(const UpgradeTemplate *upgrade);
};

// ?isSatisfied@ProductionPrerequisite@@QBE_NPBVPlayer@@@Z
bool ProductionPrerequisite::isSatisfied(const Player *player) const
{
    int i;

    if (!player)
        return false;

    for (i = 0; i < m_prereqSciences.size(); i++)
    {
        if (!player->hasScience(m_prereqSciences[i]))
            return false;
    }

    for (i = 0; i < m_prereqUpgrades.size(); i++)
    {
        const UpgradeTemplate *upgrade = m_prereqUpgrades[i];
        if (upgrade->getUpgradeType() != UPGRADE_TYPE_PLAYER)
            return false;
        if (!const_cast<Player *>(player)->hasUpgradeComplete(upgrade))
            return false;
    }

    int ownCount[32];
    int cnt = calcNumPrereqUnitsOwned(player, ownCount);

    for (i = 1; i < cnt; i++)
    {
        if (m_prereqUnits[i].flags & 1)
        {
            ownCount[i] += ownCount[i - 1];
            ownCount[i - 1] = -1;
        }
    }

    for (i = 0; i < cnt; i++)
    {
        if (ownCount[i] == -1)
            continue;
        if (ownCount[i] == 0)
            return false;
    }

    return true;
}
