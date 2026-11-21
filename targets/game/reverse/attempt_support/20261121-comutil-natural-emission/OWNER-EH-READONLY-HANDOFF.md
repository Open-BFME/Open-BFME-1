# COMUTIL: local EH ownership, bounded read-only review

**Sicher:** The C61F80 handler is not a mandatory rehome prerequisite to recovering its real343B C++ parent. Native owner-aware verification already supports a parent's compiler-generated local EH thunk and metadata. Leave the old generated row untouched; this review grants0 body/byte credit and does not prove an uncompiled future candidate.

## Exact original/anchor relationship

Original member `Release\comutil.obj` SHA256 a4e82e871bdfdd14760c6eb72ed544a38eaa9e13083ea342c57d75c0325270f6: parent `?ConvertBSTRToString@_com_util@@YGPADPAG@Z` is343B, EXTERNAL2, `.text` section17, NODUPLICATES1. Its DIR32 at+6 points to the local STATIC3/type32 `__ehhandler$?ConvertBSTRToString@_com_util@@YGPADPAG@Z`,10B `.text$x` section19. Handler and80B `.xdata$x` section20 are both ASSOCIATIVE5 to17, so their lifetime/retention follows the parent, not a second public provider.

Fresh retail reads prove AFD8B0+6 -> C61F80; handler bytes `b83c182501e94c4ed9ff` -> FuncInfo E5183C and CRT thunk9F6DD6. Original xdata begins E51808, contains64 non-relocation bytes all exactly equal to retail, and four independent DIR32s: +28->$L60941/AFD96C (inside parent at+188), +48->$T60951/E51818, +60->$T60949/E51808, +68->$T60950/E51828. Full raw bytes and current hashes are in READONLY-PROOF.json.

The existing generated row `eh_00c61f80` instead binds `__ehhandler$?eh_anchor@@YAXXZ` from game/gen_small/eh_anchor.cpp. Its current object hash is a9179bb5f0a8c995948ff4715aa7c881c183a2ebf8d74b63afe79e2dc1be02ca. That is another local STATIC3/type32 symbol at+8 in its18B `.text$x`, not an external duplicate of the real parent handler. The tracked anchor explicitly says that its generic stub reproduces thousands of generated rows; `eh_anchor` itself is not a recovered row. Neither source nor row needs modification for a different object's legitimate local emission.

## Existing sanctioned route and checks

1. Parent identity already occupies AFD8B0 as a vendored member row. After a real whole-member C++ recovery exists, its ordinary same-name source replacement is `tools/add_match.py <original-parent-name> 0x00AFD8B0 343 <proper-source> --replace-existing --model <model>`, with ordinary scoped build/hooks and full-member link closure. This is conditional documentation, not permission to add a duplicate NODUP parent while the archive member is still needed.
2. `tools/build.py:compile_function` compares the parent normally. `dir32_references`3513ff deliberately treats compiler-local EH labels as TU-local, so no live address pin or external alias is required. `body_guard.py`220ff delegates `$T` metadata and skips local code from its data checker; that is not independent EH equivalence proof.
3. The actual owner is `tools/link_cycle.py`, documented51-55 and implemented in `Measure.code_ref`1822-1864. If the local thunk is outside an already mapped unit, it must carry the exact owner's `__ehhandler$` name. `eh_verdict`836ff checks stub shape, verified frame-handler provider, FuncInfo header, unwind transitions/actions, try/catch descriptors and handlers. It creates an EH closure node, not a new function row. `Shifted.eh`3515ff checks the rebased thunk/tables; closure creation3275ff includes every dependency and rejects generated/dump leaves. Existing `test_eh_thunk_counts_for_its_owner_only_when_funcinfo_matches`243ff has positive matching-owner and negative foreign-owner/wrong-unwind controls. Tests were read, not run.
4. The old C61F80 row remains generated, as progress.source_lane475ff requires; it cannot become10B of recovered credit merely because a different real parent now emits equivalent machinery. Native closed-source credit also still requires genuine dependency closure: today's9F6DD6 row is a6B gen-import, not evidence of newly recovered CRT code.

## What is refused and why

Direct10B row retirement remains intentionally unsupported: add_match.replaceable_scaffold58ff / gen_small_repoint170ff exclude gen-ehstub, and test_add_match_gen_small.py194ff explicitly rejects it. This is not demonstrated to be a false reject. `eh_state_pins.py:label_of`191ff accepts only `$L` funclets and fixes their state-bound labels; it is not a rehome tool for `__ehhandler$`. `code_scaffold.code_aliases` requires exported definers and is diagnostic linking scaffolding, not an authorship/rehome route. No whitelist, pin, generator edit or tooling repair is needed/requested for parent-owned emission.

**Remaining member blockers stay real:** the3 small definitions have the measured ANY2 versus NODUP1 collision (or inline zero emission), both conversion parents are original NODUP1, and the typed vtMissing/retained CRT lifetime must be solved for the whole original member. This bounded review changes only the claim that C61F80 must first be rehomed; it does not resolve those other prerequisites or establish a bankable source.

No compiler, linking, tests, source/tool/ledger changes, claim actions or Git commands were performed. Only these private diagnostic files were written.
