// cl: /EHs-c-

#include <vector>

struct Rva009A2030Pair
{
	void *m_first;
	void *m_second;
};

class Rva009A2030OwnedRecord
{
public:
	~Rva009A2030OwnedRecord();
	Rva009A2030OwnedRecord *scalarDelete(unsigned flags);

private:
	void releaseContents();
	std::vector<Rva009A2030Pair> m_pairs;
};

void __cdecl operator delete(void *);

Rva009A2030OwnedRecord *Rva009A2030OwnedRecord::scalarDelete(unsigned flags)
{
	this->~Rva009A2030OwnedRecord();
	if (flags & 1)
		::operator delete(this);
	return this;
}

// The retail wrapper at 0x0006B630 has no recovered public spelling. This
// helper carries its exact thiscall scalar-delete shape under an address alias.
void ForceRva009A2030OwnedRecordDeletingDestructor()
{
	Rva009A2030OwnedRecord value;
}
