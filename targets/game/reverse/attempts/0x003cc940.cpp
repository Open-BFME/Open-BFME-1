// ?method@Rva003CC940@@QAE?AURva003CC940Point@@XZ
// partial score=0.7483 date=2026-10-09
// Opaque layout and ABI evidence: targets/game/reverse/identity_evidence/003cc940-position-retry.md
struct Rva003CC940Point {
    float m_at00, m_at04, m_at08;
    // ??0Rva003CC940Point@@QAE@XZ absent-from-retail
    Rva003CC940Point() {}
    // ??0Rva003CC940Point@@QAE@ABU0@@Z absent-from-retail
    Rva003CC940Point(const Rva003CC940Point &other)
        : m_at00(other.m_at00), m_at04(other.m_at04), m_at08(other.m_at08) {}
};
class TerrainLogic;
struct Coord3D;
struct Rva003CC940Terrain {
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0C(); virtual void slot10(); virtual void slot14();
    virtual float slot18(float, float, Coord3D *) const;
};
extern TerrainLogic *TheTerrainLogic;
struct Rva003CC940Config { char m_at00[0xc]; float m_at0c; };
struct Rva003CC940Node { char m_at00[0x30]; int m_at30; };
class Rva003CC940 {
public:
    Rva003CC940Point method();
    float m_at00, m_at04;
    Rva003CC940Config *m_at08;
    char m_at0c[4];
    Rva003CC940Node *m_at10[8];
};

Rva003CC940Point Rva003CC940::method()
{
    Rva003CC940Point point;
    point.m_at00 = m_at00;
    point.m_at04 = m_at04;
    float scale = m_at08->m_at0c * (1.0f / 3.0f);
    float xOffset = 0.0f, xWeight = 0.0f;
    float yWeight = 0.0f, yOffset = 0.0f;
    if (m_at10[0]) { xOffset = (float)m_at10[0]->m_at30; xWeight = (float)m_at10[0]->m_at30; }
    if (m_at10[1]) { xWeight += (float)m_at10[1]->m_at30; xOffset -= (float)m_at10[1]->m_at30; }
    if (m_at10[2]) { yWeight = (float)m_at10[2]->m_at30; yOffset = (float)m_at10[2]->m_at30; }
    if (m_at10[3]) { float n = (float)m_at10[3]->m_at30; yWeight += n; yOffset -= n; }
    if (m_at10[4]) {
        float n = (float)(m_at10[4]->m_at30 * 0.7071067811865476);
        xWeight += n; xOffset += n; yWeight += n; yOffset += n;
    }
    if (m_at10[5]) {
        float n = (float)(m_at10[5]->m_at30 * 0.7071067811865476);
        xWeight += n; xOffset += n; yWeight += n; yOffset -= n;
    }
    if (m_at10[6]) {
        float n = (float)(m_at10[6]->m_at30 * 0.7071067811865476);
        xWeight += n; xOffset -= n; yWeight += n; yOffset += n;
    }
    if (m_at10[7]) {
        float n = (float)(m_at10[7]->m_at30 * 0.7071067811865476);
        xWeight += n; xOffset -= n; yWeight += n; yOffset -= n;
    }
    if (xWeight != 0.0f) point.m_at00 += xOffset / xWeight * scale;
    if (yWeight != 0.0f) point.m_at04 += yOffset / yWeight * scale;
    point.m_at08 = ((Rva003CC940Terrain *)TheTerrainLogic)->slot18(point.m_at00, point.m_at04, 0);
    return point;
}
