# Corrected bank for retail RVA 0x001B0E90

## Scope and boundary

This is a nonmatching saved attempt, not a C++ recovery. The current ledger retains the generated dump `?d_001b0e90@@YAXXZ` at `game/gen_asm/d_001aba80.asm`, extent 337 bytes. Retail's final `ret 8` starts at body offset `+0x14E`; its complete extent ends at `+0x151`, followed by INT3 padding. The matched `BuffTransfer0040A260::transfer` caller reaches the body through ILT RVA `0x000397FC`, supplies two pointers and uses the returned snapshot pointer. The bank preserves that address-derived caller contract; the original factory and callback class identities remain unknown.

## Independently observed correctness repairs

### Formatting arguments

The literal at VA `0x0109C918` is `No draw module specified for Buff! In Buff (%s)` and has exactly one conversion. Retail pushes the name character pointer at `+0x62`, reserves four bytes for a by-value `AsciiString` at `+0x63`, constructs that object via RVA `0x00888BC0`, and pushes the message receiver at `+0x78` for the cdecl `AsciiString::format` call at RVA `0x00888FF0`. Caller cleanup at `+0x7E` is `add esp,12`.

The previous bank passed raw record-range byte length as an additional first vararg. That incorrectly supplied an integer to `%s` and required 16-byte cleanup. The corrected bank passes only the template name. Its argument cleanup is now 12 bytes. The existing `AsciiString::str()` accessor replaces the handcrafted string storage/helper; `string_base.h` independently describes the null-string fallback at retail VA `0x0107388B`.

### Terrain virtual slot

The previous address-derived terrain view jumped from declarations `slot88` to `slot90`, omitting `slot8C`. Its method labelled `slot90` consequently occupied physical offset `0x8C`. Retail dispatches through `[edx+0x90]` at `+0x138`. The missing offset placeholder is restored, preserving the witnessed `(context,result)` stack arguments and pointer result without inventing a native method identity.

The native Zero Hour `TerrainVisual.h` has no BFME Buff callback declaration, so its full layout does not establish this slot. The bank retains an address-derived local slot view, as existing matched `Rva001A3410TerrainDispatch.cpp` does.

### Existing pointer owners

| Retail operand offset | Retail VA | Existing owner |
| --- | --- | --- |
| `+0xC2`, `+0xD0` | `0x01336E5C` | `void *g_Rva00F36E5C`, `Libraries/Source/debug/Rva00F36E5C.cpp` |
| `+0x12C` | `0x012F7014` | `TerrainVisual *TheTerrainVisual`, `GameClient/Terrain/TerrainVisual.cpp` |

Both cells already have independently verified four-byte zero data rows. Explicit casts preserve the witnessed virtual ABI views. The bank adds no provider, alias, pin, data row or shared header. The entry-object callback is physical slot `+0x28`, takes no stack arguments and returns a pointer. The debug callbacks remain `+0x60` and `+0x6C`.

## Actual attempt results

The initial current bank emitted 368 bytes. Removing the extra argument emitted 351 bytes. Two bounded range/accessor shapes emitted 349 bytes and still failed. The final combined correctness source emits 351 bytes against retail's 337, with 254 non-relocation differences. Its first drift is at offset `+0x1B`: retail loads the range end before preserving the begin pointer in EDI; the draft uses another register schedule. The warning block also remains after the success block.

The normal `re_log.py record ... partial --stash ...` tool measured the corrected bank at **0.1632**, and preferred it over the remeasured old source. The probe's normalized instruction-shape figure **0.717** is a diagnostic and is not its measured byte score. The canonical bank SHA256 is `28b008cd3f2ab1f24fd6a95a3026a14d2e94007024b2640f40792e2865066d61`; its immutable history JSON records `score_kind=measured` and `score=0.1632`. The prior exact source is retained separately in immutable history.

All compile/probe and automatic score measurement results above completed before the permission transition. No further Wine probes are claimed. No production source, function ledger, symbol ledger, provider, baseline or header was changed, and new implementation/data/headline credit is zero.

## Claim and environment outcome

The ordinary `claims.py release 0x001B0E90` command was invoked before the permission transition. Both local claim refs are now absent, but the old terminal handle is unavailable, so a terminal result is not invented. Fresh authoritative remote verification now exits 128 with `Could not resolve host: github.com`; its exact receipt is `build/native_1b0e90/release_verification.json`. This network failure is separate from the source byte mismatches. A fresh ordinary release retry exits 0 but explicitly reports `origin unreachable; releasing nothing` and `released 0`; its receipt is `build/native_1b0e90/release_retry.json`. That process exit does not confirm a released remote claim. Remote release confirmation remains unavailable until network access works.

Scratch probes and logs are in `build/native_1b0e90`. The corrected source is banked under `targets/game/reverse/attempts/0x001b0e90.cpp` and has not been placed in `game/`.
