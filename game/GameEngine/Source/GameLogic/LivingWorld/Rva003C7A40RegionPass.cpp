// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// INI LivingWorldRegionCampaign parser calls this pass on its 0x58-byte
// region container at RVA 0x003C7A40.
#include <vector>

class Rva003C5890Item;
class Rva003C5890Owner
{
public:
    void append(const Rva003C5890Item *item);
};
class Rva003C5820Key;
class Rva003C5820Output;
class Rva003C5820Owner
{
public:
    void appendMatch(Rva003C5820Output *output, Rva003C5820Key *key);
};

struct Rva003C7A40Region
{
    char m_pad00[0x30];
    std::vector<Rva003C5820Key *> m_keys;
    char m_pad3c[0xb0];
    Rva003C5820Output *m_output;
};

class Rva003C7A40Owner
{
public:
    void rva003C7A40();
private:
    char m_pad00[0x30];
    std::vector<Rva003C7A40Region *> m_regions;
    Rva003C5890Owner *m_collection;
};

void Rva003C7A40Owner::rva003C7A40()
{
    if (m_collection == 0)
        return;
    for (unsigned int i = 0; i < m_regions.size(); ++i)
        m_collection->append((const Rva003C5890Item *)m_regions[i]->m_output);
    for (unsigned int i = 0; i < m_regions.size(); ++i)
    {
        Rva003C7A40Region *region = m_regions[i];
        for (unsigned int j = 0; j <
            (unsigned int)(region->m_keys.end() - region->m_keys.begin()); ++j)
        {
            Rva003C5820Key **keys = region->m_keys.begin();
            ((Rva003C5820Owner *)m_collection)->appendMatch(
                region->m_output, (Rva003C5820Key *)&keys[j]);
        }
    }
}
