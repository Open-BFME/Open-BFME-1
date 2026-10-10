// ??1LivingWorldEyeTower@@UAE@XZ
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <vector>

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

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
    AsciiString m_name;
    AsciiString m_type;
    AsciiString m_source;
    AsciiString m_effect;
    ParticleSystemHandle m_particleSystem;
    unsigned char m_unmodelled20[0x1c];
    _STL::vector<TowerPair> m_points;
    unsigned char m_unmodelled48[0x2c];
};

// ??1LivingWorldEyeTower@@UAE@XZ
LivingWorldEyeTower::~LivingWorldEyeTower()
{
    m_name.StringBase<char>::clear();
    m_type.StringBase<char>::clear();
    m_source.StringBase<char>::clear();
    m_effect.StringBase<char>::clear();
    m_points.clear();
}
