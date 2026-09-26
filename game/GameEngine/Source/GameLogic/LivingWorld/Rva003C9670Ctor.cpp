// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME: constructor of the 0x58-byte object the "LivingWorldRegionCampaign"
// INI block builds (retail 0x003C9670, 255 bytes). Its only caller, the block
// parser 0x003C9B60, allocates 0x58 bytes, runs this constructor and fills the
// result from the field table at 0x010EDC48, which fixes the public field
// offsets. Entry #0 of that table ("Region", parser 0x003C9980) allocates
// 0xF4-byte objects (constructor 0x0061AF80, vtable 0x01117258) and appends
// them to this object's +0x30 vector, so this is the region container, not a
// region. The class name stays address-derived: no string, vtable or caller
// names it.

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

class Rva003C9670
{
public:
	Rva003C9670(const AsciiString &name);

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
	AsciiString m_string2C; // +0x2c
	std::vector<Gen_p4pod *> m_vector30; // +0x30: the 0xF4-byte objects parser 0x003C9980 appends
    Gen_000231DC *m_effectMap; // +0x3c
    RegionObjectTree m_regionObjects; // +0x40
	int m_regionPopupDefaultColor; // +0x4c
	int m_regionPopupOverColor; // +0x50
	AsciiString m_regionConqueredSound; // +0x54
};

// ??0Rva003C9670@@QAE@ABVAsciiString@@@Z
Rva003C9670::Rva003C9670(const AsciiString &name) :
    m_regionObject(),
    m_name(name),
    m_zOffset(0),
	m_smallArmyCommandPoints(20),
	m_mediumArmyCommandPoints(50),
    m_regionPopupDefaultColor(0xff2e9ce8),
    m_regionPopupOverColor(0xffff2117)
{
    register Rva003C9670 *self = this;

    self->m_regionObject.clear();
    m_vector30.clear();
    self->m_effectMap = new Gen_000231DC();
}
