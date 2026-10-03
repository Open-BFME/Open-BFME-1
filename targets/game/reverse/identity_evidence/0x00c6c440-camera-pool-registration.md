# CameraShaker pool registration and cleanup ownership

Retail C6C440 is 12 bytes: PUSH VA01070930; CALL atexit009F6E26; POP ECX; RET at +0B, followed by INT3. Shipped CRT slot VA012A5A50 points to VA0106C440.

The unchanged camerashakesystem.cpp COFF static initializer _$E54 is precisely this registration and its private callback _$E55 is the 40-byte cleanup at RVA00C70930 through RET+27, then INT3. Callback DIR32 fields at +0x01/+0x20 reference the CameraShakerClass ObjectPool allocator with addend4, yielding BlockListHead VA012F7FF4; REL32+0x14 invokes operator delete00881EB0.

Independent typed callers establish the allocator identity. The existing matched CameraShakeSystemClass::Add_Camera_Shake at 006D19A0 loads ECX=VA012F7FF0 at 006D19C3, calls ILT00002603 to allocator006D1370 at 006D19CC, then calls ILT00026E77 to CameraShaker constructor006D14B0 at 006D19F7. The allocator links 256 objects at stride60 and requests0x3C04 bytes. The CameraShaker deleting destructor006D18A0 loads the same pool address at 006D18B4 and calls ILT00011103 to free006D1480 at 006D18B9. Thus this is the CameraShaker pool rather than the8-byte GenericSLNode or AABTreeNode pool.

Retired callback rows _$E2 from slnode.cpp and _$E6 from aabtreecull.cpp each falsely claimed these same40bytes. Their unchanged COFF callbacks refer respectively to GenericSLNode and AABTreeNode allocators. Four recorded DIR32 allocator names aliasing VA012F7FF0 made their masked byte checks pass but do not prove identity. Their private initializer consumers are not reanchored, removed or claimed. Only unsupported ledger ownership is retired; camera _$E55 remains. Independent review approved by review_links.

This12-byte registration has no pool operand. Pool layout/data/runtime are not accepted: the current pool layout is16bytes versus retail20bytes with the lock at +10. Other allocator pins and deleting-destructor aliases remain separate uncorrected debt. No pool data extent, initialization correctness or runtime behavior is claimed. No sources, headers, shims, pins or data rows change.

Fresh before3-TU gate:57/57 exact. Current COFF symbols/relocations, source/object hashes and independent retail decoding are in the ignored campaign crt-slnode receipts.
