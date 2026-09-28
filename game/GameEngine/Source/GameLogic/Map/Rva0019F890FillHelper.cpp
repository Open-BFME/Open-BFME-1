// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/buildlistinfo /Iinputs/reference/shims/moduledata /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x0019F890: 900-byte recursive helper. Matched Rva0019FD00Fill.cpp
// proves the private six-argument signature and owner layout; retain its names.
// SidesList layout: matched CachedSidesLoader0019EC80.cpp proves 0x28 count
// and 0x18 records at 0x2C. Retail here reads the team vector at 0x63C;
// Rva0019BA40TeamRecAppend.cpp independently proves each 16-byte team node.
// Native STLport set return temporaries reproduce the 0x84-byte frame.
// StaticNameKey initializers at VA012A7918/012A7770 point respectively to
// playerName/teamLibraryMapName, the dir32_addresses.csv names for both.
// The 0x35E3B0 clone constructor uses one pointer argument on a 0x4C ScriptList.
// Existing named callees and the constructor thunk preserve the witnessed ABIs.
#define _STLP_NO_EXCEPTIONS 1
#include "PreRTS.h"
#include "Common/Dict.h"
#include <vector>
#include <set>
template<> inline bool StringBase<char>::isEmpty() const {return !m_data || !m_data->length;}
template<> inline int StringBase<char>::compare(const StringBase<char>& s) const {
 int thatLen=s.m_data?s.m_data->length:0;
 const char *thatData=s.m_data?s.m_data->data:"";
 int thisLen=m_data?m_data->length:0;
 const char *thisData=m_data?m_data->data:"";
 int n=thisLen<thatLen?thisLen:thatLen;
 int c=memcmp(thisData,thatData,n);
 if(c)return c;
 return thisLen-thatLen;
}
template<class T> inline bool operator==(const StringBase<T>&a,const StringBase<T>&b) {return a.compare(b)==0;}
class Rva0019A7D0Vector;
class Rva0019A1D0Owner;
class Rva0019BE80TeamRec {public:int append(const Dict*);};
class Rva00357800Owner {public:void swap(Rva00357800Owner*);};
namespace Rva0035E510 {class BfmeNodeEAT {public:void bfmeSwapEAT(BfmeNodeEAT*);};}
extern void j_00020d92();
class ScriptList {
 char body[0x4c];
public:
 __forceinline ScriptList(ScriptList *source) {
  typedef void (ScriptList::*Ctor)(ScriptList*);
  union {void (*raw)();Ctor member;} ctor;
  ctor.raw=j_00020d92;
  (this->*ctor.member)(source);
 }
 ~ScriptList();
};
struct Rva001A0320Record {int field00;Dict m_dict;ScriptList *field08;_STL::vector<AsciiString> names;};
struct TeamRecord0019F890 {short next,previous,reserved,free;int generation;Dict dict;};
class SidesList {public:char field00[0x28];int m_count;Rva001A0320Record m_records[32];char field32c[0x63c-0x32c];TeamRecord0019F890 *teams;};
class CachedSidesLoader0019EC80 {public:SidesList *load(const AsciiString&);};
struct BfmeStringNoCaseLess {bool operator()(const AsciiString&a,const AsciiString&b)const {return a.compareNoCase(b)<0;}};
class Rva00197AE0Temporary: public _STL::set<AsciiString,BfmeStringNoCaseLess> {};
class Rva001A0320Owner {
 char m_prefix[0x28];int m_count;Rva001A0320Record m_records[32];
private:
 void fillHelper(int index,Rva0019A7D0Vector *out,void *entry,Rva00197AE0Temporary *temporary,ScriptList *scripts,Rva0019A1D0Owner *tree);
};
extern const StaticNameKey TheKey_teamOwner,TheKey_teamName,TheKey_playerName,TheKey_teamLibraryMapName;
// Retail initializers identify VA 0x012A7918/0x012A7770 as playerName/teamLibraryMapName (dir32_addresses.csv).
void Rva001A0320Owner::fillHelper(int index,Rva0019A7D0Vector *out,void *entry,Rva00197AE0Temporary *temporary,ScriptList *scripts,Rva0019A1D0Owner *tree) {
 Rva001A0320Record *record;
 if(index<0 || index>=m_count)record=0;else record=&m_records[index];
 _STL::vector<AsciiString> *names=(_STL::vector<AsciiString>*)entry;
 _STL::vector<AsciiString>::reverse_iterator end=names->rend(),it=names->rbegin();
 for(;it!=end;++it) {
  AsciiString name=*it;
  if(temporary->find(name)!=temporary->end())continue;
  temporary->insert(name);
  SidesList *sides=((CachedSidesLoader0019EC80*)out)->load(name);
  if(!sides)continue;
  Rva001A0320Record *side=sides->m_count>1?&sides->m_records[1]:0;
  fillHelper(index,out,&side->names,temporary,scripts,tree);
  if(side->field08) {
   ScriptList local(side->field08);
   ((Rva0035E510::BfmeNodeEAT*)&local)->bfmeSwapEAT((Rva0035E510::BfmeNodeEAT*)scripts);
   ((Rva00357800Owner*)scripts)->swap((Rva00357800Owner*)&local);
  }
  AsciiString owner=record->m_dict.getAsciiString(TheKey_playerName.key(),0);
  for(int n=sides->teams[0].next;n!=0;n=sides->teams[n].next) {
   Dict *dict=&sides->teams[n].dict;
   AsciiString teamOwner=dict->getAsciiString(TheKey_teamOwner.key(),0);
   if(teamOwner.isEmpty())continue;
   if(dict->getAsciiString(TheKey_teamName.key(),0)==AsciiString("team")+teamOwner)continue;
   Dict copy(*dict);
   copy.setAsciiString(TheKey_teamOwner.key(),owner);
   copy.setAsciiString(TheKey_teamLibraryMapName.key(),name);
   ((Rva0019BE80TeamRec*)tree)->append(&copy);
  }
 }
}




