# Loader at RVA 0x00694230

## Result and reopening condition

This is a partial reconstruction tested against revision `63d08bf862ded7ac3c2635c72921a8eff0a8f354` with model `gpt-6.1-sol`. The complete candidate emits 654 bytes for the independently decoded 654-byte retail extent. Its probe reports 101 masked byte differences, first at `+0x19`, four relocation operands without matching retail instruction boundaries, and normalized instruction similarity 0.991. These are probe measurements, not byte equality or an identity certificate. All trial sources, raw probe output, object bytes, relocation records and mismatch offsets remain under `build/audio-00694230/`.

Reopen this bank with a supported source lifetime or callee visibility hypothesis that changes the allocation of the record pointer and wait/size value. Retail keeps those values in EBP and EBX respectively; the candidate exchanges those roles. A useful hypothesis must also resolve the unwind action's callee binding without introducing a second identity for RVA 0x006915E0. Repeating boolean reuse or signed scalar declarations does not justify reopening: both emitted the same shape. No new STL ledger row or pin is required by the current candidate, and none was added.

## New evidence and initial hypothesis

The earlier records had no saved target body and reported an incomplete 489-byte draft with reporting out of line. The current ledger supplies the native worker reference ABI at RVA 0x00694130, the owner accounting method at RVA 0x00693FB0, the flag reset at RVA 0x006BA120, the record setter at RVA 0x006BA150 and canonical string headers. The retry hypothesis was that those declarations, a real AsciiString set and the complete inline debug stream sequence would recover the missing structure. A contradictory decoded caller or a compiler result that failed to improve on the previous reported normalized similarity would refute that hypothesis. The first complete draft measured 658 bytes, 180 masked differences and similarity 0.986, so the structural hypothesis survived its first measurement.

The EA evidence ledger associates this RVA with `AudioFileCache::readAudioFile` and `GameEngineDevice/Source/MilesAudioDevice/MilesAudioCache.cpp`. The actual Zero Hour donor is `GeneralsMD/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp`, specifically `AudioFileCache::openFile`. Its WAV format handling and both diagnostics are useful semantic evidence, but its locking and cache insertion flow differ. The bank retains the existing address-derived owner vocabulary and the opaque method `Gen0002857EOwner::Rva00694230`; it does not assert a corrected real class or member identity.

## Boundary, callers and argument layout

`retail-disassembly.log` decodes the entire target from RVA 0x00694230 through the final `ret 4` at RVA 0x006944BB, ending at RVA 0x006944BE. The other return instructions are at RVAs 0x00694371 and 0x00694424. All direct conditional transfers stay inside that extent. The stop branch goes to the registration-restoring epilogue at RVA 0x006944A9. It does not pass through the delete-array call at RVA 0x006944A1. The target has no tail jump outside the body.

The complete caller at RVA 0x00694570 passes its selected record pointer in one stack dword and its worker receiver in ECX to ILT RVA 0x0000FDCB. The target's `ret 4` agrees. The caller does not consume a result. The record begins with the string data pointer and is also the receiver of both the flag reset and record setter. The existing handle, owner and worker sources support that address-derived record vocabulary. The target reads the receiver's stop byte at +0x44 and mutex handle at +0x48, inserts into the container at +0x2C and updates the accounting total at +0x38 against the limit at +0x3C.

The target's direct callees and actual ILT routes are retained in `checked-00694230.log`. The record setter's complete 102-byte body copies nine dwords from its second explicit argument into record +0x08, stores the first argument at +0x2C, stores the third at +0x30 and the low byte of the fourth at +0x40, and returns with `ret 16`. The flag reset writes only +0x41 and +0x42 and has a plain return. Existing canonical callee spellings are used without new pins.

## Container value evidence

Both failure paths use the receiver's container at +0x2C. The first calls ILT RVA 0x0001BC02, resolving to the 310-byte tree inserter at RVA 0x000C0430. The unsupported-format path instead calls ILT RVA 0x00030EA9, resolving to the 40-byte set wrapper at RVA 0x00453DB0. The latter uses hidden result storage, copies one iterator pointer and one boolean at result +0x04, and returns with `ret 8` for the result pointer and value reference. The initial native draft inlined both wrappers. The scoped byte gate exposed the incorrect second callee even though the masked probe did not distinguish the relocation target.

The complete tree inserter reaches `_M_insert` at RVA 0x000BFCC0 through ILT RVA 0x00032B87. Both allocation paths call the value construction helper through ILT RVA 0x00007554, which actually jumps to RVA 0x000620B0. That complete 66-byte helper calls the string copy constructor at RVA 0x00887B60. The complete 121-byte copy constructor reads only the source's data pointer at +0x00, writes only the destination's pointer at +0x00, increments the pointed-to buffer reference count when non-null and uses its critical-section guard. There is no second payload field copied by this chain. The complete 92-byte comparator at RVA 0x0005FEB0 and the inserter's inline comparison read a halfword length at buffer +0x04 and compare characters beginning at buffer +0x08 with `repe cmpsb`. Together these establish a single AsciiString value independently of the 20-byte node allocation or donor template name. The ledger's unrelated ModelConditionInfo spelling at RVA 0x000620B0 is not type evidence for this caller.

The construction helper has one EH state. Its cleanup calls ILT RVA 0x0002AAA9, resolving to the one-byte return at RVA 0x000607F0. The existing scalar placement-delete pin and the decoded two-argument call agree with non-owning placement construction cleanup. The bank's local set-wrapper specialization is inline and noinline, so it supplies callee visibility without adding a second strong out-of-line definition. `wrapper-probe.log` independently measures that helper as exact at 40 bytes. No STL row or symbol pin was changed.

## Exception and ownership evidence

`eh-target.log` shows exactly one target unwind state, state 0 to -1. Its action at RVA 0x00C472B0 adjusts ECX to `[ebp-0x38]` and jumps through ILT RVA 0x0001E961 to RVA 0x006915E0. The complete 25-byte helper reads a handle at +0x00 and an ownership byte at +0x04, releases the mutex only when owned, clears that byte and returns. There are no string or buffer destructors in the target's unwind map.

`object-eh.log` shows that the candidate has the same state count, predecessor and `[ebp-0x38]` receiver adjustment. Its action relocates to `??1Rva006915E0@@QAE@XZ`, however, whereas the existing retail helper row is `?release@Rva006915E0@@QAEXXZ`. The emitted destructor body is the same 25-byte guarded release, but its symbol is not independently bound to the retail helper. This binding remains a blocker for exact collection even if the main body later matches. No alias pin was invented to hide it.

The ADPCM branch frees the original array, replaces the buffer pointer with the decompressed output, and recomputes WAV information. The PCM branch preserves the original pointer. Successful completion passes ownership information to the existing record setter. The unsupported-format branch resets the record, inserts the failed name, releases the guard, reports and deletes the original buffer. The stop path leaves the buffer alone, as the decoded target does. Mutex timeout repeats the wait loop without acquiring ownership.

## Virtual and imported ABI evidence

The returned File object's +0x2C and +0x34 calls match size and read-entire-and-close slots in the decoded MemoryReadFile, Win32LocalFile, RAMFile and LocalFile tables. Their complete relevant methods use no explicit stack arguments and return their 32-bit size or buffer in EAX. The signed File::size declaration follows the existing canonical matched method at RVA 0x009CB670. The target uses access flags 0x41.

The Debug constructor establishes vtable VA 0x01133058. Its slots +0x60, +0x6C, +0x38 and +0x4C lead to RVAs 0x008896E0, 0x0088BA10, 0x0088C020 and 0x0088BB60. The report-start helper returns AL and takes no explicit arguments. The stream-opening method reads a file pointer and line dword, returns its receiver in EAX and uses `ret 8`. String insertion returns its receiver and uses `ret 4`. Finish reads a full dword mode, compares it with 2 and returns its boolean in AL on the returning path with `ret 4`. The reference's bool argument spelling for CrashDone is therefore insufficient for this BFME call. The bank keeps an opaque slot method with an int mode and boolean result.

The finish ledger's 1216-byte extent includes a 28-byte jump table beginning at RVA 0x0088C004. `checked-0088bb60.log` rejects linear decoding of that extent. `checked-debug-code.log` successfully decodes the complete 1188-byte instruction region, and `debug-tail.log` verifies every table destination and both SEH scope destinations against that region's instruction starts. The final code path calls the imported `_exit`; the following bytes are table data. The SEH scope uses predecessor -1, filter VA 0x00C8BFD4 and handler VA 0x00C8BFF1. The complete returning and non-returning paths were reviewed separately from that data.

PE imports identify WaitForSingleObject and ReleaseMutex independently of pins. The decoded calls agree with two and one stdcall dwords respectively. The MSS exports identify `_AIL_WAV_info@8` and `_AIL_decompress_ADPCM@12`; the caller supplies the buffer and a nine-dword packet to the former, and packet, output-pointer address and output-size address to the latter. Only the packet's first dword is interpreted here, as format 1 or 0x11; the remaining eight dwords stay opaque. The complete record setter independently establishes the packet copy width. `tables-strings.log` confirms each exact diagnostic fragment.

## Experiments and rejected hypotheses

| Candidate | Bytes | Masked differences | Observation |
|---|---:|---:|---|
| trial01 | 658 | 180 | Complete native draft with both inline debug paths. |
| trial02 | 654 | 137 | Delete only on unsupported format, preserving the stop exit. |
| trial03 | 660 | 276 | Reusing fileSize for the final size worsened shape and introduced cached WAV import calls. |
| trial04 | 654 | 114 | Scoping decompression output locals inside the ADPCM branch recovered stack reservation 0x3C. |
| trial05 | 654 | 101 | Guard acquire returns the native wait status instead of a bool, recovering receiver and handle registers. |
| trial06 | 654 | 101 | Reusing the failure boolean for compression emitted the same result. |
| trial07 | 654 | 101 | Canonical signed File::size and signed size locals emitted the same result. |
| trial08 | 654 | 126 | A typed external wrapper adapter fixed the second route but enlarged the stack reservation to 0x40. |
| trial09 | 654 | 101 | A visible noinline inline specialization preserves the correct second route and stack reservation. |
| final | 654 | 101 | Corrected the decoded Debug slot argument and result declarations without changing instruction shape. |

Each numbered candidate's table entry is a single probe measurement (n=1). The final source and the bank were probed separately and reproduced the same 654-byte result and 101 masked differences. The required EH search ran nine trials. Its best result remained trial01's 658-byte shape; removing nothrow array deletion did not improve it, and disabling /EHsc worsened it. The family search ran nine trials on trial03 and did not improve that shape. Sources, choices, raw per-trial probe output and result manifests are preserved in `build/shape_search/9d3583e81ad6484fbfa494104c97f0f7/` and `build/shape_search/152d09d155ff4a7596bf93a365be6129/`. There were exactly two unchanged register experiments, trial06 and trial07; no further register spellings were tried.

The final scoped gate fails the loader byte comparison. Its first displayed relocation-target complaint is caused by the shifted first call operand, not an unknown FileSystem target; the separately decoded call proves the real callee. No baseline, pin or ledger row was changed. A full gate is not required for a bank with no source, shared-header or ledger changes. The retained mismatch offsets, raw binary snapshots and final object are in `mismatch-offsets.json`, `retail.bin`, `compiled.bin` and `final.obj` under the task build folder.
