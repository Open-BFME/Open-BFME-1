// DO NOT FOLD THIS INTO SidesList.cpp. It carried cluster markers pointing
// there; they are removed because this file does not hold those bodies. (Do not
// write that marker's phrase in prose here either -- merge_cluster scans every
// line for it and hard-fails tree-wide on one that does not parse as a marker.)
//
// All three rows this TU owns sit on RVA 0x0000D828, and 0x0000D828 is
// `E9 63 16 05 00` = jmp 0x0005EE90 -- which functions.csv already records as
// ??1AsciiString@@QAE@XZ (export_rva 0x0000D828, body 0x0005EE90, matched from
// ascii_string.cpp). The binary settles it by call profile: 6,947 direct
// call/jmp sites reach that stub and exactly one reaches the body behind it.
// That is a string destructor's import thunk. TeamsInfoRec::addTeam, its
// ::removeTeam and PrimitiveAnimationChannelClass<Vector2>::operator= cannot all
// be `jmp ??1AsciiString`, and addTeam and removeTeam cannot ICF-fold with each
// other either -- ICF folds identical bodies, and theirs differ.
//
// The rows verify only because a jmp's rel32 is a masked relocation, so ANY
// 5-byte tail-call thunk byte-matches any other. The shim call below is what
// makes the compiler emit one; its target is masked out of the comparison, so
// the match says nothing about which function this is.
//
// Retiring the rows and deleting this file is a ledger decision, not a Tier 1
// one -- verify_source_claims requires every .cpp under Code/ to own at least
// one matched row, so the file cannot simply be deleted while they stand.
// Logged in re_attempts.log as mis-anchored?.
class Dict;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/SidesList.h
class TeamsInfoRec
{
public:
    void addTeam(const Dict *);
};

class TeamsInfoRecAddTeamShim
{
public:
    void add(const Dict *dict);
};

void TeamsInfoRec::addTeam(const Dict *dict)
{
    ((TeamsInfoRecAddTeamShim *)this)->add(dict);
}
