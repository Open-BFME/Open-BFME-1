# RVA 009F4900: native member recovery attempt

Baseline: `8200647531ff7bba7eaab029619f726f3f3a2c5b`, 2026-10-05.
Outcome: banked diagnostic only. No production source, function row, symbol pin,
generated file, verifier, baseline, or runtime was changed. Progress is zero.

## Physical contract and extent

The generated row at `game/gen_asm/d_009f2f00.asm:358` covers 225 bytes.
Retail saves incoming ECX in EDI at +08 and restores that unchanged receiver
before the four direct calls. The stack arguments are a node and three output
pointers, in +28/+2C/+24 node-field order. `RET 16` is at +DE; the next 15
bytes, beginning at RVA 009F49E1, are INT3 padding. There is no EH registration,
funclet edge, direct global, literal, or DIR32 relocation in this body.

The matched `Gen009F5040::handle` (009F5040, 148 bytes) and
`linkNode_009F4D80` (009F4D80, 181 bytes) independently pass this receiver and
those four stack arguments, and do not consume EAX afterward. An address-qualified
void member is therefore supported; no vendor semantic name is asserted.
The same file's `remove` remains 134 bytes at 009F4E40.

`tools/callees.py 0x009F4900 225` reports these two providers, each used twice:

- `?bfmeIndexER@BfmeHostER@@QAEIM@Z`, 009F46E0, 100 bytes,
  `game/GameEngine/Source/Common/BfmeConv2039.cpp`.
- `?bfmeIndexES@BfmeHostES@@QAEIM@Z`, 009F4750, 101 bytes,
  `game/GameEngine/Source/Common/BfmeConv2040.cpp`.

Their complete bodies were inspected and passed the scoped gate. Each reads one
float argument, the receiver's float scale at +E8 and unsigned count at +EC,
returns unsigned EAX, and executes RET4. ER reads the base at +00; ES at +04.
Both receive the original unadjusted receiver. These are overlapping existing
ABI views, not evidence of inheritance. No new aliases or pins are needed.

The four COFF REL32 operands are +31, +4A, +61, and +7A. Physical retail
routes are respectively 009F46E0, 009F4750, 009F46E0, and 009F4750.
The existing symbol map independently resolves each exact name to that RVA.

## Required memory and arithmetic order

Call item virtual slot +00, retain that pointer, call item slot +04, and only
then load the first result's float at +10. The second result supplies floats
at +00 and +04. Store each of the first two index results immediately. XOR the
third index with the first stored output before calling the fourth indexer;
combine that result with the second output and store the difference output.
For a nonzero difference, clear only its highest set bit in the first two
outputs. The inlined 16/8/4/2/1 search matches the source algorithm of the exact
64-byte `log2Dword` donor at 009F47C0, but retail makes no out-of-line call to it.

## Measured improvement and remaining blocker

The bank is a complete experimental TU retaining all three existing functions
and replacing the inherited union call adapter with a real native member.
The simplest faithful source immediately matches through +8B, including both
virtual calls, the delayed float load, all four direct calls, all four receiver
setups, the output stores, and the pre-fourth-call XOR. It emits 228 bytes rather
than 225. The first differing byte is the branch displacement at +8D.

The residue starts in the inlined first log2 step. Retail copies ESI to EAX,
clears ECX, tests EAX against FFFF0000, and shifts EAX in the taken arm. The
compiler instead clears ECX, tests ESI, copies ESI to EAX, then shifts ESI and
copies it again in the taken arm. This adds three bytes and shifts the tail.
An independent aligned comparison confirms that the final 64 bytes are exactly
equal: retail +A1..+E0 equals compiled +A4..+E3. This shifted suffix does not
reduce the strict 78-offset-difference result or satisfy the native extent.

Six small faithful variants all produced that same 228-byte result: direct
search, force-inlined donor, ordinary inline donor, signed difference temporary,
visible external donor, and early-return zero guard. The direct-search version
is preserved, with no extra donor emission. No assembly, barriers, arbitrary
compiler switches, fabricated inheritance, or union workaround was added.

`probe.py` reports 78 non-relocation differences and structural similarity
0.977. That similarity is not a byte-match score. `re_log.py` independently
measured the bank at 0.6267, using the repository's distance formula including
twice the three-byte size error. Five old blocked records describe the older attempt; four explicitly report
153 non-relocation differences. None had a source bank. No stronger bank existed.

Strict `compile_function(..., retain_compiled=True)` found no unresolved calls
and no masked fallback. Its boundary check correctly rejects claiming 225 bytes:
the compiled body would stop after POP EBX at +E0, omitting RET16 at +E1.
The native retail size must not be expanded to fit the experiment.

For diagnostic caller verification only, the witnessed native member's RVA was
added to an in-memory copy of `load_symbol_map()`. No persisted pin was created.
The full experimental handle148, linkNode181, and remove134 all remain strict
byte-exact with valid boundaries. The bank's only defined external code symbols
are those three and calculate_009F4900; it emits no log2 donor, index provider,
EH helper, or additional strong definition. This is evidence about the bank,
not production integration or new recovery credit.

After reverting the experimental production source, the affected TU, both
provider TUs, and the log2 donor passed 6/6 functions across four sources:
zero string references, two verified float constants, and four checked DIR32
references. `progress.py` against the exact baseline reports +0 bytes in all
conversion, linking, and exact-coverage categories. Its linking census remains
the existing historical snapshot; this attempt makes no fresh census claim.

The bounded attempt stops here. Resume from the bank only with a new reason to
change the first inlined log2 copy; repeating the same getter/provider shapes
is unnecessary. Production must remain unchanged until all 225 bytes and all
three existing bodies verify together.
