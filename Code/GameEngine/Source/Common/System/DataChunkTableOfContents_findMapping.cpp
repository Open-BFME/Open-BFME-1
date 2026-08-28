// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?findMapping@DataChunkTableOfContents@@AAEPAVMapping@@ABVAsciiString@@@Z: Code/GameEngine/Source/Common/System/DataChunk.cpp

// DataChunkTableOfContents::findMapping, 0x00103CA0, 126 bytes.
//
// The reference's body unchanged -- walk m_list, return the first Mapping
// whose name matches -- and the name is not inferred: a byte-true call site
// already encodes this address, and the five-byte incremental-link thunk that
// jumps here is ledgered under the same symbol in
// DataChunkTableOfContentsFindMappingThunk.cpp.
//
// It gets its own translation unit because DataChunk.cpp, which carries the
// same body, compiles against the real AsciiString, where compare is declared
// and not defined. Retail INLINES the comparison: both lengths and both data
// pointers are read out of the string headers, the shorter length picked, and
// the bytes run through a repe cmpsb -- the memcmp intrinsic. So the slice
// here is the eight-byte BFME string header with compare spelled out, and
// operator== is compare() == 0 above it.
//
// Mapping's layout falls out of the two offsets the loop uses: a vptr from
// MemoryPoolObject at +0, next at +4 and name at +8.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
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

	BfmeStringData *m_data;
};

inline bool operator==(const AsciiString &a, const AsciiString &b) { return a.compare(b) == 0; }

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class Mapping
{
public:
	void *m_vptr;						// MemoryPoolObject
	Mapping *next;						// this+0x04
	AsciiString name;					// this+0x08
	UnsignedInt id;						// this+0x0C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkTableOfContents
{
	Mapping *m_list;					// this+0x00
	Int m_listLength;
	UnsignedInt m_nextID;
	Bool m_headerOpened;

	Mapping *findMapping(const AsciiString &name);
};

// ?findMapping@DataChunkTableOfContents@@AAEPAVMapping@@ABVAsciiString@@@Z
Mapping *DataChunkTableOfContents::findMapping( const AsciiString& name )
{
	Mapping *m;

	for( m=m_list; m; m=m->next )
		if (name == m->name )
			return m;

	return NULL;
}
