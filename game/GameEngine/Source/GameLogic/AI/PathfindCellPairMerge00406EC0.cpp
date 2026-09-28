// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <map>

// Retail RVA 0x00406EC0 (283 bytes), called by the zone workers at
// 0x00407030 and 0x004085F0 with the manager in ECX and two cell pointers.
// The method sorts the cell zone IDs, then inserts their packed properties
// into the map at manager+0x235FC only when the pair is absent.
// Semantic method identity is unproved; all adapter types retain the RVA.
// Cell zone +0xA, properties +0xC, and 32-byte mapped value are witnessed
// by this body and map::operator[] at 0x00406C50. No shared layout is changed.
// find returns a nontrivially copied one-pointer STLport iterator through a
// hidden output argument. ILT 0x369BC -> 0x404A70; ILT 0xE5A2 -> 0x406C50.


struct Cell00406EC0
{
    char pad[10];
    unsigned short zone;
    unsigned type : 3;
    unsigned unused03 : 3;
    unsigned bits06 : 6;
    unsigned bits12 : 6;
    unsigned unused18 : 2;
    unsigned bit20 : 1;
    unsigned bit21 : 1;
    unsigned bits22 : 2;
};

struct PairValue00406EC0
{
    struct Item
    {
        unsigned short type;
        int bits06, bits12;
        bool bit20, bit21;
        unsigned short bits22;
    } item[2];
};

// Existing native ABI views from BfmePackedUshortMapFind4063C0.cpp and
// Rva00406C50MapIndex.cpp. Both mapped values occupy 0x20 bytes.
struct BfmePackedMapVal20 { char m_bytes[0x20]; };
struct Rva00406C50Key { unsigned int m_v; };
struct Rva00406C50Value { unsigned int m_data[8]; };
namespace _STL
{
    template <> struct less<Rva00406C50Key>
    {
        bool operator()(const Rva00406C50Key &a, const Rva00406C50Key &b) const
        {
            return a.m_v < b.m_v;
        }
    };
}
typedef _STL::map<unsigned, BfmePackedMapVal20> Map00406EC0;
typedef _STL::map<Rva00406C50Key, Rva00406C50Value> IndexMap00406EC0;

class PairMerge00406EC0
{
public:
    void merge(const Cell00406EC0 *a, const Cell00406EC0 *b);
private:
    char pad[0x235fc];
    Map00406EC0 map;
};

void PairMerge00406EC0::merge(const Cell00406EC0 *a, const Cell00406EC0 *b)
{
    unsigned short za = a->zone, zb = b->zone;
    if (za == zb)
        return;
    if (za > zb)
    {
        unsigned short t = za;
        za = zb;
        zb = t;
        const Cell00406EC0 *p = a;
        a = b;
        b = p;
    }
    unsigned key = (unsigned(za) << 16) | zb;
    Map00406EC0::iterator it = map.find(key);
    if (it == map.end())
    {
        PairValue00406EC0 value;
        value.item[0].type = a->type;
        value.item[0].bits06 = a->bits06;
        value.item[0].bits12 = a->bits12;
        value.item[0].bit20 = a->bit20;
        value.item[0].bit21 = a->bit21;
        value.item[0].bits22 = a->bits22;
        value.item[1].type = b->type;
        value.item[1].bits06 = b->bits06;
        value.item[1].bits12 = b->bits12;
        value.item[1].bit20 = b->bit20;
        value.item[1].bit21 = b->bit21;
        value.item[1].bits22 = b->bits22;
        // Use the independently recovered index callee's native type identity.
        *(PairValue00406EC0 *)&(*(IndexMap00406EC0 *)&map)[*(Rva00406C50Key *)&key] = value;
    }
}
