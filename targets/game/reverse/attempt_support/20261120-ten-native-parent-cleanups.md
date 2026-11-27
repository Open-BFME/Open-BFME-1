# Ten native C++ parent cleanups

All ten previously depended on missing or lifted parent bodies. The current readable parents now emit the complete native unwind tables. Fresh private compiles and current ordinary objects prove parent and action bytes, complete extents, state relationships and every in-extent relocation, without masking or unresolved symbols. Source and object hashes plus disassembly are retained in diagnostics/continue-20261120-body-recovery-1656/agents/melee/eh-candidates-fresh-proof.json.

| Action RVA | Bytes | Parent RVA | State | Native label |
| --- | ---: | --- | ---: | --- |
| 0x00C10768 | 22 | 0x0027F4B0 | 1 | $L15456 |
| 0x00C23208 | 39 | 0x0044AE70 | 1 | $L10559 |
| 0x00C2325B | 22 | 0x0044AE70 | 6 | $L10564 |
| 0x00C23271 | 24 | 0x0044AE70 | 7 | $L10565 |
| 0x00C23289 | 24 | 0x0044AE70 | 8 | $L10566 |
| 0x00C23357 | 24 | 0x0044AE70 | 22 | $L10580 |
| 0x00C233C3 | 24 | 0x0044AE70 | 29 | $L10587 |
| 0x00C44730 | 11 | 0x0066AB30 | 0 | $L11231 |
| 0x00C471E8 | 25 | 0x00693B90 | 0 | $L6447 |
| 0x00C47201 | 11 | 0x00693B90 | 2 | $L6450 |

Parents: AIUpdateInterface constructor (1237B), InGameUI destructor (936B), ConnectionManager::update (814B), and the address-derived Miles audio worker at 0x00693B90 (525B). Their existing code is unchanged. The audio worker keeps its opaque identity; a byte match does not establish a more descriptive name.

RVA 0x00C44730 has four byte-identical labels elsewhere in its object. The full parent unwind map selects state 0 and $L11231 uniquely; the native judge reports twin_proof=state-index. It is not accepted on byte uniqueness. Other actions have unique native labels. Existing Snapshot, vector-destruction, operator-delete and audio-handle calls retain their physically verified target addresses.

Each row is admitted separately through add_match.py compiler-label admission, built with build.cmd, committed normally, and checked with eh_state_pins.py --commit. Original generated dumps stay untouched. The ten rows contribute 226B of compiler-emitted cleanup coverage from readable parents, not ten new main functions. No full-image link, memory fix or runtime result is claimed.
