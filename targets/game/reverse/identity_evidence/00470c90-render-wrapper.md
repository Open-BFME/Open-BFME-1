# RVA 00470C90 render and its existing image-wrapper dependency

## Scope and identity

The 972-byte retail range at 00470C90 has a native ECX receiver and three
stack arguments, ending RET12 at 00471042. INT3 precedes its entry. A
three-byte alignment LEA follows the return, then five absolute switch
entries at 00471048 through 0047105B; INT3 resumes at 0047105C. The five
entries point to 00470DCA, 00470E43, 00470EEE, 00470F1C and 00470F92.
These internal data bytes belong to the emitted function section. Linear
instruction decoding across that table does not establish another boundary.

EA's FadeInTextRender.cpp is a lead, not enough to rename the owner or
callback class. The recovery retains Rva00470C90 and Text00470C90. Callback
slots are 08 (UnicodeString return by hidden result pointer), 28 (two color
words), 38 (four integer arguments), and 3C (two integer output pointers).
The bank's canonical ICoord2D, Anim2D and BFME UnicodeString declarations
preserve the complete shape; no generated source is edited.

## Correct the physical wrapper's parameter types, not its identity

The sole ledger provider at 0040D900 is Bfme5Host::bfmeRunE, 70 bytes, in
Bfme5BeginWorkEnd.cpp. It begins a virtual operation at slot B0, forwards
seven stack words to slot D4, and ends via slot DC. RET1C at +43 ends the
body; INT3 follows at +46. It contains no relocation or field access.

Its previous all-int declaration cannot express the source-level call
contract. Independently matched callers 0059E6E0 (161 bytes) and 0059ABC0
(952 bytes) load an Image pointer, convert four screen coordinates to float,
and pass color/mode integers to ILT 0000A114, which jumps to 0040D900.
0059ABC0 also independently inlines the same B0/D4/DC sequence with that
contract. The existing Display::drawImage typed pin names that route but is
not a second emitted provider identity.

Only bfmeRunE and virtual bfmeWorkE change to
(const Image*, float, float, float, float, int, int). The existing Bfme5Host
and method identities remain. The new renderer calls that emitted typed
bfmeRunE directly. No duplicate opaque alias, inheritance relationship,
shared-header migration or new callee pin is introduced. No other source
calls bfmeRunE. All five existing provider-TU rows must continue to match:
006FBDB0/70 (A), 004336F0/60 (B), 00793C20/60 (C), 0046EC50/70 (D), and
0040D900/70 (E).

## Root calls and data

The two setCurrentFrame calls route 000168E7 -> 005BA1D0. The complete
30-byte setter reads a 16-bit stack frame, stores this+04, updates this+08
from a virtual callback, and returns RET4. The two emitted animation
call sites implement three source calls: case 0 draws twice, and case 4
draws once. Case 0 jumps from 00470E3E to 00471008 for its second draw,
sharing that call site with case 4. Both sites route 00030DB9 -> 005BAAB0,
the independently matched 187-byte mode-2 body with RET16. Three __ftol2 calls and the normal Unicode buffer
release at 008881D0 use existing bindings. Both image calls route through
0000A114 to the corrected sole physical provider.

Float/double constants are VA01075358 (2^32), VA0107C64C (1/255),
VA01075334 (1), and VA01084068 (255). Each compiler constant and all five
local switch references must be checked against the actual retail targets.
TheDisplay references name the existing Display* singleton at VA012F1270;
Display.cpp defines it as NULL. The location is in the PE virtual zero tail,
not raw file bytes. This dependency is no assertion that Display.cpp links
or that this recovery earns LINKED progress.

## Complete native EH

The parent prologue references handler RVA00C25DD8. Its ten bytes load
FuncInfo RVA00E1602C and jump to __CxxFrameHandler. The 28-byte FuncInfo
has magic 19930520, one unwind state, map RVA00E16024, and no try/catch or
IP-to-state tables. State 0 transitions to -1 using action RVA00C25DD0.
The eight-byte cleanup computes ECX=EBP-1C and jumps through ILT0003B304
to the five-byte UnicodeString destructor at 0005EEA0, then releaseBuffer
at 008881D0. The C++ compiler's native handler, action and metadata must
reproduce this graph; normal-path byte matching alone does not prove it.

## Verification (2026-10-05)

The unchanged bank replay and typed provider each reproduce their complete
972-byte and 70-byte extents. Scoped strict gates pass all five provider rows,
all three new-TU rows, and both typed witness callers (2433 ledger bytes).
The root gate verifies 12 floating-constant references and 10 global/DIR32
references. Independent full patching of the parent, cleanup, handler,
FuncInfo and unwind map verifies all 1026 bytes and all 39 relocations with
no masked or unresolved fields; its explicit bindings also verify all five
switch-table destinations. The cleanup is $L25573, derived from state 0 of
the emitted unwind map, and eh_state_pins reports proven/unique.

An isolated compile of unmodified Display.cpp emits the exact TheDisplay
external in a four-byte .bss section, value zero and no relocations. It has
no initialized raw bytes; this is a physical zero-storage provider check,
not a native linker or whole-Display-TU acceptance result.

The approved StringFromGUID2-only Wibo SHA-256 is
7aa93ec61c2a184f96e117d5047786d43b359c68c050e1a0e911b7ed5c0dbd82.
Original MSVC7.1 tools performed the scoped compilation. No runtime, gate,
generated source, pin, shared header, or baseline changes were needed.

Against base 064e2c188cb043aca06042d2fb1cee52f1c95578, progress.py reports
+972 rebuilt-source bytes and +990 authored C++ bytes (the latter includes
18 bytes moved from generated EH rows to actual compiler-emitted EH).
The existing 70-byte wrapper contributes no new C++ bytes. LINKING and
LINKED remain +0; no census or native-link claim is made.
