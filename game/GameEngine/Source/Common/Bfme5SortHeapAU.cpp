// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *left, const void *right, unsigned int count);

class BfmeNameAU
{
public:
	inline int bfmeCompare(const BfmeNameAU *other) const
	{
		int otherLength = other->m_bfmeData ? other->m_bfmeData->m_length : 0;
		const char *otherData = other->m_bfmeData ? other->m_bfmeData->m_data : "";
		int length = m_bfmeData ? m_bfmeData->m_length : 0;
		const char *data = m_bfmeData ? m_bfmeData->m_data : "";
		int count = length < otherLength ? length : otherLength;
		int order = _memicmp(data, otherData, count);

		if (order != 0)
			return order;

		return length - otherLength;
	}

private:
	struct Header
	{
		int m_references;
		unsigned short m_length;
		unsigned short m_capacity;
		char m_data[1];
	};

	Header *m_bfmeData;
	int m_bfmeUnused08;
	int m_bfmeUnused0C;
};

class BfmeRecAU
{
public:
	int m_bfmeTag;
	BfmeNameAU m_bfmeName;
	void *m_bfmeThing;
};

class BfmeCompAU
{
public:
	bool operator()(const BfmeRecAU *left, const BfmeRecAU *right) const
	{
		if ((left->m_bfmeThing == 0) ^ (right->m_bfmeThing == 0))
			return right->m_bfmeThing == 0;

		return left->m_bfmeName.bfmeCompare(&right->m_bfmeName) < 0;
	}

	int m_bfmeState;
};

template void _STL::sort_heap<BfmeRecAU **, BfmeCompAU>(BfmeRecAU **, BfmeRecAU **, BfmeCompAU);
