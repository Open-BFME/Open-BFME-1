// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME: DataChunkTableOfContents::write, retail 0x00102E60.
//
// The caller is DataChunkOutput::~DataChunkOutput at 0x001036C0.  Its
// incremental-link call passes m_pOut and m_contents, proving that this is
// the OutputStream writer rather than the adjacent ChunkInputStream reader.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char Byte;

struct BfmeAsciiStringData
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
	Int getLength(void) const { return m_data ? m_data->m_len : 0; }
	const char *str(void) const { return m_data ? (const char *)(m_data + 1) : ""; }

private:
	BfmeAsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MapReaderWriterInfo.h
class OutputStream
{
public:
	virtual Int write(const void *pData, Int numBytes) = 0;
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
	void write(OutputStream &s);

private:
	Mapping *m_list;
	Int m_listLength;
	UnsignedInt m_nextID;
	bool m_headerOpened;
};

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
