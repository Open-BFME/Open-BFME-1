// cl: /DNDEBUG /MD /EHsc
extern "C" void *__cdecl memset(void *, int, unsigned int);

// DieMux field metadata establishes these roles; the original owner spelling is unknown.
class Rva002551A0DieMuxData
{
public:
    Rva002551A0DieMuxData();
private:
    int m_deathTypes;
    int m_veterancyLevels;
    int m_exemptStatus[3];
    int m_requiredStatus[3];
    float m_damageAmountRequired;
    float m_minKillerAngle;
    float m_maxKillerAngle;
};

Rva002551A0DieMuxData::Rva002551A0DieMuxData()
{
    m_deathTypes = -1;
    m_veterancyLevels = -1;
    memset(m_exemptStatus, 0, 0xc);
    memset(m_requiredStatus, 0, 0xc);
    m_damageAmountRequired = -1.0f;
    m_minKillerAngle = 1.0f;
    m_maxKillerAngle = -1.0f;
}
