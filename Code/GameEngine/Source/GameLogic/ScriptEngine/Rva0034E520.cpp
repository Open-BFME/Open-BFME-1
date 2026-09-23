// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include <list>
#include <algorithm>

struct BFMEFindStringHeader
{
 int refCount;
 unsigned short length;
 unsigned short capacity;
 char data[1];
};

struct BFMEFindAsciiStringView
{
 BFMEFindStringHeader *m_data;

 int compare(const BFMEFindAsciiStringView &string) const
 {
  const BFMEFindAsciiStringView *self = this;
  const BFMEFindAsciiStringView *that = &string;
  int thatLen = that->m_data ? that->m_data->length : 0;
  const char *thatData = that->m_data ? &that->m_data->data[0] : (const char *)"";
  int thisLen = self->m_data ? self->m_data->length : 0;
  const char *thisData = self->m_data ? &self->m_data->data[0] : (const char *)"";
  int n = thisLen < thatLen ? thisLen : thatLen;
  int c = memcmp(thisData, thatData, n);
  if (c != 0)
   return c;
  return thisLen - thatLen;
 }
};

inline bool operator==(const BFMEFindAsciiStringView &a, const BFMEFindAsciiStringView &b)
{
 return a.compare(b) == 0;
}

// Retail 0x0034E520, 110 bytes. The owner name is unknown, so the class and
// method retain the address. The list root is at this+0x1726C. A node holds
// next and previous links, then an AsciiString-compatible value at +8.
// Retail calls the matched STLport __find at 0x00080110, conditionally unlinks
// its node, destroys the value at 0x0005EE90, and frees 12 bytes through
// STLport's matched node allocator at 0x0082E5F0.
class BFMERetailAsciiString { public: ~BFMERetailAsciiString(); };

struct Rva0034E520Node
{
    Rva0034E520Node *next;
    Rva0034E520Node *prev;
    BFMEFindAsciiStringView value;
};

class Rva0034E520
{
public:
    bool m(const BFMEFindAsciiStringView &key, bool remove);
    char pad_00[0x1726c];
    std::list<BFMEFindAsciiStringView> m_1726c;
};

bool Rva0034E520::m(const BFMEFindAsciiStringView &key, bool remove)
{
    std::list<BFMEFindAsciiStringView>::const_iterator it =
        std::find(m_1726c.begin(), m_1726c.end(), key);
    if (it != m_1726c.end()) {
        if (remove) {
            Rva0034E520Node *node = *(Rva0034E520Node **)&it;
            Rva0034E520Node *next = node->next;
            Rva0034E520Node *prev = node->prev;
            prev->next = next;
            next->prev = prev;
            ((BFMERetailAsciiString *)&node->value)->~BFMERetailAsciiString();
            _STL::__node_alloc<true, 0>::deallocate(node, 12);
        }
        return true;
    }
    return false;
}
