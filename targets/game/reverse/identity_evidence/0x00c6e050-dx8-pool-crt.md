# DX8 native object-pool registration ownership

Retail SHA256 1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75.

CRT slots VA012A5DC8 and VA012A5DCC contain VA0106E050 and VA0106E060. Each body is exactly12 bytes: push its own callback (VA01071350 / VA01071380), call atexit RVA009F6E26, pop ECX, RET at offset11, followed by four INT3. Native existing dx8renderer.cpp emits _$E22 and _$E25 with callbacks _$E23 and _$E26, respectively.

The callbacks are independently established ObjectPoolClass destructors. DEFINE_AUTO_POOL(PolyRenderTaskClass,256) and DEFINE_AUTO_POOL(MatPassTaskClass,256) own the real static Allocator objects. Canonical DIR32 identities locate them at VA0134B128 and VA0134B13C. Callbacks read and update BlockListHead at offset4, VA0134B12C and VA0134B140. They delete each linked allocation through retail operator delete RVA00881EB0 (cdecl void(void*)). Each callback is40 bytes, RET at offset39 and then INT3. The native callbacks retain their honest address-derived ledger identities; only source provider and object-symbol are corrected from the donor _$E55 / _$E58 to native _$E23 / _$E26.

Independent existing native COFF inspection established complete40-byte equality after both real DIR32 relocations plus operator-delete REL32 were applied, not masked similarity. Fresh scoped verification supplies the acceptance receipt. No new pool definition, semantic rename, pin, header, shim, or data row is introduced.

LIMITATION: existing game mempool.h has a16-byte generic declaration while BFME native pool allocation bodies expose locking at offset0x10. This packet changes no source or globals and these callbacks never access that lock. Registration and callback code ownership are verified only; complete pool extent, static-data acceptance, runtime/layout correctness, whole-image linkage are expressly unresolved and not claimed.
