# Supersampled glyph rasterizer retry at 0x0093F440

## Result

This is a banked partial, with no source recovery or ledger replacement. The tested revision is cbcb79d0784092768988547a74ad9640d84a4b42 and the model is gpt-6.1-sol. The saved body measures 1354 bytes and 1034 non-relocation differences against the 1329-byte retail extent, with quality 0.1843. The preferred trial measures 1336 bytes and 939 differences, with quality 0.2829. Its first differing byte is +0x17: the compiled frame is 0xA8 rather than retail's 0xAC. Eight relocation-layout differences remain. Quality is computed by tools/finish_measure.py; normalized instruction similarity is a separate diagnostic.

The preferred body is targets/game/reverse/attempts/0x0093f440.cpp. Every trial source, raw probe, decoded extent, scoped gate output and measurement receipt is retained under build/worker-0093f440/. No exact recovery is claimed.

## Retry hypothesis and evidence

The earlier scalar counters let the compiler strength-reduce the outer block loop into several induction variables. Retail instead multiplies the current block_y by the cell height inside the loop and increments block_y before its comparison. The new hypothesis was that a two-component native aggregate used through references prevents that scalar transformation. It would be refuted if the emitted loop retained the same induction-variable shape or failed to improve the saved body's measured result. The Vector2i counter trial restores the outer multiplication and increment/comparison topology. Applying min<int> only to the vertical sample bound then improves measured quality further. This establishes a useful compiler shape, not the original local variable's type.

The neighbouring landed sources were checked at 0x0093F310, 0x0093F3F0 and 0x0093F980. The landed buffer helper at 0x0093DFB0 supplies the vector and current-buffer offsets; the wrapper at 0x0093C330 supplies the two-field SelectObject cleanup; the constructor at 0x0093C340 supplies the global DC and bitmap layout. The existing dir32 name g_fontCharsGdiState0134AEAC is used. These resolve layout and cleanup questions for the retry but do not resolve the remaining frame and register allocation differences. No new pin was added.

## Boundary, ABI and data checks

The entire 1329-byte target decodes to one common ret 4 at +0x52E, followed by alignment padding. Every outgoing conditional edge lands on a decoded instruction inside the extent. The early missing-glyph paths converge on the common cleanup and return. There is no outgoing tail jump in the main body. The complete caller at 0x009412F0 passes a character in a four-byte stack slot, uses its low 16 bits, leaves the receiver in ECX, and consumes the returned pointer in EAX. There is no receiver adjustment or hidden return storage at that call.

The target writes the character record's 16-bit Value at +0, 16-bit Width at +2, zero 16-bit Offset04 at +4 and pointer Buffer at +8. Bytes +6 and +7 are padding and are not initialized by these stores. These writes establish the record layout; the allocation size alone does not. The target reads unsigned byte samples from the bitmap, shifts each by four and writes 16-bit packed output samples.

The complete 187-byte Update_Current_Buffer helper at 0x0093DFB0 reads the vector data at +0x14, count at +0x20, current offset at +0x28 and height at +0x2C. Its allocated buffer record writes a pointer at +0, capacity at +4 and zero position at +8. Its new[] call allocates two bytes per sample. The complete 78-byte copy helper reached at 0x0093D6F0 reads and writes one DWORD from the reference argument into the vector slot. Its successful return is AL and its two returns clean four stack bytes. The indirect resize call uses the receiver in ECX, two four-byte arguments and an AL result. This is evidence for a pointer payload, not an STL pair inferred from allocation size. The earlier 64-byte screening extent was rejected because it truncates the complete helper; checked-buffer-copy-78.log is the corrected check.

The 17-byte operator new and new[] wrappers at 0x00881F30 and 0x00881F70 take a 32-bit cdecl size and return a pointer in EAX. The complete GDI-state constructor at 0x0093C340 sets up a top-down 64 by 64, 24-bit DIB, placing its bits pointer at +0x0C and DC at +0x10. The target's imported GetGlyphIndicesW, GetTextExtentPoint32W, ExtTextOutW and SelectObject calls were checked against their stack arguments and imported stdcall signatures.

Retail has one unwind state. Its cleanup action at 0x00C5D720 computes ECX from EBP-0x4C and tail-jumps to the complete 14-byte wrapper at 0x0093C330. That wrapper reads the saved object at +4 and DC at +0, calls SelectObject and returns without owning either handle. The complete handler at 0x00C5D728 tail-jumps to the EH runtime. The proposed guard has those two fields and restore semantics. The compiled frame and cleanup placement remain unverified against retail because the main body is not exact.

The raw complete decode is decoded-complete.log. Successful checked_callees outputs are checked-target.log, checked-caller.log, checked-buffer.log, checked-new.log, checked-new-array.log, checked-buffer-copy-78.log, checked-cleanup.log, checked-gdi-state.log, checked-unwind.log and checked-handler.log, all under build/worker-0093f440/.

## Identity and canonical declarations

The array-backed caller, supersampling work and Zero Hour Store_GDI_Char donor support the existing bank's method identity. The complete donor source was read rather than relying on a previous description. The landed caller uses an address-derived owner and records a layout dispute with the other font lookup body. The shared render2dsentence.h character record inherits a base that shifts its fields away from the writes at +0, +2, +4 and +8 observed here. Therefore the existing private bank view is retained, with its existing names, and a canonical FontCharsClass integration is not asserted. Byte equality would not settle that discrepancy. class_gate passes because this class is not registered there; that pass is not identity evidence.

## Measured experiments

Every number below is parsed directly from the named raw probe. The full clamp search covers all sixteen combinations of the four clamp spellings. Equivalent repeats confirm the preferred result. The min<long> variants introduce a different aligned prologue and are rejected. Making the complete buffer helper visible leaves the target unchanged; the helper itself still matches its existing 187-byte retail extent.

| Experiment | Emitted bytes | Non-relocation differences | First differing byte | Measured quality | Normalized shape | Raw log |
| --- | ---: | ---: | ---: | ---: | ---: | --- |
| Saved body | 1354 | 1034 | 0x1C | 0.1843 | 0.816 | probe-baseline.log |
| DWORD glyph output storage with WORD comparison | 1354 | 1034 | 0x1C | 0.1843 | 0.816 | probe-glyph32.log |
| Complete buffer helper visible in the TU | 1354 | 1034 | 0x1C | 0.1843 | 0.816 | probe-visible_buffer.log |
| Native two-int loop-counter aggregate | 1327 | 1043 | 0x17 | 0.2122 | 0.852 | probe-native_block.log |
| Only outer counter in an aggregate | 1354 | 1034 | 0x1C | 0.1843 | 0.816 | probe-outeraggregate.log |
| Reuse one cell division result | 1327 | 1026 | 0x17 | 0.2250 | 0.795 | probe-cellstep.log |
| Cell and text dimensions in one escaping aggregate | 1269 | 1129 | 0x17 | 0.0602 | 0.808 | probe-group_dims.log |
| Only horizontal sample end uses min<int> | 1335 | 1130 | 0x36 | 0.1407 | 0.876 | probe-min-trial-01.log |
| Only vertical sample end uses min<int> | 1336 | 939 | 0x17 | 0.2829 | 0.879 | probe-min-trial-02.log |
| Vertical sample end uses min<long> | 1372 | 1179 | 0x0 | 0.0482 | 0.765 | probe-min_sy_long.log |
| /Os | 1041 | 960 | 0x0 | 0.0000 | 0.332 | probe-size_bias.log |
| /Og- | 1640 | 1228 | 0x0 | 0.0000 | 0.245 | probe-no_global_opt.log |
| Cleaned preferred body | 1336 | 939 | 0x17 | 0.2829 | 0.879 | probe-bank.log |

Grouping both dimensions, reusing a single division result, changing counter scopes, naming GDI locals, moving the character allocation declaration and the two optimization-flag trials do not improve the preferred result. The horizontal-only min<int> trial restores the retail initial register selection and 0xAC frame, but its byte score is worse; its source and raw output remain preserved as min-trial-01.cpp and probe-min-trial-01.log. Earlier EH and generic family sweeps were not repeated.

## Verification and reopening

check_csv-initial.log and check_csv-final.log pass. pin-consistency.log and pin-consistency-final.log pass without pin changes. class-gate.log and class-gate-preferred.log pass for the private bank view. name-regression-api.log reports no descriptive-name regressions using the tool's pure comparison API; the documented path-form CLI is incompatible with this revision's Git-ref CLI and its failure is retained in name-regression.log. find-declared.log fails for the unlanded bank method, which has no source ledger entry. It is not treated as a landing pass. probe-preferred-corrected.log reproduces the preferred body's measurements after banking; probe-preferred.log retains a rejected CLI invocation that omitted the --size flag.

The strict scoped candidate byte gates fail in scoped-candidate-gate.log and scoped-preferred-gate.log, with the latter testing the actual preferred bank path. Their apparent shifted REL32 destinations arise from the nonmatching instruction layout and are not evidence for new callees or pins. The decoded retail calls remain 0x0093DFB0 and 0x00881F30. No full gate is required for this bank and evidence-only change.

The remaining byte blocker is the four-byte frame deficit, spill/register choices and instruction scheduling around the cell products and nested loops, with seven excess emitted bytes overall. Reopening needs a justified source shape that reduces those measured residues without regressing the preserved best result. Any exact landing must also reconcile the canonical record and owner declarations, and verify the compiled unwind cleanup placement. No STL row or symbol pin was added or changed.
