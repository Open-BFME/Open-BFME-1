// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?getName@DataChunkTableOfContents@@QAE?AVAsciiString@@I@Z: Code/GameEngine/Source/Common/System/DataChunk.cpp
// readable body of ?read@DataChunkTableOfContents@@QAEXAAVChunkInputStream@@@Z: Code/GameEngine/Source/Common/System/DataChunk.cpp
// readable body of ?write@DataChunkTableOfContents@@QAEXAAVOutputStream@@@Z: Code/GameEngine/Source/Common/System/DataChunk.cpp
// readable body of ?findMapping@DataChunkTableOfContents@@AAEPAVMapping@@ABVAsciiString@@@Z: Code/GameEngine/Source/Common/System/DataChunk.cpp

// The DataChunkTableOfContents id<->name table: the two list walks and the two
// stream halves.
//
//   getName     0x00102D90   id   -> name, by value
//   findMapping 0x00103CA0   name -> Mapping *
//   read        0x00102F20   the 'CkMp' block off a ChunkInputStream
//   write       0x00102E60   the same block onto an OutputStream
//
// All four are here rather than in DataChunk.cpp because they need the BFME
// string slice below: an eight-byte header with the comparison spelled out,
// where DataChunk.cpp compiles against the real AsciiString whose compare is
// declared and not defined. read's caller is the map loader; write's is
// DataChunkOutput::~DataChunkOutput at 0x001036C0, whose incremental-link call
// passes m_pOut and m_contents and so proves which stream each one takes.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char Byte;
typedef bool Bool;

#define NULL 0

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

struct BfmeStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;					// +4
	UnsignedShort m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/string_base.h
template <typename T>
class StringBase
{
public:
	StringBase() : m_data(0) {}
	T *getBufferForRead(Int len);				// ?getBufferForRead@?$StringBase@D@@QAEPADH@Z

protected:
	BfmeStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : public StringBase<char>
{
public:
	static AsciiString TheEmptyString;

	AsciiString() {}
	AsciiString(const AsciiString &that);
	~AsciiString();

	Int getLength(void) const { return m_data ? m_data->m_len : 0; }
	const char *str(void) const { return m_data ? (const char *)(m_data + 1) : ""; }

	// Retail INLINES the comparison: both lengths and both data pointers come
	// out of the string headers, the shorter length is picked, and the bytes
	// run through a repe cmpsb -- the memcmp intrinsic.
	Int compare(const AsciiString &that) const
	{
		Int thatLen = that.m_data ? that.m_data->m_len : 0;
		const char *thatData = that.m_data ? (const char *)(that.m_data + 1) : "";
		Int thisLen = m_data ? m_data->m_len : 0;
		const char *thisData = m_data ? (const char *)(m_data + 1) : "";
		Int n = thisLen < thatLen ? thisLen : thatLen;
		Int c = memcmp(thisData, thatData, n);
		if (c != 0)
			return c;
		return thisLen - thatLen;
	}
};

inline bool operator==(const AsciiString &a, const AsciiString &b) { return a.compare(b) == 0; }

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class Mapping
{
public:
	virtual ~Mapping();					// MemoryPoolObject vptr at this+0x00

	Mapping *next;						// this+0x04
	AsciiString name;					// this+0x08
	UnsignedInt id;						// this+0x0C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MapReaderWriterInfo.h
class ChunkInputStream
{
public:
	virtual Int read(void *pData, Int numBytes);
	virtual UnsignedInt tell(void);
	virtual Bool absoluteSeek(UnsignedInt pos);
	virtual Bool eof(void);
};

class OutputStream
{
public:
	virtual Int write(const void *pData, Int numBytes) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkTableOfContents
{
public:
	AsciiString getName(UnsignedInt id);
	void read(ChunkInputStream &s);
	void write(OutputStream &s);

private:
	Mapping *findMapping(const AsciiString &name);		// private: retail mangles it ?findMapping@...@@AAE...

	Mapping *m_list;					// this+0x00
	Int m_listLength;
	UnsignedInt m_nextID;
	Bool m_headerOpened;
};

template <typename T>
const T &max(const T &a, const T &b)
{
	return a > b ? a : b;
}

// ?getName@DataChunkTableOfContents@@QAE?AVAsciiString@@I@Z
// Either the matching name or AsciiString::TheEmptyString is assigned into the
// ABI's hidden return object.
AsciiString DataChunkTableOfContents::getName(UnsignedInt id)
{
	volatile Int constructionState = 0;
	Mapping *m;

	for (m = m_list; m; m = m->next)
	{
		if (m->id == id)
			return m->name;
	}

	return AsciiString::TheEmptyString;
}

// ?findMapping@DataChunkTableOfContents@@AAEPAVMapping@@ABVAsciiString@@@Z
// The name is not inferred: a byte-true call site already encodes this address,
// and the five-byte incremental-link thunk that jumps here is ledgered under
// the same symbol in DataChunkTableOfContentsFindMappingThunk.cpp.
Mapping *DataChunkTableOfContents::findMapping( const AsciiString& name )
{
	Mapping *m;

	for( m=m_list; m; m=m->next )
		if (name == m->name )
			return m;

	return NULL;
}

// ?read@DataChunkTableOfContents@@QAEXAAVChunkInputStream@@@Z
void DataChunkTableOfContents::read(ChunkInputStream &s)
{
	Int count, i;
	UnsignedInt maxID = 0;
	unsigned char len;
	Mapping *m;

	Byte tag[4] = {'x', 'x', 'x', 'x'};
	s.read(tag, sizeof(tag));
	if (tag[0] != 'C' || tag[1] != 'k' || tag[2] != 'M' || tag[3] != 'p')
		return;

	s.read((char *)&count, sizeof(Int));

	for (i = 0; i < count; i++)
	{
		m = new Mapping;
		s.read((char *)&len, sizeof(unsigned char));

		if (len > 0)
		{
			char *str = m->name.getBufferForRead(len);
			s.read(str, len);
			str[len] = '\0';
		}

		s.read((char *)&m->id, sizeof(UnsignedInt));
		m->next = m_list;
		m_list = m;
		m_listLength++;

		if (m->id > maxID)
			maxID = m->id;
	}

	m_headerOpened = count > 0 && !s.eof();
	m_nextID = max(m_nextID, maxID + 1);
}

// ?write@DataChunkTableOfContents@@QAEXAAVOutputStream@@@Z
void DataChunkTableOfContents::write(OutputStream &s)
{
	Mapping *m;
	unsigned char len;

	Byte tag[4] = {'C', 'k', 'M', 'p'};
	s.write(tag, sizeof(tag));

	s.write((void *)&this->m_listLength, sizeof(Int));

	for (m = this->m_list; m; m = m->next)
	{
		len = m->name.getLength();
		s.write((char *)&len, sizeof(unsigned char));
		s.write((char *)m->name.str(), len);
		s.write((char *)&m->id, sizeof(UnsignedInt));
	}
}
