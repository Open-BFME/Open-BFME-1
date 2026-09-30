// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/buildlistinfo /Iinputs/reference/shims/moduledata /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x0019EC80, 1096 bytes: case-insensitive filename cache of SidesList pointers.
// Canonical SidesListCtorThunk.cpp establishes sizeof(SidesList)==0x9EC,
// count at +0x28 and 32 entries of 0x18 bytes at +0x2C. This limited view
// retains those offsets; the ZH SidesList header has a different layout.
// DataChunkInput's 40-byte BFME layout and pointer-returning registerParser
// differ from the vendored ZH declaration, so the exact BFME ABI is below.
// Callbacks: ILT 0x4A755 -> 0x19BE80 and 0x283A3 -> 0x198700;
// dispatch 0x1579E -> 0x1028D0. The binding stores an 8-byte member pointer
// (entry and zero this-adjustment). Constructing those witnessed words keeps
// the callback materialization after the AsciiString temporary construction.
// Vtables are externs at the retail addresses: base 0x107C7D0; binding 0x109BFD4;
// scripts 0x109BFC8, independently witnessed by BfmeOwnCP at 0x191640.
// The native pair/vector callees copy an AsciiString plus a four-byte pointer;
// their bodies and this caller establish the payload, not old generated names.
#define _STLP_NO_EXCEPTIONS 1
#include "PreRTS.h"
#include "Common/Dict.h"
#include <vector>
#include <utility>
extern "C" __declspec(dllimport) int __cdecl _memicmp(const void*,const void*,unsigned);
class BfmeParserRegistryVE;
class BfmeSubVE;

class UserParser {
};

struct DataChunkInfo;

class ChunkInputStream {
public:
  virtual int read(char *data, int size) = 0;
  virtual int tell() = 0;
};

class DataChunkTableOfContents {
public:
  DataChunkTableOfContents();
  ~DataChunkTableOfContents();
  void read(ChunkInputStream &stream);

private:
  void *m_list;
  int m_listLength;
  unsigned int m_nextID;
  bool m_headerOpened;
};

class CachedFileInputStream : public ChunkInputStream {
public:
  CachedFileInputStream();
  ~CachedFileInputStream();

  int read(char *data, int size);
  int tell();
  bool open(AsciiString path);
  void close();

private:
  unsigned char m_storage[12];
};

// The retail DataChunkInput is a 40-byte local.  Keep its storage explicit;
// its registry/drop base is passed as an address view at the call sites.
class DataChunkInput {
protected:
  ChunkInputStream *m_file;
  DataChunkTableOfContents m_contents;
  int m_fileposOfFirstChunk;
  void *m_parserList;
  void *m_chunkStack;
  void *m_currentObject;
  void *m_userData;

public:
  explicit DataChunkInput(ChunkInputStream *stream);
  ~DataChunkInput();

  bool parse(void *context);
  UserParser *registerParser(
      const AsciiString &name, const AsciiString &empty,
      bool (*callback)(DataChunkInput &, DataChunkInfo *, void *),
      void *context);

};

class BfmeParserRegistryVE {
};

class BfmeSubVE {
public:
  void bfmeDropVE(void *value);
};


namespace _STL { template<> vector<AsciiString>::iterator vector<AsciiString>::erase(iterator,iterator); }
struct DeleteSlot0019EC80 {virtual ~DeleteSlot0019EC80();};
struct SideEntry0019EC80 {
 DeleteSlot0019EC80 *field00; Dict field04; DeleteSlot0019EC80 *field08; _STL::vector<AsciiString> field0c;
 void clear() {delete field00;field00=0;field04.clear();delete field08;field08=0;field0c.clear();}
};
#pragma pointers_to_members(full_generality,multiple_inheritance)
class SidesList {
 char field00[0x28]; int m_numSides; SideEntry0019EC80 m_sides[32]; char field32c[0x9ec-0x32c];
public:
 SidesList();
 void addEmptySide() {if(m_numSides<32) {int i=m_numSides;++m_numSides;m_sides[i].clear();}}
};
typedef bool (SidesList::*Callback0019EC80)(DataChunkInput&,DataChunkInfo*);
static __forceinline Callback0019EC80 callbackAt0019EC80(unsigned address) {
 union Bits { Callback0019EC80 method;struct {unsigned address;int adjustment;} words; } bits;
 bits.words.address=address;bits.words.adjustment=0;return bits.method;
}
typedef bool (*CallbackBase0019EC80)(DataChunkInput&,DataChunkInfo*,void*);
extern "C" int _bfmeVftVE[];
extern "C" int _bfmeVftXB[];
extern int g_0109BFD4[];
void j_0001579e();
void j_0004a755();
void j_000283a3();
class ParserBase0019EC80 {
public:
 ParserBase0019EC80(DataChunkInput *file,const AsciiString &label,const AsciiString &parent) {
   vtable_=_bfmeVftVE;file_=file;token_=file->registerParser(label,parent,(CallbackBase0019EC80)j_0001579e,this);
 }
 ~ParserBase0019EC80() {vtable_=_bfmeVftVE;((BfmeSubVE*)file_)->bfmeDropVE(token_);}
protected:
 void *vtable_; DataChunkInput *file_;UserParser *token_;
};
class ParserBinding0019EC80:public ParserBase0019EC80 {
 SidesList *owner_; Callback0019EC80 callback_;
public:
 __forceinline ParserBinding0019EC80(SidesList *owner,Callback0019EC80 cb,DataChunkInput *file,const AsciiString &label):ParserBase0019EC80(file,label,AsciiString::TheEmptyString) {vtable_=g_0109BFD4;owner_=owner;callback_=cb;}
};
class Rva00352810ParserRegistration {
protected:
 void *vtable_; DataChunkInput *file_; void *token_;void *context_;void *count_;
public:
 Rva00352810ParserRegistration(void*,void*,DataChunkInput*,AsciiString*);
};
class BfmeOwnCP:public Rva00352810ParserRegistration {
 SidesList *owner_;void *items_[32];int count_;
public:
 BfmeOwnCP(SidesList *owner,DataChunkInput *file):Rva00352810ParserRegistration(items_,&count_,file,0) {vtable_=_bfmeVftXB;owner_=owner;count_=0;}
 ~BfmeOwnCP();
};
typedef _STL::pair<AsciiString,SidesList*> CacheEntry0019EC80;
namespace _STL {
template<> vector<AsciiString>::iterator vector<AsciiString>::erase(iterator,iterator);
template<> void _Construct(CacheEntry0019EC80*,const CacheEntry0019EC80&);
template<> __declspec(noinline) CacheEntry0019EC80 make_pair(const AsciiString &a,SidesList*const &b) {return CacheEntry0019EC80(a,b);}
template<> void vector<CacheEntry0019EC80>::_M_insert_overflow(CacheEntry0019EC80*,const CacheEntry0019EC80&,const __false_type&,size_t,bool);
template<> __forceinline void vector<CacheEntry0019EC80>::push_back(const CacheEntry0019EC80 &v) {
 if(_M_finish!=_M_end_of_storage._M_data) {_Construct(_M_finish,v);++_M_finish;}
 else {__false_type tag;_M_insert_overflow(_M_finish,v,tag,1,true);}
}
}
template<> __forceinline int StringBase<char>::compareNoCase(const StringBase<char> &b) const {
 const StringBase<char> *self=this,*that=&b;
 int nb=that->m_data?that->m_data->length:0;
 const char *pb=that->m_data?that->m_data->data:"";
 int na=self->m_data?self->m_data->length:0;
 const char *pa=self->m_data?self->m_data->data:"";
 int n=na<nb?na:nb;int c=_memicmp(pa,pb,n);if(c) return c;return na-nb;
}
class CachedSidesLoader0019EC80 {
 _STL::vector<CacheEntry0019EC80> entries_;
public: SidesList *load(const AsciiString &name);
};
SidesList *CachedSidesLoader0019EC80::load(const AsciiString &name) {
 _STL::vector<CacheEntry0019EC80>::iterator it=entries_.begin(),end=entries_.end();
 for(;it!=end;++it) if(it->first.compareNoCase(name)==0) return it->second;
 CachedFileInputStream file;
 if(!file.open(name)) return 0;
  SidesList *sides=new SidesList;
  sides->addEmptySide();sides->addEmptySide();
  DataChunkInput input(&file);
  ParserBinding0019EC80 teams(sides,callbackAt0019EC80((unsigned)j_0004a755),&input,AsciiString("Teams"));
  BfmeOwnCP scripts(sides,&input);
  ParserBinding0019EC80 libraries(sides,callbackAt0019EC80((unsigned)j_000283a3),&input,AsciiString("LibraryMapLists"));
  if(!input.parse(0)) return 0;
  file.close();
  entries_.push_back(_STL::make_pair(name,sides));
  return sides;
}

typedef char SidesSize0019EC80[sizeof(SidesList)==0x9ec?1:-1];
typedef char SideEntrySize0019EC80[sizeof(SideEntry0019EC80)==24?1:-1];
typedef char BindingSize0019EC80[sizeof(ParserBinding0019EC80)==24?1:-1];
typedef char ScriptsSize0019EC80[sizeof(BfmeOwnCP)==156?1:-1];
typedef char InputSize0019EC80[sizeof(DataChunkInput)==40?1:-1];
typedef char CallbackSize0019EC80[sizeof(Callback0019EC80)==8?1:-1];
