// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <hash_map>

class SubsystemInterface
{
public:
    SubsystemInterface();
    virtual ~SubsystemInterface();
    virtual void init() = 0;
    virtual bool loadIniFilesFromLegend();
    virtual void reset() = 0;
    virtual void update() = 0;

private:
    void *m_name;
};

// The store's 44-byte nodes contain a link, a key and this 36-byte value.
// Its fields are opaque here because only the container's lifetime is used.
class FXList
{
public:
    virtual ~FXList();

private:
    unsigned char m_opaque[32];
};

class FXListStore : public SubsystemInterface
{
public:
    FXListStore();
    virtual ~FXListStore();
    virtual void init();
    virtual void reset();
    virtual void update();

private:
    _STL::hash_map<int, FXList> m_fxmap;
};

FXListStore::FXListStore()
{
}

FXListStore::~FXListStore()
{
    m_fxmap.clear();
}
