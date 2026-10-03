# ScriptActions action 480 at RVA 00303910

## Identity and ABI

The bank's `doTeamRepairNearest` name was attributed to a supposedly matched
caller and the `TEAM_REPAIR_NEREST` string. The caller provider,
`ScriptActionsExecuteActionThunk.cpp`, is actually a naked byte dump and
contains no source-level call naming this method. Independent retail dispatch
also refutes the claimed action association: RVA303C24 indexes table VA70D6A0
by the action enum. Entry479 reaches RVA30C9DF and the one-string/float body
00303670. Entry480 at VA70DE20 reaches RVA30CA4E, whose call at30CA6E uses
ILT459B7 to00303910 and passes two parameter string fields by reference.
The existing script-template initializer associates `TEAM_REPAIR_NEREST`
with479 and a team/radius parameter pair, not480.

Keep the ScriptActions receiver inherited from executeAction's saved ECX,
but call this method `rva00303910`. Its two const-reference string arguments
and thiscall ABI follow the dispatch arm and RET8 at00303A61; INT3 starts
at00303A64. Ghidra and direct PE disassembly confirm the340-byte body.

## Indirect calls and the bank's wrong health label

Object's body pointer is read at+200. ActiveBody constructor00211A50 installs
secondary table VA010A7718 at owner+10 (store00211AA6). Slot4 contains
ILT40A29A ->0020E140, a raw load from interface+08. Slot5 contains
ILT441B78 ->0020E150, which checks interface+10 then divides interface+08
by interface+10, with a zero-result fallback. The constructor independently
places current/max health at owner+18/+20. Therefore the bank's slot5
`getHealth` spelling incorrectly names the ratio getter as the raw getter.
The TU uses the proven BodyModuleInterface type and an address-qualified
slot14 method, without asserting an original ratio-method name.

The ScriptEngine dispatch at slot44 takes a by-value AsciiString and bool
and returns a team pointer. Its local view and slot spelling keep the body
address; the canonical external global remains ScriptEngine*. The Zero Hour
getTeamNamed declaration instead takes one const-reference string, and does
not establish this BFME overload's spelling. No semantic slot name is promoted.

## Source shape and binding checks

Start from the served bank. Repeating `if (!object) continue;` in the first
loop changes346B/202 differences into341B/78. Repeating it in both loops
removes the remaining alignment difference and matches340 bytes modulo nine
relocations. Canonical ascii_string.h preserves that exact result; the
established ObjectDlinkPmf.h model supplies the witnessed virtual-base PMF
encoding. ILT1140 reaches000C8980, reading this+260 after the PMF's +4
adjustment.
Existing string-base copy, override and AI repair symbols are reused; strict
verification passes for all340 bytes and all four DIR32 references. No new
pin was needed.
