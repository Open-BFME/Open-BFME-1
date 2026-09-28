// ?parseHordeContainComboHorde@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.88 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Oi /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/stringinline
// stlport
//
// ?parseHordeContainComboHorde@@YAXPAVINI@@PAX1PBX@Z, retail 0x0023E5F0 (1017 B).
//
// The HordeContain module-data FieldParse table at rva 0x00CAF700 pairs the key
// "ComboHorde" (rva 0x00CAF664) with ILT thunk 0x0004A417, which jumps to this
// body (the ledger row ?j_0004a417@@YAXXZ carries the same target). The same
// table registers "SplitResult" against the landed parseHordeContainSplitResult
// at 0x0023E420 and "RanksThatStopAdvance" at ModuleData+0x24C, so the parser
// family is HordeContain's. The ComboHorde collection member sits at +0x230.
//
// One ComboHorde line parses a BfmeAudioPairState (the two sound names and the
// two AudioEventRTS rows the ctor at 0x00234CD0 builds): a Target name, a Result
// name, then a token loop accepting InitiateVoice / InitiateVoice2 sound names,
// each looked up on TheAudio (0x012ED668) and reported to the index-buffer
// debug manager (0x01336E5C) when unknown. Unknown keys throw INIException with
// the assembled "'Unknown key '...' in HordeContain's ComboHorde line" message;
// the pair is then pushed into the STLport vector<BfmeAudioPairState*> slot.
//
// The body was lifted under the wrong name ?postProcessLoad@WeaponStore@@UAEXXZ
// (a WeaponStore virtual); this TU is the corrected identity: plain cdecl INI
// parse callback, arg1 = INI* (m_sepsColon at +0x41C), arg3 = the store vector.
//
// STATE (probe.py, 2026-09-27): ours=1018 B, retail=1017 B, 53 non-reloc bytes
// differ, shape 0.990, 5 structural differences -- and ALL FIVE are downstream
// of one defect: the frame is 4 bytes too big (sub esp,0x1c vs 0x18, add esp
// 0x28 vs 0x24). Two of them are the same EH-state transposition in the
// setEventName by-value sequence, and the fifth is the trailing int3 that pads
// the last 1 byte. Every other difference is a bare [esp+N] displacement
// shifted by the frame. The instruction stream is otherwise 1:1 with retail.
//
// FRAME EVIDENCE, EXACT (2026-09-28). Anchor: E = entry ESP, S = ESP after the
// four register pushes = E-0x34, so a frame dword at S+k prints as [esp+(k-0x34)]
// and the incoming args are S+0x38 (ini), S+0x3C (instance), S+0x40 (store),
// S+0x44 (userData). Every by-value AsciiString ctor and every operator+= and
// getNextToken call in retail pops its own stack argument (ret 4), so one
// outstanding push is the rule at each site below.
//
// RETAIL's 0x18 frame is [S+0x10, S+0x28) and holds exactly:
//   S+0x10,S+0x14  the message INIException (0x374 lea ecx,[esp+0x14], 1 push)
//   S+0x18         the audio AsciiString temp (0x120 lea ecx,[esp+0x1c], 1 push)
//   S+0x1C         entry (0x396 lea eax,[esp+0x1c], 0 pushes)
//   S+0x20         the by-value AsciiString argument's saved-ESP slot
//                  (0x1cb mov [esp+0x24],esp, 1 push)
//   S+0x24         the 'Target'/'Result' INIException (0x3b8 and 0x3db
//                  lea ...,[esp+0x24], 0 pushes)
//   -- NO message in the frame at all. See the next paragraph.
//
// RETAIL'S MESSAGE SITS ON INCOMING ARG3's SLOT. 0x338, 0x342 and 0x358 are all
// `lea ecx,[esp+0x44]` with exactly one outstanding push, and 0x361 is
// `mov eax,[esp+0x40]` with none; all four give S+0x40, which is arg3 (`store`,
// read back at 0x392). The message is built straight onto a dead parameter
// slot -- the mechanism in docs/shape_levers.md, "A dead parameter slot takes
// only block-scoped locals". Retail's `ref` likewise rides a dead parameter
// slot, so retail spends 4 dwords on the frame and 0 on the message.
//
// OURS (this source, /FAsc listing, offsets relative to E) is 0x1c = [-40,-12):
//   -40  _message$4637 + $T5436        the AsciiString message
//   -36  $T5519/$T5595                the two voice branches' audio temps
//   -32  _entry$ + $T5437             entry
//   -28  $T5520/$T5596 (ref) and $T5440/$T5442 (8 B, the 'Target' and 'Result'
//        INIException temps -- these two ALREADY overlap each other)
//   -20  $T5443 (8 B)                 the message INIException  <== the extra dword
//   -12  __$EHRec$ (12 B) is the SEH chain, not part of the sub-esp frame
// So the object MSVC refused to fold is $T5443, the message's INIException, and
// the block-scoped `ref` is the local that wins the single dead parameter slot.
// Ablation still agrees: dropping message+throw, OR the setEvent block, OR the
// push_back each drops the frame to 0x18.
//
// CLOSEST APPROACH, 2026-08-28: 0x18 and 1010 B, ONE INSTRUCTION SHORT.
// Route (1) below reaches the right frame but pays 23 bytes for the message
// destructor. Modelling the message as a DESTRUCTOR-FREE view of the same
// StringBase<char> (same one-pointer layout, same pinned ctor and operator+=
// thunks, `~ComboHordeMessage() {}` -- an empty inline destructor still emits
// nothing at the block end) with the block closed gives:
//
//   frame 0x18, 1010 B, and the message block is byte-for-byte retail's
//   EXCEPT that retail's `mov dword ptr [esp + 0x34], 7` between the ctor and
//   the first operator+= is absent. That state store is the unwind state for
//   the message, so it exists only when the message is destructible -- and
//   declaring a real destructor puts back both the 8-byte state store and the
//   block-end destructor call (+23 B total). MSVC 7.1 gives no third option:
//   an empty user-declared destructor emits neither the state nor a call.
//
// So the exact remaining defect is: the message must be destructible (for the
// state store at retail +0x346) and its block must close (for the dead
// parameter slot) and no destructor call may be emitted (retail's block has the
// throw as its only exit). A destructor-bearing class whose call MSVC elides
// because the block provably does not fall through would close all three at
// once; nothing in the 7.1 front end reaches that conclusion today.
//
// TWO 0x18 ROUTES, AND WHY NEITHER IS THE BODY (measured 2026-09-28 with
// build/e5f0_harness.py, ~21 s per compile; it reports size and `sub esp`).
//
// (1) CLOSE THE MESSAGE'S SCOPE BEFORE THE THROW. Spelling:
//       if (token != 0) {
//           const char *text;
//           { AsciiString message("Unknown key '"); ...appends...; text = message.str(); }
//           throw INIException(3, text);
//       }
//     -> frame 0x18, 1033 B. This is the ONLY spelling measured that puts
//     `_message` on the dead parameter slot (the /FAsc table shows
//     `_message$4638 = 8`, sharing +8 with `_ini$` and `_ref$`), which is
//     exactly retail's mechanism. The 16 extra bytes are the price: the block
//     now has a normal exit, so ~AsciiString -> releaseBuffer is called before
//     the throw (+5 lea / +7 state store / +5 call) and str() is materialised
//     into `text` instead of inlined at the push (+3). probe: 110 diffs, 14
//     misaligned reloc sites -- the whole tail shifts, so it is WORSE than the
//     0x1c base even though the frame is right.
//
// (2) READ arg1 BEFORE `new` (`token = getNextTokenOrNull(); entry = new ...`)
//     -> frame 0x18, 1018 B, but probe 114 diffs / 11 structural: the
//     `mov ebx,[esp+0x38]` arg1 load moves ahead of operator new.
//
// (3) MOVE THE MESSAGE INTO A __forceinline HELPER (build + throw, or build and
//     return str()) -> the base's 1018 B shape, still 0x1c. So the dead
//     parameter slot is only offered to a block-scoped local of the CALLER's
//     body, never to a helper's local.
//
// The trap: (1) and (3) are mutually exclusive in MSVC 7.1. The message takes
// the dead parameter slot only when its scope CLOSES before the `throw`
// statement, and closing the scope forces the destructor -- while retail emits
// no destructor there (releaseBuffer is called twice in the body, for the two
// audio temps, not three times) because retail's block has the throw as its
// only exit. Getting both at once is the open lever; a message type whose
// destructor the compiler can see is trivial would break the tie, and the
// pinned releaseBuffer callee (0x00887940) is what forbids it.
//
// 2026-09-28 batch, all measured at 0x1c / 1018 B unless stated: the message at
// scope depth 2/3/4 with direct init or with an assignment; `text` declared
// before the message in the same block, at the throw statement, and in an outer
// block; the whole unknown-key block wrapped in extra braces; the append union
// declared before the message; the appends in a __forceinline helper; the
// message, the message+throw, and the two sibling throws all routed through one
// __forceinline helper; the two sibling throws each in a block of their own; the
// unknown-key test lifted one scope out; the three voice tests written as
// short-circuit `&&`; the helper taking `ini`; `text_pointer_sibling_blocks`
// (frame 0x18, 1033 B); a function-scope `AsciiString message;` + assignment
// (frame 0x18 but 1036-1044 B, and it adds an EH state, so the state numbering
// diverges too); `entry` as a `*const`; a named `BfmeComboHordeVector *` local;
// the voice helper's inner block removed; the two wrapper helpers removed; the
// lookup and the setEventName argument each given their own block (0x20).
//
// LEVERS ALREADY TRIED AND DEAD (all keep realshapediffs=0 but leave 0x1c):
//   token/entry declaration order (both orders, and split declare/assign);
//   entry as *const, entry via a reference alias, pair& parameters;
//   int eventOffset -> template <int EventOffset> parameter;
//   the pinned member-function thunks as direct member calls (setEventName is
//   pinned at 0x00025266) instead of the union cast, one at a time and both;
//   the message built in a __forceinline helper (build + throw), the concats in
//   a helper, the message block re-nested, message text read into a local
//   before the throw; a named vs unnamed reporting stream local, one call per
//   statement, the debug global hoisted; voice-suffix and message literals as
//   file-scope constants; while(1)+break instead of the three nested ifs;
//   strncmp prefixes; split "expected" throws; /Ob0 /Ob1 /Ob2 /O1 /O2 /Ot /Os
//   /EHa /Gw /Gx /Gy /Ga /Gr /Zp8 /Ai with and without /Oi (identical code for
//   /Ob1 and /Ob2, so the flag set is not the lever).
// The ONLY source that reaches 0x18 is one that reorders the first two
// statements -- `token = getNextTokenOrNull(); entry = new BfmeAudioPairState;`
// -- which moves the `mov ebx,[esp+0x38]` (arg1) load ahead of operator new
// and costs 7 shape diffs. The slot win therefore comes from the statement
// ORDER, not the declaration order: something about reading arg1 before the
// `new` lets MSVC merge a slot. Reproduce that merge without moving the
// `mov ebx` is the open lever.
//
// The one code-shape defect that may be independent of the frame is the
// transposition of the by-value argument sequence, repeated twice:
//   retail  push ecx / mov ecx,esp / mov [esp+0x24],esp / push esi / call ctor
//   ours    push ecx / mov [esp+0x20],esp / mov ecx,esp / push esi / call ctor
// Both stores write ESP into the same EH slot (the displacement differs by the
// frame delta), so this is the same defect seen from the other side.
//
// IDENTITY NOTE for whoever lands it: the message's str() fallback must be the
// named empty static, not a TU literal -- retail's `mov eax,0x0107388B` is
// ?bfmeEmptyStr107388B / ?TheNullChr@?1??str@AsciiString@@ (dir32_addresses.csv
// rows), while the stringinline shim's str() returns "". That is relocation
// masked, so the byte gate cannot see it; the DIR32 gate can.

typedef int Int;

#include <string.h>

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

// Canonical by-value string model: game/../inputs/reference/shims/stringinline/StringInline.h
// Rule 2 there is load-bearing here -- an out-of-line string dtor transposes the
// EH saved-esp store against the ctor `this` on every flag combination.
#include "StringInline.h"

// pinned ??4AsciiString@@QAEAAV0@PBD@Z (retail ILT 0x00028BB9) as a member-function
// cast, the same shape retail's other three pinned thunks are reached through.
extern void j_00028bb9(void);

#include "Common/INIException.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken(const char *seps);
	const char *getNextTokenOrNull(const char *seps);
	const char *getSepsColon(void) const { return m_sepsColon; }

	char m_unreconstructed_000[0x41c];
	const char *m_sepsColon;
};

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *val);
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *val);

class RefCountedThing
{
public:
	virtual ~RefCountedThing();

	// non-virtual view; the out-of-line destructor at 0x000877B0 does the
	// InterlockedDecrement-and-delete through the vtable.
	Int m_refCount;
};

class ThingRef
{
public:
	~ThingRef();

	RefCountedThing *m_ptr;
};

// TU-local model of the retail audio object at 0x012ED668, slotted so the
// lookup left by the retail `call dword ptr [edx+0x118]` sits at vtable offset
// 0x118. TheAudio is already recorded in dir32_addresses.csv under the
// AudioManager spelling used here.
class AudioManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69();
	virtual ThingRef lookupAudioEventInfo(const AsciiString &eventName);
};

extern AudioManager *TheAudio;

class AudioEventRTS
{
public:
	// pinned through member-function casts to the retail ILT thunks
	void setEventName(AsciiString name);
	void setEventInfo(ThingRef *ref);

	// the two 0x70-byte AudioEventRTS rows that BfmeAudioPairState embeds
	unsigned char m_pad[0x70];
};

class BfmeAudioPairState
{
public:
	BfmeAudioPairState();

	AsciiString m_firstName;
	AsciiString m_secondName;
	AudioEventRTS m_firstEvent;
	AudioEventRTS m_secondEvent;
};

extern void j_00025266(void);  // retail ILT thunk 0x00025266
extern void j_0000b4e7(void);  // retail ILT thunk 0x0000B4E7
extern void j_00022057(void);  // retail ILT thunk 0x00022057 (AsciiString append)

// index-buffer debug manager, retail global 0x01336E5C
class BFMEIndexBufferDebugStream
{
public:
	virtual BFMEIndexBufferDebugStream *Put_Unsigned(unsigned value);
	virtual void Slot04();
	virtual void Slot08();
	virtual void Slot0C();
	virtual void Slot10();
	virtual void Slot14();
	virtual void Slot18();
	virtual void Slot1C();
	virtual void Slot20();
	virtual void Slot24();
	virtual void Slot28();
	virtual void Slot2C();
	virtual void Slot30();
	virtual void Slot34();
	virtual BFMEIndexBufferDebugStream *Put_String(const char *text);
	virtual void Slot3C();
	virtual void Slot40();
	virtual void Slot44();
	virtual void Slot48();
	virtual BFMEIndexBufferDebugStream *Finish(int report);
};

class BFMEIndexBufferDebugClass
{
public:
	virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3C();
	virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4C();
	virtual void Slot50(); virtual void Slot54(); virtual void Slot58(); virtual void Slot5C();
	virtual void Begin_Report();
	virtual void Slot64(); virtual void Slot68();
	virtual BFMEIndexBufferDebugStream *Get_Stream(void *owner, void *context);
};

extern BFMEIndexBufferDebugClass *g_BFMEIndexBufferDebug;
extern void _bfme_debugRecordCallsite(int kind);
bool __cdecl _bfme_debugReportingEnabled(void);

#include <vector>

typedef _STL::vector<BfmeAudioPairState *> BfmeComboHordeVector;

// file-scope aliases for the three pinned member-function thunks
typedef void (AudioEventRTS::*BfmeSetName)(AsciiString);
union BfmeSetNameCall { void (*freeFunction)(void); BfmeSetName memberFunction; };
typedef void (AudioEventRTS::*BfmeSetRef)(ThingRef *);
union BfmeSetRefCall { void (*freeFunction)(void); BfmeSetRef memberFunction; };
typedef AsciiString &(AsciiString::*BfmeComboAppend)(const char *);
union BfmeComboAppendCall { void (*freeFunction)(void); BfmeComboAppend memberFunction; };
typedef AsciiString &(AsciiString::*BfmeSetFromCStr)(const char *);
union BfmeSetCall { void (*freeFunction)(void); BfmeSetFromCStr memberFunction; };


// The look-up-and-report-and-store dance is common to both voice keys; retail
// inlined it into each branch of the token loop (the two expansions share the
// same scratch slots, which is what makes the body land inside 0x18 bytes of
// frame). Keeping it as one __forceinline helper below gives the compiler the
// same two expansions with the shared slots; the next-token read stays inside
// the same scope so the ThingRef's destruction sits after it, as retail has.
__forceinline const char *parseComboHordeSound(INI *ini, BfmeAudioPairState *entry,
	int eventOffset, const char *voiceSuffix)
{
	const char *soundName = ini->getNextToken(ini->getSepsColon());
	ThingRef ref = TheAudio->lookupAudioEventInfo(AsciiString(soundName));
	if (!ref.m_ptr)
	{
		if (_strcmpi(soundName, "NoSound") != 0
			&& _bfme_debugReportingEnabled())
		{
			_bfme_debugRecordCallsite(1);
			g_BFMEIndexBufferDebug->Begin_Report();
			BFMEIndexBufferDebugStream *stream =
				g_BFMEIndexBufferDebug->Get_Stream(0, 0);
			stream->Put_String("Unknown sound '")->Put_String(soundName)
				->Put_String(voiceSuffix)->Finish(2);
		}
	}

	{
		BfmeSetNameCall setEventName;
		setEventName.freeFunction = j_00025266;
		(((AudioEventRTS *)((char *)entry + eventOffset))->*setEventName.memberFunction)(AsciiString(soundName));

		BfmeSetRefCall setEventRef;
		setEventRef.freeFunction = j_0000b4e7;
		(((AudioEventRTS *)((char *)entry + eventOffset))->*setEventRef.memberFunction)(&ref);
	}

	return ini->getNextTokenOrNull(ini->getSepsColon());
}

__forceinline const char *parseComboHordeSoundFirst(INI *ini, BfmeAudioPairState *entry)
{
	return parseComboHordeSound(ini, entry, 8,
		"' requested for HordeContain's InitiateVoice");
}

__forceinline const char *parseComboHordeSoundSecond(INI *ini, BfmeAudioPairState *entry)
{
	return parseComboHordeSound(ini, entry, 0x78,
		"' requested for HordeContain's InitiateVoice2");
}

void __cdecl parseHordeContainComboHorde(INI *ini, void *instance, void *store,
	const void *userData)
{
	BfmeAudioPairState *entry = new BfmeAudioPairState;
	const char *token = ini->getNextTokenOrNull(ini->getSepsColon());

	if (token == 0 || strcmp(token, "Target") != 0)
		throw INIException(3, "'Target' expected");

	{
		BfmeSetCall setName;
		setName.freeFunction = j_00028bb9;
		(entry->m_firstName.*setName.memberFunction)(
			ini->getNextToken(ini->getSepsColon()));
	}

	token = ini->getNextTokenOrNull(ini->getSepsColon());
	if (token == 0 || strcmp(token, "Result") != 0)
		throw INIException(3, "'Result' expected");

	{
		BfmeSetCall setName;
		setName.freeFunction = j_00028bb9;
		(entry->m_secondName.*setName.memberFunction)(
			ini->getNextToken(ini->getSepsColon()));
	}

	token = ini->getNextTokenOrNull(ini->getSepsColon());
	if (token != 0)
	{
		if (strcmp(token, "InitiateVoice") == 0)
		{
			token = parseComboHordeSoundFirst(ini, entry);
		}

		if (token != 0)
		{
			if (strcmp(token, "InitiateVoice2") == 0)
			{
				token = parseComboHordeSoundSecond(ini, entry);
			}

			if (token != 0)
			{
				AsciiString message("Unknown key '");
				{
					typedef AsciiString &(AsciiString::*BfmeComboAppend)(const char *);
					union BfmeComboAppendCall
					{
						void (*freeFunction)(void);
						BfmeComboAppend memberFunction;
					} append;
					append.freeFunction = j_00022057;
					(message.*append.memberFunction)(token);
					(message.*append.memberFunction)(
						"' in HordeContain's ComboHorde line");
				}
				throw INIException(3, message.str());
			}
		}
	}

	((BfmeComboHordeVector *)store)->push_back(entry);
}