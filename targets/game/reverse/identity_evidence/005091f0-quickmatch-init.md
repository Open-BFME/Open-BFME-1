# Quick-match gadget initializer, 005091F0 / 1890 bytes

The receiver is the existing BfmeAptScreenQuickMatchMenu. Its independently
matched 573-byte constructor at 00505830 keys the same sixteen gadget members
by WOLQuickMatchMenu.wnd names, and the authored 00507F70 map population method
uses those same members. Retail saves incoming ECX, takes no stack arguments,
and ends with a plain RET at +761. The contiguous extent is 0x762 bytes;
subsequent bytes are padding. The exact original BFME member spelling is not
established, so the native method retains the RVA token rva005091F0InitGadgets.

The body follows the original WOLQuickMatchMenu initialization algorithm, with
BFME menu members in place of file-local windows. It looks up the buddies and
title windows, resolves the constructor's gadget keys, registers the text
window, checks all three ladder lists, initializes images and preferences,
populates player/disconnect/ping controls, and initializes the map and progress
controls. Its final transition string is WOLQuickMatchMenuFade.

The bank omitted the byte store [this+220]=1 before resetting the disconnect
combo. Retail performs that store at +438. Independently matched System
0050A470 tests that same byte before processing this combo's callbacks, while
the 26-byte setter at 00505530 stores its selected value at +224. The analogous
ping pair is flag +218 / selected value +21C, independently checked against
setter 00505550. The inherited bank names m_isMatching, m_matchingLevel,
m_isStopping and m_selectedMap are therefore unsupported; this source uses
address-derived member names. Hash-scoped name corrections document these
four changes without editing the constructor's separate claims.

## Direct-call contracts

The 39 distinct targets were inventoried before reconstruction. Final strict
verification matches all 1890 bytes, resolves all 84 REL32 sites with 135
object relocations, and reports zero unresolved symbols. No pins are added.
The native source uses the existing canonical strings, QuickMatchPreferences,
LadderInfo and gadget headers.

* ILT 00017567 forwards to the complete 27-byte body at 00477DA0. It forwards
  this and its one NameKeyType stack argument to WindowManager slot DC, preserves the
  returned EAX, and RET4. The WindowManager header and independent callers
  establish a GameWindow* result. The old BfmeThingEGD declaration says void;
  the local typed ILT member view preserves the actual pointer-returning ABI.
* ILT 000269B8 forwards to the authored 406-byte color-combo population body
  00505DB0, receiving menu ECX and QuickMatchPreferences& with RET4. Its old
  free-function ledger label is retained; this conversion adds no identity
  claim or helper ownership to that existing row.
* ILT 00035701 forwards to 005082D0, menu ECX plus int side and const LadderInfo*,
  RET8. This same typed contract is independently used by System 0050A470.
* ILT 0002716A forwards to the authored 197-byte start-button updater 00505570,
  a zero-argument receiver member. Existing BfmeQuickMatchProgressBody::update
  names the independently authored 127-byte progress helper at 00505410.
* Existing populateQuickMatchMapSelectListbox(QuickMatchPreferences&) at
  00507F70 retains its actual native member identity. UpdateLocalPlayerStats
  at 0050B930 is a free no-argument function: retail supplies no receiver.
* The existing legacy BfmeQuickMatchLadderPanel::populateLadderList contract
  reaches 00508C80 on the singleton at VA012F4820 with no stack arguments.
  Its historical owner label is not used to identify this initializer.

The typed member-pointer expressions use existing address-only ILT symbols.
They are ordinary C++ calls with independently proved receiver and argument
types; there are no raw instruction bytes, stack references or new symbol pins.

## Data and shape evidence

The named constructor proves keys/pointers at 228..2AC. GameSpyInfo slots 68
and E4 return the local name and register the text window respectively;
GameSpyConfig slot C returns ping timeout; GameSpyGame slot 8 resets it.
WindowManager slots B0/DC set focus/look up a window, as established by the
existing headers and independent native callers.

Selected/deselected images are stored at VA012F480C/10, buddies key/window at
012F47F8/FC, initialization state at 012F4809, max/min points at 012B7224 and
012F481C, and ping entry count at 012F4818. The disconnect values are the five
integers {0,5,10,25,50} at 012B7228. GameSpyColor[0] is loaded from 012B9200.
These are menu state/preferences, not assumed runtime GlobalData constants.

The shared minimum-points state is declared external: unlike a private static,
it can alias the menu object, preserving retail's store/load ordering. Native
std::max receives named getter results, reproducing retail's reference
lifetimes and 0x28 frame without volatile or assembly. Every selected-position
call explicitly passes notify=false, as witnessed by the stack arguments.

Scratch receipts are build/four-hour-qminit/{retail.asm,callees.txt,
lookup-retail.asm,probe2.txt,probe3.txt,probe4.txt,strict3.txt,strict-clean.txt,strict-key.txt}.
The old 1862-byte/.67 bank was the starting source. Model GPT-6; new native
coverage 1890 bytes, dependency credit zero.

The name guard's declaration alignment also pairs old setGroup/slot0 with new
lookup/initializer declarations. These are not claimed identity equivalences:
GameWindowTransitions::setGroup remains the canonical named call, and unused
virtual slots remain opaque. ILT17567 is independently the477DA0 lookup, not
setGroup. The historical BfmeThingEGD void view is replaced with its evidenced
pointer-return contract; the initializer keeps its RVA rather than assert an
unproven original member spelling. Hash-scoped corrections record these facts.
