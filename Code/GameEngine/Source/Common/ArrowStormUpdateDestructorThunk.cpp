// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <list>

class ArrowStormUpdateRootBase
{
public:
    virtual ~ArrowStormUpdateRootBase();

private:
    unsigned char m_pad[8];
};

class ArrowStormUpdateBaseInterface1 { public: virtual void slot(); };
class ArrowStormUpdateBaseInterface2 { public: virtual void slot(); private: unsigned char m_pad[0xC]; };
class ArrowStormUpdateBaseInterface3 { public: virtual void slot(); };

class ArrowStormUpdateObjectModule : public ArrowStormUpdateRootBase
{
};

class ArrowStormUpdateBehaviorModule : public ArrowStormUpdateObjectModule,
    public ArrowStormUpdateBaseInterface1
{
public:
    virtual ~ArrowStormUpdateBehaviorModule() {}
};

class ArrowStormUpdateUpdateModule : public ArrowStormUpdateBehaviorModule,
    public ArrowStormUpdateBaseInterface2,
    public ArrowStormUpdateBaseInterface3
{
public:
    virtual ~ArrowStormUpdateUpdateModule() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdate : public ArrowStormUpdateUpdateModule
{
public:
    virtual ~SpecialAbilityUpdate();

private:
    unsigned char m_pad[0xC4];
};

class ArrowStormUpdate : public SpecialAbilityUpdate
{
public:
    virtual ~ArrowStormUpdate();

private:
    _STL::list<int> m_specialObjectIDList;
};

// ??1ArrowStormUpdate@@UAE@XZ
ArrowStormUpdate::~ArrowStormUpdate()
{
}
