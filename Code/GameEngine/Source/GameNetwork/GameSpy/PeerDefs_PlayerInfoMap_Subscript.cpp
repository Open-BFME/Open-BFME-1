// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
// PlayerInfoMap::operator[], RVA 0x006359C0, 288 bytes.
// Identity: matched GameSpyInfo::updatePlayerInfo at0x00636C60 calls
// ILT0x151E0 ->0x6359C0 using its PlayerInfoMap. The hinted insertion is
// independently matched at0x634650 for the same PlayerInfo instantiation.
#define _STLP_NO_EXCEPTIONS 1
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
// The retail body directly constructs PlayerInfo(). Disable the old builtin
// value-initialization workaround for this TU before parsing map.
#include <utility>
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(T) T()
#include <map>
#include "StringInline.h"
class PlayerInfo {
public:
    PlayerInfo();
    PlayerInfo(const PlayerInfo &);
    ~PlayerInfo();
private:
    char fields[52];
};
struct AsciiComparator {
    bool operator()(AsciiString a, AsciiString b) const;
};
typedef _STL::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;
template PlayerInfo& PlayerInfoMap::operator[](const AsciiString&);
