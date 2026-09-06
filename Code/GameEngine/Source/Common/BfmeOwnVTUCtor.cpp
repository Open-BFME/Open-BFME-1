// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: BfmeOwnVTU's constructor (0x009CC220, 90 B). Vtable pin
// ??_7BfmeOwnVTU@@6B@,0x01143B3C already names the class (see
// tools/vtable_lookup.py 0x01143B3C); slot 0 is a scalar dtor at 0x009CC200
// distinct from Win32BIGFileSystem's own destructor pair, so BfmeOwnVTU is a
// standalone class, not proven to derive from ArchiveFileSystem/
// Win32BIGFileSystem despite the adjacent vtable slots -- IDENTITY IS NOT
// RECOVERED beyond the address-derived pins already on record
// (?bfmeApplyVTU@BfmeOwnVTU@@QAEXH@Z, 0x009CC020).
//
// Retail zeroes four dwords at +4/+8/+0xC/+0x10 immediately after the vptr
// store, then calls bfmeInit1182() (already matched, no args) and
// this->bfmeApplyVTU(state) with an SEH frame around both calls. The frame
// only appears when a member needs unwind cleanup on a partially constructed
// object, so the four words are modeled as a member whose default ctor
// inlines (matching the zero-store shape) but whose destructor stays
// out-of-line (declared, not defined here) to force that unwind path.

void bfmeInit1182(void);

// Three words with a real destructor -- forces the SEH unwind frame retail
// shows, and the "this" stash to [esp+4] lands right after this subobject
// finishes construction, matching the per-subobject EH progress marker MSVC
// emits once a base/member with a nontrivial destructor completes.
// Trivial 3-word POD (no destructor, needs no unwind protection).
class BfmeOwnVTUHead
{
public:
	BfmeOwnVTUHead()
	{
		m_a = 0;
		m_b = 0;
		m_c = 0;
	}

private:
	void *m_a;
	void *m_b;
	void *m_c;
};

// One word with a real destructor -- the EH progress marker (the "this"
// stash to [esp+4]) is emitted right when this member starts constructing,
// which lands after the trivial head above and before this word's own
// zero-store, matching retail's placement.
class BfmeOwnVTUTail
{
public:
	BfmeOwnVTUTail()
	{
		m_extra = 0;
	}
	~BfmeOwnVTUTail();

private:
	void *m_extra;
};

class BfmeOwnVTU
{
public:
	BfmeOwnVTU(int state);
	virtual ~BfmeOwnVTU();

	void bfmeApplyVTU(int state);

private:
	BfmeOwnVTUHead m_head;	// +0x4 .. +0xc
	BfmeOwnVTUTail m_tail;	// +0x10
};

BfmeOwnVTU::BfmeOwnVTU(int state)
{
	bfmeInit1182();
	bfmeApplyVTU(state);
}
