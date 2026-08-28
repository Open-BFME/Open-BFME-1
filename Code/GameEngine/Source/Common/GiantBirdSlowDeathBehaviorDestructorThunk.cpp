// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the retail destructor to clean C++.

class Gen_dtor_000b33c0
{
public:
    virtual ~Gen_dtor_000b33c0();

private:
    unsigned char m_data[0x6c];
};

class SlowDeathBehaviorPrimary
{
public:
    virtual void slowDeathBehaviorPrimaryAnchor();

private:
    unsigned char m_data[8];
};

class SlowDeathBehaviorSecondary
{
public:
    virtual void slowDeathBehaviorSecondaryAnchor();
};

class SlowDeathBehaviorTertiary
{
public:
    virtual void slowDeathBehaviorTertiaryAnchor();

private:
    unsigned char m_data[0xc];
};

class SlowDeathBehaviorDieInterface
{
public:
    virtual void slowDeathBehaviorDieAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlowDeathBehavior.h
class SlowDeathBehaviorInterface
{
public:
    virtual void slowDeathBehaviorAnchor();
};

class Gen_dtor_00207da0 : public SlowDeathBehaviorPrimary,
    public SlowDeathBehaviorSecondary,
    public SlowDeathBehaviorTertiary,
    public SlowDeathBehaviorDieInterface,
    public SlowDeathBehaviorInterface
{
public:
    virtual ~Gen_dtor_00207da0();

private:
    unsigned char m_data[0x28];
};

class GiantBirdSlowDeathBehavior : public Gen_dtor_00207da0
{
public:
    virtual ~GiantBirdSlowDeathBehavior();

private:
    unsigned int m_acceleratedTimeScale;
    Gen_dtor_000b33c0 m_deathSound;
    unsigned char m_pad[0xc];
    unsigned int m_unknownD0;
    unsigned char m_unknownD4;
};

// ??1GiantBirdSlowDeathBehavior@@UAE@XZ
GiantBirdSlowDeathBehavior::~GiantBirdSlowDeathBehavior()
{
}
