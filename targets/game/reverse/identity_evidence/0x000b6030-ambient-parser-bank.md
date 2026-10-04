# RVA 000B6030 ambient parser bank, 2026-10-04

## Outcome and limits

This is **banked experimental evidence, not a production conversion**. Original
MSVC 7.1 emits 976 bytes versus retail's 976, with 33 non-relocation byte
differences, three shifted relocation operand sites, and instruction shape
0.987. The previous bank emits 980 bytes, 482 differences, shape 0.957. The
score is 1 - 33/976 = 0.9661885246; it is not a claim of correctness or linking.

The first divergent instruction is the final enabled-fallback branch at
+0x35D (its displacement first differs at +0x35E). Retail places the nonnull
first-receiver call at +0x390 and jumps backward to the sound test at +0x36E;
the reconstruction places that call at +0x370 before the common test. The
entire earlier instruction stream agrees modulo its relocation operands.
The final parser strict `build.verify_functions(selected_rows=...)` check
fails: 33 byte differences AND eight unresolved typed call identities. No
`add_match`, production body, pin, resolver change, literal pin, census change,
or byte-match claim is made.

## Ground truth and independent ABI evidence

Actual readonly PyGhidra MCP `decompile_function`, `list_xrefs`, `disassemble`
and `read_bytes` were used. All 976 parser bytes returned by MCP were compared
against the full PE SHA256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
The same full-byte comparison passed for 0x00087750/73,
0x000877B0/35 and 0x000B5CB0/49. The parser's final RET is +0x3CF.
The initial disassembly request exceeded MCP's 200-instruction limit; the
follow-up successfully requested bounded beginning/end segments. No tool error
was treated as byte evidence.

Original caller at VA005D0CBC..005D0CCE pushes, right-to-left:
enabled output, dynamic reference output, force-off output, final template,
drawable receiver, properties; it calls ILT 0002940B -> 000B6030.
Inside the parser, argument two is loaded at VA004B6171 and uses
ILT0001BFD1 -> 00416FA0. Argument three uses ILT0003E4D7 -> 00087BD0.
The latter reads `[receiver + 0xE0 + index*4]`, returning the nonnull entry +4.
The former delegates 00416F20, whose provider walk accesses +0x158 and whose
fallback follows the template/override chain at receiver+4. Thus the old
bank's argument-two `ThingTemplate` and argument-three `soundOwner` labels
are misleading. Address-qualified receiver views are retained; the existing
ThingTemplate-labelled provider rows are not independent identity evidence.
Do not broaden this into provider renames without an independent audit.

Entry release decrements the object's +4 count, conditionally invokes deleting
vslot 0 with argument 1, and clears the output reference **inside** the nonnull
branch. The previous bank cleared it unconditionally. The enabled byte is
then initialized before testing TheAudio and properties.

## Causal source-visibility result

Both real reference-holder bodies must be visible in the TU:

- 000877B0/35: load held pointer; if nonnull InterlockedDecrement at +4;
  on result <= 0 and nonnull pointer invoke deleting vslot 0; no slot clear.
- 00087750/73: self-assignment guard; increment incoming pointee first;
  release outgoing pointee; copy incoming pointer; return receiver, RET 4.

Together these independently decoded definitions change 980/478 to 976/33.
They restore the late EBX push, properties in EBX, enabled output in ESI,
string/reference local slots, and the second allocation's retained pointer.
Either definition alone returns to 980/478. Their actual bodies separately
pass strict `build.verify_functions(selected_rows=...)`: 2/2, all 35 and 73
bytes concrete, no unresolved imports. This verifies bytes and imported
InterlockedIncrement/Decrement bindings, **not acceptance of their experimental
holder names/types as canonical providers**. Existing selected providers remain
`Rva00087750Ref::operator=` and the `ThingRef` destructor alias; reconcile
those providers and every extra emitted COMDAT before a production landing.

The bank includes canonical DynamicAudioEventInfo, Dict, StaticNameKey and
AsciiString declarations, with physical BFME audio views instead of copying
the incompatible ZH audio layout. It retains native float setters and
AudioPriority, and corrects the order to MinVolume then Volume as witnessed by
original NameKey literals/call sites. The obsolete explicit StringBase
specialized destructor had to be removed to compile against current headers.
No arithmetic or rounding mode has been changed.

Important integration constraint: Rva000B6030DynamicInfo uses inline physical
view adapters that reinterpret its pointer for calls to canonical native
DynamicAudioEventInfo methods. This remains experimental scaffolding. Removing
those adapters and casting directly at the parser's calls produces 973 bytes
and 678 differences. The matching prefix therefore does not justify shipping
that view as a second canonical type or claiming the helper graph is resolved.

## Remaining dependencies and bounded negative results

The strict parser check reports these eight unresolved typed call identities:

- address-view constructor corresponding to 000B5CB0
- address-view reference destructor corresponding to 000877B0
- address-view reference copy assignment corresponding to 00087750
- address-view dynamic reference assignment corresponding to 000B5FD0
- typed indexed event accessor corresponding to 00087BD0
- first-receiver sound accessor corresponding to 00416FA0
- address-view permanent-sound test corresponding to 000874E0
- native DynamicAudioEventInfo::overrideLoopFlag corresponding to 000B5650

The five newly landed scalar/priority override methods now resolve. The new
bank does not add aliases to bypass the remaining identities. In particular,
000874E0 returns a full EAX 0/1 and checks +0x84 == 0 or 3, or control bit0 at
+0x3C; the ZH inline isPermanentSound body is not the BFME implementation.

Focused tests that did NOT improve the 33-difference tail:

- sequential versus nested sound/base-reference tests, combined condition
- inverted if/else versus ternary sound selection, shared-label C++ tail
- inline pointer-returning lookup helper, split copy branches
- visible exact indexed/template-provider getter bodies
- final enabled ternary / logical OR / reversed predicate

Early return from the enabled path worsens the whole EH/register shape.
Caching the second allocation's raw input in a manual local also worsens it.
Native setter definitions with noinline visibility leave 980/478 without the
holder pair; allowing those setters to inline changes the body to 1026 bytes.
No broad compiler-flag, register, assembly, or resolver sweeps were performed.

## Reproduction

The bank at `targets/game/reverse/attempts/0x000b6030.cpp` supplies its compiler
flags and exact symbol in the first line generated by re_log.py. Run
`python3 tools/probe.py <bank> <symbol> 0x000B6030 --size 976 --all`.
The holder destructor and copy-assignment symbols are respectively
`??1Rva000B6030InfoRef@@QAE@XZ` and
`??4Rva000B6030InfoRef@@QAEAAV0@ABV0@@Z`; sizes are 35 and 73.
The earlier bank is preserved by re_log's attempt-history mechanism.

## Snapshot-bound declaration corrections

The name guard pairs seven removed old-bank shadow declarations with the new
physical views. The audio owner identity itself is not withdrawn: the canonical
DynamicAudioEventInfo header is now included, and canonical AudioManager is
retained for TheAudio. The old eight-byte AudioEventInfo shell, incomplete event
class, fake manager vslots and extra-argument dynamic constructor were never
complete canonical definitions. The replacement address-qualified views avoid
redeclaring those real types while retaining explicit unresolved ABI evidence.
These are false-pairing corrections limited to the two bank snapshots, not
permission to rename production audio owners. The two holder spellings remain
unproved against the selected ThingRef/Rva00087750Ref/Rva000B5FD0Ref providers.
The ThingTemplate receiver label is independently contradicted by the original
Object caller's drawable/final-template argument order as described above.
