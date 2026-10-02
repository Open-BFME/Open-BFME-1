// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// RVA 0x003CA480: vtable 0x010EE010 matches the constructor at 0x003C8880.
#include <vector>

void j_00018a2f();

class Gen_dtor_003c9b30
{
public:
    virtual ~Gen_dtor_003c9b30();
};

class BfmeBaseVUQ
{
public:
    virtual ~BfmeBaseVUQ() {}
};

class LivingWorldRegionManager : public BfmeBaseVUQ
{
public:
    virtual ~LivingWorldRegionManager();
private:
    char m_pad04[0x10];
    std::vector<void *> m_pending14;
    int m_20;
    int m_24;
    std::vector<Gen_dtor_003c9b30 *> m_campaigns28;
};

LivingWorldRegionManager::~LivingWorldRegionManager()
{
	typedef void (Gen_dtor_003c9b30::*DestructorCall)();
	union { void (*raw)(void); DestructorCall member; } destructorCall;
	destructorCall.raw = j_00018a2f;

    for (unsigned int i = 0; i < m_campaigns28.size(); ++i) {
        Gen_dtor_003c9b30 *campaign = m_campaigns28[i];
        if (campaign) {
            (campaign->*destructorCall.member)();
            ::operator delete(campaign);
        }
    }
    m_campaigns28.clear();
}
