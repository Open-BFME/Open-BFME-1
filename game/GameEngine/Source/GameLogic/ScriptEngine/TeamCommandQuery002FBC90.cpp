// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport
// Retail team command-button queries: 0x002FBC90 (760B), 0x002FB8D0 (766B),
// and 0x002FB4F0 (782B). The dispatcher reaches these through ILT thunks;
// action identities remain address-derived rather than inferred from adjacency.
// Layouts follow the byte-verified named-unit query siblings and the ZH
// PartitionManager.h filter declarations, with BFME's next-link at +4.
// The visible noinline mask-filter constructor permits native temporary reuse.
// Mask construction order 88/53/129 and the Bool option result preserve the
// retail scheduling. The 46B valid-target constructor is independently exact
// at 0x001ED510; calls route through 0x0003A5AD.

#include "StringInline.h"
#include <bitset>

typedef bool Bool;
typedef int Int;
typedef float Real;

class Object;
class Team;
class Player;
class CommandButton;
class UpgradeTemplate;

struct Coord3D
{
    Real x;
    Real y;
    Real z;
};

template <size_t NUMBITS>
class BitFlags
{
public:
    enum BogusInitType
    {
        kInit = 0
    };

    __declspec(nothrow) BitFlags(BogusInitType, Int bit);
    BitFlags(BogusInitType, Int a, Int b, Int c) { m_bits.set(a); m_bits.set(b); m_bits.set(c); }
    ~BitFlags() {}

private:
    _STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<192> KindOfMaskType;

#define MAKE_KINDOF_MASK(bit) KindOfMaskType(KindOfMaskType::kInit, (bit))

extern const KindOfMaskType KINDOFMASK_NONE;

class ScriptEngine
{
public:
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
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;
};

class ControlBar
{
public:
    const CommandButton *findCommandButton(const AsciiString &name);
};

enum GUICommandType { GUI_COMMAND_NONE = 0 };
class Overridable
{
public:
    Overridable *friend_getFinalOverride() {
        if (m_nextOverride) return m_nextOverride->friend_getFinalOverride();
        return this;
    }
    const Overridable *friend_getFinalOverride() const {
        if (m_nextOverride) return m_nextOverride->friend_getFinalOverride();
        return this;
    }
private:
    void *m_memoryPoolVTable;
    Overridable *m_nextOverride;
    Bool m_isOverride;
};
class SpecialPowerTemplate : public Overridable
{
public:
    unsigned int getID() const { return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_id; }
private:
    AsciiString m_name;
    unsigned int m_id;
};
class CommandButton
{
public:
    Bool isReady(const Object *) const;
    GUICommandType getCommandType() const { return m_command; }
    const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_specialPower; }
    unsigned int getOptions() const { return m_options; }
private:
    unsigned char m_beforeCommand[0x10];
    GUICommandType m_command;
    const UpgradeTemplate *m_upgradeTemplate;
    unsigned int m_options;
    unsigned char m_beforeSpecialPower[0x18];
    const SpecialPowerTemplate *m_specialPower;
};

#include "../command_source_type.h"

class Object
{
public:
    const Coord3D *getPosition() const
    {
        return &m_position;
    }

private:
    unsigned char m_beforePosition[0x38];
    Coord3D m_position;
};

class PartitionFilter
{
public:
    PartitionFilter() : m_next(0) {}
    virtual ~PartitionFilter() {}
    virtual Bool allow(Object *object) = 0;
    virtual Int getPlayerMask();
    PartitionFilter *link(PartitionFilter *next);

    PartitionFilter *m_next;
};

class PartitionFilterSameMapStatus : public PartitionFilter
{
public:
    PartitionFilterSameMapStatus(const Object *object) : m_object(object) {}

protected:
    virtual Bool allow(Object *object);

private:
    const Object *m_object;
};

class PartitionFilterValidCommandButtonTarget : public PartitionFilter
{
public:
    __declspec(noinline) PartitionFilterValidCommandButtonTarget(Object *source,
        const CommandButton *button, Bool match, CommandSourceType sourceType)
        : m_source(source), m_commandButton(button), m_match(match),
          m_commandSource(sourceType) {}

protected:
    virtual Bool allow(Object *object);

private:
    Object *m_source;
    const CommandButton *m_commandButton;
    Bool m_match;
    CommandSourceType m_commandSource;
};

class PartitionFilterGarrisonable : public PartitionFilter
{
public:
    PartitionFilterGarrisonable(Bool match) : m_match(match) {}

protected:
    virtual Bool allow(Object *object);

private:
    Bool m_match;
};

class PartitionFilterPlayerAffiliation : public PartitionFilter
{
public:
    PartitionFilterPlayerAffiliation(const Player *player,
        unsigned int affiliation, Bool match)
        : m_player(player), m_match(match), m_affiliation(affiliation) {}

protected:
    virtual Bool allow(Object *object);
    virtual Int getPlayerMask();

private:
    const Player *m_player;
    Bool m_match;
    unsigned int m_affiliation;
};

struct VptrZeroBlock24
{
    unsigned int m_dword00;
    unsigned int m_dword04;
    unsigned int m_dword08;
    unsigned int m_dword0c;
    unsigned int m_dword10;
    unsigned int m_dword14;
};

class Rva000C3DD0VptrZeroBlockObject : public PartitionFilter
{
public:
    __declspec(noinline) Rva000C3DD0VptrZeroBlockObject(
        const VptrZeroBlock24 &first, const VptrZeroBlock24 &second) : m_first(first), m_second(second) {}
    virtual Bool allow(Object *object);

    VptrZeroBlock24 m_first;
    VptrZeroBlock24 m_second;
};

class PartitionManager
{
public:
    Object *getClosestObject(const Coord3D *position, Real maxDistance,
        Int distanceCalculation, PartitionFilter *filters);
};

extern ScriptEngine *TheScriptEngine;
extern ControlBar *TheControlBar;
extern PartitionManager *ThePartitionManager;

enum AllowPlayerRelationship
{
    ALLOW_SAME_PLAYER = 0x01,
    ALLOW_ALLIES = 0x02,
    ALLOW_ENEMIES = 0x04,
    ALLOW_NEUTRAL = 0x08
};

class AIGroup
{
public:
    Object *getSpecialPowerSourceObject(unsigned int);
    Object *getCommandButtonSourceObject(GUICommandType);
    Bool getCenter(Coord3D *);
    void groupDoCommandButtonAtPosition(const CommandButton *, const Coord3D *, CommandSourceType);
    void groupDoCommandButtonAtObject(const CommandButton *, Object *, CommandSourceType);
};
class AI { public: AIGroup *createGroup(); };
class Team { public: void getTeamAsAIGroup(AIGroup *); Player *getControllingPlayer() const; };
extern AI *TheAI;
class TeamCommandQuery002FBC90
{
public:
    void apply(const AsciiString &teamName, const AsciiString &commandAbility);
};
void TeamCommandQuery002FBC90::apply(const AsciiString &teamName, const AsciiString &commandAbility)
{
    Team *team = TheScriptEngine->getTeamNamed(teamName, false);
    if (!team) return;
    AIGroup *group = TheAI->createGroup();
    team->getTeamAsAIGroup(group);
    const CommandButton *button = TheControlBar->findCommandButton(commandAbility);
    if (!button) return;
    Object *source;
    if (button->getSpecialPowerTemplate())
        source = group->getSpecialPowerSourceObject(button->getSpecialPowerTemplate()->getID());
    else
        source = group->getCommandButtonSourceObject(button->getCommandType());
    if (!source) return;
    if (!button->isReady(source)) return;
    Coord3D position;
    group->getCenter(&position);
    KindOfMaskType excluded(KindOfMaskType::kInit, 88, 53, 129);
    if ((Bool)((button->getOptions() >> 5) & 1)) {
        Object *target;
        {
            PartitionFilterSameMapStatus mapFilter(source);
            target = ThePartitionManager->getClosestObject(&position, 1000000.0f, 0,
                PartitionFilterPlayerAffiliation(team->getControllingPlayer(), ALLOW_ENEMIES, true).link(
                    Rva000C3DD0VptrZeroBlockObject(*(const VptrZeroBlock24 *)&KINDOFMASK_NONE,
                        *(const VptrZeroBlock24 *)&excluded).link(&mapFilter)));
        }
        if (target) group->groupDoCommandButtonAtPosition(button, target->getPosition(), CMD_FROM_SCRIPT);
    } else {
        Object *target;
        {
            PartitionFilterSameMapStatus mapFilter(source);
            target = ThePartitionManager->getClosestObject(&position, 1000000.0f, 0,
                PartitionFilterPlayerAffiliation(team->getControllingPlayer(), ALLOW_ENEMIES, true).link(
                    Rva000C3DD0VptrZeroBlockObject(*(const VptrZeroBlock24 *)&MAKE_KINDOF_MASK(7),
                        *(const VptrZeroBlock24 *)&KINDOFMASK_NONE).link(
                        PartitionFilterValidCommandButtonTarget(source, button, true, CMD_FROM_SCRIPT).link(
                            Rva000C3DD0VptrZeroBlockObject(*(const VptrZeroBlock24 *)&KINDOFMASK_NONE,
                                *(const VptrZeroBlock24 *)&excluded).link(&mapFilter)))));
        }
        if (target) group->groupDoCommandButtonAtObject(button, target, CMD_FROM_SCRIPT);
    }
}

// Retail 0x002FB8D0: the object-query mask index is the third argument.
class TeamCommandQuery002FB8D0
{
public:
    void apply(const AsciiString &teamName, const AsciiString &commandAbility, Int kindofBit);
};
void TeamCommandQuery002FB8D0::apply(const AsciiString &teamName, const AsciiString &commandAbility, Int kindofBit)
{
    Team *team = TheScriptEngine->getTeamNamed(teamName, false);
    if (!team) return;
    AIGroup *group = TheAI->createGroup();
    team->getTeamAsAIGroup(group);
    const CommandButton *button = TheControlBar->findCommandButton(commandAbility);
    if (!button) return;
    Object *source;
    if (button->getSpecialPowerTemplate())
        source = group->getSpecialPowerSourceObject(button->getSpecialPowerTemplate()->getID());
    else
        source = group->getCommandButtonSourceObject(button->getCommandType());
    if (!source) return;
    if (!button->isReady(source)) return;
    Coord3D position;
    group->getCenter(&position);
    KindOfMaskType excluded(KindOfMaskType::kInit, 88, 53, 129);
    if ((Bool)((button->getOptions() >> 5) & 1)) {
        Object *target;
        {
            PartitionFilterSameMapStatus mapFilter(source);
            target = ThePartitionManager->getClosestObject(&position, 1000000.0f, 0,
                PartitionFilterPlayerAffiliation(team->getControllingPlayer(), ALLOW_ENEMIES, true).link(
                    Rva000C3DD0VptrZeroBlockObject(*(const VptrZeroBlock24 *)&KINDOFMASK_NONE,
                        *(const VptrZeroBlock24 *)&excluded).link(&mapFilter)));
        }
        if (target) group->groupDoCommandButtonAtPosition(button, target->getPosition(), CMD_FROM_SCRIPT);
    } else {
        Object *target;
        {
            PartitionFilterSameMapStatus mapFilter(source);
            target = ThePartitionManager->getClosestObject(&position, 1000000.0f, 0,
                PartitionFilterPlayerAffiliation(team->getControllingPlayer(), ALLOW_ENEMIES, true).link(
                    Rva000C3DD0VptrZeroBlockObject(*(const VptrZeroBlock24 *)&MAKE_KINDOF_MASK(kindofBit),
                        *(const VptrZeroBlock24 *)&KINDOFMASK_NONE).link(
                        PartitionFilterValidCommandButtonTarget(source, button, true, CMD_FROM_SCRIPT).link(
                            Rva000C3DD0VptrZeroBlockObject(*(const VptrZeroBlock24 *)&KINDOFMASK_NONE,
                                *(const VptrZeroBlock24 *)&excluded).link(&mapFilter)))));
        }
        if (target) group->groupDoCommandButtonAtObject(button, target, CMD_FROM_SCRIPT);
    }
}

// Retail 0x002FB4F0: additional garrisonable-target filter.
class TeamCommandQuery002FB4F0
{
public:
    void apply(const AsciiString &teamName, const AsciiString &commandAbility);
};
void TeamCommandQuery002FB4F0::apply(const AsciiString &teamName, const AsciiString &commandAbility)
{
    Team *team = TheScriptEngine->getTeamNamed(teamName, false);
    if (!team) return;
    AIGroup *group = TheAI->createGroup();
    team->getTeamAsAIGroup(group);
    const CommandButton *button = TheControlBar->findCommandButton(commandAbility);
    if (!button) return;
    Object *source;
    if (button->getSpecialPowerTemplate())
        source = group->getSpecialPowerSourceObject(button->getSpecialPowerTemplate()->getID());
    else
        source = group->getCommandButtonSourceObject(button->getCommandType());
    if (!source) return;
    if (!button->isReady(source)) return;
    Coord3D position;
    group->getCenter(&position);
    KindOfMaskType excluded(KindOfMaskType::kInit, 88, 53, 129);
    if ((Bool)((button->getOptions() >> 5) & 1)) {
        Object *target;
        {
            PartitionFilterSameMapStatus mapFilter(source);
            target = ThePartitionManager->getClosestObject(&position, 1000000.0f, 0,
                PartitionFilterPlayerAffiliation(team->getControllingPlayer(), ALLOW_ENEMIES, true).link(
                    Rva000C3DD0VptrZeroBlockObject(*(const VptrZeroBlock24 *)&KINDOFMASK_NONE,
                        *(const VptrZeroBlock24 *)&excluded).link(&mapFilter)));
        }
        if (target) group->groupDoCommandButtonAtPosition(button, target->getPosition(), CMD_FROM_SCRIPT);
    } else {
        Object *target;
        {
            PartitionFilterSameMapStatus mapFilter(source);
            target = ThePartitionManager->getClosestObject(&position, 1000000.0f, 0,
                PartitionFilterPlayerAffiliation(team->getControllingPlayer(), ALLOW_ENEMIES, true).link(
                    Rva000C3DD0VptrZeroBlockObject(*(const VptrZeroBlock24 *)&MAKE_KINDOF_MASK(7),
                        *(const VptrZeroBlock24 *)&KINDOFMASK_NONE).link(
                        PartitionFilterGarrisonable(true).link(
                        PartitionFilterValidCommandButtonTarget(source, button, true, CMD_FROM_SCRIPT).link(
                            Rva000C3DD0VptrZeroBlockObject(*(const VptrZeroBlock24 *)&KINDOFMASK_NONE,
                                *(const VptrZeroBlock24 *)&excluded).link(&mapFilter))))));
        }
        if (target) group->groupDoCommandButtonAtObject(button, target, CMD_FROM_SCRIPT);
    }
}
