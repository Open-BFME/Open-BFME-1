# Guarded Q1 registry call: use the existing provider

Base `fadddcc7e908b4df2fd3a02d3dc0125b393ee3f6`; claimed row
`Rva009EBBC0`, RVA `009EBBC0`, 21 bytes.

## Target facts

The complete native wrapper loads `g_theAssetRegistry` at VA `0134FAAC`,
null-tests it, forwards its one stack word and directly calls `009EEEC0`.
It neither adjusts the receiver nor cleans the forwarded argument. The
existing 69-byte row `BfmeQ1172::bfmeGo1172(int)` owns that callee. Its native
body uses the incoming ECX, the critical section at +2C, the table at +44,
the iterator at +58/+5C and its int argument at +1E8; it ends in RET 4.
The provider is unchanged and verified together with the caller.

Replace the declaration-only `Q1Receiver0134FAAC::m009EEEC0(int)` call with
that existing provider, through a cast of the same canonical global pointer.
Remove only the obsolete declaration. All 21 raw caller bytes remain identical;
the global DIR32 relocation at +2 is unchanged and only the REL32 referent
at +16 changes. No new name, pin, alias, data row, layout or header is added.
Normal verification passes all 14 rows in the caller/provider pair, including
15 DIR32 references and zero body-guard findings. Frozen definitions pass.

## Donor review and limits

BFME 2 reference `b5a7b8290a0c4c20b03a3664609d434904e228eb`,
`Code/Libraries/Source/assetmanager/q1_registry_forwards.cpp`, uses the same
declared-provider call-binding pattern on its guarded registry wrappers
(`Gen_009EBB60Target` and `AssetRegistry`). Its provider/layout differences
and the partial registry declarations in `assetmanager_impl.cpp` are retained
as donor context only. No BFME 2 address, wrapper name, body or class layout
is asserted to be this BFME 1 target. BFME 1 native calls establish the actual
identity and ABI above. No other call to the removed member exists in `game/`.

Against the frozen `1d5131d3f1` index, the file's unresolved names decrease
from three to two, but it remains unlinked: the QuickMatch global and its
`m0003CAD3` call still have no current source provider under those spellings.
That separate callee is the still-dump 1,254-byte body at `00508660`, reached
through ILT `0003CAD3`; it is not a trivial additional respelling to claim.
Frozen LINKED remains 0 -> 0. The current selection preview is UNKNOWN because
22,720 newer/missing objects are unavailable; no current/full linking gain is
claimed. The fetch helper refuses an existing index; the latest successful
workflow is already the same `1d5131d3f1` snapshot, so the existing index is
preserved and no unchanged broad scan is repeated.

Qwen only reviewed the supplied two-body ABI summary on four CPU threads.
Its generic caution supplies no independent proof or source patch. Full native
disassembly, original source/object, relocation comparison and ordinary gates
are saved under `build/continuation-20261031-1514` and the create-only local
diagnostic run `W:/OpenBFME/diagnostics/continuation-20261031-1514`.
