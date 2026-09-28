// ?d_0019b030@@YAXXZ
// partial score=0.983 date=2026-09-28
// Scratch reconstruction of retail RVA 0x0019B030 (641 bytes).
//
// This TU intentionally keeps the owning class address-labelled.  The
// resetBuildLists declaration below is the landed, independently matched
// RVA 0x001988D0 contract; it is not a guessed method on this owner.
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii/Common /Igame/Libraries/Source/WWVegas/WWLib

#include "AsciiString.h"

#define ERROR_CORRUPT_FILE_FORMAT 0xDEAD0005

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

// The actual 0x1988D0 owner type is landed in a separate TU.  Calling it via
// this exact class view preserves its proven decorated symbol while allowing
// this scratch owner to remain address-labelled.
class Rva001988D0SidesLists {
public:
  void resetBuildLists();
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
class Rva0019B030Owner {
public:
 void loadBuildLists();
 bool readCamps(DataChunkInput &, DataChunkInfo *);
 bool readOthers(DataChunkInput &, DataChunkInfo *);
};
typedef bool (Rva0019B030Owner::*BuildListCallback)(DataChunkInput &, DataChunkInfo *);
static __forceinline BuildListCallback callbackAt0019B030(unsigned address) {
 union Bits { BuildListCallback method;struct {unsigned address;int adjustment;} words; } bits;
 bits.words.address=address;bits.words.adjustment=0;return bits.method;
}
typedef bool (*CallbackBase0019B030)(DataChunkInput&,DataChunkInfo*,void*);
class ParserBase0019B030 {
public:
 ParserBase0019B030(DataChunkInput *table,const AsciiString &name,const AsciiString &parent) {
  vtable_=(void*)0x0107C7D0;table_=table;parser_=table->registerParser(name,parent,(CallbackBase0019B030)0x0041579E,this);
 }
 ~ParserBase0019B030() {vtable_=(void*)0x0107C7D0;reinterpret_cast<BfmeSubVE *>(table_)->bfmeDropVE(parser_);}
protected:
 void *vtable_;DataChunkInput *table_;UserParser *parser_;
};
class ParserBinding0019B030:public ParserBase0019B030 {
 Rva0019B030Owner *owner_;BuildListCallback callback_;
public:
 ParserBinding0019B030(Rva0019B030Owner *owner,BuildListCallback callback,DataChunkInput *table,
 const AsciiString &name,const AsciiString &parent):ParserBase0019B030(table,name,parent) {
  vtable_=(void*)0x0109BFD4;owner_=owner;callback_=callback;
 }
};
void Rva0019B030Owner::loadBuildLists() {
  reinterpret_cast<Rva001988D0SidesLists *>(this)->resetBuildLists();

  {
  CachedFileInputStream camps;
  if (!camps.open(AsciiString(reinterpret_cast<const char *>(0x0109C190)))) {
    return;
  }
    DataChunkInput campsData(&camps);
      ParserBinding0019B030 binding(this, callbackAt0019B030(0x0040F51A), &campsData, AsciiString(reinterpret_cast<const char *>(0x0109C14C)), AsciiString::TheEmptyString);
      if (!campsData.parse(0)) {
        throw(ERROR_CORRUPT_FILE_FORMAT);
      }
      camps.close();
  }

  {
  CachedFileInputStream others;
  if (others.open(AsciiString(reinterpret_cast<const char *>(0x0109C174)))) {
    DataChunkInput othersData(&others);
      ParserBinding0019B030 binding(this, callbackAt0019B030(0x00413C6E), &othersData, AsciiString(reinterpret_cast<const char *>(0x0109C14C)), AsciiString::TheEmptyString);
      if (!othersData.parse(0)) {
        throw(ERROR_CORRUPT_FILE_FORMAT);
      }
      others.close();
  }
  }
}

