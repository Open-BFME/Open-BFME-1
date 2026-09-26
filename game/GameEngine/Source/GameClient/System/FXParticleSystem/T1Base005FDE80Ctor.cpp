// Native constructor at RVA 0x005FDE80, 196 bytes.
// The matched T1Derived_005E2FA0 constructor names this address-derived base.
// The independently matched copy constructor at 0x005EC640 installs the same
// intermediate tables (0x01113120/1C/18) and final tables (0x011130FC/F8/F4/E0).
// The three-interface head is 0x1C bytes; DefaultPhysicsModuleInfo is the
// fourth base. Native base destructors supply retail's constructor cleanup.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/GameEngine/Source/GameClient/System /Igame/GameEngine/Source/GameClient/System/FXParticleSystem /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Source/Common /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath

#include "FXParticleSystem/fx_particle_system.h"

// Same assignment body as game_client_random_variable.cpp, visible inline
// here because retail inlines its three-dword aggregate copy.
inline GameClientRandomVariable &GameClientRandomVariable::operator=(
    const GameClientRandomVariable &that)
{
    struct Raw {
        unsigned int distribution;
        float minimum;
        float maximum;
    };
    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

class T1A1_005DD290 {
public:
    T1A1_005DD290(void *first, void *second);
    virtual void primarySlot();
    virtual ~T1A1_005DD290();
private:
    unsigned int m_storage[4];
};

class T1Vt0111082C {
public:
    virtual void unusedVirtual();
};
class T1Vt0110F9E4 {
public:
    virtual void unusedVirtual();
};

class T1Intermediate_005FDE80
    : public T1A1_005DD290,
      public T1Vt0111082C,
      public T1Vt0110F9E4 {
public:
    T1Intermediate_005FDE80(void *first, void *second)
        : T1A1_005DD290(first, second) {}
    virtual ~T1Intermediate_005FDE80();
};

struct T1Float3_005FDE80 {
    float x, y, z;
};
struct T1SourceImage_005FDE80 {
    unsigned char prefix[0x0C];
    T1Float3_005FDE80 values;
    int field3;
    GameClientRandomVariable variable;
};

class T1Base_005FDE80
    : public T1Intermediate_005FDE80,
      public FXParticleSystem::DefaultPhysicsModuleInfo {
public:
    T1Base_005FDE80(void *first, void *source);
    virtual ~T1Base_005FDE80();
};

T1Base_005FDE80::T1Base_005FDE80(void *first, void *source)
    : T1Intermediate_005FDE80(first, source)
    , FXParticleSystem::DefaultPhysicsModuleInfo()
{
    const T1SourceImage_005FDE80 *image =
        (const T1SourceImage_005FDE80 *)source;
    m_field3 = image->field3;
    *(T1Float3_005FDE80 *)&m_field0 = image->values;
    m_var1 = image->variable;
}
