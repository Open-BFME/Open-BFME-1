# Retail filter dispatch array at VA 0x01128B24

The missing datum is defined once in game/GameEngineDevice/Source/W3DDevice/GameClient/Rva007D6B70Ctor.cpp using its existing exact compiler symbol ?g_01128B24@@3PAPAXA and element type void *. The complete physical array has seven 32-bit code pointers. This retains every source identity and function body and does not add inheritance or guessed members to Rva007D6B70. The ordinary identifier g_01128B24 is declared and consumed by one game source file; there is no competing recorded spelling, interior owner or overlapping data row.

Retail SHA-256 is 1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75. The array lies in .rdata. Its initial bytes are a6 15 44 00 de 54 40 00 88 b3 41 00 ae f4 43 00 7d 0d 43 00 71 e9 40 00 74 ea 41 00. The constructor at VA 0x00BD6B70 stores the array base into the receiver at VA 0x00BD6B74, zeroes fields +4 through +0x44, returns the receiver, and uses RET with no arguments. The static initializer reaches this constructor through the actual ILT route, retained in filter-static-ctor-caller.log.

| Slot | Retail pointer VA | Five-byte ILT bytes | Final body VA | Observed receiver and arguments |
| --- | --- | --- | --- | --- |
| 0 | 0x004415A6 | E9 35 50 79 00 | 0x00BD65E0 | ECX receiver; no stack arguments; EAX success; RET. |
| 1 | 0x004054DE | E9 2D FA 7C 00 | 0x00BD4F10 | ECX receiver; no stack arguments; releases receiver resources; EAX=1; RET. |
| 2 | 0x0041B388 | E9 F3 96 7B 00 | 0x00BD4A80 | ECX receiver; two writable pointer arguments; sets first byte to zero and second dword to six; AL=1; RET 8. |
| 3 | 0x0043F4AE | E9 6D 5B 79 00 | 0x00BD5020 | ECX receiver; four stack words; dispatches slots 5 and 6; Bool return; RET 16. |
| 4 | 0x00430D7D | E9 3E 5E 7A 00 | 0x00BD6BC0 | One stack argument; AL=1; RET 4. |
| 5 | 0x0040E971 | E9 7A 79 7C 00 | 0x00BD62F0 | ECX receiver; mode word; EAX success; RET 4. |
| 6 | 0x0041EA74 | E9 07 64 7B 00 | 0x00BD4E80 | No stack arguments; resets device state; tail-jumps to VA 0x00D03C50, whose ordinary RET preserves the no-argument contract. |

The seven-cell extent follows from the complete ordered dispatch contracts, not the initial observation window. Zero Hour W3DShaderManager.h declares exactly seven slots, in this same order: init, shutdown, preRender, postRender, setup, set and reset. Retail filterPreRender at VA 0x00B16A10 forwards two arguments to vptr+8; filterPostRender at VA 0x00B16A50 forwards four words to vptr+0x0C; filterSetup at VA 0x00B16AA0 forwards one mode word to vptr+0x10. The post-render body calls vptr+0x14 at VA 0x00BD5056 and vptr+0x18 at VA 0x00BD5EE3. This witnesses the two last slots in the same physical table. BFME adds a fourth post-render word relative to Zero Hour; the RET 16 and the actual caller agree. No EA class identity is inferred from the reference.

The array is bounded before its first slot by the separately referenced EXVapor01.tga string at VA 0x01128B14. The bytes after its last slot are two zero dwords at VA 0x01128B40 and VA 0x01128B44, followed by the separately referenced shaders\hilightfilter.pso string at VA 0x01128B48. Every file-backed section was scanned for every byte-address across the claimed array and the following zero dwords. The only array-base reference is the constructor immediate at VA 0x00BD6B76; there are no interior or separator references. The adjacent strings have independent retail references. The seven reference slots, matching retail dispatch offsets and argument cleanup, and independently referenced neighboring literals establish the complete pointer run.

Raw evidence is under build/rlink/dir32-six-20261008/: retail-probe.log records bytes and the constructor; contracts-boundaries-owners.log and absolute-refs.json record all ILT chains, slot bodies, overlap checks and address references; body-00bd*.log record complete slot bodies; filter-pre-call.log, filter-post-call.log, filter-setup-call.log, filter-shutdown-caller.log and filter-reset-full.log record retail callers and cleanup; reference-contracts.log records the unmodified reference interface. names-consumers.log, source-declarations-count.log, implicit-symbols-fixed.log and consumer-coff.log check source and compiler scope.

The PE has no base-relocation directory. Normal add_data_match.py admission checks sizeof the actual array and each compiled COFF DIR32 initializer against the seven retail cells. ILT declarations provide pointer values only and are never invoked through opaque signatures. The decorated text in the TU is a real external definition. No linker alias, shared header, function ledger row or pin changes.

An eighth virtual slot belonging to this lead, a different ILT chain or slot cleanup, an interior recorded owner, another actual source consumer of this compiler symbol, overlap with an adjacent literal, or any changed verified constructor byte would refute the claimed extent or scope.

Compiler probes of every additional game source containing these class names emit no reference or definition for any of the six array symbols, and no corresponding implicit vftable symbol. The eight additional TUs compile successfully; implicit-coff.log preserves their actual compiler output and zero relevant-symbol counts. constructor-routes.log records each real caller and the five-byte ILT route to the constructor.

Normal admission, the unchanged official key test and ./build.sh each exit zero; their raw logs are admit-01128B24.log, pass-01128B24.log and build-01128B24.log under the evidence folder. The official test deletes this key's baseline line. The function body remains textually identical, and every row in its source passes byte verification. source-body-preservation.log records the textual comparison.

Final ledger checks pass: check-csv-after.log, pin-consistency-after.log and declared-unmatched-after.log. Ordinary linking is measured in link-before.log and link-after.log. This source changes from LINKED 0 to 62 bytes and links cleanly.
