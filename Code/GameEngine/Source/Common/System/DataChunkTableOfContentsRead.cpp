// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME: DataChunkTableOfContents::read, retail 0x00102F20.
//
// This focused TU preserves the BFME layouts used by the adjacent table
// helpers while keeping the stream's virtual read calls and Mapping's inline
// default construction local to this body.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char Byte;
typedef bool Bool;

template <typename T>
class StringBase
{
	public:
		StringBase() : m_data(0) {}
		T *getBufferForRead(Int len);

	private:
		void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : public StringBase<char> {};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MapReaderWriterInfo.h
class ChunkInputStream
{
public:
	virtual Int read(void *pData, Int numBytes);
	virtual UnsignedInt tell(void);
	virtual Bool absoluteSeek(UnsignedInt pos);
	virtual Bool eof(void);
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
	void read(ChunkInputStream &s);

private:
	Mapping *m_list;
	Int m_listLength;
	UnsignedInt m_nextID;
	Bool m_headerOpened;
};

template <typename T>
const T &max(const T &a, const T &b)
{
	return a > b ? a : b;
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
