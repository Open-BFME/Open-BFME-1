# MultiList CRT registration 0x00C6E1C0

Baseline SHA256 1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75. CRT slot VA0x012A5E08 contains VA0x0106E1C0. Registration body is12B: push callbackVA0x01071520; call __atexit RVA0x009F6E26; popECX; ret. Preceding/following INT3 padding and BoundaryValidator support exact boundary. It has no global-pool operand and zero stack arguments. Keep address-derived ledger identity; compiler initializer ordinals are provider labels, not source-level function names.

Callback RVA0x00C71520/40B starts at preceding padding boundary and returns before following padding. It reads/writes only poolVA0x0134ECD4+4 (BlockListHead), reads next block link, calls canonical operator delete RVA0x00881EB0, and iterates. Existing canonical DEFINE_AUTO_POOL(MultiListNodeClass,256) and ObjectPoolClass destructor at mempool.h200 naturally supply this body. The current ledger _$E56 ordinal is stale; the native MSVC7.1 object confirms _$E2 and the ledger correction retains _$E56 as its existing address identity.

Scope limitation: current canonical ObjectPoolClass is16B and lacks the BFME native pool lock at+0x10, giving20B total. This packet does not recover pool data, assert whole-global/runtime correctness, change headers or add pins. Callback depends only on proven BlockListHead+4 and registration no pool operand. Virtual BSS must not be read through naïve raw-file offsets.

Authoritative availability was eligibility.carved_rows on ../crt-short-audit-v2.csv against current ledger, not a reimplemented selector. Both claims accepted under sol1843-crt-multilist; lease a12069a796d2423dbce031657dd9c0c8.

Native compiler proof on base1c89b48f6e97a1995788dfa27c02d94c02685e24: unchanged multilist.cpp SHA2568c8e71c18bcfe9e16bd105c4cc2e17ba1e8f00630c9f1b2ca0b119f7127ba939 emits initializer_$E1/12B and callback_$E2/40B. Both strict relocation-resolved byte comparisons equal retail with no unresolved references. Fresh whole-owning-TU gate accepts20/20 functions and9 recorded DIR32 references; no strings or floating constants remain unverified.
