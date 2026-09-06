// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: retail 0x00532DF0 (264 bytes) is a reloc-masked byte twin of the __partial_sort
// in Bfme5PartialSort.cpp (0x00515550) for another record/comparator pair; names re-tagged.

// Open-BFME5: _STL::__partial_sort<Rva00532DF0Rec **, int, Rva00532DF0Rec *, Rva00532DF0Comp>,
// retail 0x00515550, 264 bytes.

extern "C" __declspec(dllimport) int __cdecl _memicmp(
	const void *left, const void *right, unsigned int count);

class Rva00532DF0Name
{
public:
	inline int bfmeCompare(const Rva00532DF0Name *other) const
	{
		int otherLength = other->m_data ? other->m_data->m_length : 0;
		const char *otherData = other->m_data ? other->m_data->m_data : "";
		int length = m_data ? m_data->m_length : 0;
		const char *data = m_data ? m_data->m_data : "";
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

	Header *m_data;
	int m_unused08;
	int m_unused0C;
};

class Rva00532DF0Rec
{
public:
	int m_tag;
	Rva00532DF0Name m_name;
	void *m_thing;
};

class Rva00532DF0Comp
{
public:
	bool operator()(const Rva00532DF0Rec *left, const Rva00532DF0Rec *right) const
	{
		if ((left->m_thing == 0) ^ (right->m_thing == 0))
			return right->m_thing == 0;

		return left->m_name.bfmeCompare(&right->m_name) < 0;
	}

	int m_state;
};

namespace _STL
{

template <class RandomAccessIterator, class Compare, class Tp, class Distance>
void __make_heap(RandomAccessIterator first, RandomAccessIterator last,
	Compare comp, Tp *, Distance *);

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp);

template <class RandomAccessIterator, class Compare>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last,
	Compare comp);

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __partial_sort(RandomAccessIterator first, RandomAccessIterator middle,
	RandomAccessIterator last, Tp *, Compare comp)
{
	__make_heap(first, middle, comp, (Tp *)0, (Distance *)0);
	for (RandomAccessIterator i = middle; i < last; ++i)
	{
		if (comp(*i, *first))
		{
			Tp item = *i;
			*i = *first;
			__adjust_heap(first, (Distance)0,
				(Distance)(middle - first), item, comp);
		}
	}
	sort_heap(first, middle, comp);
}

template void __partial_sort<Rva00532DF0Rec **, int, Rva00532DF0Rec *, Rva00532DF0Comp>(
	Rva00532DF0Rec **, Rva00532DF0Rec **, Rva00532DF0Rec **, Rva00532DF0Rec **, Rva00532DF0Comp);

}
