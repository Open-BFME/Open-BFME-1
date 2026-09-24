// ?Update@Rva0061DF60@@QAEXXZ
// partial score=0.221719457 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc /I Code/Libraries/Source/WWVegas/WWLib /I Code/Libraries/Source/WWVegas/WWMath /I Code/Libraries/Source/WWVegas/WWDebug /I Code/Libraries/Source/WWVegas/WWSaveLoad /I Code/Libraries/Source/WWVegas/WW3D2 /I Code/Libraries/Include

#include "rendobj.h"

class Rva0061DF60
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7(Vector3 position);
    void Update();

private:
    char _pad04[4];
    RenderObjClass *m_primary;
    char _pad0c[0x38];
    int m_mode;
    char _pad48[4];
    bool m_enabled;
    char _pad4d[3];
    Vector3 m_from;
    Vector3 m_to;
    float m_amount;
};

void Rva0061DF60::Update()
{
    if (m_enabled && m_mode != 0) {
        RenderObjClass *primary = m_primary;
        primary->Validate_Transform();

        Vector3 position;
        primary = m_primary;
        if (primary != 0) {
            Matrix3D transform(primary->Get_Transform());
            position = transform.Get_Translation();
        }

        Vector3 delta(m_to);
        delta -= m_from;
        if (m_mode == 1) {
            delta *= m_amount;
        } else if (m_mode == 2) {
            delta *= -m_amount;
        }

        slot7(position + delta);
    }
}
