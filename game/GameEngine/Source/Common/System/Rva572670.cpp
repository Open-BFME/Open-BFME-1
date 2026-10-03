// cl: /DNDEBUG /MD /EHsc

// The 93-byte body at retail 0x00572670. IDENTITY IS NOT RECOVERED -- the name
// and the 16-byte record type carry address-derived placeholders. No named
// caller reaches it, so nothing in the image spells out what it is; what the
// bytes DO prove is a shape:
//
//   - a 16-byte element type (the trailing `sar ecx,4` on a pointer difference
//     fixes the size exactly),
//   - a by-value 16-byte parameter forwarded field-by-field into the outgoing
//     argument block (retail reads four consecutive incoming slots and writes
//     them straight to [esp+0..0xC] after `sub esp,0x10`, never through a
//     register-allocated local),
//   - one element assigned from *first to *result before the forwarding call,
//   - and a call through incremental-link thunk 0x0000CE0A to 0x00571C40 with
//     (first, 0, last - first, the record, one trailing scalar).

class Rva572670Record
{
public:
	int m_a;
	int m_b;
	int m_c;
	int m_d;
};

struct BfmeScoreObject;
class Player;
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
		Distance len, Tp value, Compare comp);
}

void rva572670(Rva572670Record *first, Rva572670Record *last, Rva572670Record *result,
	Rva572670Record value, int extra)
{
	*result = *first;
	_STL::__adjust_heap<BfmeScoreEntry *, int, BfmeScoreEntry,
		BfmeScoreEntryLess>((BfmeScoreEntry *)first, 0, (int)(last - first),
			*(BfmeScoreEntry *)&value, *(BfmeScoreEntryLess *)&extra);
}
