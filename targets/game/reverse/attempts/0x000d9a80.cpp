// ?update@Player@@QAEXXZ
// partial score=0.78 date=2026-09-27
// model=opencode/space-bunny-free
// 520/551 bytes emitted, shape 0.781, 32 structural differences (was 551 B,
// shape 0.754, 33, 407 non-reloc).  Blockers are listed in the comment below.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport


#define Matrix4x4 Matrix4
#include "PreRTS.h"

#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/Team.h"
#include "Common/MessageStream.h"
#include "GameLogic/AI.h"
#include "GameLogic/AIPlayer.h"
#include "GameLogic/GameLogic.h"

// ---------------------------------------------------------------------------
// ?update@Player@@QAEXXZ -- BFME's own body, retail 0x000D9A80, 551 bytes.
// Reconstructed from the retail disassembly; the readable copy lives in
// game/GameEngine/Source/Common/RTS/Player.cpp.  This file is the standalone
// evidence copy.
//
// PROVEN IDENTITY
//   The only caller is PlayerList::update (0x000DF2D0, 32 bytes, matched at
//   game/GameEngine/Source/Common/RTS/PlayerListUpdate.cpp) which reaches this
//   body through ILT 0x0004771C; the lift name ?update@Player@@QAEXXZ and the
//   full 551-byte boundary (ret at +0x226, add esp,0x20) both check out.
//
// MEASURED (probe.py, model=opencode/space-bunny-free, 2026-09-27):
//   520/551 bytes emitted (retail 551), shape 0.781, 32 structural
//   differences, 405 non-reloc differing bytes (was 551 B, 0.754, 33, 407).
//   The readable copy in Player.cpp measures the same.
//
// WHAT THIS SEAT FIXED (all measured, all in the readable copy)
//  1. The pending key is BFME's StringBase<char> handle, NOT the vendored
//     Zero Hour AsciiString.  This is the one blocker the earlier seats
//     called a header problem, and it is not: the Zero Hour AsciiString this
//     TU includes (Common/AsciiString.h on the cl: line's include path) is a
//     bare `char *m_text` with an EMPTY inline destructor, so a copy made from
//     it is elided whole -- no copy call, no release call, and a str() that
//     returns the handle itself instead of the characters inside it.  BFME's
//     AsciiString is `class AsciiString : public StringBase<char>` whose single
//     member is a `Header *` (int ref_count; unsigned short length, capacity;
//     T data[1]), so the characters are at handle+8 -- exactly retail's
//     `lea ebp,[eax+8]` at +0x00B5.  Declaring the handle as it is (see
//     BfmeUpdateStringHandle below) makes MSVC emit retail's copy call
//     (0x00887B60, one stack slot, ret 4, at +0x00AA), its null test with the
//     static empty string fallback, its `movsx`/lea/add hash loop, and the
//     release call (0x00887940, at +0x00E4).  It also flipped the frame:
//     `this` now lives in ebp (push ebp; mov ebp,ecx) as at retail +0x0018,
//     where before this seat it was in ebx.  See
//     docs/analysis/ascii_string_layout.md and inputs/reference/shims/
//     stringbaseascii/Common/AsciiString.h: the inline str() specialization
//     is the established pattern, and an `extern char n[]` fallback was
//     rejected because nothing in this build defines it (probe only compiles,
//     so it would only have broken the real link).
//  2. The bucket count is in ELEMENTS.  Retail shifts the 32-bit pointer
//     difference right by two twice (+0x00A7 and +0x00F5); an earlier seat had
//     removed the shift.  On the 64-bit pointer type the expression compiles
//     to `sar reg,4`, i.e. a scan that starts sixteen buckets too low, so the
//     difference is now taken on 32-bit pointer values.
//
// KNOWN BLOCKERS FOR THE NEXT SEAT (none of these is a spelling problem)
//  1. AIPlayer::update is retail vtable slot 5 (call [eax+0x14]).  The vendored
//     ZH header puts it at slot 3 (call [eax+0x0C]) because BFME's AIPlayer
//     base chain has two more leading virtual slots.  Proof: retail's
//     AISkirmishPlayer vtable 0x01096FB0 has computeSuperweaponTarget at slot
//     4, onStructureProduced at 8 and buildSpecificAITeam at 9 -- the header's
//     relative order shifted by a constant +2.  The TU-local slot view reaches
//     the right offset but the load lands in ecx, not eax.
//  2. MessageStream::appendMessage(GameMessage::Type) is retail vtable slot 13
//     (call [eax+0x34]); the header emits slot 10, and the TU-local slot view
//     puts the base in edx, not eax.
//  3. The SEH prologue ORDER.  Retail is `push -1; push handler; mov eax,fs:0;
//     push eax; mov fs:[0],esp` (the scope-table form, handler 0x00FF9DB8) and
//     this TU still gets `mov eax,fs:0; push -1; push 0`, so retail's function
//     carries a scope table and this one does not.  Retail's single state store
//     is the -1 at +0x01DD, immediately before the team-list destructor, so
//     only ONE object in retail's body needs unwinding.
//  4. Retail spills `this` at [esp+0x18] (+0x0024) before the AI branch and
//     reloads it at [esp+0x20] (+0x010F) after the char pointer has clobbered
//     ebp.  Nothing in the source forces those two stores.
//  5. The countdown block is 3 instructions shorter than retail: retail emits
//     mov ecx,eax; dec ecx; mov eax,ecx; test eax,eax; mov [esi+8],ecx (+0x005A
//     .. +0x0064), this body emits dec eax; mov [edi+8],eax.  The tested
//     value and the stored value are the same expression, so MSVC folds the
//     copy; retail tested a second copy.
//  6. The key address is formed twice (+0x005D in esi, +0x0080 in edi) where
//     retail forms it once (+0x0066 in edi) and pushes that register twice.
//     Writing the address into a local does not stop MSVC rematerialising it.
//  7. The bucket scan reloads [ebx+4] each turn (retail +0x0105) instead of
//     hoisting it, and retail's `div` bound is a first computation that the
//     loop bound recomputes; this body CSEs both.
//  8. 31 bytes are missing overall, mostly in the tail: retail's epilogue runs
//     the inlined std::list destructor loop with _M_deallocate (+0x01E5 .. 
//     +0x0212) where this body's list temp is released by a shorter path.
// ---------------------------------------------------------------------------

// The instance list link retail walks with ?_bfme_nextInInstanceList.
class BfmeTeamInstanceLink
{
public:
	BfmeTeamInstanceLink *_bfme_nextInInstanceList();
};

// The team-prototype object whose instance list is walked: retail reads
// TeamPrototype+0x274 for the head.
class BfmePlayerTeamView
{
public:
	unsigned char m_unmodelled_000[0x0c];
	void *m_head;

	void updateGenericScripts();					///< retail 0x000F1430 via ILT 0x00048671
};
class BfmePlayerTeamInstanceIterator;

struct BfmePlayerTeamPrototypeInstances
{
	unsigned char m_unmodelled_000[0x274];
	BfmePlayerTeamView *m_teamInstanceList;
};

class BfmePlayerTeamInstanceIterator
{
public:
	BfmePlayerTeamInstanceIterator(BfmePlayerTeamView *head) : m_cur(head) { }

	Bool done() const { return m_cur == NULL; }
	BfmePlayerTeamView *cur() const { return m_cur; }

	void advance()
	{
		if (m_cur)
			m_cur = (BfmePlayerTeamView *)
				((BfmeTeamInstanceLink *)m_cur)->_bfme_nextInInstanceList();
	}

	private:
	BfmePlayerTeamView *m_cur;
	Int m_unmodelled;
};

//=============================================================================
// ?update@Player@@QAEXXZ -- BFME's own body, retail 0x000D9A80, 551 bytes.
// The Zero Hour body that stood here had three extra blocks BFME does not
// have (the energy brown-out check, the academy-stat poll) and no pending
// table, so it is replaced rather than extended.  Every offset in the views
// below is read straight out of that body:
//
//   this+0x1D8, this+0x1EC  the two string-keyed int maps an expired
//                         pending key is copied into (retail calls the
//                         map<StringBase,AsciiString>::operator[] ILT
//                         0x0000B271 -> 0x000D97B0 twice, +0x1EC first)
//   this+0x200            the pending table itself: a hash table whose
//                         buckets the begin helper 0x000D0A30 (ILT
//                         0x0000CFE5) scans for the first live entry and
//                         hands back as an {entry, table} out pair
//   this+0x288            m_playerTeamPrototypes, copied to the stack before
//                         the walk so the walk cannot be disturbed
//   this+0x29E            m_logicalRetaliationModeEnabled
//
// A pending node is {next, key handle, countdown}: the walk follows +0x00,
// the count it decrements is +0x08, and the key both map inserts and the
// restart hash are taken from +0x04.

// BFME's static empty string, retail ?n@@3PADA at 0x0010738B: the fallback
// the inlined StringBase<char>::str() returns for a null handle.  A named
// object rather than a literal because MSVC folds a literal's first byte and
// would then delete the branch retail keeps.
static char BfmeUpdateEmptyString[1] = { 0 };

// BFME's StringBase<char>-shaped string handle, as this body proves it: one
// pointer to a {ref_count, length, capacity, data[+8]} header.  Retail copies
// the pending key through the StringBase copy constructor (0x00887B60, one
// stack slot, ret 4), reads its characters at handle+8 with the static empty
// string as the null fallback (0x0010738B) and releases it through
// ?releaseBuffer@BFMERetailAsciiString@@AAEXXZ (0x00887940).  The vendored
// Zero Hour AsciiString this TU includes is a bare char* with an empty
// destructor, so it can spell neither the copy nor the release.  Declared here,
// 4 bytes wide, so the node below keeps the retail +0x04 key slot and the map
// insert still takes its address.
class BfmeUpdateStringHandle
{
public:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	BfmeUpdateStringHandle(const BfmeUpdateStringHandle &source);	///< retail 0x00887B60, ret 4
	~BfmeUpdateStringHandle() { releaseBuffer(); }					///< retail 0x00887940

	// Retail inlines the whole accessor: the null test, the +8 character
	// offset and the static empty string in one expression.
	const char *str() const { return m_data ? m_data->data : BfmeUpdateEmptyString; }

private:
	void releaseBuffer();											///< retail 0x00887940

	Header *m_data;
};

struct BfmePendingNode;

// What the begin helper hands back: the first live node, and the table it
// came from (retail reloads the table from this pair rather than from `this`).
struct BfmePendingCursor
{
	BfmePendingNode *m_entry;
	const void *m_table;
};

struct BfmePendingNode
{
	BfmePendingNode *m_next;			///< +0x00 chain retail walks
	BfmeUpdateStringHandle m_key;		///< +0x04 key both map inserts use
	UnsignedInt m_framesLeft;			///< +0x08 the countdown
};

// STLport hash table header: element count, bucket array, one past its end.
struct BfmePendingTable
{
	UnsignedInt m_count;
	BfmePendingNode **m_buckets;
	BfmePendingNode **m_bucketEnd;

	void bfmeBeginEntry(BfmePendingCursor *out);		///< retail 0x000D0A30 via ILT 0x0000CFE5
};

// BFME's map<AsciiString,int> -- the same COMDAT the landed
// BfmeThingEZCMaps.cpp reaches, so the same ILT and the same int* result.
struct BfmePlayerUpdateMap
{
	int *insert(void *key);							///< retail 0x000D97B0 via ILT 0x0000B271

private:
	UnsignedByte m_unreconstructed_000[0x14];
};

struct BfmePlayerUpdateFields
{
	UnsignedByte m_unreconstructed_000[0x1D8];
	BfmePlayerUpdateMap m_expiredKeys;					///< retail this+0x1D8
	BfmePlayerUpdateMap m_expiredValues;				///< retail this+0x1EC
	BfmePendingTable m_pending;						///< retail this+0x200
	UnsignedByte m_unreconstructed_20C[0x29E - 0x20C];
	Bool m_logicalRetaliationModeEnabled;				///< retail this+0x29E
};

// TU-local slot views (see game/GameEngine/Source/Common/RTS/Player.cpp):
// retail calls AIPlayer::update at vtable slot 5 ([eax+0x14]) and
// MessageStream::appendMessage(Type) at slot 13 ([eax+0x34]); the vendored
// headers emit slots 3 and 10, so both are reached by slot, asserting only
// the slot and not the name.
class BFMEAIPlayerVirtuals
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
};
struct BFMEPlayerAIView
{
	char data[0x220];
	BFMEAIPlayerVirtuals *ai;
};
class BfmeUpdateMessageStreamSlots
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual GameMessage *slot34(GameMessage::Type type) = 0;
};

struct BfmePlayerTeamListFields
{
	UnsignedByte m_unreconstructed_000[0x288];
	Player::PlayerTeamList m_playerTeamPrototypes;		///< retail this+0x288
};

struct BfmePlayerUpdateGlobalData
{
	UnsignedByte m_unreconstructed_000[0x126C];
	Bool m_clientRetaliationModeEnabled;				///< retail GlobalData+0x126C
};

#pragma comment(linker, "/alternatename:?bfmeBeginEntry@BfmePendingTable@@QAEXPAUBfmePendingCursor@@@Z=?j_0000cfe5@@YAXXZ")
#pragma comment(linker, "/alternatename:?insert@BfmePlayerUpdateMap@@QAEXPAXPAH@Z=?j_0000b271@@YAXXZ")
#pragma comment(linker, "/alternatename:?updateGenericScripts@BfmePlayerTeamView@@QAEXXZ=?j_00048671@@YAXXZ")
#pragma comment(linker, "/alternatename:?_bfme_nextInInstanceList@BfmeTeamInstanceLink@@QAEPAV1@XZ=?j_00022a70@@YAXXZ")
#pragma comment(linker, "/alternatename:??0BfmeUpdateStringHandle@@QAE@ABV0@@Z=??0GameSpyGroupRoom@@QAE@ABV0@@Z")
#pragma comment(linker, "/alternatename:?releaseBuffer@BfmeUpdateStringHandle@@QAE@XZ=?releaseBuffer@BFMERetailAsciiString@@AAEXXZ")

void Player::update()
{
	BfmePlayerUpdateFields *fields = (BfmePlayerUpdateFields *)this;

	// The vendored header lands m_ai at +0x150; BFME keeps the AIPlayer at
	// +0x220 (see repairStructuresAt and friends in game Player.cpp).  Retail
	// calls it through vtable slot 5; the header emits slot 3.
	BFMEAIPlayerVirtuals *ai = ((BFMEPlayerAIView *)this)->ai;
	if (ai)
		ai->slot14();

	// Age the pending table.  Retail takes the first live entry, walks the
	// chain from it, and when the chain runs out picks the next start bucket
	// from a hash of the key it stopped on -- so one frame never has to touch
	// the whole table.
	BfmePendingCursor cursor;
	fields->m_pending.bfmeBeginEntry(&cursor);
	BfmePendingNode *node = cursor.m_entry;
	while (node != 0)
	{
		UnsignedInt framesLeft = node->m_framesLeft;
		if (framesLeft != 0)
		{
			UnsignedInt nextCount = framesLeft - 1;
			node->m_framesLeft = nextCount;
			if (nextCount == 0)
			{
				// Retail forms the key address once (retail +0x0066) and
				// pushes that same value for both map inserts.
				BfmeUpdateStringHandle *key = &node->m_key;
				fields->m_expiredValues.insert(key);
				*fields->m_expiredKeys.insert(key) = (int)node;
			}
		}
		// Successor: the chain link, or -- when the chain runs out -- the
		// first live bucket at or after hash(key) % bucketCount + 1.  Both
		// paths land on the same countdown, so the scan result is the node
		// the loop body ages next, never a node it skips.
		BfmePendingNode *next = node->m_next;
		if (next == 0)
		{
			// Restart bucket: hash the key the walk stopped on and take the
			// first live bucket at or after hash % bucketCount + 1.
			UnsignedInt hash = 0;
			{
				BfmeUpdateStringHandle key(node->m_key);
				for (const char *p = key.str(); *p != 0; ++p)
					hash = hash * 5 + (UnsignedInt)(int)(signed char)*p;
			}
			// Retail measures the bucket array in elements: it subtracts the
			// two bucket pointers and shifts the 32-bit difference right by
			// two, once for the modulo bound (retail +0x00A0) and again for
			// the scan bound (+0x00F5).  The difference is taken on 32-bit
			// pointer values because that is the width retail shifts; on the
			// 64-bit pointer type it is a shift by four and the scan starts
			// sixteen buckets too low.
			const Int bucketCount = ((Int)(UnsignedInt)
				fields->m_pending.m_bucketEnd - (Int)(UnsignedInt)fields->m_pending.m_buckets) >> 2;
			for (UnsignedInt i = hash % bucketCount + 1; i < (UnsignedInt)bucketCount; ++i)
			{
				next = fields->m_pending.m_buckets[i];
				if (next != 0)
					break;
			}
		}
		node = next;
	}

	// Allow the teams this player owns to update themselves.  Retail copies
	// the prototype list to the stack first, then walks the copy.
	BfmePlayerTeamListFields *teamFields = (BfmePlayerTeamListFields *)this;
	Player::PlayerTeamList teamPrototypes(teamFields->m_playerTeamPrototypes);
	for (Player::PlayerTeamList::iterator it = teamPrototypes.begin();
		it != teamPrototypes.end(); ++it)
	{
		BfmePlayerTeamPrototypeInstances *prototype =
			(BfmePlayerTeamPrototypeInstances *)*it;
		// Retail tests the link once per turn, at the top of the loop, and
		// advances the link unconditionally after the body has run.
		BfmePlayerTeamView *team =
			(BfmePlayerTeamView *)prototype->m_teamInstanceList;
		while (team != 0)
		{
			team->updateGenericScripts();
			team = (BfmePlayerTeamView *)
				((BfmeTeamInstanceLink *)team)->_bfme_nextInInstanceList();
		}
	}

	//Kris: August 25, 2003 (DAY OF CODE LOCK -- NO NEW FEATURES, REALLY!)
	if( ThePlayerList->getLocalPlayer() == this )
	{
		UnsignedInt now = TheGameLogic->getFrame();
		//Only check and post the message once every second so we don't spam the message stream to account for lag.
		if( now % LOGICFRAMES_PER_SECOND == 0 )
		{
			Bool clientRetaliation = ((BfmePlayerUpdateGlobalData *)
				TheWritableGlobalData)->m_clientRetaliationModeEnabled;
			if( clientRetaliation != fields->m_logicalRetaliationModeEnabled )
			{
				//Post a logical message that will switch the retaliation mode on or off.
				// Retail pushes 0x461 here.  The vendored enumerator compiles to
				// 0x449 because BFME's GameMessage::Type carries 24 more entries
				// ahead of it, so the observed immediate is spelled out rather
				// than the header name.
				GameMessage *msg = ((BfmeUpdateMessageStreamSlots *)TheMessageStream)->slot34(
					(GameMessage::Type)0x461);
				if( msg )
				{
					msg->appendIntegerArgument( getPlayerIndex() );
					msg->appendBooleanArgument( clientRetaliation );
				}
			}
		}
	}
}
