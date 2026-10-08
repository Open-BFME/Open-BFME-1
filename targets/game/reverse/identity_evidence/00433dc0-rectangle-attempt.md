# Rectangle draw attempt at 0x00433DC0

## Result and reopening condition

The body is a complete drawing method on the existing opaque `Rva00435270Layout` owner. No original EA class or method name is established. The source remains a partial because its initial color calculation, stack homes and virtual-call register choices differ from retail. Reopen with evidence for a different native color-expression lifetime or wrapper visibility that changes the first divergence. Repeating the measured flag, minimum-helper and coordinate spellings below without new evidence is not a justified experiment.

## Boundary and ABI evidence

The tested revision is `0bef414b52a39a3ab1ec98dca60d8a214de4260e`. The assigned row remains an assembly dump. `tools/eligibility.py` admits the row as open work; eligibility and the coordinator assignment are separate from reservation. No saved reconstruction existed when this run began.

Retail starts at 0x00433DC0 after the aligned minimum helper and padding. Its only return is at 0x00433F25 with `ret 0x18`, ending at 0x00433F28 before padding. All conditional branches stay within the body, and there are no direct calls or external tail jumps. `build/rva00433dc0/all_decoded.log`, `boundaries.json` and `checked_target.log` retain the complete instructions, hashes, endpoints and checked inventory.

The complete matched caller at 0x00435270 passes the floats at receiver offsets 0x4C, 0x50, 0x54 and 0x58, the word at 0x2C and literal 1. Its instruction-aligned call at 0x0043529B reaches ILT 0x00007356, whose complete jump reaches the target. ECX is the unadjusted layout receiver. There is no hidden return storage, and the caller does not consume a result. The target reads only the signed word at layout offset 0x28; its signed minimum branches agree with the existing `m_progress28` declarations in the landed apply and range bodies. The existing address-derived setter pin is consistent, but its autopin annotation does not establish an original semantic identity.

The first four arguments are floats because the target subtracts them with x87 single-precision operands. The fifth argument is a packed color word whose high byte is extracted with `shr 24`. The sixth argument is a signed four-byte border width, converted with `fild`. It is not an optional-outline flag. Both outlines are unconditional. The fill uses right minus left and bottom minus top. The outlines expand both dimensions by twice the border; their origins are left minus border and top minus border, with an additional unit offset on the first outline. The first color clamps its extracted alpha to the current progress; the second clamps twice that alpha to progress; the third color is the fixed packed gray word.

The canonical global declaration is `Display *TheDisplay`, owned by `Display.cpp` and its data row. The current shared Display header does not declare these BFME float draw slots at their retail positions. The candidate therefore keeps the canonical global pointer type and an opaque, address-qualified slot view, without copying or modifying the Display class.

The actual W3DDisplay table at VA 0x0111EDD0 is installed by the landed constructor and destructor. Slot 0xB0 routes through ILT 0x000096F6 to 0x006E9B70, which loads the renderer at receiver offset 0x164 and tail-jumps to 0x00934820. Slot 0xDC routes through ILT 0x00008265 to 0x006E9B80, which makes the same receiver adjustment and tail-jumps to 0x00934940. Both complete renderer targets end with plain `ret` and consume no stack argument. Slot 0xC0 routes through ILT 0x0000A06A to the matched fill body at 0x006EA050; all returns clean five words. Slot 0xBC routes through ILT 0x00046E39 to the matched outline body at 0x006E9D40; all returns clean six words. Their complete field operations establish four float coordinates, a packed color, and the outline's additional float width. The slot declarations use the existing fill and outline color declarations. Results at these calls are ignored. Every complete body and return path is retained in `all_decoded.log`; checked inventories are in `checked_begin.log`, `checked_end.log`, `checked_reset.log`, `checked_render.log`, `checked_fill.log` and `checked_outline.log`.

The target constructs no owning member or container and has no exception frame, so payload construction and constructor-unwind checks do not apply. The renderer callback's own EH frame is not reconstructed here; only its complete no-stack-argument receiver contract is used.

## Experiments and rejected hypotheses

There was no saved body against which to compare. The initial complete body modeled four floats, two machine words, signed reference-returning minima and inline draw wrappers. Changing the minimum's operand order, a named alpha versus a temporary, direct color argument versus parameter assignment, unsigned color declarations and a generated frame-array variant did not repair the initial scheduling. Expanding the draw wrappers manually did not help. CPU scheduling and inline-policy flags did not produce equality. A native minimum template and moving alpha ahead of the coordinate locals did not help. Typed begin/end call views changed register choices without an exact result. Mutating alpha before the second minimum produced the same shape as its multiply expression.

Writing expanded outline arguments as expressions restored their arithmetic order and common subexpressions. Separately masking the color word before combining it with the clamped alpha produced the best measured body. Merging that mask back into one expression lost the improvement. Swapping both minimum argument order and comparison order produced the same best shape. The final candidate retains canonical unsigned-long color at the outline slot and inline-helper markers; its measured instruction result equals the best trial.

The table is generated from unedited probe logs. Differences and quality are diagnostic masked-byte measurements, not acceptance. In the best body one relocation site does not align with a retail address operand, so even its diagnostic score does not validate that binding.

| Trial | Emitted bytes | Probe differences | First offset | Diagnostic quality |
|---|---:|---:|---:|---:|
| trial02 | 363 | 303 | +0x05 | 0.1417 |
| trial03 | 363 | 303 | +0x05 | 0.1417 |
| trial04 | 363 | 303 | +0x05 | 0.1417 |
| trial05 | 363 | 303 | +0x05 | 0.1417 |
| trial06 | 363 | 303 | +0x05 | 0.1417 |
| trial07 | 363 | 303 | +0x05 | 0.1417 |
| trial08 | 363 | 302 | +0x05 | 0.1444 |
| trial09 | 363 | 302 | +0x05 | 0.1444 |
| trial10 | 363 | 302 | +0x05 | 0.1444 |
| trial11 | 363 | 304 | +0x05 | 0.1389 |
| trial12 | 359 | 303 | +0x05 | 0.1528 |
| trial13 | 363 | 308 | +0x01 | 0.1278 |
| trial14 | 363 | 302 | +0x05 | 0.1444 |
| trial15 | 360 | 127 | +0x05 | 0.6472 |
| trial16 | 363 | 302 | +0x05 | 0.1444 |
| trial17 | 360 | 127 | +0x05 | 0.6472 |

The generated frame search is preserved at `build/shape_search/42f38e83ce204b7e85f661658fe63c46/`, with the original, finite choices, every trial and manifest. Its raw probes are `build/rva00433dc0/family_probe00.log` and `family_probe01.log`. Other complete source snapshots and their raw probe logs are under `build/rva00433dc0/`.

## Verification

The final candidate probe is `build/rva00433dc0/candidate.log`. The strict repository byte gate failed in `build/rva00433dc0/scoped_gate.log`; `scoped_gate.py` calls the repository's unchanged verification implementation with an in-memory candidate row and never writes the ledger. CSV and full pin checks pass in `check_csv_final.log` and `pin_consistency.log`. The class gate passes in `class_gate.log`. The declared-definition check reports zero matched rows for this non-landed scratch body in `declared_unmatched.log`, as expected for a bank; no whitelist or baseline was changed. No full gate is required for this bank, and no source, header, function row or pin was landed.

The saved bank is byte-for-byte the final candidate after its two metadata lines. Its immutable attempt archive has the same content hash. A fresh bank probe reproduces the candidate in build/rva00433dc0/bank_probe.log. Class checking of the bank passes in bank_class_gate.log. The file comparison through the name-regression module passes in name_regression_files.log; the current CLI accepts Git revisions rather than the file arguments shown in the worker brief. The verdict is the sole appended row of this run and retains the repository tool's CRLF terminator. No background task was started.
