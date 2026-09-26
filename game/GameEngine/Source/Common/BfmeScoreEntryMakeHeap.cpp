// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__make_heap<BfmeScoreEntry *, BfmeScoreEntryLess,
// BfmeScoreEntry, int>, retail 0x005727E0.  Two calls to the matched
// __adjust_heap at 0x00571C40 (ILT 0x0000CE0A).

class Player;

struct BfmeScoreObject
{
	char m_pad[0x18];
	int m_order;
};

struct BfmeScoreEntry
{
	BfmeScoreObject *m_object;
	Player *m_player;
	int m_secondary;
	int m_primary;
};

struct BfmeScoreEntryLess
{
	bool operator()(const BfmeScoreEntry *left,
		const BfmeScoreEntry *right) const;
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp);

template <class RandomAccessIterator, class Compare, class Tp, class Distance>
void __make_heap(RandomAccessIterator first, RandomAccessIterator last,
	Compare comp, Tp *, Distance *)
{
	Distance len = last - first;
	if (len < 2)
		return;
	Distance parent = (len - 2) / 2;
	for (;;)
	{
		__adjust_heap(first, parent, len, *(first + parent), comp);
		if (parent == 0)
			return;
		--parent;
	}
}

template void __make_heap<BfmeScoreEntry *, BfmeScoreEntryLess,
	BfmeScoreEntry, int>(BfmeScoreEntry *, BfmeScoreEntry *,
	BfmeScoreEntryLess, BfmeScoreEntry *, int *);

}
