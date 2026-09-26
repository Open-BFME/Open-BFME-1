// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

typedef int Int;

template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

struct Rva003691A0Pair
{
	void *m_first;
	void *m_second;
};

class Rva003691A0OwnedRecord
{
public:
	~Rva003691A0OwnedRecord();

private:
	std::vector<Rva003691A0Pair> m_pairs;
	Int m_unmodelled0C;
	StringBase<char> m_name;
};

Rva003691A0OwnedRecord::~Rva003691A0OwnedRecord()
{
}

class Rva0036B6B0OwnedPointerCollection
{
public:
	void clearOwnedRecords();

private:
	char m_unmodelled[ 8 ];
	std::vector<Rva003691A0OwnedRecord *> m_records;
};

void Rva0036B6B0OwnedPointerCollection::clearOwnedRecords()
{
	for( std::vector<Rva003691A0OwnedRecord *>::iterator it = m_records.begin(); it != m_records.end(); ++it )
		delete *it;

	m_records.clear();
}
