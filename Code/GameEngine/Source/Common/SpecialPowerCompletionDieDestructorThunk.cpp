// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the SpecialPowerCompletionDie notification body to C++.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
    AsciiString(const AsciiString &);
    ~AsciiString();

private:
    unsigned char m_data[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate
{
public:
    AsciiString getName() const;
};

class Object;

class Owner
{
public:
    unsigned char m_unreconstructed_00[0x34];
    SpecialPowerTemplate *m_specialPowerTemplate;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
    unsigned char m_unreconstructed_00[0x24];
    int m_playerIndex;

    int getPlayerIndex() const { return m_playerIndex; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
    Player *getControllingPlayer() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
    virtual void objectModuleAnchor();

protected:
    Owner *m_owner;
    Object *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
    virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleInterface
{
public:
    virtual void dieModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModule : public ObjectModule,
    public BehaviorModuleInterface,
    public DieModuleInterface
{
protected:
    unsigned int m_creatorID;
    bool m_creatorSet;

    Owner *getSpecialPowerCompletionDieModuleData() const
    {
        return m_owner;
    }

    Object *getObject() const
    {
        return m_object;
    }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
    virtual void unused00();
    virtual void unused01();
    virtual void unused02();
    virtual void unused03();
    virtual void unused04();
    virtual void unused05();
    virtual void unused06();
    virtual void unused07();
    virtual void unused08();
    virtual void unused09();
    virtual void unused10();
    virtual void unused11();
    virtual void unused12();
    virtual void unused13();
    virtual void unused14();
    virtual void unused15();
    virtual void unused16();
    virtual void unused17();
    virtual void unused18();
    virtual void unused19();
    virtual void unused20();
    virtual void unused21();
    virtual void unused22();
    virtual void unused23();
    virtual void unused24();
    virtual void unused25();
    virtual void unused26();
    virtual void unused27();
    virtual void unused28();
    virtual void unused29();
    virtual void unused30();
    virtual void unused31();
    virtual void unused32();
    virtual void unused33();
    virtual void unused34();
    virtual void unused35();
    virtual void unused36();
    virtual void notifyOfCompletedSpecialPower(
        int playerIndex, const AsciiString &completedPower,
        unsigned int creatorID);
};

extern ScriptEngine *TheScriptEngine;

class __declspec(novtable) SpecialPowerCompletionDie : public DieModule
{
public:
    virtual ~SpecialPowerCompletionDie();
};

// ??1SpecialPowerCompletionDie@@UAE@XZ
SpecialPowerCompletionDie::~SpecialPowerCompletionDie()
{
    if (m_creatorID != 0)
    {
        TheScriptEngine->notifyOfCompletedSpecialPower(
            getObject()->getControllingPlayer()->getPlayerIndex(),
            getSpecialPowerCompletionDieModuleData()->m_specialPowerTemplate->getName(),
            m_creatorID);
    }
}
