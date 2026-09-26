// Retail 0x00211890, 74 bytes. The caller's damage source ID selects an
// Object, whose three float fields at +0x14/+0x24/+0x34 are copied to a
// local point before forwarding it. The second caller of the same destination
// proves a float plus three-float-pointer thiscall ABI. The original owner
// name remains unknown, so both methods retain address-derived identities.
struct Rva00211890DamageInfo
{
    unsigned char m_beforeSourceID[8];
    int m_sourceID;
};

struct Rva00211890ObjectView
{
    unsigned char m_before14[0x14]; float m_field14;
    unsigned char m_before24[0x0c]; float m_field24;
    unsigned char m_before34[0x0c]; float m_field34;
};

struct Rva00211890Coord
{
    float x, y, z;
};

class Object;
class GameLogic
{
public:
    Object *findObjectByID(int id);
};
extern GameLogic *TheBfmeGameLogic;

class Rva00211890Owner
{
public:
    void forwardSourcePosition(float amount, Rva00211890DamageInfo *damage);
    void applyAt(float amount, const Rva00211890Coord *point);
};

void Rva00211890Owner::forwardSourcePosition(
    float amount, Rva00211890DamageInfo *damage)
{
    Rva00211890ObjectView *source = reinterpret_cast<Rva00211890ObjectView *>(
        TheBfmeGameLogic->findObjectByID(damage->m_sourceID));
    if (source != 0)
    {
        Rva00211890Coord point;
        point.x = source->m_field14;
        point.y = source->m_field24;
        point.z = source->m_field34;
        applyAt(amount, &point);
    }
}
