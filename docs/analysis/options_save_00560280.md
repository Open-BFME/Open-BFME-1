# Apt options Save — RVA 0x00560280

The matched `BfmeAptScreenOptions` constructor at RVA 0x00563370 registers
`AptOptions::Save` at +0x1B3 through ILT 0x00012544, whose jump target is
0x00560280. This is a member callback with one unused `const char *` argument;
retail returns with `ret 4`. The old `OptionsMenuInit(WindowLayout *, void *)`
assembly lift had the wrong emitted symbol and signature. Its ledger identity
was already corrected. This change removes the lift and supplies that identity
as native C++ without renaming an unrelated Zero Hour initializer.

The full extent is 7,212 bytes: executable code through offset 0x1C11, two
alignment bytes and a six-entry LOD switch table at +0x1C14. All 418 relocation
sites align. The strict gate verifies the body and 81 literal references, with
zero skipped literals and no added pins.

## Behavior and layout

The callback stops the outstanding audio preview first. Pages 2 and 3 share
LOD, resolution, brightness, scroll speed, five volume controls, health bars,
mouse setup, unit decals, EAX and audio-LOD settings. It writes the embedded
preferences and signals the pending quit layout. Page 4 stores nine advanced
checkboxes, texture reduction, particle count and five current global options,
then returns to page 2. Page 3 additionally stores send delay and online IP.

The screen's state is at +0x258, its 20-byte OptionPreferences at +0x260, and
the inherited preference map at +0x264. Resolution staging is +0x274 through
+0x280 and +0x308; control pointers span +0x284 through +0x304. The final
selector is +0x30C. Names without independent witnesses retain offsets.
`name_oracle.py` reports no screen layout and no witness for GameLODManager
+0x16C4; neither is given a guessed member name. The six LOD names/values are
independently established by the retail StaticGameLODNames table and the
already matched GameLODManager implementation. Zero Hour's shared header has
three levels and different member offsets, so this TU keeps the bounded BFME
view used by the aligned accesses.

The GlobalData offsets in this body are accesses witnessed in retail, not
claims about shipped INI defaults. No numerical default is presented as runtime
configuration. Unknown virtual slots also retain their numbers.

## Callee contracts

`callees.py 0x00560280 7212` resolves all 19 distinct direct targets. Existing
canonical StringBase<char>/AsciiString definitions supply construction,
assignment, formatting and destruction. The actual STLport map is
`map<AsciiString, AsciiString>` and uses the existing body binding at 0x0007DF70.
The misleading UnicodeString label shown by old aliases at 0x00887C90 is not
used: the emitted call is StringBase<char>::set(const StringBase<char>&).

The existing named slider/window and checkbox/combo functions are used at their
aligned targets. Custom settings call the existing opaque `bfmeGo1148` at
0x0007C8A0 with the preferences address; the clear helper at 0x0007E5F0 removes
15 advanced keys. The existing opaque `bfmeSetSB` at 0x0007CAB0 accepts one int
on GameLODManager. The tiny address-derived method at 0x00465B80 writes the
pending flag at its receiver +0x1AC. No new semantic identity is inferred for
these helpers. AudioLOD and online-IP setters are the already matched bodies
0x00092810 and 0x00092710; the latter stores `GameSpyIPAddress`.

## Shape evidence

The native reconstruction preserves the source-level operations rather than
emitting instructions. The decisive levers were the authentic slider inline
and its caller's nullable-window ternary, function-scope `val`/`index`, and a
local holding the fixed LOD selector before constructing its preference key.
Those establish the retail 0x18-byte frame and register lifetimes. The complete
comparison also caught the two global writes enabling heat effects and unit
decals for higher presets; both are present. The initial outer switch was
replaced with the witnessed separate page comparisons. Canonical strings and
STL containers generate the exception cleanup and jump table naturally.

Validation: exact full extent; strict callee/relocation and 81-string gate;
normal ledger, identity, conversion, commit and outgoing push checks. New native
credit is exactly 7,212 bytes. Existing callees receive no additional credit.
