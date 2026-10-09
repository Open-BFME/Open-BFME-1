// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// BuildAssistant unit availability, including the BFME command-index path.
// Evidence: targets/game/reverse/identity_evidence/000fdbf0-buildassistant-ispossibletomakeunit.md
#include "ascii_string.h"
typedef int Int;
typedef bool Bool;
class UpgradeTemplate;
class Player;
class ThingTemplate
{
public:
    Bool isEquivalentTo(const ThingTemplate *) const;
    unsigned char m_unmodelled00[0x20];
    AsciiString m_name;
};
class Rva000FDBF0Named
{
public:
    virtual AsciiString namedSlot00() const;
};
class Rva000FDBF0CandidateIface
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual Rva000FDBF0Named *slot0A();
};
struct Rva000FDBF0Candidate
{
    unsigned char m_unmodelled00[0xc];
    Rva000FDBF0CandidateIface m_interface;
};
class Object
{
public:
    const AsciiString &getCommandSetString() const;
    Bool hasUpgrade(const UpgradeTemplate *) const;
    Player *getControllingPlayer() const;
    // ?getBehaviorModules@Object@@QBEPAPAURva000FDBF0Candidate@@XZ absent-from-retail
    Rva000FDBF0Candidate **getBehaviorModules() const { return *(Rva000FDBF0Candidate **const *)((const unsigned char *)this + 0x1f0); }
};
class Rva000F9700Owner
{
public:
    Bool method(Int);
};
class Player
{
public:
    Bool canBuild(const ThingTemplate *) const;
    Bool hasUpgradeComplete(const UpgradeTemplate *);
    unsigned char m_unmodelled00[0x684];
    Rva000F9700Owner m_field684;
};
class Rva0049B2A0
{
public:
    const ThingTemplate *method() const;
};

class CommandButton
{
public:
    // ?getThingTemplate@CommandButton@@QBEPBVThingTemplate@@XZ absent-from-retail
    const ThingTemplate *getThingTemplate() const { return ((const Rva0049B2A0 *)this)->method(); }
    unsigned char m_unmodelled00[0x10];
    // ?getCommandType@CommandButton@@QBEHXZ absent-from-retail
    Int getCommandType() const { return *(const Int *)((const unsigned char *)this + 0x10); }
    unsigned char m_unmodelled10[4];
    unsigned char m_unmodelled14[4];
    unsigned int m_options;
    unsigned char m_unmodelled1C[8];
    const UpgradeTemplate *m_upgradePair;
};
class CommandSet
{
public:
    const CommandButton *getCommandButton(Int) const;
};
class ControlBar
{
public:
    const CommandSet *findCommandSet(const AsciiString &);
};
class UpgradeTemplate
{
public:
    unsigned char m_unmodelled00[4];
    Int m_type;
};
extern ControlBar *TheControlBar;

class BuildAssistant
{
public:
    virtual Bool isPossibleToMakeUnit(Object *owner, const ThingTemplate *set, Int upgradeOwner) const;
};

// ?isPossibleToMakeUnit@BuildAssistant@@UBE_NPAVObject@@PBVThingTemplate@@H@Z
Bool BuildAssistant::isPossibleToMakeUnit(Object *owner, const ThingTemplate *set, Int upgradeOwner) const
{
    if (owner == 0)
        return false;
    if (set == 0 && upgradeOwner == -1)
        return false;

    Bool hadUpgradeBit = upgradeOwner != -1;
    if (set != 0)
    {
        Rva000FDBF0Candidate **m_commandSetCandidates = owner->getBehaviorModules();
        for (Rva000FDBF0Candidate **node = m_commandSetCandidates; *node; ++node)
        {
            Rva000FDBF0Named *named = (*node)->m_interface.slot0A();
            if (named)
            {
                if (named->namedSlot00().compare(set->m_name) == 0)
                    return true;
            }
        }
    }
    const CommandSet *found = TheControlBar->findCommandSet(owner->getCommandSetString());
    if (found == 0)
        return false;

    const CommandButton *foundCommand = 0;
    Int matchCount = 0;
    for (Int slotIndex = 0; slotIndex < 20; ++slotIndex)
    {
        const CommandButton *button = found->getCommandButton(slotIndex);
        if (button == 0)
            continue;
        if (!hadUpgradeBit)
        {
            Int m_kind = button->getCommandType();
            if ((m_kind != 3 && m_kind != 1) ||
                !button->getThingTemplate()->isEquivalentTo(set))
                continue;
            const Bool &needsUpgrade = (button->m_options >> 6) & 1;
            if (needsUpgrade)
            {
                const UpgradeTemplate *upgrade = button->m_upgradePair;
                if (!upgrade)
                    continue;
                if (upgrade->m_type == 1)
                {
                    if (!owner->hasUpgrade(upgrade))
                        continue;
                }
                else if (upgrade->m_type != 0 || !owner->getControllingPlayer()->hasUpgradeComplete(upgrade))
                    continue;
            }
        }
        else
        {
            if (button->getCommandType() != 0x2c)
                continue;
            if (matchCount != upgradeOwner)
            {
                ++matchCount;
                continue;
            }
        }
        foundCommand = button;
        break;
    }
    if (foundCommand == 0)
        return false;
    Player *player = owner->getControllingPlayer();
    if (!hadUpgradeBit)
    {
        if (!player->canBuild(foundCommand->getThingTemplate()))
            return false;
    }
    else if (!player->m_field684.method(upgradeOwner))
        return false;
    return true;
}
