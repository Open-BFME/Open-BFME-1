# Datum identity at VA 0x012ACFE0

Unresolved and unchanged. Retail establishes a four-byte single-precision value with bytes CD CC 4C 3E (nearest float to 0.2) in .data. All four competing spellings describe the same scalar type; the image does not establish a source identifier or exclude a compiler constant.

The typed absolute users are the six bodies listed below. They only load or multiply this value with x87 instructions; no direct writer was found. The max-lift-shaped body at RVA `0x001B5A30` multiplies the same address twice in both normal and damaged branches. The existing source explicitly uses distinct external spellings to retain that instruction layout. A bare consolidation would require its own successful byte-preserving compiler experiment.

Zero Hour `Locomotor.cpp` defines `getMaxLift` and `getMaxSpeedForCondition`, but their bodies do not contain this BFME scale or declare a corresponding global. That role comparison therefore cannot establish the datum identity. No data definition or row was added, because the brief forbids defining a compiler constant and the distinction remains open.

A proven retail initialization or writer, an EA identifier tied to this address, or an independent reference declaration with matching use would settle the identity. A successful source consolidation would then have to preserve every current body byte. The current lack of a direct writer is not proof that the object is immutable.

The inspected extent is VA `0x012ACFE0` through exclusive `0x012ACFE4` in `.data`. Initial bytes are `cd cc 4c 3e`. The extent and declaration audit is in `build/rlink/extent-and-declarations.log`. No other DIR32 name lies strictly inside any corrected extent; the only data-row overlap after correction is its own owner.

| Existing decorated spelling | Game files declaring it before correction |
|---|---:|
| `?g_rva001B59ScaleConstant@@3MC` | 5 |
| `?g_rva001B59ScaleConstantDamaged@@3MC` | 2 |
| `?g_rva001B59ScaleConstantDamagedAlias@@3MC` | 2 |
| `?g_rva001B59ScaleConstantNormalAlias@@3MC` | 2 |

Counts use direct game-source declarations and declaration-producing macro invocations, count a file once, and exclude comment-only mentions. The raw search and exact declaring lines are in `build/rlink/declarations-rg.jsonl` and `build/rlink/extent-and-declarations.log`. These counts do not decide the preferred identity.

| Retail user RVA | Ledger spelling | Absolute references |
|---|---|---|
| `0x001B57E0` | `?bfmeRateYL@BfmeHostYL@@QAEMPAVObject@@@Z` | VA 0x5b580c: `fld dword ptr [0x12acfe0]`; VA 0x5b582b: `fld dword ptr [0x12acfe0]` |
| `0x001B5910` | `?getScaledFirst@Rva001B59FloatView@@QBEMPBURva001B59ScaleContext@@@Z` | VA 0x5b592b: `fld dword ptr [0x12acfe0]`; VA 0x5b5947: `fld dword ptr [0x12acfe0]` |
| `0x001B59D0` | `?getScaledSecond@Rva001B59FloatView@@QBEMPBURva001B59ScaleContext@@@Z` | VA 0x5b59eb: `fld dword ptr [0x12acfe0]`; VA 0x5b5a07: `fld dword ptr [0x12acfe0]` |
| `0x001B5A30` | `?rva001B5A30@Locomotor@@QBEMPAVObject@@W4BodyDamageType@@@Z` | VA 0x5b5a60: `fld dword ptr [0x12acfe0]`; VA 0x5b5a66: `fmul dword ptr [0x12acfe0]`; VA 0x5b5a7d: `fld dword ptr [0x12acfe0]`; VA 0x5b5a83: `fmul dword ptr [0x12acfe0]`; VA 0x5b5a9e: `fld dword ptr [0x12acfe0]`; VA 0x5b5aa4: `fmul dword ptr [0x12acfe0]` |
| `0x001B5C00` | `?bfmeComputeET@BfmeHostET@@QAEMPAVBfmeThingET@@PAM@Z` | VA 0x5b5c2b: `fld dword ptr [0x12acfe0]` |
| `0x001B7E90` | `?effectiveMaxSpeed@BfmeSub1CC_EC3@@QAEMPAX@Z` | VA 0x5b7efc: `fld dword ptr [0x12acfe0]`; VA 0x5b7f16: `fld dword ptr [0x12acfe0]`; VA 0x5b7f24: `fld dword ptr [0x12acfe0]`; VA 0x5b7f3c: `fld dword ptr [0x12acfe0]` |

Raw retail data, complete user disassembly, all five-byte E9 routes to these users and callers through the routes are retained in `build/rlink/retail-probe.log` and `build/rlink/focused-retail.log`. The latter rejects raw byte coincidences that are not data operands, but any remaining instruction-shaped references need their enclosing body context. The parse-real callback is independently disassembled in `build/rlink/parse-real-retail-full.log`.

For corrected addresses, `build/rlink/add-data-012acfe0.log` records the byte, sizeof and relocation gate. Relevant per-source gates are `build/rlink/after-<source-stem>.log`; all changed sources are listed in `build/rlink/changed-sources.json`. Ledger, pin and declaration gates are `check-csv-after.log`, `pin-consistency-after.log`, and `declared-unmatched-after.log` in that folder. Per-file LINKED results and remaining unrelated blockers are in `link-before.log` and `link-after.log`.
