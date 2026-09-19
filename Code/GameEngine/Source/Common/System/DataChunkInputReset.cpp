// cl: /DNDEBUG /MD /EHsc
// DataChunkInput::reset at retail 0x00102680.
// The adjacent clearChunkStack body and the DataChunkInput layout prove the
// linked stack at +0x1c and the first-chunk file offset at +0x14.

typedef int Int;

class ChunkInputStream
{
public:
	virtual Int read(void *data, Int size);
	virtual Int tell(void);
	virtual void absoluteSeek(Int position);
};

class InputChunk
{
public:
	virtual ~InputChunk();
	InputChunk *m_next;
};

class DataChunkInput
{
public:
	ChunkInputStream *m_file;
	char m_contents[0x10];
	Int m_fileposOfFirstChunk;
	void *m_parserList;
	InputChunk *m_chunkStack;

	void clearChunkStack()
	{
		InputChunk *chunk = m_chunkStack;
		while (chunk != 0)
		{
			InputChunk *next = chunk->m_next;
			delete chunk;
			chunk = next;
		}
		m_chunkStack = 0;
	}

	void reset();
};

void DataChunkInput::reset()
{
	clearChunkStack();
	m_file->absoluteSeek(m_fileposOfFirstChunk);
}
