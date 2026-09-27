# ScoreScreen constructor at RVA 00578160

The matched `createAptScreenScoreScreen` caller in `AptScreenFactories.cpp`
constructs `BfmeAptScreenScoreScreen(void*)` through ILT 00017233. Retail starts
at 00578160 and ends at 00578C94 after RET4: 2868 bytes. The existing scaffold already
has that complete extent. The selector registrations, singleton VA 012F4B50 and
vtables VA 0110AAB8/0110AAB4 independently agree with this identity. The matched
290-byte destructor 00575050 installs the same two vtables at receiver+0/+218.
No semantic identity is inferred from matching bytes alone.

Fresh read-only Ghidra decompilation used the existing `bfme` project and the
same retail executable (SHA256
c1a907c44b84df129c1f18dc7365ea25ba438f9b8f39a374b86ed852936ff0a9).
The constructor and three cleanup helpers were inspected alongside retail
instructions, callee contracts, the factory and destructor. Ghidra's inferred
C types are not byte-match evidence.

## Layout and ownership

The actual base is 0x258 bytes with its secondary GameWindow at +218. This layout
is also witnessed by the independently landed Skirmish constructor 0057DA50.
The constructor's scalar at +258 and mode at +25C are separate fields; unknown
members keep their offsets. Native multiple inheritance produces both vptr
stores without volatile stores or forced vtable pointers. Compile-time checks
verify the base and complete 0x334-byte screen sizes.

The 21-state retail unwind map calls 00574BC0 for+264. That authored 150-byte
vector destructor walks eight-byte elements and destroys an AsciiString at +4;
`Gen00574BC0 { int field00; AsciiString field04; }` therefore supplies its
existing address-derived element identity. The+2E8 cleanup 002CBEF0 is the
existing STLport `_Bvector_base<allocator<bool>>` destructor: native
`vector<bool>` supplies the five-word storage and ownership. Three ordinary
AsciiStrings live at+300/+320/+330. The checked-objective provider 005703A0
independently reads the eight bytes at +308. All strings use `ascii_string.h`.

The functor family stores a target at +0 and an eight-byte multiple-inheritance
member pointer at +8; +4 is unwritten native alignment padding. The 24-byte
wrapper has an eight-byte polymorphic reference-counted head and a 16-byte
binding. Existing49-byte constructors 00571780 and 005717D0 independently install
VA 0110A964 and VA 0110A970 and copy those same four words. These existing wrapper
identities are retained. Holders own one pointer and increment wrapper+4 on
copy. Direct by-value arguments reproduce callee ownership; fabricated named
callback locals and raw vtable stores from the older bank are gone.

All ten distinct direct callees resolve without new pins. The registry adapters
use the already witnessed ILTs 000338ED/0000ACFE/0003DF14 and the real owned
four-byte holder ABIs. `AptScreenShow.cpp` independently establishes the two
member forms, string references and argument cleanup. The seven plain targets
all consume one 32-bit argument (RET4); provider and init callbacks consume
three (RET12). Typed member pointers supply callback constants, preserving
native pointer-to-member representation rather than manually writing words.

## Callback identity and data operands

| Encoded ILT RVA | Body RVA | Identity used |
|---|---|---|
|00026152|005701D0|address-derived screen callback|
|0000A76D|005731C0|address-derived screen callback; receiver unused|
|000328B2|00570200|address-derived screen callback; receiver unused|
|0003936A|005780E0|address-derived screen callback|
|00035639|005731D0|address-derived screen callback; receiver unused|
|00003C01|005710A0|existing `_bfme_renameAccept`|
|000077C0|00570220|address-derived screen callback|
|0003A1E3|005731E0|address-derived three-argument provider|
|00005FBA|00571DF0|existing `_bfme_getPlayerColor`|
|0002F806|00571E50|existing `_bfme_getPlayerFaction`|
|0001AC49|00570260|address-derived three-argument provider|
|00023C77|005702B0|existing `bfmeProvide`|
|000289B6|00570300|address-derived three-argument provider|
|0003EC6B|005703A0|existing `bfmeProvideObjectiveChecked`|
|00007C25|005729C0|existing `heroVetUpgrade`|
|000016E0|00571EC0|existing `_bfme_onInitGadget`|

Each route was decoded independently from the image. The provider PMF casts
normalize the pointer/integer payload spelling of the existing three-argument
API; this constructor stores callbacks and does not invoke a cast PMF.
The other external data operands are the eleven-key table VA 012B7F9C,
the already witnessed singleton VA 012F4B50 and canonical
`g_theWindowManager` VA 012F19E8. Every non-string DIR32 symbol has one base,
including all repeated wrapper and callback references. The wrapper vtable
bases agree with their authored constructor family, and the screen vtable
bases agree with its authored destructor. No symbol pins were added.

## Measured reconstruction

This starts from the existing 2665-byte bank. Correct base/container ownership,
real owned callback arguments, native memset initialization and typed member
pointers remove its long-standing saved-this and callback-layout mismatches.
Bound color/faction objects preserve the real loop payloads. Reusing the
existing player counter for the final two loops reproduces the two CSE
post-increment temporary slots; separate counters had left exactly four bytes
at +979/+9E6/+A13/+A80 differing. No dummy variable, compiler-memory barrier,
volatile shaping, asm or fallback is used.

The cleaned source strictly matches 2868/2868 bytes with 84 resolved encoded calls
and zero differing bytes. Scratch receipts are
`build/round4-score-ctor/{strict-clean.txt,dir32.txt,score.cod,retail.txt,eh.txt}`;
probe30 is the first exact source, followed by independently reverified cleanup.
The normal add_match/scoped build and commit/push hooks provide publication
verification. Model GPT-6; approximately 45 minutes of bounded recovery and review.

## Bank naming corrections

The old bank supplied provisional local representations, not witnessed names
for every helper. Existing authored constructors 00571780/005717D0 and holder
destructors 00572D10/00572D80 establish the wrapper and holder families used
here. Thus ScoreProviderWrapper becomes Rva00571780FunctorWrapper, and
ScoreProviderHolder becomes Rva00572D10FunctorHolder. The init counterpart is
Rva005717D0FunctorWrapper. The registry view keeps 00464ED0, the already
witnessed registry body, rather than asserting the bank's ScoreRegistryWindow
type identity. The two unnamed storage groups retain their measured offsets
278 and 294; no independent source establishes ScoreScreenFiveFields or
ScoreScreenZeroBlock as original type names.

Several token-alignment findings are not actual renames. FunctorBinding is
still present as a distinct 16-byte type; it was not renamed to a holder.
ScoreInitWrapper aligns with the provider wrapper in the detector, but the
native init wrapper is the separate Rva005717D0FunctorWrapper. The old fake
RawVecBuffer at +2E8 is replaced by native vector<bool>, independently proved
by cleanup 002CBEF0. It is unrelated to the five scalar fields at +278..+288,
despite the detector pairing RawVecBuffer/m_start/m_end with those fields.
Likewise the removed raw m_vftable and base m_zero04/m_zero08/m_zero0c are
unrelated to the owned holder pointer and fields +27C/+280/+284 that the token
alignment pairs with them. Native virtual bases supply the removed vptr
representation. The registry view and init holder are distinct types even
though the detector also pairs their declarations. Exact before/after source
hashes in name_corrections.json document these individual findings; they do
not authorize future name losses or change the naming gate.
