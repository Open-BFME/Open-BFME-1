// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/asciistring8outofline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

typedef int ObjectID;

class ModuleData;
class SpecialPowerTemplate;

class Object
{
public:
    ObjectID getID() const { return m_id; }
    class Player *getControllingPlayer() const;

private:
    char m_padding[0x74];
    ObjectID m_id;
};

class Player
{
public:
    int getPlayerIndex() const { return m_playerIndex; }

private:
    char m_padding[0x24];
    int m_playerIndex;
};

class Overridable
{
public:
    virtual ~Overridable();
    virtual void anchor();

    Overridable *friend_getFinalOverride()
    {
        if (m_nextOverride)
            return m_nextOverride->friend_getFinalOverride();
        return this;
    }

    const Overridable *friend_getFinalOverride() const
    {
        if (m_nextOverride)
            return m_nextOverride->friend_getFinalOverride();
        return this;
    }

protected:
    Overridable *m_nextOverride;
    Bool m_isOverride;
    char m_padding[3];
};

class SpecialPowerTemplate : public Overridable
{
public:
    AsciiString getName() const
    {
        const SpecialPowerTemplate *finalTemplate =
            (const SpecialPowerTemplate *)friend_getFinalOverride();
        return finalTemplate->m_name;
    }

    Bool hasPublicTimer() const
    {
        const SpecialPowerTemplate *finalTemplate = getFO();
        return finalTemplate->m_publicTimer;
    }

private:
    const SpecialPowerTemplate *getFO() const
    {
        return (const SpecialPowerTemplate *)friend_getFinalOverride();
    }

    AsciiString m_name;
    char m_padding[0x104];
    Bool m_publicTimer;
};

class SpecialPowerModuleData
{
private:
    char m_padding[8];

public:
    const SpecialPowerTemplate *m_specialPowerTemplate;
};

class Module
{
public:
    virtual ~Module();

protected:
    const SpecialPowerModuleData *m_moduleData;
    Object *m_object;
};

class BehaviorModuleInterface
{
public:
    virtual void behaviorModuleAnchor();
};

class BehaviorModule : public Module, public BehaviorModuleInterface
{
protected:
    virtual ~BehaviorModule() {}

public:
    virtual void behaviorAnchor();
};

class SpecialPowerModuleInterface
{
public:
    virtual AsciiString getPowerName() const = 0;
};

class InGameUI
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
    virtual void slot0a();
    virtual void slot0b();
    virtual void slot0c();
    virtual void slot0d();
    virtual void slot0e();
    virtual void slot0f();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot1a();
    virtual void slot1b();
    virtual void slot1c();
    virtual void slot1d();
    virtual void slot1e();
    virtual void slot1f();
    virtual void slot20();
    virtual void slot21();
    virtual Bool removeSuperweapon(int, const AsciiString &, ObjectID, const SpecialPowerTemplate *);
};

extern InGameUI *TheInGameUI;

class SpecialPowerModule : public BehaviorModule,
    public SpecialPowerModuleInterface
{
public:
    AsciiString getPowerName() const
    {
        return getSpecialPowerModuleData()->m_specialPowerTemplate->getName();
    }

#ifdef SPECIAL_POWER_ALIAS
public:
#else
protected:
#endif
    virtual ~SpecialPowerModule();

private:
    const SpecialPowerModuleData *getSpecialPowerModuleData() const { return m_moduleData; }
    Object *getObject() const { return m_object; }
};

SpecialPowerModule::~SpecialPowerModule()
{
    if (getSpecialPowerModuleData()->m_specialPowerTemplate->hasPublicTimer() == 1 &&
        getObject()->getControllingPlayer())
        TheInGameUI->removeSuperweapon(
            getObject()->getControllingPlayer()->getPlayerIndex(),
            getPowerName(),
            getObject()->getID(),
            getSpecialPowerModuleData()->m_specialPowerTemplate);
}
