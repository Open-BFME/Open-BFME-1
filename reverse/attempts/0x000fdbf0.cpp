// ?rva000fdbf0@@YG_NPBVObject@@PBVCommandSet@@0@Z
// partial score=0.3 date=2026-09-21
// cl: /DNDEBUG /MD

// Retail 0x000FDBF0, 444 bytes. Free function (no ECX `this` at all: the
// object pointer arrives as the first of three stack arguments, `ret 0xc`),
// called through a table entry that also reaches a class ctor/dtor pair
// (Bfme5BasedListCtor.cpp) sharing the same image region, but the calling
// convention does not match a thiscall virtual method, so that table hit is
// not trusted as an owner identity (vtable_lookup's own caveat).
//
// Two calls are proven Object members by their already-landed mangled names
// (Object.cpp): getCommandSetString() const and hasUpgrade(const
// UpgradeTemplate*) const. That fixes param0 as `const Object *`. Param0's
// field at +0x1f0 is a singly-linked list of "candidate" pointers; each
// candidate+0xc holds a second vtable-having object resolved through two
// chained virtual calls (slot+0x28 then the result's slot 0, an out-param
// AsciiString getter) and compared against param1's own AsciiString field at
// +0x20 -- this proves param1 carries a name at +0x20, matching CommandSet's
// shape elsewhere in this codebase, but param1 is kept address-derived since
// the two vtable-having objects in the +0x1f0 chain are unidentified.
//
// The second half looks up TheControlBar->findCommandSet(name) and scans its
// (up to 20) command buttons via CommandSet::getCommandButton, resolving an
// upgrade requirement through the same BfmeCommandButtonResolveILT /
// bfmeTopLU pattern used elsewhere in this codebase, and checking it against
// param2 (a second `const Object *`, passed to Object::hasUpgrade) -- so this
// is a 3-argument predicate: (const Object *owner, const CommandSet *,
// const Object *upgradeOwner) -> bool, most likely "can upgradeOwner's
// command buttons satisfy commandSet's requirement for owner". Ported
// straight-line with goto labels matching retail hex offsets because the
// branch topology (early-outs, a match-vs-scan counter split, several
// shared failure tails) is dense enough that restructuring risks silently
// changing it.

typedef int Int;
typedef bool Bool;

class AsciiString
{
public:
	int compare(const AsciiString &that) const;

private:
	void *m_data;
};

class UpgradeTemplate;

class Object
{
public:
	const AsciiString &getCommandSetString() const;
	Bool hasUpgrade(const UpgradeTemplate *upgrade) const;

private:
	unsigned char m_unmodelled000[0x1F0];
	void *m_commandSetCandidates; // +0x1f0: singly-linked list of candidates
};

struct Rva000FDBF0Candidate
{
	Rva000FDBF0Candidate *m_next; // +0
	unsigned char m_unmodelled04[8];
};

class Rva000FDBF0Resolver
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0A();
	virtual Rva000FDBF0Resolver *slot0B(); // vtbl+0x2c... placeholders up to +0x28
};

// A minimal chained-virtual interface covering exactly the two calls made
// through candidate+0xc: slot+0x28 (10) resolves to a second object, whose
// own slot 0 fills an out-param AsciiString.
class Rva000FDBF0Named
{
public:
	virtual void namedSlot00(AsciiString *out);
};

class Rva000FDBF0CandidateIface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Rva000FDBF0Named *slot0A(); // vtbl+0x28
};

class CommandButton
{
public:
	unsigned char m_unmodelled00[0x10];
	Int m_kind; // +0x10
	unsigned char m_unmodelled14[4];
	Int m_flags18; // +0x18
	unsigned char m_unmodelled1C[8];
	void *m_upgradePair; // +0x24
};

class CommandSet
{
public:
	CommandButton *getCommandButton(Int index) const;

private:
	unsigned char m_unmodelled00[0x20];
	AsciiString m_name; // +0x20
};

class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name) const;
};

extern ControlBar *TheControlBar;

Rva000FDBF0CandidateIface *bfmeCheckCW(Object *self); // retail 0x000220C5 -> 0x5feb0 compare thunk site, arg-address helper
Bool bfmeCheckFH(void *arg);                          // retail 0x0003E80B
Bool bfmeBlocked985C(Int arg);                        // retail 0x0000BA37
void *rva0000205cc(CommandButton *button, void *arg); // BfmeCommandButtonResolveILT::resolve, retail 0x000205CC
void *rva00020824(void *arg);                          // retail 0x00020824
Bool rva0001f780(void *self, void *arg);               // retail 0x0001F780
Bool rva000235bf(void *arg);                            // retail 0x000235BF
Bool rva00007b4e(void *arg);                            // retail 0x00007B4E

// ?rva000fdbf0@@YG_NPBVObject@@PBVCommandSet@@0@Z (address-derived; not landed)
Bool __stdcall rva000fdbf0(const Object *owner, const CommandSet *set, const Object *upgradeOwner)
{
	AsciiString scratch;
	Int matchCount;
	Int slotIndex;
	Bool hadUpgradeBit;
	void *resolved;

	if (owner == 0)
		return false;

	if (set == 0)
	{
		if (upgradeOwner != 0)
			goto L31;
		return false;
	}

L31:
	if (set != 0)
		goto scanCandidates;

scanCandidates:
	{
		Bool matched = false;
		if (set == 0)
			goto afterCandidateScan;

		Rva000FDBF0Candidate *node =
			*(Rva000FDBF0Candidate **)((const unsigned char *)owner + 0x1F0)
				? *(Rva000FDBF0Candidate **)((const unsigned char *)owner + 0x1F0)
				: 0;
		if (node == 0)
			goto afterCandidateScan;

		while (node != 0)
		{
			Rva000FDBF0CandidateIface *base =
				*(Rva000FDBF0CandidateIface **)((unsigned char *)node + 0xC);
			Rva000FDBF0Named *named = base->slot0A();
			if (named != 0)
			{
				named->namedSlot00(&scratch);
				matched = (scratch.compare(*(const AsciiString *)((const unsigned char *)set + 0x20)) == 0);
			}
			if (matched)
				return true;
			node = node->m_next;
		}
	}

afterCandidateScan:
	{
		const AsciiString &ownerSetName = owner->getCommandSetString();
		const CommandSet *found = TheControlBar->findCommandSet(ownerSetName);
		if (found == 0)
			return false;

		matchCount = 0;
		slotIndex = 0;
		hadUpgradeBit = (upgradeOwner != 0);

		while (slotIndex < 0x14)
		{
			CommandButton *button = found->getCommandButton(slotIndex);
			if (button == 0)
				return false;

			if (hadUpgradeBit)
				goto checkKind3;

			if (button->m_kind == 3)
				goto kind3;
			if (button->m_kind != 1)
				return false;

			resolved = rva0000205cc(button, upgradeOwner ? (void *)upgradeOwner : 0);
			if (!bfmeCheckFH(resolved))
				return false;

			if (((button->m_flags18 >> 6) & 1) != 0)
			{
				if (button->m_upgradePair == 0)
					return false;
				if (*(Int *)((unsigned char *)button->m_upgradePair + 4) != 1)
					goto notSingleUpgrade;

				if (upgradeOwner == 0)
					return false;
				if (!upgradeOwner->hasUpgrade((const UpgradeTemplate *)button->m_upgradePair))
					return false;

				resolved = rva00020824(button);
				if (hadUpgradeBit)
					goto kind3;

				{
					void *name = rva0000205cc(button, resolved);
					if (!rva00007b4e(name))
						return true;
					return false;
				}
			}

		kind3:
			return true;

		notSingleUpgrade:
			{
				Int upgradeCount = *(Int *)((unsigned char *)button->m_upgradePair + 4);
				if (upgradeCount != 0)
					return false;
				void *thing = rva00020824(button->m_upgradePair);
				if (!rva000235bf(thing))
					goto kind3;
				return false;
			}

		checkKind3:
			if (button->m_kind != 0x2C)
				return false;
			if (matchCount == slotIndex)
				goto kind3;
			++matchCount;
			++slotIndex;
			continue;

			++slotIndex;
			continue;
		}
	}

	return false;
}
