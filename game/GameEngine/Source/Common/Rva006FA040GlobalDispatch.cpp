// Open-BFME: guarded global virtual dispatch reconstructed from retail RVA 0x006FA040.

class Rva006FA040Target
{
public:
#define RVA006FA040_SLOT(n) virtual void slot##n(void) = 0;
    RVA006FA040_SLOT(0)
    RVA006FA040_SLOT(1)
    RVA006FA040_SLOT(2)
    RVA006FA040_SLOT(3)
    RVA006FA040_SLOT(4)
    RVA006FA040_SLOT(5)
    RVA006FA040_SLOT(6)
    RVA006FA040_SLOT(7)
    RVA006FA040_SLOT(8)
    RVA006FA040_SLOT(9)
    RVA006FA040_SLOT(10)
#undef RVA006FA040_SLOT
    virtual void invoke(int value) = 0;
    virtual void invokeAlternate(int value) = 0;
};

// Retail's global at 0x012F64BC is TheParticleSystemManager, proven by the DIR32
// of updateSubObjectsFromShroud and the initSubsystem<ParticleSystemManager>
// registration site that pushes its address. Only the pointer's decorated name
// matters here, so the class is forward declared by that defining name rather
// than pulled in: the manifest stub in System/game_engine_subsystems.h derives
// from SubsystemInterface and declares none of the slots these two bodies
// dispatch through, so it cannot spell the calls. The vtable shape stays
// described by Rva006FA040Target below, which is exactly the shape that was
// already proven against retail's bytes (+0x2C and +0x30).
class ParticleSystemManager;

extern ParticleSystemManager *TheParticleSystemManager;

void Rva006FA040Invoke(int value)
{
    if (TheParticleSystemManager != 0)
    {
        reinterpret_cast<Rva006FA040Target *>(TheParticleSystemManager)->invoke(value);
    }
}

void Rva006FA0A0Invoke(int value)
{
    if (TheParticleSystemManager != 0)
    {
        reinterpret_cast<Rva006FA040Target *>(TheParticleSystemManager)->invokeAlternate(value);
    }
}
