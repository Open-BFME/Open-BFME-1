// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: score-screen linear insert over 16-byte BfmeScoreEntry,
// retail 0x00573980, 133 bytes.  The matched unguarded insert at 0x00570CC0
// and the pinned pointer comparator at 0x00570420 prove the specialization;
// copy_backward is the 16-byte POD helper reached through ILT 0x0002DBE1.

class Team;
class Player
{
public:
	int getRelationship(const Team *that) const;
	bool isPlayerDead(void) const;
	char m_pad[0x230];
	Team *m_team;
};

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

void Rva00570CC0(BfmeScoreEntry *last, BfmeScoreEntry value,
	BfmeScoreEntryLess comp);

namespace _STL
{

struct random_access_iterator_tag
{
};

BfmeScoreEntry *BfmeCopyBackward00570FC0(BfmeScoreEntry *first,
	BfmeScoreEntry *last, BfmeScoreEntry *result,
	const random_access_iterator_tag &tag, int *distance);

void Rva00573980(BfmeScoreEntry *first, BfmeScoreEntry *last,
	BfmeScoreEntry val, BfmeScoreEntryLess comp)
{
	if (comp(&val, first))
	{
		random_access_iterator_tag tag;
		BfmeCopyBackward00570FC0(first, last, last + 1, tag, (int *)0);
		*first = val;
	}
	else
	{
		Rva00570CC0(last, val, comp);
	}
}

}
