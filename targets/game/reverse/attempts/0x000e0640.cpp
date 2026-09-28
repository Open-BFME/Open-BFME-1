// ?Rva000E0640@PlayerList@@QAEPAVTeam@@VAsciiString@@H@Z
// partial score=0.72 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc
//
// Address-keyed reconstruction of retail 0x000E0640, 897 bytes.  It replaces
// game/GameEngine/Source/GameLogic/Map/SidesListAddSideThunk.cpp, a naked
// __emit copy published under ?addSide@SidesList@@QAEXPBVDict@@@Z -- a name
// the body refutes on its own terms: the body ends `ret 8`, never reads ECX
// and never touches a Dict argument.
//
// IDENTITY.  Class PROVEN: the sole caller (0x0038F7B0, reached through ILT
// 0x0001BE82) loads the global 0x012ED748 -- ThePlayerList -- into ECX right
// before the call, and afterwards compares the result against
// [[[0x012ED748]+0x14]+0x230], which is exactly the tail this body computes
// at +0x02F8.  name_oracle --class PlayerList --offset 0x14 answers
// `m_players` (confidence 1.00, layout witness) and Zero Hour's PlayerList.h
// defines getNeutralPlayer() as m_players[0], so the tail is
// `getNeutralPlayer()->getDefaultTeam()`.  Player+0x230 is unwitnessed, so the
// accessor that reads it keeps the offset token.
//
// The METHOD name is not proven.  Zero Hour's PlayerList::validateTeam
// (PlayerList.cpp:294-305) opens with the same TheTeamFactory->findTeam(owner)
// and closes with the same getNeutralPlayer()->getDefaultTeam(), but this fork
// splices in a split on '/', a "Plyr" prefix strip, a "Faction" prefix strip
// and a walk of the SidesList side array followed by its team record, and it
// takes a second, never-read 4-byte parameter (the caller pushes ebx) that the
// released header does not declare.  So the name keeps the address token per
// docs/naming_evidence.md: ?Rva000E0640@PlayerList@@QAEPAVTeam@@VAsciiString@@H@Z
//
// MEASURED 2026-09-28 (tools/probe.py, this file, this pass): ours = 912 bytes
// against retail's 897, 571 non-relocation bytes differ, 0.922 of instructions
// match once registers and constants are normalised, and 19 structural
// differences remain with the first divergence at +0x65.  The previous banked
// state measured 859 / 628 / 0.792 / 43 structural.
//
// WHAT THIS PASS CHANGED, each measured, four real defects and four levers:
//
//  1. DEFECT, semantic.  The two-argument findTeam was called
//     findTeam(teamName, sideFaction).  Retail pushes the teamOwner slot
//     (E-0x30) first and the teamName slot (E-0x28) second (+0x0244 /
//     +0x023F), so the call is findTeam(teamOwner, teamName).  sideFaction is
//     filled from the playerFaction key and is not a team name at all.
//
//  2. DEFECT, structure.  The first test was `if (!team) { ... } done: return
//     team;`, which shares one epilogue and therefore emits a single `ret 8`.
//     Retail has TWO `ret 8` sites (+0x005D and +0x0337) and its first test is
//     `test esi,esi; je +0x0060` -- the FOUND path falls through and the
//     not-found block is the jump target.  `if (team) return team;` followed by
//     the block reproduces that polarity and the second epilogue exactly.  The
//     body now matches retail instruction for instruction from +0x0000 through
//     the whole early-return block at +0x003B..+0x005D, including
//     `sub esp,0x30`, the single `push esi`, the immediate spill of `this`, the
//     immediate `mov dword ptr [esp+0x40],0` EH-state store, and the
//     `push ebx; push edi` at the block entry +0x0060.  0.792 -> 0.841.
//
//  3. DEFECT, root cause of the whole old residue.  The old body reached the
//     side array through a RANGE-CHECKED accessor,
//     `side >= 0 && side < n ? &m_sides[side] : 0`.  Retail evaluates the bound
//     at the CALL SITE, in the loop head, and only then forms the address, so
//     the frame and the register allocation come out right:
//        i < TheSidesList->getNumSides() ? TheSidesList->getSide(i) : 0
//     with `getSide` unchecked.  This is the single change that removed the
//     `xor ebx,ebx` constant register: with the checked accessor the compiler
//     kept the induction variable in ebp, which left ebx free to hold the
//     literal 0, which forced the two-push prologue, the 7-byte immediate
//     EH-state-6 stores and the 0x2c frame.  With the bound at the call site
//     the index is memory-resident, ebx is taken by the EH state (`mov bl,6` at
//     +0x010D, stored with `mov byte [esp+0x44],bl`), ebp disappears from the
//     function entirely, the frame is 0x30 and the epilogue matches.
//     0.841 -> 0.918.  Measured FAILED alternatives: adding the `i >= 0 &&`
//     half as well (0.865 -- it loses the strength reduction and the ebx
//     constant comes straight back), `volatile int i` (0.804), hoisting
//     getNumSides() into a local (0.903), `unsigned` bound (0.914), the
//     checked accessor moved to a separate `if` statement (no change).
//
//  4. LEVER, measured.  The outer walk is a `for` header, not a `while` with a
//     trailing `++i`: retail's latch increments the index inside the
//     compare-and-store group (+0x02D6 `inc ecx`, +0x02DC store, +0x02E4 `jl`).
//     0.841 -> 0.861 on its own, and 893 -> 895 bytes.
//
//  5. LEVER, measured.  The two guards share one `continue` target in retail
//     (+0x014F and +0x0167 both land on the release chain at +0x02BC), which
//     `if (!exists || !sideFaction.startsWith("Faction", 7)) continue;` states
//     directly.  0.918 -> 0.922, 19 structural differences.
//
// WHAT IS STILL DIFFERENT, all of it compiler-internal allocation rather than
// algorithm.  The prologue, the early-return epilogue, the block entry, the
// split/set/dtor sequence, the EH state sequence, the inner team-record walk
// and the final epilogue all match; 19 structural sites remain:
//
//   * FRAME SLOT ORDER, two objects transposed.  Ours allocates the split
//     prefix at E-0x34 and the "Faction" value at E-0x38; retail allocates
//     E-0x38 and E-0x34.  The presence byte is at E-0x39 in BOTH, one byte
//     below the prefix, so the allocator agrees on the bottom of the frame and
//     disagrees on the middle.  Declaration order does not move it: swapping
//     `prefix`/`exists`, hoisting `playerName` above the `for`, splitting the
//     declaration of `sideFaction` and reordering `faction`/`sideName` were each
//     measured and each changed nothing (0.922 either way).
//   * THE SPLIT RESULT.  Retail keeps the callee's returned slot pointer in
//     esi and reaches the second half with `add esi,4` (+0x0081/+0x0092);
//     this build reloads the frame address twice.  Spelled as
//     `BfmePairEL *halves = &Rva00194810(...); halves->first; halves->second;
//     halves->~BfmePairEL();` the pointer DOES land in esi and the body drops
//     to 903 bytes / 560 diffs, but MSVC then emits `lea eax,[esi+4]` where
//     retail has `add esi,4`, so shape falls to 0.906 and structural
//     differences rise to 23.  Kept the by-value form (fewest structural
//     differences); the pointer form is the alternative to try next.
//   * THE LOOP'S TWO INDUCTION VARIABLES ARE SWAPPED.  Retail keeps the byte
//     OFFSET in edi (saved to the pair slot E-0x18 at +0x0108, restored at
//     +0x029C) and the plain INDEX in its own frame slot E-0x2C.  This build
//     keeps the index in edi and puts the offset in a second frame slot at
//     E-0x28, so sideName/teamName/faction shift down one dword.  The latch
//     shape is otherwise identical (+0x02CF reload, +0x02DB `inc`, +0x02DC
//     `add ...0x18`, +0x02DF `cmp`, two stores, +0x02E9 `jl`).
//   * THE NEGATIVITY TEST.  Retail's loop head tests the offset twice --
//     `test edi,edi; jl` and `cmp ecx,[eax+0x28]; jge` (+0x0110/+0x0118) -- so
//     its source bound had an `i >= 0` half.  Adding that half here measures
//     WORSE (0.865, frame 0x2c, ebx constant back) because it defeats the
//     strength reduction, so the single-bound spelling is kept and the test
//     stays absent.
//   * REGISTER CHOICES inside the inner walk: retail loads the base pointer
//     into ecx and derives esi from it (`mov ecx,[ecx]` / `shl eax,4` /
//     `mov edi,eax` / `lea esi,[edi+ecx+0xc]`), this build keeps the base in
//     edi and derives the dict pointer with `lea ecx,[esi+edi+0xc]`.  Same
//     instructions, different registers.
//   * THE TAIL reuses edx where this build needs one more register
//     (`mov edx,[esp+0x38]; mov eax,[edx+0x14]` against
//     `mov eax,[esp+0x38]; mov ecx,[eax+0x14]`).
//   * Retail emits the hotpatch no-op `mov edi,edi` at +0x010E, right after
//     `mov bl,6`; no source spelling tried here reproduces it.
//
// THE TEAM-RECORD ELEMENT IS PROVEN, not inferred, and that killed the older
// `blocked` verdict's `layout/team-pool-0x63C` blocker.  The MATCHED row
//   ?writeTeams@SidesList@@QAEXAAVDataChunkOutput@@@Z  0x00193F60  180 bytes
//   game/GameEngine/Source/GameLogic/Map/SidesListWriteTeams.cpp
// walks this exact member -- SidesList+0x63C, its own ledger note reads "BFME
// SidesList team pool writer at this plus 0x63c" -- with the identical
// free-list walk and the identical per-element re-read of the start pointer.
// It spells the element `BfmeTeamInfoSlot` and it is 0x10 bytes with the chain
// index at +0x00 and the Dict at +0x0C, which is exactly what retail's
// `movsx eax,word [eax]` on the base (+0x01D0), `shl eax,4` (+0x01E7) and
// `+0xC` stride encode.  0x630/0x64C are the TeamsInfoRec pair
// Rva0019BA40TeamRecAppend.cpp owns; 0x63C is the FIRST one's m_teams start
// pointer, so the "0x10 vs 0x18" caveat compared two different members and no
// conflict is left to reconcile.  The Dict member stays 4 raw bytes: the
// 0x14-byte BfmeStringPresenceDict shim exists only to pad SidesInfo to its
// 0x18 side stride and would destroy the proven 0x10 stride here.
//
// CORRECTED CALLEE CONTRACT (measured from the image, the old note was wrong):
// 0x0004A8E5 is `ret 4`, not `ret 8` -- retail pushes TWO arguments and then
// runs `add esp,8` at +0x007E itself, which is why a one-argument declaration
// is right.
//

// Callee contracts, read from the retail image (ret N from each callee's own
// terminal instruction):
//    0x000273EF -> 0x000F8290  Team *TeamFactory::findTeam(const AsciiString &)   ret 4
//    0x0004A8E5 -> 0x00194810  bfme split of a name on '/'; the pair comes back
//                                 through the caller-allocated slot pushed leftmost,
//                                 and the callee also returns that slot in EAX
//    0x000444EA -> 0x000DFB20  the split pair's dtor (two releaseBuffer calls)
//    0x00887C90               AsciiString::set(const AsciiString &)              ret 4
//    0x008875A0               AsciiString::startsWith(const char *, int)          ret 8
//    0x00888F90               StringBase(const StringBase &, int start, int len)  ret 0xc
//    0x00887940               releaseBuffer                                     ret
//    0x00009304 -> 0x00090290  StaticNameKey::key() -- a plain `ret`; the caller
//                                 keeps the bool* it already pushed for the Dict
//                                 fetch that follows
//    0x0002FF6D -> 0x00068580  Dict::getAsciiString(int key, bool *exists) -- a
//                                 CLASS return, so the caller pushes the
//                                 destination leftmost, then key, then exists
//    0x000220C5 -> 0x0005FEB0  AsciiString::compare(const AsciiString &)          ret 4
//    0x000391EE -> 0x000F7F40  Team *TeamFactory::findTeam(const AsciiString &,
//                                 const AsciiString &)                           ret 8
//
// Literals: 0x1084218 "Plyr" (4) at +0x00AF and 0x108420C "Faction" (7) at
// +0x0157.  Two ledger pins were added for this body, both checked with
// tools/pin_consistency.py (verdict: consistent, and --check stays OK):
//   ?TheKey_playerFaction@@3VStaticNameKey@@B -> 0x012A7938
//   ??1BfmePairEL@@QAE@XZ                     -> 0x000444EA
//

typedef int Int;

// Retail's header: the length is a 16-bit field, which is what makes the
// inlined getLength() read a word rather than a dword.
struct BfmeAsciiStringHeader
{
	int references;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

template <typename T>
class StringBase
{
	friend class AsciiString;

	StringBase() : m_data(0) {}
	// Retail inlines AsciiString's forwarders, so a caller that builds a
	// string from another one encodes these base bodies directly.
	StringBase(const StringBase<T> &source, int start, int len);

	~StringBase() { releaseBuffer(); }
	void releaseBuffer();

public:
	void set(const StringBase &other);
	bool startsWith(const char *prefix, int len) const;
	int compare(const StringBase &other) const;
	int getLength() const { return m_data ? m_data->length : 0; }

private:
	BfmeAsciiStringHeader *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &source, int start, int len)
		: StringBase<char>(source, start, len) {}
	~AsciiString() {}
	void releaseBuffer() { StringBase<char>::releaseBuffer(); }
	bool operator==(const AsciiString &other) const { return compare(other) == 0; }
};

// The class-returning Dict lookup.  A local of exactly this type is what makes
// the caller push its own address as the return slot, so every destination of
// a fetch below is spelled BfmeStringPresenceValue.
class BfmeStringPresenceValue : public AsciiString
{
public:
	// MSVC 7.1 does not inherit constructors, and the two destinations that a
	// fetch does not fill are built with the substring constructor.
	BfmeStringPresenceValue(const AsciiString &source, int start, int len)
		: AsciiString(source, start, len) {}
};

// The value retail 0x00194810 splits and returns.  The name is proven by the
// matched row at 0x00194810 itself: ?Rva00194810@@YA?AUBfmePairEL@@ABVBfmeWordEL@@@Z
// names both the return class and the argument class, so the pair's dtor call
// at +0x00A8 is ?~BfmePairEL@@YAEXXZ.
class BfmeWordEL : public AsciiString
{
};

struct BfmePairEL
{
	AsciiString first;
	AsciiString second;
	~BfmePairEL();
};

BfmePairEL __cdecl Rva00194810(const BfmeWordEL &name);

class StaticNameKey
{
public:
	int key() const;

	// 0x012A75B8 and 0x012A75C0, per the pin notes on those two rows.
	static StaticNameKey TheKey_teamOwner;
	static StaticNameKey TheKey_teamName;
	// 0x012A7938 and 0x012A7918: dir32_addresses.csv already places
	// ?TheKey_playerFaction@@3VStaticNameKey@@B at the first and
	// ?TheKey_playerName@@3VStaticNameKey@@A at the second, both from bodies
	// that read the same two keys off a SidesInfo dict.
	static StaticNameKey TheKey_playerFaction;
	static StaticNameKey TheKey_playerName;
};

// The three pushes retail makes for 0x00068580 are a two-argument call with a
// class return: the destination is pushed leftmost, then the key, then the
// presence pointer, and ECX is the Dict.  The class and the return type are
// the established spelling (pin ?getAsciiString@BfmeStringPresenceDict@@QBE?
// ?AVBfmeStringPresenceValue@@HPA_N@Z -> 0x0002FF6D).
class BfmeStringPresenceDict
{
private:
	char m_data[0x14];

public:
	BfmeStringPresenceValue getAsciiString(int key, bool *exists) const;
};

class SidesInfo
{
public:
	BfmeStringPresenceDict *getDict() { return &m_dict; }

private:
	char m_prefix[4];
	BfmeStringPresenceDict m_dict;
};

// The team record this body walks.  The shape is PROVEN, not inferred: the
// MATCHED body ?writeTeams@SidesList@@QAEXAAVDataChunkOutput@@@Z at 0x00193F60
// (game/GameEngine/Source/GameLogic/Map/SidesListWriteTeams.cpp, 180 bytes,
// matched) walks the SAME member -- SidesList+0x63C -- with the identical
// `register Int index = m_teams[0].next; ... index = teams[index].next;`
// free-list walk and the identical per-element re-read of the start pointer.
// Its ledger note says so in as many words.  That body spells the element
// `BfmeTeamInfoSlot` and it is 0x10 bytes with the chain index at +0x00 and the
// Dict at +0x0C, which is exactly what retail's `shl eax,4` / `+0xc` stride
// arithmetic encodes here.  The earlier verdict's blocker (an unproven stride
// of 0x10 against the 0x630 member's 0x18) compared two DIFFERENT members:
// 0x630/0x64C are the TeamsInfoRec pair, 0x63C is the first one's m_teams
// start pointer, so there is no conflict left.
//
// The Dict member is spelled as 4 raw bytes because the 0x14-byte
// BfmeStringPresenceDict shim above exists only to pad SidesInfo to retail's
// 0x18 side stride; embedding it here would destroy the proven 0x10 stride.
struct BfmeTeamInfoSlot
{
	short next;
	short previous;
	short reserved;
	short free;
	Int generation;
	char m_dict[4];
};

class SidesList
{
public:
	int getNumSides() { return m_numSides; }

	// Retail does NOT range-check inside an accessor: it tests the index (as a
	// byte offset, so the negativity test is on the offset) and the count at
	// the CALL SITE (+0x0110 `test edi,edi` / +0x0118 `cmp ecx,[eax+0x28]`),
	// and only then forms &m_sides[index].  Spelling the bound at the call
	// site instead of inside a checked accessor is what reproduces that.
	SidesInfo *getSide(int side)
	{
		return &m_sides[side];
	}

	// +0x63C, the vector start pointer the team-record walk indexes -- the same
	// member and the same spelling as the landed writeTeams body.  The cast is
	// load-bearing: `this + 0x63C` would scale by sizeof(SidesList).
	BfmeTeamInfoSlot *getTeamRecords()
	{
		return *(BfmeTeamInfoSlot **)((char *)this + 0x63C);
	}

private:
	char m_prefix[0x28];
	int m_numSides;
	SidesInfo m_sides[32];
};

class Team
{
};

class TeamFactory
{
public:
	Team *findTeam(const AsciiString &name);
	Team *findTeam(const AsciiString &name, const AsciiString &other);
};

extern TeamFactory *TheTeamFactory;
extern SidesList *TheSidesList;

class Player
{
public:
	// Player+0x230 has no layout witness in the oracle, so the accessor keeps
	// the offset token rather than asserting a member name.
	Team *Rva000E0230() { return *(Team **)((char *)this + 0x230); }
};

class PlayerList
{
public:
	// ?Rva000E0640@PlayerList@@QAEPAVTeam@@VAsciiString@@H@Z
	Team *Rva000E0640(AsciiString owner, Int unused);

	// name_oracle --class PlayerList --offset 0x14 answers m_players with
	// confidence 1.00 (layout witness), which is the member the tail at
	// +0x02FC reads.
	char m_prefix[0x14];
	Player *m_players[32];
};

// ?Rva000E0640@PlayerList@@QAEPAVTeam@@VAsciiString@@H@Z
Team *PlayerList::Rva000E0640(AsciiString owner, Int unused)
{
	Team *team = TheTeamFactory->findTeam(owner);
	if (team)
		return team;

	{
		AsciiString prefix;
		// Retail never initialises the presence byte: the first fetch always
		// writes it, and the second passes a null pointer.  It is declared next
		// to the split prefix because retail allocates it one byte below that
		// object (E-0x39 against E-0x38).
		bool exists;
		{
			BfmePairEL halves = Rva00194810(static_cast<BfmeWordEL &>(owner));
			prefix.set(halves.first);
			owner.set(halves.second);
		}

		// Retail tests the FIRST half of the split (the frame slot the first
		// set() writes, E-0x38) and jumps straight to the tail when it does not
		// start with "Plyr", so the whole side walk is one guarded block.
		if (prefix.startsWith("Plyr", 4))
		{
			BfmeStringPresenceValue playerName(prefix, 4, prefix.getLength() - 4);

			// A `for` header, not a `while` with a trailing `++i`: retail's latch
			// increments the index INSIDE the compare-and-store group
			// (+0x02D6 `inc ecx` / +0x02DC store / +0x02E4 `jl`), which is the
			// for-header shape.  Measured: shape 0.841 -> 0.861, 893 -> 895 bytes.
			for (int i = 0; i < TheSidesList->getNumSides(); ++i)
			{
				// The bound is spelled at the CALL SITE, not inside a checked
				// accessor: retail evaluates it in the loop head (+0x0107
				// `cmp edi,ecx` / +0x0111 reload / +0x0115 `lea`) and only
				// then forms &m_sides[index].  An `i >= 0 &&` half as well
				// was measured and is worse (shape 0.922 -> 0.865): it loses
				// the strength reduction and the ebx constant comes back.
				SidesInfo *side = (i < TheSidesList->getNumSides()
					? TheSidesList->getSide(i)
					: 0);

				BfmeStringPresenceValue sideFaction = side->getDict()->getAsciiString(
					StaticNameKey::TheKey_playerFaction.key(), &exists);
				// One `continue` target for both guards, exactly as retail has:
				// the `!exists` branch (+0x014F) and the `!startsWith` branch
				// (+0x0167) both land on the release chain at +0x02BC.
				if (!exists || !sideFaction.startsWith("Faction", 7))
					continue;

				BfmeStringPresenceValue faction(sideFaction, 7,
					sideFaction.getLength() - 7);
				if (!(faction == playerName))
					continue;

				BfmeStringPresenceValue sideName = side->getDict()->getAsciiString(
					StaticNameKey::TheKey_playerName.key(), 0);

				for (int index = TheSidesList->getTeamRecords()[0].next;
					index != 0;
					index = TheSidesList->getTeamRecords()[index].next)
				{
					BfmeStringPresenceValue teamOwner =
						reinterpret_cast<BfmeStringPresenceDict *>(
							TheSidesList->getTeamRecords()[index].m_dict)
							->getAsciiString(StaticNameKey::TheKey_teamOwner.key(), &exists);
					if (teamOwner == sideName)
					{
						BfmeStringPresenceValue teamName =
							reinterpret_cast<BfmeStringPresenceDict *>(
								TheSidesList->getTeamRecords()[index].m_dict)
								->getAsciiString(StaticNameKey::TheKey_teamName.key(),
									&exists);
						// Retail pushes the teamOwner slot (E-0x30) first
						// and the teamName slot (E-0x28) second, so the
						// two-argument findTeam takes (owner, name) in
						// that order.  The previous banked body passed
						// sideFaction here, which no Dict key in this
						// body ever fills.
						Team *found = TheTeamFactory->findTeam(
							(const AsciiString &)teamOwner,
							(const AsciiString &)teamName);
						if (found)
						{
							// The one exit that skips the neutral default: the
							// whole cleanup chain is emitted inline and jumps
							// to the shared epilogue.
							team = found;
							goto done;
						}
					}
				}
			}
		}

		team = m_players[0]->Rva000E0230();
	}

done:
	return team;
}
