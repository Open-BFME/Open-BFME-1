# Terrain edge fan at RVA 0x0072A3D0

## Result and reopening condition

This is a banked C++ partial, not an exact source recovery. The final candidate is build/target-0072a3d0/trial12-bank.cpp, measured at revision 8cf7f68567dfb187f95fabff0352a695bf1e4417. It retains the bank's Rva0072A3D0Owner::rva0072A3D0 identity. The remaining blocker is float/x87-final-height-store-scheduling. Retail delays each triangle's final Z store until all call arguments have been pushed; the candidate stores it after only the three Vector3 pointers have been pushed. The stores retain the same semantic destinations after ESP adjustment. The final shorter displacement also reduces the emitted size. Reopen with a concrete hypothesis that moves these stores while preserving the independently verified helpers and the matched prefix. Repeating the pointer-lifetime, processor-tuning, or callee-visibility trials below is not a new hypothesis.

The retry hypothesis was that the old geometry/layout blocker could be addressed by the landed five-argument walkers, complete triangle helper, and complete caller. A corrected four-triangle body should improve over the saved bank. The refutation condition was a complete corrected reconstruction no closer than the saved body. The measurements support the hypothesis. The old EH diagnosis is refuted: the complete target has no FS registration, exception-state stores, cleanup calls, or destructible locals.

## Complete boundary and ABI evidence

The complete retail decode is build/target-0072a3d0/0072a3d0.disasm. The half-open extent is [0x0072A3D0, 0x0072AEF2). Every conditional and unconditional branch remains in that interval and lands on an instruction. There is one return at +0xB1F; its complete ret 0x20 ends at the exclusive endpoint. There is no outgoing tail jump or indirect call. The prologue allocates 0x90 bytes and saves four registers, placing incoming arguments at ESP+0xA4 through ESP+0xC0 after the prologue. The epilogue restores those registers and that allocation.

In entry order, arg0 is a nullable array of unsigned 16-bit output indices; arg1 is a nullable float-record output pointer; arg2 and arg3 are signed local X and Y offsets; arg4 and arg5 are signed X and Y extents; arg6 is an unsigned 16-bit index lookup array; arg7 points to the signed 32-bit current index. These types follow the word loads/stores, signed comparisons, dimensions passed to the walkers, and dword reads/increments through arg7. ECX supplies the unadjusted receiver. There is no hidden return storage or used result.

The complete caller at 0x0072B1C0 has twelve instruction-aligned calls through ILT 0x0000FB00. Each passes eight dword slots in reverse order and the same receiver in ECX. None consumes EAX. Its integer declarations for raw pointer slots are not pointee-type evidence; the target's accesses establish those types. The complete caller and all terminal paths are retained in 0072b1c0.disasm and checked-caller.log. No new pin is proposed.

| Retail helper | Complete extent | ABI and effects |
|---|---:|---|
| 0x00729300 through 0x00046C54 | 83 bytes | Const receiver; two signed coordinates; ret 8; bool in AL. Reads dimensions +8/+0xC, stride +0x34, and byte-buffer endpoints +0x44/+0x48. Both returns are decoded. |
| 0x007293E0 through 0x0003B034 | 314 bytes | Same receiver; coordinate reference, X offset, Y offset, X extent, Y extent; ret 0x14; bool in AL. Writes only the coordinate object. Both returns and all clamps are decoded. |
| 0x00729570 through 0x000466FA | 310 bytes | The same five-argument ABI; walks X before Y and writes only coordinates. Both returns and all clamps are decoded. |
| 0x00729F60 through 0x000453F9 | 897 bytes | Same receiver; record pointer, four signed region arguments, then three const Vector3 pointers; ret 0x20; unused result. Complete loops, conditional writes, and common return are decoded. |

The checked-target, checked-bitplane, checked-left, checked-right, and checked-intersection logs retain the coordinator's complete decoded-callee checks. Existing matching rows support callee identities. They do not prove a native target method name. The Zero Hour fillVBRecursive donor was read directly under GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainBackground.cpp. It supplies the edge-fan structure, but its square extent, height-match scan, and recursive tail differ from this BFME body. No exact native target method name is claimed.

## Geometry records and ownership

The receiver reads origins +0x40/+0x44, grid width +0x48, and map pointer +0x4C, agreeing with landed neighbors. Map dimensions are at +8/+0xC, border at +0x10, sample count at +0x20, and unsigned 16-bit sample pointer at +0x24. The old bank put dimensions one dword too early. Each inlined lookup computes a signed sample index, checks it against zero and the count, checks the pointer, reads a word, zero-extends it, and converts it with fild before scaling. The target lacks the bank's extra per-point clamps.

Every triangle input has three consecutive float fields at offsets 0, 4, and 8. Their construction uses signed integer-to-float conversion for X and Y, cell scaling, border subtraction, and unsigned sample conversion for Z. This uses every field, not an allocation size. The complete 0x00729F60 helper places all three pointers in TriClass. Complete TriClass::Compute_Normal at 0x006CB2B0 (189 bytes) reads all three fields from every corner and writes three fields to the separate normal. Complete CollisionMath::Collide at 0x008DAAA0 (390 bytes) reads the normal and first corner, forms a three-float intersection, and conditionally writes the cast result. Complete LineSegClass::recalculate at 0x003FE770 (203 bytes) reads both three-float endpoints and writes delta, normalized direction, and length. Their full decodes and checked-call logs are retained in the task folder. No allocation, ownership transfer, destructor, or unwind state occurs. The candidate includes canonical vector3.h.

Output records have a 12-byte stride. On a successful cast, receiver mode +0xB8 equal to 1 writes contact height at record offset 0; mode 2 writes at offset 4. The third field is untouched. No STL type, row, or pin is added.

| Triangle call offset | Corner order and storage before argument pushes |
|---|---|
| +0x370 | Bottom-left at +0x4C; current right at +0x40; current left at +0x7C. |
| +0x666 | Previous left at +0x88; current right at +0x94; advanced left at +0x4C. |
| +0x8EC | Current left at +0x58; previous right at +0x64; advanced right at +0x70. |
| +0xB10 | Current left at +0x70; current right at +0x64; final corner at +0x58. |

The initial triangle is guarded by the bottom-left flip bit. Otherwise the function loads both edge indices and increments the index by three without writing that triangle. Both first walker results are ignored; both loop flags start true. The final triangle is guarded by the saved top-right flip bit. The final right corner's displayed Y uses X origin plus right.y, whereas its height lookup uses Y origin plus right.y. The final corner adds X extent to both original minimum coordinates, including Y. These expressions are retained from instructions at +0x9D8/+0x9F8 and +0xA5F/+0xA6A, not corrected from geometric expectation.

## Measured and rejected trials

Rows below are generated from the unedited trial probe logs in build/target-0072a3d0/. Every probe received --size 2850. Quality is the repository finish_measure byte metric, including twice the emitted-size difference. Normalized instruction shape is diagnostic only.

| Trial | Compiled bytes | Non-relocation differences | First difference | Quality | Normalized shape |
|---|---:|---:|---|---:|---:|
| trial00-saved | 1889 | 1734 | +0x2 | 0.0000 | 0.350 |
| trial01-layout | 2820 | 2382 | +0x6 | 0.1432 | 0.948 |
| trial02-map-lifetime | 2820 | 2408 | +0x6 | 0.1340 | 0.951 |
| trial03-index-lifetime | 2826 | 2434 | +0x7 | 0.1291 | 0.703 |
| trial04-visible-walkers | Compilation failed | | | | |
| trial05-visible-walkers | 2847 | 100 | +0x354 | 0.9628 | 0.995 |
| trial06-direct-intersection | 2847 | 100 | +0x354 | 0.9628 | 0.995 |
| trial07-vector-set | 2925 | 2245 | +0x2 | 0.1596 | 0.603 |
| trial08-g7 | 2805 | 2346 | +0x40 | 0.1453 | 0.883 |
| trial09-g5 | 2847 | 100 | +0x354 | 0.9628 | 0.995 |
| trial10-visible-intersection | 2847 | 100 | +0x354 | 0.9628 | 0.995 |
| trial11-scale-global | 2847 | 100 | +0x354 | 0.9628 | 0.995 |
| trial12-bank | 2847 | 100 | +0x354 | 0.9628 | 0.995 |

Trial01 corrects the complete geometry, map layout, and helper ABI. Trial02 caches the map and trial03 precomputes the bottom-left index; neither improves. Trial04 preserves a compilation failure caused by the missing Byte typedef. Trial05 exposes the authentic bit-plane test and walkers as inline copies, with noinline walker attributes. That supplies the compiler's true memory-effect knowledge and matches the prefix and frame. Trial06 removes the triangle forwarding wrapper without improving. Trial07 uses Vector3::Set and regresses. Trial08 uses /G7 and regresses. Trial09 uses /G5 and is unchanged. Trial10 exposes the full triangle helper and is unchanged. Trial11 uses the recorded named scale global and leaves the remaining instruction schedule unchanged. Trial12 orders declarations to retain the old bank's names and reproduces trial05; it is the banked candidate. The generated flag-declaration alternative also does not improve; its unedited result is build/shape_search/94a138d78f344f2eb3f68e1563cd0750/result.json. The bounded unchanged x87 experiments are finished.

The task folder's difference-offsets.json contains every differing and omitted offset. The trial05 shape log isolates the moved stores. The final bank-probe.log reproduces trial12. The raw bank-byte-gate.log reports the target failure and passes all three visible helper copies at their existing extents. Its wrapper catches the target's failing exit to continue verifying the helpers; the wrapper's zero exit is not a passing target verdict. Copies are inline and add no strong duplicate definitions or ledger rows. CSV validation, pin consistency, and the class gate pass, with raw output in final-check-csv.log, pin-consistency.log, and bank-class-gate.log. The name-regression source-comparison function reports no descriptive-to-placeholder change in the final bank; the current CLI takes Git revisions, so the coordinator still runs its staged hook. There is no source landing or shared-header edit; this bank requires no full gate.

The declared-unmatched check fails for this partial bank. Its raw bank-declarations.log reports zero matched ledger rows for the bank and an unclaimed Rva00729300BitPlane::test definition. That helper copy passes its existing retail extent in the scoped byte gate, but this does not make the declaration check pass. No whitelist, pin, or ledger change was made. The coordinator must retain this validation limitation when collecting the bank; it is not a source landing.
