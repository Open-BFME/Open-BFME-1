# Pathfinder movement predicate at RVA 003E7B90

The recovered symbol is `?rva003e7b90@Pathfinder@@QAEEPAVObject@@PBUCoord3D@@11@Z`. It retains the saved reconstruction's method and member names. The owner and physical ABI are established independently of byte equality. The EA chain label `Pathfinder::IsValidHordeMemberRegularMovement` is supporting context only; this recovery does not adopt that method identity.

## Boundary and callers

Retail begins after INT3 at 003E7B90. Both terminal paths restore the four saved registers and 36-byte frame, then execute `ret 16` at offsets 01B6 and 01C2. INT3 starts at 003E7D55, establishing the complete 453-byte extent. Every conditional branch and internal jump stays within the decoded body; there is no outgoing tail jump or exception registration.

The complete callers at 002768A0 and 0027C250 call ILT 00014FBA at instruction-aligned offsets 0171 and 05C3. Its five bytes decode to `jmp 003E7B90`. Both load ECX from `TheAI` plus 0C, which is the Pathfinder receiver used by matched neighbours. They push, in reverse order, the final coordinate pointer, source coordinate pointer, layer-position pointer, and Object pointer, then test AL. The target reads the Object at its first stack argument and reads the other three arguments as pointers. Its calls and returns require no hidden result storage or receiver adjustment.

The first caller's ledger extent includes inline switch data. Its executable instructions occupy 2434 bytes, followed by the two-byte `mov edi,edi` alignment and two adjacent jump tables totalling 40 bytes. The indirect dispatches at offsets 00B7 and 053F reference those tables. Each table entry points to a decoded instruction boundary inside the same caller. `checked_callees.py` succeeds on the complete executable portion; its rejection of the whole ledger extent is retained as a data-versus-code diagnostic, not suppressed. The second caller decodes completely over its 2669-byte extent.

## Callee and layout contracts

Every target call was decoded, including its ILT jump. The complete target and the following complete helpers were checked with `checked_callees.py`; their disassemblies and unedited checker output are retained under `build/worker-003e7b90/`.

| ILT | Body and extent | Independently decoded contract |
|---|---|---|
| 000441CF | 003E1F10, 163 bytes | Pathfinder receiver, Object pointer, two 12-byte coordinate values, `ret 28`, AL result. The values' X and Y fields are used as floats and adjusted in place, then passed to worldToCell. |
| 000022BB | 00087A80, 26 bytes | Receiver is an override-chain node; successive pointers at offset 04 are followed. EAX returns the final node; plain `ret`. |
| 00010EA1 | 001BE410, 35 bytes | Object receiver; reads Team at 023C, obtains its controlling Player, tests Player type at 2C, returns AL; plain `ret`. The actual Team accessor at 000EC8F0 was separately decoded over its complete 12-byte extent. |
| 0001C675 | 001A7C20, 245 bytes | TerrainLogic receiver, Object pointer followed by coordinate pointer, `ret 8`, EAX layer. The complete body reads coordinate X/Y/Z and retains the two arguments in its bridge and Pathfinder calls. Its virtual calls are terrain operations at slots 37 and 6, not calls through a coordinate or Object receiver. |
| 000461FF | 003DEE30, 297 bytes | Object pointer, signed integer output reference, one-byte Boolean output reference, `ret 12`, void result. It stores the integer at output offset 00 and Boolean at output offset 00, with no output-pointer retention. |
| 000171E8 | 003D7EC0, 156 bytes | Pathfinder receiver, coordinate pointer, two-integer cell output, `ret 8`, AL overflow result. Reads X/Y as floats, writes both output fields, clips against receiver offsets 14 through 20. Its indirect import is `MSVCR71.dll!floor`, independently checked by the strict import guard. |
| 00042249 | 003D4F00, 95 bytes | Pathfinder receiver, signed layer/X/Y dwords, `ret 12`, EAX cell pointer. Calls the layer helper on receiver `this + 085C + 44*layer`; its ground fallback uses row pointers at 10 and 16-byte cells. The layer helper at 003FBB20 was decoded over all 85 bytes, including both coordinate fields and every return. |
| 0002B9E0 | 003D4F90, 158 bytes | Pathfinder receiver, movement-record pointer, cell pointer, `ret 8`, AL result. Reads record DWORD 00, bytes 04/05, signed DWORD 08, and cell packed DWORD 0C. This establishes the full payload, rather than inferring it from record size. |
| 0002F3F6 | 003D5170, 23 bytes | Cdecl signed integer argument, plain `ret`, EAX Boolean result for the closed interval 17 through 64. |

The target constructs the movement record from the AI DWORD at 01B8, negated template byte at 04CC, computer-control result, and template signed DWORD at 0444 minus one. These become record offsets 00, 04, 05, and 08 respectively. Both the producer and the complete predicate agree. The visible radius helper additionally reads template DWORDs at 00C8/00D4, template float at 0408, and Object float at 00BC. These accesses match the already recovered radius donor and the decoded retail helper.

The three-float coordinate layout comes from the canonical `game/Libraries/Include/Lib/Coord3D.h`. The address-derived `Rva003E7B90CoordCopy` adds no fields or ownership and is compile-time checked to remain 12 bytes. Its constructors read and write X, Y and Z at offsets 00, 04 and 08. Its inline empty destructor models the outgoing copies' compiler lifetime without introducing an external destructor, cleanup helper, invented native type identity, or shared-header change. The actual outgoing helper consumes precisely those two coordinate values. Neither this caller nor that helper has exception states or cleanup calls. Constant member-pointer unions compile to the independently decoded direct ILT calls; the target contains no runtime virtual or indirect dispatch.

## Retry hypothesis and measurements

The previous reconstruction's first divergence was the outgoing by-value coordinate call. New context consisted of the landed `sameCell`, `worldToCell`, radius helper, cell predicate, and adjacent Pathfinder bodies. The hypothesis was that native coordinate lifetime and authentic callee visibility, rather than register spellings, explained the missing prologue and stack reuse. Failure to recover the outgoing-copy address stores, or failure of the visible helper to match independently, would refute it.

| Saved trial | Measurement against the decoded 453-byte target |
|---|---|
| trial00-original.cpp | 443 bytes, 355 differing non-relocation bytes, 15 shifted relocation sites; first difference 0003. |
| trial01-copyctor.cpp | 445 bytes, 369 differences; a copy constructor alone does not recover the outgoing lifetime stores. |
| trial03-copydtor-scope.cpp | 453 bytes, 27 differences; copy construction plus empty destruction recovers the complete prologue. The initial unscoped destructor trial fails compilation because its goto skips local initialization. |
| trial04-decoded-corrections.cpp | 453 bytes, 16 differences; correct layer-1 fallthrough, literal 5.0f, and callee return declarations. |
| trial05-native-returns.cpp | 453 bytes, 42 differences; early return with function-scope local lifetime is rejected. |
| trial06-adjusted-scope.cpp | 453 bytes, 37 differences; a narrower adjusted-position scope is rejected. |
| trial08-canonical-scoped.cpp | 453 bytes, 16 differences; canonical coordinate header plus address-derived copy view preserves the private-view improvement. |
| trial09-failure-lifetime.cpp | Same 16 differences; sharing the failure label does not fix return order. |
| trial10-main-guard.cpp | 453 bytes, three differences at 007C, 00AB, 00D7; guarded main block fixes return order. |
| trial11-maxlayer-home.cpp | 453 bytes, three differences at 00D2, 00D7, 00F2; explicit max-layer parameter home moves the mismatch. |
| trial12-output-homes.cpp | 453 bytes, 233 differences; forcing output references onto parameter homes damages allocation and is rejected. |
| trial13-object-reference.cpp | Same three differences as trial10; an Object parameter reference supplies no improvement. |
| trial14-visible-radius.cpp | Caller matches outside relocations; the separately probed 297-byte radius helper also matches outside relocations. Authentic output non-retention fixes the three stack slots. |
| trial15-correct-getcell-twin.cpp | Strict caller and helper verification passes after selecting the actual 00042249 ILT, without a new pin. |

The first strict run exposed the historical bank's `getCell` spelling resolving to the other body at 003D4E80. Retail calls 00042249, which jumps to 003D4F00. Reusing the already recorded address-named thunk with the decoded member-call signature repairs this target's reference; no existing identity, pin, or other source is changed. Direct underlying-body declarations are otherwise resolved through their retail ILTs by the current verifier, so the old blanket ILT blocker is refuted.

The source preserves the bank's descriptive identifiers, uses canonical coordinates, retains the original address-named method, and makes the radius definition inline and noinline to avoid a second strong definition. No STLport row or pin is needed. The only inline assembly is the donor's established two-instruction x87 integer conversion, whose emitted helper is independently byte-exact.

## Verification and falsification

All work was tested from base revision `c050aa134026577b06495644ce2177000c8ee197`. `strict-post-land.log` retains the final two-body strict byte and call checks, constant checks, DIR32 checks, and body guard. `scoped-gate.log` is the ordinary build.sh verification of the converted ledger row. Declaration, canonical-class, name-regression library comparison, name-oracle, and global pin checks pass. The name-regression CLI in this revision accepts Git revisions rather than two filenames; the unchanged comparator was therefore called directly on the saved bank and new source. The original bank and every experimental source remain under the task folder for reproduction; raw probe output is unedited.

The initial CSV check passed. The final ordinary `check_csv.py` invocation cannot complete in this read-only-index checkout: add_match removed the obsolete bank, while `git ls-files` still lists it until its deletion is staged, causing a FileNotFoundError. The new source is also untracked until collection. `check-csv-final.log` retains the failure. The coordinator must stage the explicit conversion paths, then rerun the unchanged checker and commit hooks. This is a collection prerequisite, not a byte or ABI mismatch; no checker, baseline, or index was changed to bypass it.

Refutation requires a caller with different argument order, width or receiver, a target branch escaping this proven extent, a helper accessing another value field or retaining an output address, or strict verification resolving a call/global differently from retail. No such contradiction remains in the decoded bodies used for this recovery. The EA semantic method name remains unclaimed. No full gate is required by a source-only conversion with no shared header or shim edit; the scoped gate covers the new row and the existing helper is separately verified in the new translation unit.
