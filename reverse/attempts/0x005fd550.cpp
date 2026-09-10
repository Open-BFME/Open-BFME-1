// ??0TerrainCollisionModule@FXParticleSystem@@QAE@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@PBVTerrainCollisionModuleTemplate@1@@Z
// partial score=0.78 date=2026-09-10
// cl: /DNDEBUG /MD /GX /O2 /Ob2

class BfmeListCU
{
};

class BfmeLinkCU
{
public:
    BfmeListCU *m_list;
    BfmeLinkCU *m_next;
    BfmeLinkCU *m_prev;
};

class BfmeHolderCU
{
public:
    BfmeHolderCU(BfmeListCU **list, void *user);
    virtual void unusedVirtual();

private:
    unsigned int m_storage[4];
};

class FXList;

class GameClientRandomVariable
{
public:
    float getValue() const;
    unsigned int m_storage[3];
};

__forceinline void copyRandom(const GameClientRandomVariable *source,
    GameClientRandomVariable *destination)
{
    destination->m_storage[0] = source->m_storage[0];
    destination->m_storage[1] = source->m_storage[1];
    destination->m_storage[2] = source->m_storage[2];
}

namespace FXParticleSystem
{

class ParticleSystem;

template <class T>
class TrackingPtr
{
};

class TerrainCollisionModuleTemplate;

class TerrainCollisionEventFXLookupShim
{
public:
    const FXList *lookup(const char *name) const;
};

extern "C" TerrainCollisionEventFXLookupShim *g_terrainCollisionEventFXListStore;

class __declspec(novtable) TerrainCollisionCategorySlice
{
public:
    __forceinline TerrainCollisionCategorySlice()
    {
        *(volatile unsigned int *)this = 0x01110830;
    }

    virtual void unusedVirtual();
};

class __declspec(novtable) TerrainCollisionFlagsSlice
{
public:
    __forceinline TerrainCollisionFlagsSlice()
    {
        *(volatile unsigned int *)this = 0x0107375c;
        bool one = true;
        *(volatile unsigned char *)((unsigned char *)this + 4) = one;
        *(volatile unsigned char *)((unsigned char *)this + 5) = one;
    }

    virtual void unusedVirtual();

private:
    bool m_flag0;
    bool m_flag1;
};

class Snapshot
{
public:
    virtual ~Snapshot();
};

class __declspec(novtable) TerrainCollisionModuleInfo : public Snapshot
{
public:
    TerrainCollisionModuleInfo();
    virtual ~TerrainCollisionModuleInfo();
    virtual void unusedVirtual();

private:
    unsigned int m_eventName;
    GameClientRandomVariable m_eventTime;
    bool m_flag;
    const FXList *m_cached;
};

class __declspec(novtable) TerrainCollisionParticleBase
    : public BfmeHolderCU,
      public TerrainCollisionCategorySlice,
      public TerrainCollisionFlagsSlice
{
public:
    __forceinline TerrainCollisionParticleBase(
        TrackingPtr<ParticleSystem> &system, const void *source)
        : BfmeHolderCU(reinterpret_cast<BfmeListCU **>(&system),
            const_cast<void *>(source)),
          TerrainCollisionCategorySlice(),
          TerrainCollisionFlagsSlice()
    {
        unsigned char *root = reinterpret_cast<unsigned char *>(this);
        *(volatile unsigned int *)root = 0x01113244;
        *(volatile unsigned int *)(root + 0x14) = 0x01113240;
        *(volatile unsigned int *)(root + 0x18) = 0x0111323c;
    }
};

class __declspec(novtable) TerrainCollisionModule
    : public TerrainCollisionParticleBase,
      public TerrainCollisionModuleInfo
{
public:
    TerrainCollisionModule(TrackingPtr<ParticleSystem> &system,
        const TerrainCollisionModuleTemplate *source);

private:
    int m_eventFrame;
    bool m_pending;
};

// ??0TerrainCollisionModule@FXParticleSystem@@QAE@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@PBVTerrainCollisionModuleTemplate@1@@Z
TerrainCollisionModule::TerrainCollisionModule(
    TrackingPtr<ParticleSystem> &system,
    const TerrainCollisionModuleTemplate *source)
    : TerrainCollisionParticleBase(system, source),
      TerrainCollisionModuleInfo()
{
    const unsigned char *sourceBytes =
        reinterpret_cast<const unsigned char *>(source);
    unsigned char *destination = reinterpret_cast<unsigned char *>(this);
    bool one = true;

    *(volatile unsigned int *)(destination + 0x20) = 0x011132a4;
    *(volatile unsigned int *)destination = 0x011132c0;
    *(volatile unsigned int *)(destination + 0x14) = 0x011132bc;
    *(volatile unsigned int *)(destination + 0x18) = 0x011132b8;

    GameClientRandomVariable *destinationRandom =
        reinterpret_cast<GameClientRandomVariable *>(destination + 0x28);
    const GameClientRandomVariable *sourceRandom =
        reinterpret_cast<const GameClientRandomVariable *>(sourceBytes + 0x14);
    copyRandom(sourceRandom, destinationRandom);

    const FXList **sourceCached = reinterpret_cast<const FXList **>(
        const_cast<unsigned char *>(sourceBytes) + 0x24);
    if (!*sourceCached)
    {
        const char *text = *reinterpret_cast<const char *const *>(
            sourceBytes + 0x10);
        *sourceCached = g_terrainCollisionEventFXListStore->lookup(
            text ? text + 8 : reinterpret_cast<const char *>(0x0107388b));
    }
    *reinterpret_cast<const FXList **>(destination + 0x38) = *sourceCached;

    destination[0x34] = sourceBytes[0x20];
    destination[0x1c] = sourceBytes[8];
    destination[0x1d] = sourceBytes[9];

    GameClientRandomVariable *eventTime =
        reinterpret_cast<GameClientRandomVariable *>(destination + 0x28);
    m_eventFrame = static_cast<int>(eventTime->getValue());
    m_pending = one;
}

}
