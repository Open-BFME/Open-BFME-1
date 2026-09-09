// cl: /DNDEBUG /MD /EHsc
// stlport

#include <vector>

class BfmeSubVE
{
public:
	void bfmeDropVE(void *what);
};

class DataChunkInput : public BfmeSubVE
{
public:
	bool parse(void *userData);
};

class DataChunkInfo
{
};

class AsciiString
{
public:
	AsciiString(void) : m_data(0) {}
	AsciiString(const AsciiString &source);
	~AsciiString();

private:
	void *m_data;
};

class LibraryMapsParser
{
public:
	LibraryMapsParser(void *lists, void *count, void *table, void *info);

	~LibraryMapsParser()
	{
		m_vftable = (void *)0x0107C7D0;
		m_table->bfmeDropVE(m_parser);
	}

private:
	void *m_vftable;
	DataChunkInput *m_table;
	void *m_parser;
	void *m_lists;
	int *m_count;
};

#pragma comment(linker, "/alternatename:??0LibraryMapsParser@@QAE@PAX000@Z=?d_00194050@@YAXXZ")

struct LibraryMaps
{
	char m_pad[0xc];
	std::vector<AsciiString> m_values;
};

class LibraryMapLists
{
public:
	bool readDataChunk(DataChunkInput &file, DataChunkInfo *info);

private:
	char m_pad[0x28];
	int m_count;
	LibraryMaps m_lists[1];
};

// ?readDataChunk@LibraryMapLists@@QAE_NAAVDataChunkInput@@PAVDataChunkInfo@@@Z
bool LibraryMapLists::readDataChunk(DataChunkInput &file, DataChunkInfo *info)
{
	std::vector<AsciiString> temporary[32];
	int count;
	LibraryMapsParser parser(temporary, &count, &file, info);

	if (!file.parse(0))
		return false;

	while (count > 0)
	{
		--count;
		int limit = m_count;
		if (count < limit)
		{
			LibraryMaps *list;
			if (count < 0 || count >= this->m_count)
				list = 0;
			else
				list = &m_lists[count];
			list->m_values.swap(temporary[count]);
		}
	}
	return true;
}
