// Retail 0x0061E080, vtable slot 5 in the four table variants that also
// share slot 6 at 0x0061E230. No declaration names the owner, so this local
// facade keeps the address in its class and method name. The receiver is
// reloaded from m_primary after Get_Transform(), as retail does.
// cl: /DNDEBUG /MD /EHsc /I game/Libraries/Source/WWVegas/WWLib /I game/Libraries/Source/WWVegas/WWMath /I game/Libraries/Source/WWVegas/WWDebug /I game/Libraries/Source/WWVegas/WWSaveLoad /I game/Libraries/Source/WWVegas/WW3D2 /I game/Libraries/Include
#include "rendobj.h"
#include "wwmath.h"

extern const float g_bfmeScaleBK; // pinned at retail VA 0x01075C70

class Rva0061E080Owner
{
public:
    void Rva0061E080();
private:
    unsigned char m_beforeReceivers[8];
    RenderObjClass *m_primary;
    RenderObjClass *m_secondary;
    unsigned char m_beforeScaleState[0x5c];
    unsigned char m_field6C;
    unsigned char m_gap6d[3];
    float m_field70;
    float m_field74;
    float m_field78;
};

void Rva0061E080Owner::Rva0061E080()
{
    RenderObjClass *primary = m_primary;
    if (primary == 0)
        return;
    if (m_field6C == 0)
        return;

    Matrix3D transform(primary->Get_Transform());
    float oldScale = m_primary->Get_ObjectScale();
    if (!(WWMath::Fabs(m_field74 - oldScale) > g_bfmeScaleBK))
        return;

    float newScale = oldScale + (m_field74 - m_field70) * m_field78;
    float factor = newScale / oldScale;
    transform.Scale(factor);
    m_primary->Set_ObjectScale(newScale);
    m_primary->Set_Transform(transform);
    if (m_secondary != 0)
    {
        m_secondary->Set_ObjectScale(newScale);
        m_secondary->Set_Transform(transform);
    }
}
