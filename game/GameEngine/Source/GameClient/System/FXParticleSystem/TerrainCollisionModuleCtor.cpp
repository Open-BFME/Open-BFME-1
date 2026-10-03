// ??0TerrainCollisionModule@FXParticleSystem@@QAE@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@1@PBVTerrainCollisionModuleTemplate@1@@Z
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

// The store global: ?TheFXListStore@@3PAVFXListStore@@A @ 0x012F144C, defined in
// game/GameEngine/Source/GameClient/FXList.cpp. Forward declaration only; the
// lookup itself goes through the pinned thunk below.
class FXListStore;
extern FXListStore *TheFXListStore;

extern "C" const void *bfmeVftCategoryModuleInfo8[];
#pragma comment(linker, "/alternatename:_bfmeVftCategoryModuleInfo8=??_7?$CategoryModuleInfo@$07@FXParticleSystem@@6B@")

class GameClientRandomVariable
{
public:
    float getValue() const;
    unsigned int m_storage[3];
};

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



class TerrainCollisionCategorySlice
{
public:
    virtual void unusedVirtual();
    virtual __declspec(nothrow) ~TerrainCollisionCategorySlice() {}
};

class TerrainCollisionFlagsSlice
{
public:
    TerrainCollisionFlagsSlice()
    {
        *(volatile unsigned int *)this = (unsigned int)bfmeVftCategoryModuleInfo8;
        bool one = true;
        *(volatile unsigned char *)((unsigned char *)this + 4) = one;
        *(volatile unsigned char *)((unsigned char *)this + 5) = one;
    }
    virtual void unusedVirtual();
    virtual __declspec(nothrow) ~TerrainCollisionFlagsSlice() {}

private:
    bool m_flag0;
    bool m_flag1;
};

class Snapshot
{
public:
    virtual ~Snapshot();
};

class TerrainCollisionModuleInfo : public Snapshot
{
public:
    TerrainCollisionModuleInfo();
    virtual ~TerrainCollisionModuleInfo();
    virtual void unusedVirtual();

protected:
    unsigned int m_eventName;
    GameClientRandomVariable m_eventTime;
    unsigned char m_flag;
    const FXList *m_cached;
};

struct TerrainCollisionModuleTemplateImage
{
    unsigned char m_prefix[0x10];
    const char *m_eventName;
    GameClientRandomVariable m_eventTime;
    unsigned char m_flag;
    unsigned char m_padding[3];
    const FXList *m_cached;
};

class TerrainCollisionParticleBase
    : public BfmeHolderCU,
      public TerrainCollisionCategorySlice,
      public TerrainCollisionFlagsSlice
{
public:
    __forceinline TerrainCollisionParticleBase(
        TrackingPtr<ParticleSystem> &system, const void *source)
        : BfmeHolderCU(reinterpret_cast<BfmeListCU **>(&system),
            const_cast<void *>(source))
    {
    }
};

class TerrainCollisionModule
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

// ??0TerrainCollisionModule@FXParticleSystem@@QAE@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@1@PBVTerrainCollisionModuleTemplate@1@@Z
TerrainCollisionModule::TerrainCollisionModule(
    TrackingPtr<ParticleSystem> &system,
    const TerrainCollisionModuleTemplate *source)
    : TerrainCollisionParticleBase(system, source),
      TerrainCollisionModuleInfo()
{
    const TerrainCollisionModuleTemplateImage *sourceImage =
        reinterpret_cast<const TerrainCollisionModuleTemplateImage *>(source);
    TerrainCollisionModuleTemplateImage *mutableSourceImage =
        const_cast<TerrainCollisionModuleTemplateImage *>(sourceImage);

    m_eventTime = sourceImage->m_eventTime;

    if (!sourceImage->m_cached)
    {
        const char *text = sourceImage->m_eventName;
        // The lookup body is the pinned thunk ?lookup@TerrainCollisionEventFXLookupShim
        // @FXParticleSystem@@QBEPBVFXList@@PBD@Z (0x0001669E); only the store global
        // itself carries the defining name.
        mutableSourceImage->m_cached =
            reinterpret_cast<TerrainCollisionEventFXLookupShim *>(TheFXListStore)->lookup(
            text ? text + 8 : "");
    }
    m_cached = sourceImage->m_cached;

    m_flag = sourceImage->m_flag;
    reinterpret_cast<unsigned char *>(this)[0x1c] =
        sourceImage->m_prefix[8];
    reinterpret_cast<unsigned char *>(this)[0x1d] =
        sourceImage->m_prefix[9];

    m_eventFrame = static_cast<int>(m_eventTime.getValue());
    m_pending = true;
}

}
