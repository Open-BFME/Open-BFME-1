// cl: /DNDEBUG /MD /EHsc
// Open-BFME: the this-0x20 contain companion's reaction at retail 0x0024CE60.
//
// IDENTITY IS UNKNOWN. It is NOT address-derived, and an earlier banner and
// commit message here claimed that it was; this note corrects them.
// `python3 tools/callers_of.py 0x0024CE60` finds no named caller -- only the
// anonymous ILT thunk 0x0001A31B reaches this body -- and find_emitter and
// name_oracle name no owner either.
//
// The emitted symbol `BfmeHostCK::bfmeReactCK(BfmeSrcCK *)` is an INHERITED
// PLACEHOLDER, not evidence. BfmeHostCK, bfmeReactCK and BfmeSrcCK belong to
// the retired generator's invented `Bfme*` family -- see
// docs/naming_evidence.md lines 243-244, which lists sibling spellings
// `BfmeHostZB` and `BfmeOwnVVE` as invented targets. The spelling survives
// only because the reverse/functions.csv row was landed under it, and renaming
// a matched row needs a separate retraction pass. The honest address-token
// form for this body is `Rva0024CE60::react`. Nothing in the image has been
// checked against the `BfmeHostCK`/`bfmeReactCK`/`BfmeSrcCK` names: the next
// reader must treat them as UNVERIFIED, not as recovered identity.
//
// What the body itself DOES prove: its receiver is the +0x20 companion of the
// object that owns the landed 0x0024BA90 and 0x0024CDB0 update members, which
// is the same pairing Rva0024CDB0::update spells from the other side as
// ((BfmeRvaCDB0Callback *)((char *)this + 0x20))->finish(member, 0).
//
// The TU-local shim types below are named from this address, not guessed: they
// assert only the offsets and vtable slots the bytes witness.
//
// Shape note for the next reader: the slot-17 finish call is ONE statement in
// a shared tail, not one per arm. Writing it inside each arm compiles the
// second arm's vftable load into EDX where retail has EAX -- that two-byte
// residue is what twenty-one earlier passes on this address were stuck behind.
// The explicit `else { return; }` is what lets both arms fall into that tail.
// The secondary base is still recomputed per arm: hoisting the cast above the
// branch computes `add esi,-0x20` once and breaks both arms.
class Rva0024CE60Thing;
class BfmeSrcCK;

// Reached through Rva0024CE60Owner's vslot 0x68; only its vslot 0x100 is called.
class Rva0024CE60Thing
{
public:
	virtual void bfmeSlot000T();
	virtual void bfmeSlot001T();
	virtual void bfmeSlot002T();
	virtual void bfmeSlot003T();
	virtual void bfmeSlot004T();
	virtual void bfmeSlot005T();
	virtual void bfmeSlot006T();
	virtual void bfmeSlot007T();
	virtual void bfmeSlot008T();
	virtual void bfmeSlot009T();
	virtual void bfmeSlot010T();
	virtual void bfmeSlot011T();
	virtual void bfmeSlot012T();
	virtual void bfmeSlot013T();
	virtual void bfmeSlot014T();
	virtual void bfmeSlot015T();
	virtual void bfmeSlot016T();
	virtual void bfmeSlot017T();
	virtual void bfmeSlot018T();
	virtual void bfmeSlot019T();
	virtual void bfmeSlot020T();
	virtual void bfmeSlot021T();
	virtual void bfmeSlot022T();
	virtual void bfmeSlot023T();
	virtual void bfmeSlot024T();
	virtual void bfmeSlot025T();
	virtual void bfmeSlot026T();
	virtual void bfmeSlot027T();
	virtual void bfmeSlot028T();
	virtual void bfmeSlot029T();
	virtual void bfmeSlot030T();
	virtual void bfmeSlot031T();
	virtual void bfmeSlot032T();
	virtual void bfmeSlot033T();
	virtual void bfmeSlot034T();
	virtual void bfmeSlot035T();
	virtual void bfmeSlot036T();
	virtual void bfmeSlot037T();
	virtual void bfmeSlot038T();
	virtual void bfmeSlot039T();
	virtual void bfmeSlot040T();
	virtual void bfmeSlot041T();
	virtual void bfmeSlot042T();
	virtual void bfmeSlot043T();
	virtual void bfmeSlot044T();
	virtual void bfmeSlot045T();
	virtual void bfmeSlot046T();
	virtual void bfmeSlot047T();
	virtual void bfmeSlot048T();
	virtual void bfmeSlot049T();
	virtual void bfmeSlot050T();
	virtual void bfmeSlot051T();
	virtual void bfmeSlot052T();
	virtual void bfmeSlot053T();
	virtual void bfmeSlot054T();
	virtual void bfmeSlot055T();
	virtual void bfmeSlot056T();
	virtual void bfmeSlot057T();
	virtual void bfmeSlot058T();
	virtual void bfmeSlot059T();
	virtual void bfmeSlot060T();
	virtual void bfmeSlot061T();
	virtual void bfmeSlot062T();
	virtual void bfmeSlot063T();
	virtual void bfmeMarkCK();	// vslot 0x100
};

// The BfmeSrcCK +0x1FC pointee; only its vslot 0x68 is called.
class Rva0024CE60Owner
{
public:
	virtual void bfmeSlot000O();
	virtual void bfmeSlot001O();
	virtual void bfmeSlot002O();
	virtual void bfmeSlot003O();
	virtual void bfmeSlot004O();
	virtual void bfmeSlot005O();
	virtual void bfmeSlot006O();
	virtual void bfmeSlot007O();
	virtual void bfmeSlot008O();
	virtual void bfmeSlot009O();
	virtual void bfmeSlot010O();
	virtual void bfmeSlot011O();
	virtual void bfmeSlot012O();
	virtual void bfmeSlot013O();
	virtual void bfmeSlot014O();
	virtual void bfmeSlot015O();
	virtual void bfmeSlot016O();
	virtual void bfmeSlot017O();
	virtual void bfmeSlot018O();
	virtual void bfmeSlot019O();
	virtual void bfmeSlot020O();
	virtual void bfmeSlot021O();
	virtual void bfmeSlot022O();
	virtual void bfmeSlot023O();
	virtual void bfmeSlot024O();
	virtual void bfmeSlot025O();
	virtual Rva0024CE60Thing *bfmeGetCK();	// vslot 0x68
};

// The this-0x20 secondary base; only its vslot 0x44 is called (slot 17).
class Rva0024CE60Sub
{
public:
	virtual void bfmeSlot000S();
	virtual void bfmeSlot001S();
	virtual void bfmeSlot002S();
	virtual void bfmeSlot003S();
	virtual void bfmeSlot004S();
	virtual void bfmeSlot005S();
	virtual void bfmeSlot006S();
	virtual void bfmeSlot007S();
	virtual void bfmeSlot008S();
	virtual void bfmeSlot009S();
	virtual void bfmeSlot010S();
	virtual void bfmeSlot011S();
	virtual void bfmeSlot012S();
	virtual void bfmeSlot013S();
	virtual void bfmeSlot014S();
	virtual void bfmeSlot015S();
	virtual void bfmeSlot016S();
	virtual void bfmeSlot017S();	// vslot 0x44, the shared-tail finish call
};

// The two non-virtual forwards are the landed members of the same this-0x20
// object: reverse/functions.csv rows for 0x0024BA90 and 0x0024CDB0, reached
// through the incremental-link thunks 0x0002633C and 0x0002DC31.
class BfmeRvaBA90Member;
class BfmeRvaCDB0Member;

class Rva0024BA90
{
public:
	void update(BfmeRvaBA90Member *member);
};

class Rva0024CDB0
{
public:
	void update(BfmeRvaCDB0Member *member);
};

class BfmeSrcCK
{
public:
	// Pads are never read by this body; each is named for the offset it starts
	// at, per the `char pad[N]` convention in docs/naming_evidence.md:66.
	unsigned char pad00[0x94];
	unsigned char m_bfmeFlagsCK;	// +0x94, tested against 0x20
	unsigned char pad95[0x167];
	Rva0024CE60Owner *m_bfmeOwnerCK;	// +0x1FC
	unsigned char pad200[0x14];
	int m_bfmeGuardCK;	// +0x214, early-out when nonzero
};

class BfmeHostCK
{
public:
	void bfmeReactCK(BfmeSrcCK *src);
};

void BfmeHostCK::bfmeReactCK(BfmeSrcCK *src)
{
	if (src->m_bfmeGuardCK != 0)
		return;

	Rva0024CE60Owner *owner = src->m_bfmeOwnerCK;
	Rva0024CE60Thing *thing;
	Rva0024CE60Sub *sub;

	if (owner != 0 && (thing = owner->bfmeGetCK()) != 0)
	{
		thing->bfmeMarkCK();
		sub = (Rva0024CE60Sub *)((char *)this - 0x20);
		((Rva0024BA90 *)sub)->update((BfmeRvaBA90Member *)src);
	}
	else if ((src->m_bfmeFlagsCK & 0x20) != 0)
	{
		sub = (Rva0024CE60Sub *)((char *)this - 0x20);
		((Rva0024CDB0 *)sub)->update((BfmeRvaCDB0Member *)src);
	}
	else
	{
		return;
	}

	sub->bfmeSlot017S();
}
