// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME: LivingWorldRegion constructor, retail 0x003C9670, 255 bytes.
// The Region field table at 0x010EDC48 names the record and fixes its public
// fields. The adjacent destructor and the matched Gen_003C55F0 constructor
// prove the private vector, map, and owned-effect members.

#include <vector>

template <typename T>
class StringBase
{
    friend class AsciiString;

public:
    StringBase(void) : m_data(0) {}
    StringBase(const StringBase<T> &other); // retail 0x00887B60
    ~StringBase(void); // retail 0x00887940
    void clear(void); // retail 0x00887940

private:
    void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString(void) : StringBase<char>() {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString(void) {}

    void clear(void)
    {
        StringBase<char>::clear();
    }
};

struct Gen_p4pod
{
	int m_value;
};

struct Gen_p8pod
{
	int m_value[2];
};

class Gen_000231DC
{
public:
    Gen_000231DC(void); // retail ILT 0x000231DC

private:
    char m_body[0x2c];
};

class RegionObjectTree
{
public:
    RegionObjectTree(void); // retail 0x003BACB0
    ~RegionObjectTree(void); // retail 0x003BA740

private:
    char m_body[12];
};

class LivingWorldRegion
{
public:
	LivingWorldRegion(const AsciiString &name);

private:
    StringBase<char> m_regionObject; // +0x00
    AsciiString m_name; // +0x04
    int m_zOffset; // +0x08
    AsciiString m_regionBonusArmy; // +0x0c
    AsciiString m_regionBonusResource; // +0x10
    AsciiString m_regionBonusLegendary; // +0x14
	int m_smallArmyCommandPoints; // +0x18
	int m_mediumArmyCommandPoints; // +0x1c
	std::vector<Gen_p8pod> m_armyPlacementPos; // +0x20
	AsciiString m_conqueredEffectEvenglow; // +0x2c
	std::vector<Gen_p4pod *> m_effects; // +0x30
    Gen_000231DC *m_effectMap; // +0x3c
    RegionObjectTree m_regionObjects; // +0x40
	int m_regionPopupDefaultColor; // +0x4c
	int m_regionPopupOverColor; // +0x50
	AsciiString m_regionConqueredSound; // +0x54
};

// ??0LivingWorldRegion@@QAE@ABVAsciiString@@@Z
LivingWorldRegion::LivingWorldRegion(const AsciiString &name) :
    m_regionObject(),
    m_name(name),
    m_zOffset(0),
	m_smallArmyCommandPoints(20),
	m_mediumArmyCommandPoints(50),
    m_regionPopupDefaultColor(0xff2e9ce8),
    m_regionPopupOverColor(0xffff2117)
{
    register LivingWorldRegion *self = this;

    self->m_regionObject.clear();
    m_effects.clear();
    self->m_effectMap = new Gen_000231DC();
}
