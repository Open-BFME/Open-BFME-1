// cl: -GX- /MD
// stlport

#include <algorithm>

// Retail calls the comparator value itself, so this specialization takes a
// function pointer rather than the stateful functors used by the other Q4 sorts.
typedef bool (__cdecl *Q4Compare00483F70)(int, int);

template const int &_STL::__median<int, Q4Compare00483F70>(
	const int &, const int &, const int &, Q4Compare00483F70);

template int *_STL::__unguarded_partition<int *, int, Q4Compare00483F70>(
	int *, int *, int, Q4Compare00483F70);

class BfmeNameAU
{
public:
	inline int bfmeCompare(const BfmeNameAU *other) const
	{
		int otherLength = other->m_data ? other->m_data->length : 0;
		const char *otherData = other->m_data ? other->m_data->data : "";
		int length = m_data ? m_data->length : 0;
		const char *data = m_data ? m_data->data : "";
		int count = length < otherLength ? length : otherLength;
		int order = _memicmp(data, otherData, count);

		if (order != 0)
			return order;

		return length - otherLength;
	}

private:
	struct Header
	{
		int references;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;
	int m_unused08;
	int m_unused0C;
};

class BfmeRecAU
{
public:
	int m_tag;
	BfmeNameAU m_name;
	void *m_thing;
};

#define Q4_BFME_COMPARATOR(Name)                                              \
	struct Name                                                                \
	{                                                                          \
		bool operator()(const BfmeRecAU *left, const BfmeRecAU *right) const     \
		{                                                                      \
			if ((left->m_thing == 0) ^ (right->m_thing == 0))                    \
				return right->m_thing == 0;                                       \
			return left->m_name.bfmeCompare(&right->m_name) < 0;                 \
		}                                                                      \
		int m_state;                                                           \
	}

Q4_BFME_COMPARATOR(Q4Sort005156D0);
Q4_BFME_COMPARATOR(Q4Sort00533470);

template BfmeRecAU *const &_STL::__median<BfmeRecAU *, Q4Sort005156D0>(
	BfmeRecAU *const &, BfmeRecAU *const &, BfmeRecAU *const &, Q4Sort005156D0);
template BfmeRecAU **_STL::__unguarded_partition<BfmeRecAU **, BfmeRecAU *, Q4Sort005156D0>(
	BfmeRecAU **, BfmeRecAU **, BfmeRecAU *, Q4Sort005156D0);

template BfmeRecAU *const &_STL::__median<BfmeRecAU *, Q4Sort00533470>(
	BfmeRecAU *const &, BfmeRecAU *const &, BfmeRecAU *const &, Q4Sort00533470);
template BfmeRecAU **_STL::__unguarded_partition<BfmeRecAU **, BfmeRecAU *, Q4Sort00533470>(
	BfmeRecAU **, BfmeRecAU **, BfmeRecAU *, Q4Sort00533470);
