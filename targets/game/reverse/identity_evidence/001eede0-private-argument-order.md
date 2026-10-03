# AutoHeal update and private predicate argument order

Retail update RVA 0x001EEDE0 ends with RET at +0x4BF and INT3 at +0x4C0: 1216 bytes. The Zero Hour twin is `GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/AutoHealBehavior.cpp:186`, `AutoHealBehavior::update`. Both split into whole-player, zero-radius self-heal, and filtered range-scan paths, invoke the same owner method `pulseHealObject`, and return UpdateSleepTime. BFME adds the witnessed scan-policy fields and reference-counted range-result handle. Retail calls the existing `pulseHealObject` pin through ILT 0x00045B2E to 0x001EECB0.

The bank missed only the order of LEA EAX,[ESP+64] and MOV EBX,ESI at update+0x3B5. Reordering the static predicate's C++ parameters from (helper,object) to (object,helper), and updating both native call sites, produces exactly 1216 instruction bytes modulo 40 relocations. The compiler still chooses the same private machine ABI: EAX points to scan data and EBX to the candidate Object. No external conventional ABI is imposed on this static function.

The predicate at 0x001EE670 retains its address-qualified identity. Its RET is at +0xDE, then INT3 at +0xDF (223 bytes). The swapped-signature body is independently instruction-exact over those 223 bytes and six relocations. The old and new decorated spellings describe the same compiler-private body, not two identities. The existing callback at 0x001EED80 has RET at +0x41 and INT3 at +0x42 (66 bytes); it must also pass the scoped gate in the final TU.

Object and Thing use the canonical Object header, its documented TU-member hooks, cached position at +0x38, body/AI at +0x200/+0x204, geometry storage at +0xAC and private status at +0x344. No shared header changes are required. The existing GeometryInfo view remains BFME-specific: Object's canonical header explicitly states that its 92-byte geometry is not geometry.h's upstream layout. An attempted inclusion of the upstream geometry header also reaches unavailable PreRTS/Lib/BaseType dependencies; no shared shim repair is justified for this body. Coord3D has multiple non-equivalent headers per docs/header_adoption.md.

The range call reuses the existing `BfmeWideForwardC::bfmeForwardWideC(int,float,int,int,int)` pin at 0x009F2960 rather than creating an unproven semantic alias. Independent retail decoding shows receiver+0x0C forwarding, six stack words including hidden result storage, returned EAX equal to that storage, and RET24 at +0x36 followed by INT3 at +0x39 (57 bytes). The native float argument is forwarded as one unchanged word. The existing bank archive 8863dc8119775dabb56e13f67cfefb5bb6f524268d36c60f980f5390debe5129 already used this same call spelling.

Instruction equality alone is not acceptance: the final source and all three rows require strict call, literal and DIR32 verification before a production commit.

## Final verification

Both add_match transactions passed. The final TU passed all three rows (1216/223/66 bytes), all call bindings and 14 DIR32 references. No new symbols.csv pin was needed. The helper's old decorated source signature was retired with a tombstone; the callback row and bytes are unchanged. The update replaces only its generated scaffold row. Model: gpt-6-astra.

## Commit blocked; production restored

The subsequent commit hook rejected two pre-existing `/alternatename` directives in unrelated files after `origin/master` advanced: `Rva003C8340.cpp` and `Rva00803080Set.cpp`. The hook reports that these aliases no longer exist upstream and their local aliases lack a judgeable pin. No AutoHeal instruction or relocation check failed. No hook was bypassed and no baseline was enlarged.

The uncommitted source/ledger/helper-signature changes were restored. The complete strictly verified source is now the improved update bank, with the original callback/predicate retained in production. The converted verdicts were retracted through re_log. After launcher synchronization removes the unrelated aliases, reapply the helper signature correction (same 223-byte range and address-qualified identity), then replace the update scaffold; rerun strict verification and the normal commit hook.

## Reapplication after the external guard fixes (2026-10-03)

Upstream commits `f3ef066627` and `c86648d2ae` removed the two unrelated
aliases above. The unchanged best bank (SHA-256
`dc384036102963e6f57418b57e4bb9d93b8c2eed63e24dfcde893b5c72920b95`)
was promoted through the two normal `add_match.py` transactions. The predicate
keeps its address-qualified identity and exact 223-byte range; its old source
signature is tombstoned. The 1216-byte generated update row is replaced by the
real AutoHealBehavior method. The existing 66-byte callback is unchanged.

Fresh strict verification passes all three functions, their call bindings,
and 14 DIR32 references, without new pins or shared-header changes. Ghidra
12.1.2 through pyghidra-mcp independently shows LEA EAX,[ESP+0x64], MOV EBX,ESI,
and CALL 0x005EE670 at VA 0x005EF195. Direct reads at VA 0x005EF29F,
0x005EE74E, and 0x005EEDC1 each return `C3 CC CC`, confirming each final RET
and following padding. These corroborate the existing private-ABI proof;
decompiler-created names are not identity evidence.

The complete preferred bank is now live source rather than a second competing
implementation. Its archived history and the original evidence remain intact.
