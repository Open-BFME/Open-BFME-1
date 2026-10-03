// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/buildlistinfo /Iinputs/reference/shims/moduledata /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail RVA 0019D410: complete 658-byte body, ret 8, followed by INT3.
// Address-derived owner/method: source run is SidesList.cpp, but no native
// method spelling is established. The tree key is two owning AsciiStrings;
// the mapped int indexes 16-byte records, whose +0x0c member is a Dict.
// TheKey_teamOwner and Dict::setAsciiString are independently witnessed by
// the actual calls through ILTs 00009304 and 0002AF90. The erase passes 28B
// to the node allocator, confirming a 16B node header plus 12B value.
// Native inline comparison makes lower_bound nonthrowing; its temporary
// pair has no EH state. The remaining ten states agree with retail FuncInfo
// 00DF60B4. The retained record-array pointer spans setAsciiString, while
// the next index reads the array again. No shared header edits are required.
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#define _OPERATOR_NEW_DEFINED_ // <map> already supplied placement new/delete
#include "PreRTS.h"
#include "Common/Dict.h"
#include "Common/WellKnownKeys.h"
#include <map>
#include <vector>
inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }
typedef _STL::pair<AsciiString,AsciiString> Key;
typedef _STL::pair<Key,int> Pair;
typedef _STL::pair<const Key,int> Value;
struct TeamLess0019B850 { bool operator()(const Key& a,const Key& b) const { return a.first.compare(b.first)<0 || (!(b.first.compare(a.first)<0) && a.second.compare(b.second)<0); } };
typedef _STL::map<Key,int,TeamLess0019B850> Map;
namespace _STL {
template<> __declspec(noinline) Pair make_pair(const Key& key,const int& index) { return Pair(key,index); }
}
struct Rva0019D410Record {
 short field00,field02,field04,field06;
 _STL::_Rb_tree_node_base* field08;
 Dict field0c;
};
class Rva0019D410Owner {
 Map field00;
 _STL::vector<Rva0019D410Record> field0c;
public:
 void method(const AsciiString& from,const AsciiString& to);
};
void Rva0019D410Owner::method(const AsciiString& from,const AsciiString& to) {
 if (((const StringBase<char>*)&to)->compare(*(const StringBase<char>*)&from)==0) return;
 Map::iterator end=field00.end();
 Map::iterator it=field00.lower_bound(Key(from,AsciiString::TheEmptyString));
 while(it!=end) {
  if(it->first.first.compare(from)!=0) break;
  Map::iterator next=it; ++next;
  AsciiString name=it->first.second;
  int index=it->second;
  Key key(to,name);
  Map::iterator replacement=field00.insert(_STL::make_pair(key,index)).first;
  while(index) {
   Rva0019D410Record* records=field0c.begin();
   records[index].field0c.setAsciiString(TheKey_teamOwner,to);
   records[index].field08=replacement._M_node;
   index=field0c[index].field04;
  }
  field00.erase(it);
  it=next;
 }
}
