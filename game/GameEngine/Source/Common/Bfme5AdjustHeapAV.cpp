// cl: /DNDEBUG /MD
// Retail 0x00530200: byte-twin of ??$__adjust_heap@PAPAVBfmeRecAU@@HPAV1@VBfmeCompAU@@ at
// 0x005135F0 (Bfme5InsertionSort.cpp), instantiated for the OTHER comparator: the tail
// sift-up call goes through the BfmeCompAV specialization of __push_heap
// (thunk 0x0000FB37 -> 0x0052F4D0) instead of the BfmeCompAU one (thunk 0x00019B6E ->
// 0x00513190). Everything else -- the class shapes, the xor "exactly one has a thing"
// test, the _memicmp compare -- is identical to the twin.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);
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

	Header *m_bfmeData;					// +0x00
	int m_bfmeUnused08;
	int m_bfmeUnused0C;
};

class BfmeRecAU
{
public:
	int m_bfmeTag;						// +0x00
	BfmeNameAU m_bfmeName;					// +0x04
	void *m_bfmeThing;					// +0x10
};

class BfmeCompAV
{
public:
	bool operator()(const BfmeRecAU *left, const BfmeRecAU *right) const
	{
		if ((left->m_bfmeThing == 0) ^ (right->m_bfmeThing == 0))
			return right->m_bfmeThing == 0;

		return left->m_bfmeName.bfmeCompare(&right->m_bfmeName) < 0;
	}

	int m_bfmeState;					// +0x00
};

namespace _STL
{

template <class RandomAccessIter, class Distance, class Tp, class Compare>
void __push_heap(RandomAccessIter first, Distance holeIndex,
	Distance topIndex, Tp value, Compare comp)
{
	Distance parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex && comp(*(first + parent), value))
	{
		*(first + holeIndex) = *(first + parent);
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	*(first + holeIndex) = value;
}

template <class RandomAccessIter, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIter first, Distance holeIndex,
	Distance len, Tp value, Compare comp)
{
	Distance topIndex = holeIndex;
	Distance secondChild = 2 * holeIndex + 2;
	while (secondChild < len)
	{
		if (comp(*(first + secondChild), *(first + (secondChild - 1))))
			--secondChild;
		*(first + holeIndex) = *(first + secondChild);
		holeIndex = secondChild;
		secondChild = 2 * (secondChild + 1);
	}
	if (secondChild == len)
	{
		*(first + holeIndex) = *(first + (secondChild - 1));
		holeIndex = secondChild - 1;
	}
	__push_heap(first, holeIndex, topIndex, value, comp);
}

template void __adjust_heap<BfmeRecAU **, int, BfmeRecAU *, BfmeCompAV>(
	BfmeRecAU **, int, int, BfmeRecAU *, BfmeCompAV);

}
