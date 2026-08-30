// cl: /DNDEBUG /MD /EHsc

// Open-BFME: DataChunkInput destructor, retail 0x00102910.
//
// The destructor's three walks are the concrete layout evidence: the chunk
// stack is at +0x1c, the parser list at +0x18, and the table-of-contents
// mapping list begins at +0x04.  Each node uses its virtual deleting
// destructor, as in the retail push-1 / vtable-slot-zero calls.

struct InputChunk
{
	virtual ~InputChunk();
	InputChunk *next;
};

struct UserParser
{
	virtual ~UserParser();
	UserParser *next;
};

struct Mapping
{
	virtual ~Mapping();
	Mapping *next;
};

struct DataChunkTableOfContents
{
	Mapping *m_list;
	int m_listLength;
	unsigned int m_nextID;
	bool m_headerOpened;

	~DataChunkTableOfContents()
	{
		Mapping *mapping = m_list;
		while (mapping != 0) {
			Mapping *next = mapping->next;
			delete mapping;
			mapping = next;
		}
	}
};

class DataChunkInput
{
	void *m_file;
	DataChunkTableOfContents m_contents;
	int m_fileposOfFirstChunk;
	UserParser *m_parserList;
	InputChunk *m_chunkStack;

public:
	~DataChunkInput();
};

DataChunkInput::~DataChunkInput()
{
	InputChunk *chunk = m_chunkStack;
	while (chunk != 0) {
		InputChunk *next = chunk->next;
		delete chunk;
		chunk = next;
	}
	m_chunkStack = 0;

	UserParser *parser = m_parserList;
	while (parser != 0) {
		UserParser *next = parser->next;
		delete parser;
		parser = next;
	}
}
