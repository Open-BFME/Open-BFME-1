// ?loadBuildLists@Rva0019B030Owner@@QAEXXZ
// partial score=0.46 date=2026-09-23
// Scratch reconstruction of retail RVA 0x0019B030 (641 bytes).
//
// This TU intentionally keeps the owning class address-labelled.  The
// resetBuildLists declaration below is the landed, independently matched
// RVA 0x001988D0 contract; it is not a guessed method on this owner.
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringbaseascii/Common /ICode/Libraries/Source/WWVegas/WWLib

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

typedef bool (*BfmeParserCallback)(DataChunkInput &, DataChunkInfo *, void *);
typedef void (__cdecl *BuildListCallback)(void);

class BfmeParserRegistrationVE {
public:
  BfmeParserRegistrationVE(
      DataChunkInput *table, AsciiString *name, AsciiString *label) {
    m_vtable = reinterpret_cast<void *>(0x0107C7D0);
    m_table = table;
    m_parser = table->registerParser(
        *name, *label, (BfmeParserCallback)0x0041579E, this);
  }

  __forceinline ~BfmeParserRegistrationVE() {
    m_vtable = reinterpret_cast<void *>(0x0107C7D0);
    reinterpret_cast<BfmeSubVE *>(m_table)->bfmeDropVE(m_parser);
  }

protected:
  void *m_vtable;
  DataChunkInput *m_table;
  UserParser *m_parser;
};

class Rva0019B030BuildListsBinding : public BfmeParserRegistrationVE {
public:
  __forceinline Rva0019B030BuildListsBinding(
      void *owner, BuildListCallback callback, int adjuster,
      DataChunkInput *table)
      : BfmeParserRegistrationVE(
            table,
            (AsciiString *)&AsciiString(
                reinterpret_cast<const char *>(0x0109C14C)),
            &AsciiString::TheEmptyString) {
    Rva0019B030BuildListsBinding *self = this;
    self->m_vtable = reinterpret_cast<void *>(0x0109BFD4);
    self->m_owner = owner;
    self->m_callback = callback;
    self->m_adjuster = adjuster;
  }

private:
  void *m_owner;
  BuildListCallback m_callback;
  int m_adjuster;
};

// This is a six-argument binding constructor already matched at RVA
// 0x001920C0.  The temporary label and empty string are deliberately passed
// as the actual pointer arguments used by the retail call sequence.
class BfmeParserBindingBaseVE {
public:
  virtual void bfmeSlot0(void);
  virtual void bfmeSlot1(void);

protected:
  BfmeParserRegistryVE *m_registry;
  UserParser *m_parser;
};

class BfmeParserBindingVE : public BfmeParserBindingBaseVE {
public:
  BfmeParserBindingVE(
      int owner, int callback, int adjuster,
      BfmeParserRegistryVE *registry, void *label, void *empty);

  ~BfmeParserBindingVE() {
    reinterpret_cast<BfmeSubVE *>(m_registry)->bfmeDropVE(m_parser);
  }

  virtual void bfmeSlot0(void);
  virtual void bfmeSlot1(void);

private:
  int m_owner;
  int m_callback;
  int m_adjuster;
};

class Rva0019B030Owner {
public:
  void loadBuildLists();
};

void Rva0019B030Owner::loadBuildLists() {
  BuildListCallback first_callback = (BuildListCallback)0x0040F51A;
  int first_adjuster = 0;
  reinterpret_cast<Rva001988D0SidesLists *>(this)->resetBuildLists();

  {
  CachedFileInputStream camps;
  if (!camps.open(AsciiString(reinterpret_cast<const char *>(0x0109C190)))) {
    return;
  }
    DataChunkInput campsData(&camps);
      Rva0019B030BuildListsBinding binding(
          this, first_callback, first_adjuster, &campsData);
      if (!campsData.parse(0)) {
        throw(ERROR_CORRUPT_FILE_FORMAT);
      }
      camps.close();
  }

  {
  CachedFileInputStream others;
  if (others.open(AsciiString(reinterpret_cast<const char *>(0x0109C174)))) {
    DataChunkInput othersData(&others);
      BfmeParserBindingVE binding(
          reinterpret_cast<int>(this), 0x00413C6E, 0,
          reinterpret_cast<BfmeParserRegistryVE *>(&othersData),
          reinterpret_cast<void *>(
              (AsciiString *)&AsciiString(
                  reinterpret_cast<const char *>(0x0109C14C))),
          reinterpret_cast<void *>(&AsciiString::TheEmptyString));
      if (!othersData.parse(0)) {
        throw(ERROR_CORRUPT_FILE_FORMAT);
      }
      others.close();
  }
  }
}
