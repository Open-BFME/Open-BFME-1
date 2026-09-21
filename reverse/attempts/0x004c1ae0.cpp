// ?rva004C1AE0Clone@PartitionFilterPossibleToAttack@@QBE?AURva004C1AE0Handle@@XZ
// partial score=0.33 date=2026-09-21
// Open-BFME: clone-and-wrap helper on PartitionFilterPossibleToAttack, retail 0x004C1AE0, 101 bytes.
//
// Same shape as the sibling 0x004B2470/0x004C1B60/0x0058D820 family already
// analysed in reverse/re_attempts.log (residue notes on 0x004B2470): a
// thiscall method returns a small handle struct by value (sret via
// [esp+0x18], `ret 4`) that owns a freshly `new`-ed copy of `*this`. The
// installed vtable at +0 of the new object is 0x010FD964, which
// reverse/symbols.csv resolves to ??_7PartitionFilterPossibleToAttack@@6B@
// (PartitionManager.cpp), and the landed real constructor at 0x004C12B0
// (PartitionManager.cpp:5598) establishes the exact field order BFME uses --
// AbleToAttackType at +0x04, const Object* at +0x08, CommandSourceType at
// +0x0C (reversed from the ZH header's declaration order m_obj,
// m_commandSource, m_attackType; see the "BFME declares these three the
// other way round" comment there). This body copies those same three
// fields directly from `this` into the new object with no call to
// 0x004C12B0, so it force-inlines a copy in a different call site rather
// than reusing that constructor -- matching the fully-inlined
// bfmeMakeVTE/bfmeCloneZW siblings.
//
// probe.py: 68 of 101 non-relocation bytes differ (ours compiles to 132
// bytes). Getting the SEH frame to appear at all (retail's push -1/push
// handler/fs:[0] chain, byte-exact through +0x14) needs a NAMED local
// Rva004C1AE0Handle whose `volatile` pointer member is set to 0 and then
// reassigned after the allocation -- exactly the "Follow-up" lever recorded
// for the 2-field sibling 0x004B2470 (reverse/re_attempts.log), which
// reaches 80/95 there. On this 3-field class it costs more: MSVC no longer
// applies NRVO to the mutated named local, so the tail becomes a full
// Rva004C1AE0Handle copy-construct-and-destroy (a second call plus a second
// epilogue) instead of retail's single direct store through the sret
// pointer. Tried and rejected this session: a plain `return
// Handle(new T(*this));` with no named local (76 B, clean tail, but drops
// the SEH frame entirely -- matches the "stateless is unreachable without a
// mutated local" wall the sibling notes describe); a `new T(a, b, c)` with
// three explicit constructor arguments instead of a copy constructor (145 B,
// worse -- the extra stack argument needs its own zero-guard slot, `sub
// esp,8` plus two `[esp+N],0` stores where retail has one); a
// non-member-level `PartitionFilterPossibleToAttack * volatile guard = 0;`
// local that is never read (84 B, drops the frame -- the guard has to be a
// field of the object that flows into the sret return, not an unrelated
// local, to be kept live); declaring `operator new` `throw()` (132 B, this
// IS in the banked form -- it removes a redundant EH-state=1 store that a
// throwing `operator new` produced on top of the missing-NRVO tail, taking
// 149/145 down to 132); and an explicit `__forceinline` copy constructor on
// Rva004C1AE0Handle (136 B, slightly worse than the implicit one). The
// missing-NRVO tail duplication looks like the next lever to chase -- some
// source shape that keeps the frame-triggering local mutation but still
// lets MSVC 7.1 construct directly into the sret slot.

void *__cdecl operator new(unsigned int n) throw();

class Object;
enum AbleToAttackType { ABLETOATTACK_INVALID = 0 };
enum CommandSourceType { CMDSOURCE_INVALID = 0 };

class PartitionFilter
{
public:
	virtual bool allow(Object *objOther) = 0;
};

struct Rva004C1AE0Handle
{
public:
	Rva004C1AE0Handle(void *p) : m_ptr(p) {}
	~Rva004C1AE0Handle();

	void * volatile m_ptr;
};

class PartitionFilterPossibleToAttack : public PartitionFilter
{
public:
	__forceinline PartitionFilterPossibleToAttack(const PartitionFilterPossibleToAttack &other)
		: m_attackType(other.m_attackType), m_obj(other.m_obj), m_commandSource(other.m_commandSource)
	{
	}

	virtual bool allow(Object *objOther);

	Rva004C1AE0Handle rva004C1AE0Clone() const;

	AbleToAttackType m_attackType;		// retail this+0x04
	const Object *m_obj;				// retail this+0x08
	CommandSourceType m_commandSource;	// retail this+0x0C
};

// ?rva004C1AE0Clone@PartitionFilterPossibleToAttack@@QBE?AURva004C1AE0Handle@@XZ
Rva004C1AE0Handle PartitionFilterPossibleToAttack::rva004C1AE0Clone() const
{
	Rva004C1AE0Handle result((void *)0);
	result.m_ptr = new PartitionFilterPossibleToAttack(*this);
	return result;
}
