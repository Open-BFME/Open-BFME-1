// ?rva0019F500@BfmeTableERJ@@QAEXXZ
// partial score=0.9945 date=2026-09-28
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
// Vtables are literal retail addresses: base 0x107C7D0; binding 0x109BFD4;
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



class BfmeTableERJ;
#pragma pointers_to_members(full_generality,multiple_inheritance)
typedef bool (BfmeTableERJ::*Callback0019F500)(DataChunkInput&,DataChunkInfo*);
static __forceinline Callback0019F500 callbackAt0019F500(unsigned address) {
 union Bits {Callback0019F500 method;struct {unsigned address;int adjustment;} words;} bits;
 bits.words.address=address;bits.words.adjustment=0;return bits.method;
}
typedef bool (*CallbackBase0019F500)(DataChunkInput&,DataChunkInfo*,void*);
class ParserBase0019F500 {
public:
 ParserBase0019F500(DataChunkInput *file,const AsciiString &label,const AsciiString &parent) {
   vtable_=(void*)0x0107C7D0;file_=file;token_=file->registerParser(label,parent,(CallbackBase0019F500)0x0041579E,this);
 }
 ~ParserBase0019F500() {vtable_=(void*)0x0107C7D0;((BfmeSubVE*)file_)->bfmeDropVE(token_);}
protected:
 void *vtable_; DataChunkInput *file_;UserParser *token_;
};
class ParserBinding0019F500:public ParserBase0019F500 {
 BfmeTableERJ *owner_; Callback0019F500 callback_;
public:
 __forceinline ParserBinding0019F500(BfmeTableERJ *owner,Callback0019F500 cb,DataChunkInput *file,const AsciiString &label):ParserBase0019F500(file,label,AsciiString::TheEmptyString) {vtable_=(void*)0x0109BFD4;owner_=owner;callback_=cb;}
};

extern "C" unsigned int __cdecl strlen(const char*);
#pragma intrinsic(strlen)
template<> inline void StringBase<char>::concat(const char *s) {concat(s,strlen(s));}
template<> inline bool StringBase<char>::isEmpty() const {return !m_data || !m_data->length;}
template<> inline void StringBase<char>::concat(const StringBase<char>& s) {
 const int n=s.m_data?s.m_data->length:0;
 const char *p=s.m_data?s.m_data->data:"";
 concat(p,n);
}
struct Node0019F500 {Node0019F500 *next,*previous;AsciiString name;};
class BfmeTableERJ {
 char field00[12]; Node0019F500 *field0c;
public: void rva0019F500(); void clear();
};
#pragma comment(linker,"/alternatename:?clear@BfmeTableERJ@@QAEXXZ=?j_00023010@@YAXXZ")
void BfmeTableERJ::rva0019F500() {
 clear();
 for(Node0019F500 *it=field0c->next;it!=field0c;it=it->next) {
  AsciiString name=it->name;
  if(name.isEmpty())return;
  AsciiString path("Bases\\");
  path.concat(name);
  ((StringBase<char>&)path).concat("\\",1);
  path.concat(name);
  ((StringBase<char>&)path).concat(".bse",4);
  AsciiString filename(path);
  CachedFileInputStream file;
  if(!file.open(filename))continue;
  DataChunkInput input(&file);
  ParserBinding0019F500 parser(this,callbackAt0019F500(0x0041F384),&input,AsciiString("CastleTemplates"));
  if(!input.parse(0))throw (unsigned int)0xDEAD0005;
  file.close();
 }
}

