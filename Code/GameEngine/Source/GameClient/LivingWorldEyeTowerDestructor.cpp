// ??1LivingWorldEyeTower@@UAE@XZ
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <vector>

class BFMERetailAsciiString
{
public:
    ~BFMERetailAsciiString() { releaseBuffer(); }
    void releaseBuffer();
private:
    void *m_data;
};

struct TowerPair
{
    float first;
    float second;
};

class ParticleSystemHandle
{
public:
    void *m_system;
    ParticleSystemHandle *m_previous;
    ParticleSystemHandle *m_next;
};

class BfmeBaseVUQ
{
public:
    virtual ~BfmeBaseVUQ() { }
};

class LivingWorldEyeTower : public BfmeBaseVUQ
{
public:
    virtual ~LivingWorldEyeTower();

private:
    BFMERetailAsciiString m_name;
    BFMERetailAsciiString m_type;
    BFMERetailAsciiString m_source;
    BFMERetailAsciiString m_effect;
    ParticleSystemHandle m_particleSystem;
    unsigned char m_unmodelled20[0x1c];
    _STL::vector<TowerPair> m_points;
    unsigned char m_unmodelled48[0x2c];
};

// ??1LivingWorldEyeTower@@UAE@XZ
LivingWorldEyeTower::~LivingWorldEyeTower()
{
    m_name.releaseBuffer();
    m_type.releaseBuffer();
    m_source.releaseBuffer();
    m_effect.releaseBuffer();
    m_points.clear();
}
