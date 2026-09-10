// ?finish@Rva0006AB90FunctionCurve@@QAEXXZ
// Final-key emission for the Function curve accumulator.
// cl: /Ireference/shims/iniexception /DNDEBUG /DWIN32 /MD /EHsc

#include "Common/INIException.h"

typedef int Int;

struct Rva0006AB10CurvePoint
{
    float time;
    float value;
    unsigned char reserved[8];
};

class Rva0006AB10Curve
{
public:
    void set(float time, float value, Int inTangent, Int outTangent);
    __forceinline int size() const { return m_end - m_begin; }

    unsigned char m_reserved[8];
    Rva0006AB10CurvePoint *m_begin;
    Rva0006AB10CurvePoint *m_end;
};

class Rva0006AB90FunctionCurve
{
public:
    void finish();

private:
    Rva0006AB10Curve *m_curve;
    bool m_firstKey;
    float m_lastTime;
    float m_lastValue;
    union Tangent
    {
        float value;
        Int bits;
    } m_inTangent, m_outTangent;
    bool m_haveInTangent;
    bool m_haveOutTangent;
};

void Rva0006AB90FunctionCurve::finish()
{
    if (m_firstKey)
        throw INIException(3, "Function curve does not have any keyframes");

    if (!m_curve->size())
    {
        if (!m_haveInTangent)
            m_inTangent.value = m_haveOutTangent
                ? m_outTangent.value : *(const float *)0x01075350;
    }
    else
    {
        Rva0006AB10CurvePoint *previous = m_curve->m_end - 1;
        if (!m_haveInTangent)
            m_inTangent.value = (m_lastValue - previous->value) /
                (m_lastTime - previous->time);
    }

    if (!m_haveOutTangent)
        m_outTangent.value = m_inTangent.value;

    m_curve->set(m_lastTime, m_lastValue,
        m_inTangent.bits, m_outTangent.bits);
}
