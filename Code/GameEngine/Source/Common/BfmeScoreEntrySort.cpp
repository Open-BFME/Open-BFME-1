// cl: /DNDEBUG /MD /EHsc

// Score-screen ordering and the two STLport insertion-sort layers which use it.

class Team;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	int getRelationship( const Team *that ) const;
	bool isPlayerDead( void ) const;

public:
	char m_pad[ 0x230 ];
	Team *m_team;
};

class VictoryConditions
{
public:
	virtual void slot0( void );
	virtual void slot1( void );
	virtual void slot2( void );
	virtual void slot3( void );
	virtual void slot4( void );
	virtual void slot5( void );
	virtual void slot6( void );
	virtual void slot7( void );
	virtual void slot8( void );
	virtual bool hasAchievedVictory( Player *player );
};

extern VictoryConditions *TheVictoryConditions;

struct BfmeScoreObject
{
	char m_pad[ 0x18 ];
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
	bool operator()( const BfmeScoreEntry *left,
		const BfmeScoreEntry *right ) const;
};

void Rva00570CC0( BfmeScoreEntry *last, BfmeScoreEntry value,
	BfmeScoreEntryLess comp )
{
	BfmeScoreEntry *next = last - 1;
	while ( comp( &value, next ) )
	{
		*last = *next;
		last = next;
		--next;
	}
	*last = value;
}

void Rva00571AB0( BfmeScoreEntry *first, BfmeScoreEntry *last,
	BfmeScoreEntry *, BfmeScoreEntryLess comp )
{
	for ( BfmeScoreEntry *i = first; i != last; ++i )
		Rva00570CC0( i, *i, comp );
}

// Open-BFME5: STLport's score-entry heap adjustment at retail 0x00571C40.
// The comparator is pointer-based in this BFME specialization, while the
// heap stores complete 16-byte BfmeScoreEntry records.
namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __push_heap( RandomAccessIterator first, Distance holeIndex,
	Distance topIndex, Tp value, Compare comp );

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap( RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp value, Compare comp )
{
	Distance topIndex = holeIndex;
	Distance secondChild = 2 * holeIndex + 2;
	while ( secondChild < len )
	{
		if ( comp( first + secondChild,
			first + ( secondChild - 1 ) ) )
			--secondChild;
		*( first + holeIndex ) = *( first + secondChild );
		holeIndex = secondChild;
		secondChild = 2 * ( secondChild + 1 );
	}
	if ( secondChild == len )
	{
		*( first + holeIndex ) = *( first + ( secondChild - 1 ) );
		holeIndex = secondChild - 1;
	}
	__push_heap( first, holeIndex, topIndex, value, comp );
}

template void __adjust_heap<BfmeScoreEntry *, int, BfmeScoreEntry,
	BfmeScoreEntryLess>( BfmeScoreEntry *, int, int, BfmeScoreEntry,
	BfmeScoreEntryLess );

}
