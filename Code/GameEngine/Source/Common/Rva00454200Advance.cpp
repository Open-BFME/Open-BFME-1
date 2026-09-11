// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <set>

class AsciiString
{
public:
	~AsciiString()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
	void *m_data;
};

bool operator<(const AsciiString &left, const AsciiString &right);

class DataChunkInput
{
public:
	unsigned char bfmeReadByte();
	int readInt();
	AsciiString readAsciiString();
};

struct DataChunkInfo
{
	char m_label[8];
	unsigned short m_version;
};

struct Rva00454200Element
{
	void refresh();
	bool refresh(DataChunkInput &file, DataChunkInfo *info);

private:
	unsigned char m_firstFlag;
	unsigned char m_secondFlag;
	unsigned char m_thirdFlag;
	char m_padding;
	int m_value;
	std::set<AsciiString> m_strings;
};

class Rva00454200Cursor
{
public:
	void advance();

private:
	char m_padding[0x0C];
	Rva00454200Element *m_elements;
	unsigned int m_index;
};

void Rva00454200Cursor::advance()
{
	Rva00454200Element *element = m_elements + m_index++;
	element->refresh();
}

bool Rva00454200Element::refresh(DataChunkInput &file, DataChunkInfo *info)
{
	m_firstFlag = file.bfmeReadByte() ? true : false;
	m_secondFlag = file.bfmeReadByte() ? true : false;
	if (info->m_version >= 1)
	{
		m_thirdFlag = file.bfmeReadByte() ? true : false;
		m_value = file.readInt();
	}
	else
	{
		m_thirdFlag = true;
		m_value = -1;
	}

	std::set<AsciiString> strings;
	int count = file.readInt();
	while (count > 0)
	{
		strings.insert(file.readAsciiString());
		--count;
	}
	m_strings.swap(strings);
	return true;
}
