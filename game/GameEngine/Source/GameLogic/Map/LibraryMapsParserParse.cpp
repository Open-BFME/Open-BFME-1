// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <vector>

#include "ascii_string.h"

class DataChunkInput
{
public:
	int readInt();
	AsciiString readAsciiString();
};

class DataChunkInfo;

class LibraryMapsParser
{
public:
	bool parse(DataChunkInput &file, DataChunkInfo *info);

private:
	char m_base[0xc];
	std::vector<AsciiString> *m_lists;
	int *m_count;
};

// The constructor installs 0x0109C030, whose slot 1 reaches this body through
// thunk 0x0002C74B. It reads one LibraryMaps chunk into the next vector slot.
// ?parse@LibraryMapsParser@@QAE_NAAVDataChunkInput@@PAVDataChunkInfo@@@Z
bool LibraryMapsParser::parse(DataChunkInput &file, DataChunkInfo *info)
{
	(void)info;
	std::vector<AsciiString> values;
	int count = file.readInt();
	if (count > 0)
	{
		values.reserve(count);
		do
		{
			values.push_back(file.readAsciiString());
			--count;
		} while (count > 0);
	}
	m_lists[(*m_count)++].swap(values);
	return true;
}
