// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__unguarded_partition<BfmeScoreEntry *, BfmeScoreEntry,
// BfmeScoreEntryLess>, retail 0x005724D0, 192 bytes.  Pointer comparator
// already named by the AptScoreScreen pin at 0x00570420; 16-byte iter_swap.

class Team;
class Player;
class BfmeScoreObject;

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

template <class ForwardIter1, class ForwardIter2>
inline void iter_swap(ForwardIter1 left, ForwardIter2 right)
{
	BfmeScoreEntry temporary = *left;
	*left = *right;
	*right = temporary;
}

template <class RandomAccessIter, class Tp, class Compare>
RandomAccessIter __unguarded_partition(RandomAccessIter first,
	RandomAccessIter last, Tp pivot, Compare comp)
{
	while (true)
	{
		while (comp(first, &pivot))
			++first;
		--last;
		while (comp(&pivot, last))
			--last;
		if (!(first < last))
			return first;
		iter_swap(first, last);
		++first;
	}
}

template BfmeScoreEntry *__unguarded_partition<BfmeScoreEntry *,
	BfmeScoreEntry, BfmeScoreEntryLess>(BfmeScoreEntry *, BfmeScoreEntry *,
	BfmeScoreEntry, BfmeScoreEntryLess);

}
