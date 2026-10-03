# FloatingTextData constructor: canonical wide string

RVA `0x0043F4D0`, 101 bytes, `??0FloatingTextData@@QAE@XZ`.
The TU duplicated UnicodeString despite the canonical WWLib
`unicode_string.h`. AGENTS.md requires including an existing header rather
than redeclaring its covered type. This source hygiene repair removes only
that duplicate; other pre-existing layout views are not newly identified.

The GeneralsMD twin in GameClient/InGameUI.cpp:5236 has the same field
initializations, explicit text clear and newDisplayString dispatch. Retail
and Ghidra MCP VA `0x0083F4D0` agree on the complete 101-byte constructor:
RET at RVA `0x0043F534`, followed by INT3. The string at receiver +8 is
zero-initialized, then the clear call at `0x0043F510` reaches the existing
StringBase<unsigned short>::releaseBuffer body `0x008881D0`.
Display-string dispatch remains the witnessed vtable slot +0x24.

The native lifetime is independently witnessed by the constructor prologue:
handler RVA C22A0B -> FuncInfo E12C34 -> state0 action C22A00. That action
loads the saved receiver, adds8, and jumps through ILT3B304 to UnicodeString
destructor5EEA0. `tools/eh_info.py` records the chain in
`build/audit_v3/s6_floating_eh.txt`; no new cleanup row is claimed.

Include the canonical UnicodeString and inline its actual zeroing default
constructor locally, following the already verified text-label helper.
Use the public StringBase<unsigned short>::clear() through the same native
wide-string layout view used by the canonical header. No fabricated class,
callee alias, manual destruction, or shared-header change is needed.

Fresh origin/master still has this same row and duplicate declaration.
The bounded 12-second pickaxe expired, so no introduction commit is asserted.
This row survives from the August 1 cohort. Before/after scoped gates pass
1/1 function and two recorded DIR32 references (vtable and display-string
manager). No identity, extent, pins, baseline or coverage change.
Logs: `build/audit_v3/s6_floating_before.log`, `s6_floating_after.log`.
