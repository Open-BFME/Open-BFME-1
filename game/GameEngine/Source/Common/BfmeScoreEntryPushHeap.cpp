// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__push_heap<BfmeScoreEntry *, int, BfmeScoreEntry,
// BfmeScoreEntryLess>, retail 0x00570E80.  The matched __adjust_heap at
// 0x00571C40 tails into this specialization through ILT 0x0001C819.

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
void __push_heap(RandomAccessIterator first, Distance holeIndex,
	Distance topIndex, Tp value, Compare comp)
{
	Distance parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex && comp(first + parent, &value))
	{
		*(first + holeIndex) = *(first + parent);
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	*(first + holeIndex) = value;
}

template void __push_heap<BfmeScoreEntry *, int, BfmeScoreEntry,
	BfmeScoreEntryLess>(BfmeScoreEntry *, int, int, BfmeScoreEntry,
	BfmeScoreEntryLess);

}
