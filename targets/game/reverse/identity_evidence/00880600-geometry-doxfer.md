# GeometryInfo snapshot transfer at RVA 0x00880600

The recovered body is `?DoXfer@GeometryInfo@@UAEXAAVXfer@@@Z`, over the complete 384-byte extent. Evidence was checked against revision `cbcb79d0784092768988547a74ad9640d84a4b42` and the configured BFME retail baseline. The source is `game/GameEngine/Source/Common/System/GeometryInfoDoXfer.cpp`. Raw decoding, compiler trials and check receipts are retained under `build/geometry-00880600/`.

## Identity, boundary and receiver

The GeometryInfo table at VA 0x01086138 contains this body in slot 3. The independently landed default, copy and five-argument constructors install that same table. The complete copy constructor at RVA 0x000FFD10 copies the vectors at object offsets 0x2C and 0x38 and the trailing fields through 0x58. The complete Snapshot transfer caller at RVA 0x009D6410 loads its Snapshot argument into ECX, pushes its Xfer receiver and calls Snapshot slot 3. This establishes an unadjusted GeometryInfo receiver and one four-byte Xfer reference argument. The target does not consume a hidden result pointer or produce a value.

INT3 padding precedes the target. The conditional branches at offsets 0x16, 0xA7, 0xFD and 0x127 all reach decoded instructions inside the extent. Both the early return and the normal transfer path reach the epilogue at offset 0x176 and `ret 4` at offset 0x17D. The next body starts at RVA 0x00880780. There is no outgoing branch or tail jump. `checked-00880600.txt`, `target-disassembly.txt` and `boundary-switch-caller.txt` retain these checks.

## Container value and ownership

The direct callee at RVA 0x00880260 accepts a 32-bit unsigned count followed by a 0x24-byte by-value element and ends both paths with `ret 0x28`. Its shrink and grow paths both release the element's string subobject at offset 0x1C through RVA 0x00887940. The independently decoded one-argument overload at RVA 0x00880400 constructs that value in the outgoing argument slot and forwards the count.

The actual grow helper at RVA 0x0087FDC0 calls the copy constructor through ILT RVA 0x00013476, which routes to RVA 0x000FCED0. That complete constructor reads and writes dwords at element offsets 0x00, 0x04, 0x08, 0x0C, 0x10, 0x14 and 0x18, copies the string at 0x1C through RVA 0x00887B60, and copies the byte at 0x20. The actual fill helper at RVA 0x0087F020 and the erase assignment helper at RVA 0x0087EA20 confirm the same complete field set. The remaining three bytes are alignment padding, not a second payload or key. The constructor at 0x00887B60 stores the shared buffer pointer and increments its reference count; the destructor at 0x00887940 decrements the count and frees a zero-count buffer. Assignment at 0x00887C90 releases the old buffer before retaining the new one.

The target transfers element offset 0x00 through the enum helper, offsets 0x04, 0x08 and 0x0C through the real-value overload, offsets 0x10 through 0x18 through the 12-byte coordinate overload, and offset 0x20 through the boolean overload for version 2. These call bodies establish the value widths independently of the donor names and allocation stride. The retained `BfmeElem60`, `BfmeCoord3D` and `BfmeAsciiString` names come from the saved body; the string view now inherits the canonical AsciiString declaration.

The identity constructor's FuncInfo at VA 0x011E9C5C has states 0 and 1. State 1 unwinds the constructed shape vector through object offset 0x2C and ILT RVA 0x0000AC2C; state 0 unwinds Snapshot through ILT RVA 0x00001C80. `copy-constructor-unwind.txt` retains the state map and cleanup instructions. The transfer target itself has no exception frame or unwind states. Its by-value argument is owned and destroyed by resize, not by a caller-side cleanup.

## Virtual calls and canonical declarations

The actual Xfer table at VA 0x01129258 resolves slots 4, 10, 24, 27, 30, 35 and 36 to complete decoded bodies. Slot 4 returns a boolean in AL without stack arguments. Slot 10 reads the two version bytes and returns the receiver with `ret 4`. Slots 24, 27, 30 and 35 transfer a coordinate, real value, integer and boolean respectively, return the receiver and use `ret 4`.

Slot 36 at offset 0x90 reaches the independently landed Xfer::XferEnum body at RVA 0x009D67B0. It reads the third argument as the width and the second as the payload pointer; all normal paths return the Xfer receiver with `ret 12`. Its four switch destinations were read from the actual table, and its invalid-width path calls the exception throw routine. The extent contains 196 bytes of code followed by the four-entry table. This resolves the earlier slot-0x90 ABI blocker. The shared Xfer header puts its XferEnum declaration at offset 0x94, so the retained address-derived dispatch view expresses the proven offset and reference return without changing that header.

The source includes canonical Snapshot, Xfer, Coord3DBase and AsciiString declarations. The existing geometry header carries the older Zero Hour scalar layout and does not declare this BFME DoXfer override or its shape vector. The local GeometryInfo declaration follows the independently decoded BFME constructors rather than the incompatible Zero Hour layout. No shared header, STL ledger identity or symbol pin is changed. Compiler assertions in `layout-check.cpp` verify the complete object size and every accessed member offset.

## Retry and refutation

The retry started from the saved reconstruction and checked the newly landed resize overload and value-copy helpers. A nontrivial string-copy declaration alone did not change the saved instruction stream. Reloading the vector begin pointer through an indexed loop and initializing the loop index before its guard restored the retail loop. Constructing the version through a visible two-byte constructor restored the stack slots. Calling the visible one-argument resize overload restored count evaluation before outgoing-value construction. A default argument retained the constructor-order mismatch. Trial sources and unedited probe outputs preserve each tested shape.

The final source probes equal retail over the full extent modulo the two relocations. The scoped byte gate must additionally resolve the resize relocation and the GeometryType string. A different slot-3 owner, a mismatched complete copy helper, an incompatible receiver or argument cleanup, or a failing scoped gate would refute this recovery. Naming and layout checker coverage is reported in the raw receipts; compiler assertions supply the offsets that the name oracle skips.

## Collection checks

The normal add_match verification and a separate scoped gate both pass, including function bytes, callee resolution, the GeometryType literal and the body guard. The raw receipts are `add-match.log` and `scoped-gate-python-final.log`. The declaration, class, name-oracle and pin checks also pass. Bank-to-source naming was checked through the repository's `name_regression.regressions` function because this revision's command line takes Git revisions rather than source paths. The old bank remains preserved as `baseline.cpp` in the task's build folder.

Collection is blocked on the coordinator's staged CSV check. `python tools/check_csv.py` fails while reading the removed bank because the read-only Git index still lists it; the new source is likewise awaiting staging. `check-csv-final.log` preserves the unedited failure. The coordinator must stage the complete source, ledger, tombstone, bank deletion, verdict and evidence transaction and rerun the standard check with hooks active. No checker, baseline, pin or shared header was changed to avoid that requirement. The Windows launcher cannot locate Python in this sandbox; invoking its underlying `tools/build.py` with the installed Python produces the passing scoped receipt.
