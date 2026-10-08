// ?rva000D1E30@Player@@QAEXABVAsciiString@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob1 /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source
// stlport
// Retail RVA000D1E30 / 830 bytes; member-thiscall and RET4.
// Player ownership: its call to Player::findSkirmishSide and witnessed
// Player+0x24 m_playerIndex; native initFromDict at000DB020 calls via00006BE5.
// Keep the banked caller's rva000D1E30 name: ZH Player.cpp has related
// script/team-copy statements inline, but no proven matching helper name.
// Side arrays are 24-byte records at SidesList+2C/+330 with counts at28/32C.
// Team owners at630/64C contain STLport vectors at+C; each16-byte node has
// next at0 and Dict at+C. Rva0019BA40TeamRecAppend.cpp independently uses
// that vector layout. Using a raw three-pointer surrogate changes codegen.
// Visible compare body proves its nonthrowing operations to MSVC: retail
// calls it through000220C5 without adding an EH state for its argument.
#define __PLACEMENT_VEC_NEW_INLINE
#include "ascii_string.h"
#include "unicode_string.h"
#define ASCIISTRING_H
#define UNICODESTRING_H
#include "Lib/BaseType.h"
#include "Common/Debug.h"
#include "Common/Dict.h"
#include <vector>

template <> inline int StringBase<char>::compare(const StringBase<char> &str) const {
    int otherLength = str.m_data ? str.m_data->length : 0;
    const char *otherData = str.m_data ? str.m_data->data : (const char *)"";
    int length = m_data ? m_data->length : 0;
    const char *data = m_data ? m_data->data : (const char *)"";
    int result = memcmp(data, otherData, length < otherLength ? length : otherLength);
    return result ? result : length - otherLength;
}
class Gen0035E3B0 { public: virtual ~Gen0035E3B0(); };
class Host0035E450 { public: Gen0035E3B0 *create(); };
namespace Rva0035E510 {
class BfmeNodeEAT { public: void bfmeSwapEAT(BfmeNodeEAT *other); };
}
class Rva00359E40HeldBody { public: void rvaClearActiveRecords(); };
class Rva0019BE80TeamRec { public: int append(const Dict *); };
class BfmeIndexedNodesFM { public: void bfmeRelease(int); };
extern void j_00029bef();
struct SideInfoD1E30 {
    int field_0;
    Dict dict;
    Gen0035E3B0 *scripts;
    char field_c[12];
};
struct TeamNodeD1E30 {
    short next, previous, reserved, free;
    int generation;
    Dict dict;
};
struct TeamListD1E30 {
    char prefix[12];
    _STL::vector<TeamNodeD1E30> nodes;
    short numActive, freeHead;
};
struct SidesListD1E30 {
    char prefix[0x28];
    int numSides;
    SideInfoD1E30 sides[32];
    int numSkirmishSides;
    SideInfoD1E30 skirmishSides[32];
    TeamListD1E30 teams, skirmishTeams;
    SideInfoD1E30 *getSide(int i) { return i < 0 || i >= numSides ? 0 : &sides[i]; }
    SideInfoD1E30 *getSkirmishSide(int i) { return i < 0 || i >= numSkirmishSides ? 0 : &skirmishSides[i]; }
};
// Retail ILT00029BEF ->0019C520 forwards the by-value string and an
// output-index pointer (passed as LEA at caller+267 and read at+2B2).
// Its existing forward/lookup declarations spell that second argument int.
// Use the address-named thunk with the witnessed pointer ABI; add no pin.
typedef int (SidesListD1E30::*FindTeamD1E30)(AsciiString, int *);
inline FindTeamD1E30 findTeamThunk() {
    union { void (*raw)(); FindTeamD1E30 member; } u;
    u.raw=j_00029bef;
    return u.member;
}
class SidesList;
extern SidesList *TheSidesList;
extern const StaticNameKey TheKey_playerName, TheKey_teamOwner, TheKey_teamName;
#define KEY(name) ((name).key())
class Player {
    char prefix[0x24];
    int m_playerIndex;
public:
    bool findSkirmishSide(int *);
    void rva000D1E30(const AsciiString &pname);
};
void Player::rva000D1E30(const AsciiString &pname) {
    int skirmishNdx;
    {
        int foundIndex;
        if (!findSkirmishSide(&foundIndex))
            return;
        skirmishNdx=foundIndex;
    }
    Gen0035E3B0 *sourceScripts=((SidesListD1E30 *)TheSidesList)->getSkirmishSide(skirmishNdx)->scripts;
    if (sourceScripts) {
        Gen0035E3B0 *scripts=((Host0035E450 *)sourceScripts)->create();
        SideInfoD1E30 *side=((SidesListD1E30 *)TheSidesList)->getSide(m_playerIndex);
        Gen0035E3B0 *old=side->scripts;
        if (old) {
            ((Rva0035E510::BfmeNodeEAT *)scripts)->bfmeSwapEAT((Rva0035E510::BfmeNodeEAT *)old);
            delete old;
            ((Rva00359E40HeldBody *)scripts)->rvaClearActiveRecords();
        }
        side->scripts=scripts;
    }
    AsciiString originalPlayerName=((SidesListD1E30 *)TheSidesList)->getSkirmishSide(skirmishNdx)->dict.getAsciiString(KEY(TheKey_playerName));
    for (int i=((SidesListD1E30 *)TheSidesList)->skirmishTeams.nodes[0].next; i; i=((SidesListD1E30 *)TheSidesList)->skirmishTeams.nodes[i].next) {
        if (((const StringBase<char> &)((SidesListD1E30 *)TheSidesList)->skirmishTeams.nodes[i].dict.getAsciiString(KEY(TheKey_teamOwner))).compare(originalPlayerName)==0) {
            Dict teamDict(((SidesListD1E30 *)TheSidesList)->skirmishTeams.nodes[i].dict);
            AsciiString teamName=teamDict.getAsciiString(KEY(TheKey_teamName));
            if (((const StringBase<char> &)teamName).compare(AsciiString("team")+originalPlayerName)==0)
                teamDict.setAsciiString(KEY(TheKey_teamName),AsciiString("team")+pname);
            teamDict.setAsciiString(KEY(TheKey_teamOwner),pname);
            int index;
            if ((((SidesListD1E30 *)TheSidesList)->*findTeamThunk())(pname+"/"+teamName,&index)) ((BfmeIndexedNodesFM *)&((SidesListD1E30 *)TheSidesList)->teams)->bfmeRelease(index);
            ((Rva0019BE80TeamRec *)&((SidesListD1E30 *)TheSidesList)->teams)->append(&teamDict);
        }
    }
}
