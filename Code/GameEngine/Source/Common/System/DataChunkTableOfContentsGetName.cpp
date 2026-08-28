// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME: DataChunkTableOfContents::getName, retail 0x00102D90.
//
// The body walks the Mapping list by id and assigns either the matching name
// or AsciiString::TheEmptyString into the ABI's hidden return object.  The
// focused TU keeps the BFME Mapping layout and the StringBase copy call
// independent from the broader DataChunk.cpp translation unit.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

struct BfmeStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;
	UnsignedShort m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	static AsciiString TheEmptyString;
	AsciiString(const AsciiString &that);
	~AsciiString();

private:
	BfmeStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class Mapping
{
public:
	virtual ~Mapping();

	Mapping *next;
	AsciiString name;
	UnsignedInt id;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkTableOfContents
{
public:
	AsciiString getName(UnsignedInt id);

private:
	Mapping *m_list;
	Int m_listLength;
	UnsignedInt m_nextID;
	Bool m_headerOpened;
};

// ?getName@DataChunkTableOfContents@@QAE?AVAsciiString@@I@Z
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
