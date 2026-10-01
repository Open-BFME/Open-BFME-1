# DirtySock: canonical native CloseHandle import

## Independent identity and native physical contract

Actual retail PE import-directory cells independently identify `0x01358CCC` as
`KERNEL32.dll!CloseHandle` and `0x01358D00` as `KERNEL32.dll!CreateThread`.
The matched 247-byte `_Rva007FE520` contains one call to each; the independent
full-extent `callees.py` receipt confirms both. Existing canonical DIR32 mapping
`__imp__CloseHandle@4` agrees with the actual retail cell.

Existing pristine Gamespy C `windows.h` line 116 supplies
`BOOL __stdcall CloseHandle(HANDLE)`. Native VS2003 PlatformSDK `WinBase.h`
lines 2989–2994 independently declares `WINBASEAPI BOOL WINAPI
CloseHandle(IN OUT HANDLE hObject)`. HANDLE is a pointer-sized void pointer and
BOOL is int; both are four bytes for this actual x86 compiler. One argument is
pushed, the callee pops four bytes, and the BOOL return is discarded. The old
TU-local `void __stdcall(int)` import did not express that native contract.

Retail's CreateThread call at `0x007FE584` stores EAX into the same thread word
at `0x007FE591`. The CloseHandle operand reloads that word at `0x007FE5BB`, pushes
EAX at `0x007FE5C0`, then calls through the proven native IAT at `0x007FE5C1`.
The stored representation remains a four-byte word; the native HANDLE cast
expresses the actual already-stored native thread-handle operand without
changing its bits. No struct, member, global type or layout is changed.

## Minimal repair and full byte checks

Owning clone `build/link_y4_sleep_fresh_36h`, base `8f44690408`.
Scratch `build/y4_closehandle_import`.

Remove one old local address-derived import declaration and change one call to
`CloseHandle((HANDLE)g_Rva0130ACB8Thread)`. The existing C header was already
included. No headers, compiler flags, pins, aliases or other Windows imports
change.

Before79838 and after12976 gates both exit0: **40/40 functions, 113 DIR32**,
zero string/float references. Complete COFF audit compares every raw matched
body and every relocation offset/kind. Exactly one external symbol changes:
`_Rva007FE520` +163, DIR32, old `__imp__Rva01358CCCRelease@4` to
`__imp__CloseHandle@4`. Compiler-local renumbering is permitted only if section,
value, type and storage class remain identical. The whole247-byte caller is
bytegreen; it is not asserted to be completely linked.

## Strict physical native import controls

Controls13759 exit0. The object contains exactly the twelve original compiled
bytes at `0x007FE5BB`: MOV EAX from the thread storage, PUSH EAX, FF15.
Faithful extraction is reparsed and checked against original COFF bytes and
relocations, then independently compared to retail outside its two DIR32
operands (storage +1, native IAT +8).

- Native positive LINK0: selected MAP and selected PE import-directory cell
  agree on actual `KERNEL32.dll!CloseHandle` at `0x10002000`. The actual FF15
  operand targets that exact native slot.
- Original alias LINK96.
- Missing native Kernel32 archive LINK96.
- Fake canonical IAT LINK0 but selected-import audit refuses the non-native
  cell; a successful link alone does not prove import identity.

Positive uses actual native import archives with `/NODEFAULTLIB`, no `/FORCE`,
no weak alias and no fake native import. Its only unrelated scaffold is
`_g_Rva0130ACB8Thread`; the selected MOV operand demonstrably targets its selected
MAP address (`0x10001010`) and pushes the loaded four-byte representation.
That scaffold is not a runtime handle-value proof or a matched native datum.
The guard/producers and the other native imports are outside the twelve-byte
edge control; this packet makes no full247-byte/runtime closure claim.

Actual input hashes, numerical exits, MAP/PE artifacts, complete all40 audit
and argument-operand check are archived in `controls.json` and adjacent files.

## Currency and gains

Published ThreadId three paths were verified against origin; all three leases
were normally released with --landed b9f60c. Normal sequential pull/rebase and
check_csv preceded this new claim. Official link_check76418 reports TU
**LINKED0 ->0**, 6988 own bytes, with remaining unresolved imports/data/callees
listed. Before source SHA256 equals the published ThreadId source:
`7f308fb171b487951fbfbda4139e96d55c5a57397c56bd480534363c63016d55`;
its independent official ThreadId after receipt supplies the same before state.

Pin consistency and CSV pass (171166 functions, 89947 symbols, 26 data rows).
No functions/data/symbol/pin ledger changes. **0 new code, 0 data and 0 whole-TU
linked-byte gain**; one genuine native import edge repaired.
