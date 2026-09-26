// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <vector>

struct BfmeRva44E60Input
{
	int m_first;
	int m_second;
};

struct BfmeRva44E60Record
{
	BfmeRva44E60Record(void);
	BfmeRva44E60Record(const BfmeRva44E60Record &other);

	int m_value;
	int m_first;
	int m_second;
	int m_unused;
};

class Rva00244E60
{
public:
	void add(BfmeRva44E60Input *input, int value, int *output);

	char m_head[0x12c];
	_STL::vector<BfmeRva44E60Record> m_records;
};

void Rva00244E60::add(BfmeRva44E60Input *input, int value, int *output)
{
	BfmeRva44E60Record record;
	record.m_first = input->m_first;
	record.m_second = input->m_second;
	record.m_value = value;
	m_records.push_back(record);
	*output = (int)m_records.size() - 1;
}
