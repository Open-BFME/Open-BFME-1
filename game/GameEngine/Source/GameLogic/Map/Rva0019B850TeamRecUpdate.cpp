// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/buildlistinfo /Iinputs/reference/shims/moduledata /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x0019B850, 396 bytes. Keep the established updateTeam name:
// 0x0019BA40 and 0x0019BC00 call this one-index thiscall through ILT 0x26EE.
// The map key is (teamOwner, teamName). The vector at +0x0C contains
// 16-byte records: a Dict at +0x0C and a tree node link at +8.
// New keys map to the index; existing keys link the previous and current
// records through shorts at +6/+4, then update the tree's index at node+0x18.
// Native map::insert's result wrapper and vector::begin's access expression
// are required for the retail return-buffer and register allocation.

#define _STLP_NO_EXCEPTIONS 1
#include "PreRTS.h"
#include "Common/Dict.h"
#include "Common/WellKnownKeys.h"
#include <map>
#include <vector>
typedef _STL::pair<AsciiString,AsciiString> TeamKey0019B850;
typedef _STL::pair<TeamKey0019B850,int> TeamPair0019B850;
typedef _STL::pair<const TeamKey0019B850,int> TeamValue0019B850;
typedef _STL::_Rb_tree<TeamKey0019B850,TeamValue0019B850,_STL::_Select1st<TeamValue0019B850>,_STL::less<TeamKey0019B850>,_STL::allocator<TeamValue0019B850> > TeamTree0019B850;
namespace _STL {
template<> pair<TeamKey0019B850,int>::~pair();
template<> pair<const TeamKey0019B850,int>::~pair();
template<> __declspec(noinline) TeamPair0019B850 make_pair(const TeamKey0019B850& key, const int& index) { return TeamPair0019B850(key,index); }
}
// This key ordering has its own retail tree body; keep its address in the
// comparator type instead of borrowing a different physical instantiation.
struct TeamLess0019B850 : _STL::less<TeamKey0019B850> {};
struct TeamRecord0019B850 {
    short field00, field02, field04, field06;
    _STL::_Rb_tree_node_base* field08;
    Dict field0c;
};
class Rva0019BE80TeamRec {
    _STL::map<TeamKey0019B850,int,TeamLess0019B850> field00;
    _STL::vector<TeamRecord0019B850> field0c;
public:
    void updateTeam(int index);
};
void Rva0019BE80TeamRec::updateTeam(int index) {
    TeamRecord0019B850* team = field0c.begin() + index;
    TeamKey0019B850 key(team->field0c.getAsciiString(TheKey_teamOwner),team->field0c.getAsciiString(TheKey_teamName));
    team->field08 = field00.find(key)._M_node;
    if(team->field08 == field00.end()._M_node) {
        team->field08 = field00.insert(_STL::make_pair(key,index)).first._M_node;
    } else {
        int previous = static_cast<_STL::_Rb_tree_node<TeamValue0019B850>*>(team->field08)->_M_value_field.second;
        TeamRecord0019B850* prior = field0c.begin() + previous; prior->field06 = (short)index;
        team->field04 = (short)previous;
        static_cast<_STL::_Rb_tree_node<TeamValue0019B850>*>(team->field08)->_M_value_field.second = index;
    }
}


typedef char RecordWidth0019B850[(sizeof(TeamRecord0019B850)==16)?1:-1];
