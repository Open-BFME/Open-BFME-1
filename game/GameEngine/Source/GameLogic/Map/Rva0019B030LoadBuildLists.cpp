// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii/Common /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x0019B030, 641 bytes through RET at +0x280.
// GameLogic::init (GameLogicInit.cpp) calls this through ILT 0x00040381 with
// ecx=g_bfmeTableERJ and no arguments; that matched caller names it
// BfmeTableERJ::rva0019B030. g_bfmeTableERJ is pinned at VA 0x012EF428, the
// address dir32_addresses.csv gives TheSidesList, so the owner object is the
// SidesList singleton; the method's real name is not established and the
// caller's address-labelled name is kept.
// The body resets the build-list records (landed 0x001988D0) and reads the
// "BuildLists" chunk from Bases\Camps\Camps.map (a missing file returns early)
// and then from Bases\Others\Others.map, throwing ERROR_CORRUPT_FILE_FORMAT
// on a parse failure. Each read binds an 8-byte member callback (ILT
// 0x0040F51A -> 0x0019A720 and ILT 0x00413C6E -> 0x0019A740) through the
// parser binding of the landed sibling 0x0019EC80 (base vtable 0x0107C7D0,
// binding vtable 0x0109BFD4, dispatch ILT 0x0041579E -> 0x001028D0).
// The binding constructor is defined in the class; MSVC inlines it at the
// first site and calls it out of line at the second (retail ILT 0x0002B09E ->
// 0x001920C0). Retail passes the callback there as a by-value member pointer
// (xor ecx,ecx; push ecx; mov eax,imm; push eax), not as separate ints.
// Both files use the `if (!open) return;` form: the extra unwind reference
// on the Others stream is what puts it below the Camps stream in the frame.

#include "AsciiString.h"

#define ERROR_CORRUPT_FILE_FORMAT 0xDEAD0005

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

// The retail DataChunkInput is a 40-byte local (see CachedSidesLoader0019EC80).
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

class BfmeSubVE {
public:
  void bfmeDropVE(void *value);
};

// Landed 0x001988D0 contract (Rva001988D0ResetBuildLists.cpp).
class Rva001988D0SidesLists {
public:
  void resetBuildLists();
};

// The binding's owner class (identity_evidence/parser_binding_ctor_001920c0.md).
class SidesList;

#pragma pointers_to_members(full_generality, multiple_inheritance)
class BfmeTableERJ {
public:
  void rva0019B030(void);
};

typedef bool (SidesList::*BuildListCallback0019B030)(DataChunkInput &, DataChunkInfo *);
static __forceinline BuildListCallback0019B030 callbackAt0019B030(unsigned address) {
  union Bits { BuildListCallback0019B030 method; struct { unsigned address; int adjustment; } words; } bits;
  bits.words.address = address;
  bits.words.adjustment = 0;
  return bits.method;
}

typedef bool (*CallbackBase0019B030)(DataChunkInput &, DataChunkInfo *, void *);
extern void j_0001579e();
extern void j_0000f51a();
extern void j_00013c6e();
extern "C" int _bfmeVftVE[];
extern "C" const void *bfmeVftBfmeParserBindingVE[];
#pragma comment(linker, "/alternatename:_bfmeVftBfmeParserBindingVE=??_7BfmeParserBindingVE@@6B@")
class ParserBase0019B030 {
public:
  ParserBase0019B030(DataChunkInput *table, const AsciiString &name, const AsciiString &parent) {
    vtable_ = _bfmeVftVE;
    table_ = table;
    parser_ = table->registerParser(name, parent, (CallbackBase0019B030)j_0001579e, this);
  }
  ~ParserBase0019B030() {
    vtable_ = _bfmeVftVE;
    reinterpret_cast<BfmeSubVE *>(table_)->bfmeDropVE(parser_);
  }
protected:
  void *vtable_;
  DataChunkInput *table_;
  UserParser *parser_;
};

class BfmeParserBindingVE : public ParserBase0019B030 {
  SidesList *owner_;
  BuildListCallback0019B030 callback_;
public:
  BfmeParserBindingVE(SidesList *owner, BuildListCallback0019B030 callback, DataChunkInput *table,
                      const AsciiString &name, const AsciiString &parent)
      : ParserBase0019B030(table, name, parent) {
    vtable_ = bfmeVftBfmeParserBindingVE;
    owner_ = owner;
    callback_ = callback;
  }
};

void BfmeTableERJ::rva0019B030(void) {
  reinterpret_cast<Rva001988D0SidesLists *>(this)->resetBuildLists();

  {
    CachedFileInputStream camps;
    if (!camps.open(AsciiString("Bases\\Camps\\Camps.map"))) {
      return;
    }
    DataChunkInput campsData(&camps);
    BfmeParserBindingVE binding(reinterpret_cast<SidesList *>(this), callbackAt0019B030((unsigned)j_0000f51a), &campsData,
                                AsciiString("BuildLists"), AsciiString::TheEmptyString);
    if (!campsData.parse(0)) {
      throw(ERROR_CORRUPT_FILE_FORMAT);
    }
    camps.close();
  }

  {
    CachedFileInputStream others;
    if (!others.open(AsciiString("Bases\\Others\\Others.map"))) {
      return;
    }
    DataChunkInput othersData(&others);
    BfmeParserBindingVE binding(reinterpret_cast<SidesList *>(this), callbackAt0019B030((unsigned)j_00013c6e), &othersData,
                                AsciiString("BuildLists"), AsciiString::TheEmptyString);
    if (!othersData.parse(0)) {
      throw(ERROR_CORRUPT_FILE_FORMAT);
    }
    others.close();
  }
}

typedef char BindingSize0019B030[sizeof(BfmeParserBindingVE) == 24 ? 1 : -1];
typedef char InputSize0019B030[sizeof(DataChunkInput) == 40 ? 1 : -1];
typedef char CallbackSize0019B030[sizeof(BuildListCallback0019B030) == 8 ? 1 : -1];
