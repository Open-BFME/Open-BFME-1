// The shared bucket helpers are reached through retail's ILT thunks: the index
// lookup is 0x000333C5 and the release is 0x00019574 (visible as the call
// targets at 0x0035CDF0 and 0x0035CE60). Both addresses are the matched
// gen-thunks ?j_000333c5@@YAXXZ / ?j_00019574@@YAXXZ in game/gen_small, so the
// reference has to carry those names; the thiscall shape (owner in ECX, one
// stack argument) and the int return of the lookup are read off the call sites.
extern void j_000333c5();
extern void j_00019574();

struct BfmeNodeXQ
{
	BfmeNodeXQ *m_bfmeNextXQ;
};

struct BfmeSlotXQ
{
	unsigned char m_bfmePadXQ[0x10];
	BfmeNodeXQ *m_bfmeHeadXQ;
};

class BfmeOwnerXQ
{
public:
	int bfmeMoveXQ(int from, void *key);
	int bfmeMoveXQ(BfmeOwnerXQ *source, int from);

	unsigned char m_bfmeHeadXQ[0xc];
	BfmeSlotXQ *m_bfmeTableXQ;
};

// __thiscall is not available in this compilation (MSVC rejects the keyword
// under the strict mode this TU builds with), so each thunk is reinterpreted as
// a member-function pointer of the owner through the same union pun the Miles
// TUs use (SampleStarter006B4090.cpp). MSVC folds the pun back into a direct
// call, so retail's "owner in ECX, one stack argument" shape is preserved.
//
// CAVEAT for the gate: at /Od the two bfmeMemberOf<> instantiations are emitted
// out of line (sections 3 and 5) even though nothing calls them. They are
// undeclared bodies the ledger does not claim, which is why a byte-clean
// alternative is preferred if one is ever found.
template <class M> inline M bfmeMemberOf(void (*fn)()) { union { void (*f)(); M m; } u; u.f = fn; return u.m; }

typedef int (BfmeOwnerXQ::*FindBucketIndex)(void *key);
typedef void (BfmeOwnerXQ::*TouchBucket)(int index);

int BfmeOwnerXQ::bfmeMoveXQ(int from, void *key)
{
	int to = (this->*bfmeMemberOf<FindBucketIndex>(j_000333c5))(key);

	if (to == -1)
		return from;

	BfmeSlotXQ *src = &m_bfmeTableXQ[from];
	BfmeNodeXQ *node = src->m_bfmeHeadXQ;

	src->m_bfmeHeadXQ = node->m_bfmeNextXQ;

	BfmeSlotXQ *dst = &m_bfmeTableXQ[to];

	node->m_bfmeNextXQ = dst->m_bfmeHeadXQ;
	dst->m_bfmeHeadXQ = node;

	(this->*bfmeMemberOf<TouchBucket>(j_00019574))(from);

	return to;
}

int BfmeOwnerXQ::bfmeMoveXQ(BfmeOwnerXQ *source, int from)
{
	BfmeSlotXQ *src = &source->m_bfmeTableXQ[from];
	int to = (this->*bfmeMemberOf<FindBucketIndex>(j_000333c5))(&src->m_bfmePadXQ[8]);

	if (to == -1)
		return to;

	BfmeSlotXQ *dst = &m_bfmeTableXQ[to];
	BfmeNodeXQ *node = src->m_bfmeHeadXQ;
	src->m_bfmeHeadXQ = node->m_bfmeNextXQ;

	node->m_bfmeNextXQ = dst->m_bfmeHeadXQ;
	dst->m_bfmeHeadXQ = node;

	(source->*bfmeMemberOf<TouchBucket>(j_00019574))(from);

	return to;
}
