// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?allocateID@DataChunkTableOfContents@@QAEIABVAsciiString@@@Z: Code/GameEngine/Source/Common/System/DataChunk.cpp

// DataChunkTableOfContents::allocateID, 0x00103D60, 100 bytes.
//
// The reference's body unchanged: hand back the id of an existing mapping, or
// make one, number it, name it, prepend it and count it.
//
// It sits beside findMapping rather than inside its translation unit because
// retail reaches findMapping through its incremental-link thunk, which only
// happens across a compilation boundary.
//
// The layout the two share is confirmed from this side: the table's list at
// +0x00, its length at +0x04 and the next id at +0x08, and a mapping's next at
// +0x04, name at +0x08 and id at +0x0C behind the pool object's vptr, in the
// 0x10 bytes the allocation asks for. The id is taken before the counter is
// bumped, and the name assignment lands between the two.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

#define NULL 0

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
	AsciiString(void) : m_data(0) {}

	AsciiString &operator=(const AsciiString &that);	// retail 0x00887C90

	BfmeStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class Mapping
{
public:
	virtual ~Mapping();					// pool object vptr, this+0x00

	Mapping *next;						// this+0x04
	AsciiString name;					// this+0x08
	UnsignedInt id;						// this+0x0C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkTableOfContents
{
public:
	UnsignedInt allocateID(const AsciiString &name);

private:
	Mapping *findMapping(const AsciiString &name);		// ILT 0x0001587A

	Mapping *m_list;					// this+0x00
	Int m_listLength;					// this+0x04
	UnsignedInt m_nextID;					// this+0x08
	Bool m_headerOpened;
};

UnsignedInt DataChunkTableOfContents::allocateID(const AsciiString& name )
{
	Mapping *m = findMapping( name );

	if (m)
		return m->id;
	else
	{
		// allocate new id mapping
		m = new Mapping;

		m->id = m_nextID++;
		m->name =  name ;

		// prepend to list
		m->next = m_list;
		m_list = m;

		m_listLength++;

		return m->id;
	}
}
