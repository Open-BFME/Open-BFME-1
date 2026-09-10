// cl: /DNDEBUG /MD /EHsc
// BFME writes the nested LibraryMapLists and LibraryMaps chunks from this record array.

class AsciiString
{
public:
	AsciiString(void) : m_data(0) {}
	AsciiString(const AsciiString &source);
	~AsciiString();

private:
	void *m_data;
};

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short version);
	void closeDataChunk();
	void writeInt(int value);
	void writeAsciiString(const AsciiString &value);
};

struct LibraryMaps
{
	char m_pad[0xc];
	AsciiString *m_first;
	AsciiString *m_last;
	AsciiString *m_capacity;
};

class LibraryMapLists
{
private:
	char m_pad[0x28];
	int m_count;
	LibraryMaps m_lists[1];

public:
	void writeDataChunk(DataChunkOutput &output);
};

// ?writeDataChunk@LibraryMapLists@@QAEXAAVDataChunkOutput@@@Z
void LibraryMapLists::writeDataChunk(DataChunkOutput &output)
{
	output.openDataChunk("LibraryMapLists", 1);
	int listCount = m_count;
	int index = 0;
	if (listCount > 0)
	{
		LibraryMaps *cursor = m_lists;
		do
		{
			output.openDataChunk("LibraryMaps", 1);
			LibraryMaps *list;
			if (index < 0 || index >= m_count)
				list = 0;
			else
				list = cursor;
			output.writeInt(list->m_last - list->m_first);
			AsciiString *last = list->m_last;
			for (AsciiString *value = list->m_first; value != last; ++value)
				output.writeAsciiString(*value);
			output.closeDataChunk();
			++index;
			++cursor;
		} while (index < listCount);
	}
	output.closeDataChunk();
}
