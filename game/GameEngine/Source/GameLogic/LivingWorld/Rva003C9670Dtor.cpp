// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

template <typename T>
class StringBase
{
    friend class AsciiString;
    friend class Rva003C9670;

public:
    StringBase(void) : m_data(0) {}
    StringBase(const StringBase<T> &other);
    void clear(void);

private:
    ~StringBase(void);
    void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString(void) : StringBase<char>() {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString(void) {}
};

class Gen_003C55F0
{
public:
    ~Gen_003C55F0(void);
};

class RegionObjectTree
{
public:
    ~RegionObjectTree(void);

private:
    char m_body[12];
};

class LivingWorldRegion
{
public:
    virtual ~LivingWorldRegion(void);
};

struct Gen_p4pod
{
    int m_value;
};

struct Gen_p8pod
{
    int m_value[2];
};

class Rva003C9670
{
public:
    ~Rva003C9670(void);

private:
    StringBase<char> m_regionObject;
    AsciiString m_name;
    int m_zOffset;
    AsciiString m_regionBonusArmy;
    AsciiString m_regionBonusResource;
    AsciiString m_regionBonusLegendary;
    int m_smallArmyCommandPoints;
    int m_mediumArmyCommandPoints;
    std::vector<Gen_p8pod> m_armyPlacementPos;
    AsciiString m_string2C;
    std::vector<Gen_p4pod *> m_vector30;
    Gen_003C55F0 *m_effectMap;
    RegionObjectTree m_regionObjects;
    int m_regionPopupDefaultColor;
    int m_regionPopupOverColor;
    AsciiString m_regionConqueredSound;
};

// ??1Rva003C9670@@QAE@XZ
Rva003C9670::~Rva003C9670(void)
{
    unsigned int i = 0;
    if (i < m_vector30.size())
    {
        do
        {
            delete reinterpret_cast<LivingWorldRegion *>(m_vector30[i]);
            ++i;
        } while (i < m_vector30.size());
    }
    m_vector30.clear();
    if (m_effectMap)
        delete m_effectMap;
}
