# Renderer initializer at RVA 0x0078C070

The complete 514-byte body is recovered as `Rva00785FD0Renderer::rva0078C070` in `game/Libraries/Source/WWVegas/WW3D2/Rva00785FD0RendererInitialize.cpp`. The address-derived class and method names, member names and local component names are retained from the bank. The EA class name remains unknown. The existing `initializeRva0078C070` pin describes the same address and receiver; this recovery adds no pin or second body.

## Retry hypothesis and measurements

The saved body treats the scale, translation and bias as independent scalars. Zero Hour `GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2d.cpp`, `Render2DClass::Update_Bias`, instead computes both bias components through a `Vector2` value before adding them to the offset. Retail at `0x0078C0E3` through `0x0078C116` divides X and Y, stores the Y result, adjusts X, reloads Y, and adjusts Y. The scalar bank adjusts X before computing Y. This supports testing a paired bias value and paired scale/translation lifetimes. Failure to reproduce that instruction sequence or improve the measured frame and stack operands would refute this compiler-shape hypothesis. A matrix-type substitution alone is rejected by its unchanged measurement.

The tested starting revision is `871e04e61d8563350f71ca698afcd652e9016d94`. Each source and unedited probe output is retained in `build/target-0078c070/`; the probes explicitly request the complete retail size. The difference counts below mask COFF relocation operands and are diagnostic until the strict gate verifies their destinations.

| Trial source | Compiled bytes | Differing bytes | Observation |
|---|---:|---:|---|
| `00-bank.cpp` | 506 | 299 | Saved body reproduces the recorded mismatch. |
| `01-native-matrix.cpp` | 506 | 299 | Native matrix spelling leaves the shape unchanged. |
| `03-vector-bias.cpp` | 502 | 357 | Adding the pair directly changes the arithmetic and scheduling. |
| `04-bias-value.cpp` | 514 | 40 | A separate paired bias reproduces the missing Y spill and reload. |
| `05-resolution-pair.cpp` | 514 | 228 | Pairing the resolution displaces the conversion slots. |
| `06-scale-pair.cpp` | 514 | 40 | Paired scale reduces the frame but retains the store mismatch. |
| `07-zero-before-translate.cpp` | 514 | 29 | Clearing the Z diagonal before translation restores the instruction order. |
| `08-paired-scale-order.cpp` | 514 | 29 | Paired scale reduces the frame to `0x48`. |
| `09-paired-scale-translation.cpp` | 514 | 0 | Paired translation permits the retail `0x44` frame and every stack operand. |

`02-listing.cpp` is a diagnostic build of the matrix trial with `/FAsc`; it changes no body bytes. The saved assembler listings for the bias and scale trials expose the scalar slots and the four 16-byte transpose temporaries. The final source also probes exactly at its destination path. Matching these paired lifetimes establishes a valid C++ reconstruction; it does not independently establish the original names of the local objects.

## Complete boundary and receiver evidence

`decoded-0078c070.log` retains all instructions and padding after the target. The two unsigned-conversion branches at `0x0078C089` and `0x0078C0AF` and the bias branch at `0x0078C0DF` stay inside the body. Both bias paths join at `0x0078C11A`. There is no direct or indirect call, exception registration or early return. The sole exit restores `0x44` bytes at `0x0078C26A` and tail-jumps at `0x0078C26D`; the five-byte jump ends at `0x0078C272`, followed by INT3 padding. `checked-target.log` independently confirms the full decode and outgoing tail transfer.

The complete landed caller at RVA `0x00782ED0`, size 247, allocates `0xE0` bytes at `0x00782EF0`, passes the allocation in ECX to constructor ILT `0x0003164C`, and stores the returned object at VA `0x01306954`. Its existing-object and newly-constructed paths join with that receiver in ECX. The call at `0x00782F30` reaches ILT `0x0002DE57`, whose complete five-byte body jumps to `0x0078C070`. No stack argument is supplied. The next instruction calls the globals-reset function without reading EAX or an x87 result. The decoder and `checked-caller.log` retain the complete caller; `decoded-0002de57.log` retains the target route. The landed caller source names the existing renderer class independently of this reconstruction.

The complete tail ILT `0x00008D4B` jumps to `0x0078B4F0`. That complete 1694-byte helper saves ECX into ESI at `0x0078B4FD`, accesses the renderer's matrices and vertex-buffer field through ESI, and has one exit at `0x0078BB8D` with a plain RET after restoring its local frame and saved registers. All conditional branches remain within its extent. It reads no incoming stack argument. The indirect D3D transform calls at `0x0078B6AA` and `0x0078B9C1` pass the device, transform index and matrix pointer on the stack; the indirect material-release calls use their material receivers, separate from the renderer. None changes the incoming renderer contract. `decoded-0078b4f0.log`, `checked-helper.log`, `decoded-00008d4b.log` and `checked-thunk.log` retain this evidence. The source's one-pointer fastcall cast states ECX forwarding and zero stack arguments to the existing ledger thunk; it does not rename the helper or claim a new helper ABI identity.

## Member, value and inline evidence

The existing landed constructor at `0x0078B310`, size 378, and its source `Rva00785FD0RendererConstructor.cpp` establish the four-byte texture handle, mode at `+0x08`, stencil generation at `+0x0C`, three 64-byte matrices at `+0x10`, `+0x50` and `+0x90`, vertex-buffer pointer at `+0xD0`, and counters at `+0xD4`, `+0xD8` and `+0xDC`. The target resets the two control words, writes all sixteen float cells of the first matrix, then resets the `+0xD4` counter. The new source retains that layout and uses the constructor's `DX8VertexBufferClass *` declaration. The constructor is layout evidence, not a new constructor recovery; this target has no owning temporary, destructor call or unwind cleanup.

The resolution objects are the existing signed four-byte DX8Wrapper data rows at VAs `0x012D6DB4` and `0x012D6DB8`. The target explicitly interprets each as unsigned: FILD reads the dword and the negative-sign path adds the float `2^32` at VA `0x01075358`. The signed storage declarations and unsigned casts retain both contracts. Scale, translation and bias calculations read and write 32-bit float components. The complete native `Vector2` constructors, assignment and arithmetic definitions in `vector2.h` read and write X and Y only; the reconstruction uses no container or allocation-size inference.

`Matrix4::Make_Identity`, `Transpose`, its four-Vector4 constructor, `Init`, and assignment are visible in the unchanged native math headers. `Vector4` constructs and copies all four float components. Transpose builds four values from the matrix columns and assigns all sixteen output components. Retail's corresponding loads and stores occupy `0x0078C171` through `0x0078C249`. The unchanged `DX8Wrapper::Set_Transform(D3DTS_WORLD, ...)` inline then clears bit 18 and sets bit 0 at VA `0x0133F49C`, exactly as retail does at `0x0078C24F` through `0x0078C25E`. No out-of-line matrix helper or hidden return-storage ABI is introduced.

These identity and ABI claims would be refuted by a decoded caller passing a different receiver or stack argument, a tail helper consuming an incoming stack slot, a retail field access contradicting the stated matrix/counter layout, or a strict relocation check resolving any reference to another retail object. Exact equality is separately required over the full target extent.

## Verification receipts

`final-source-probe.log` confirms exact shape at the final source path. `add-match.log` retains the verified dump replacement, strict byte match, float constants, DIR32 destinations and body guard. `scoped-gate.log`, `declared-final.log`, `bank-name-core.log`, `class-gate.log`, `diff-check.log` and `pins-final.log` retain passing checks. `check_csv-initial.log` passes on the starting tree. `check-csv-final.log` fails because the working-tree validator includes the deleted bank from the read-only Git index, then attempts to open it. Its source-presence check also requires the new source to be tracked. The coordinator must stage the complete conversion, including the bank deletion and new source, and rerun `check_csv.py` with the normal commit hooks. No check or tool is changed to bypass this collection requirement.

The revision's `name_regression.py` CLI accepts Git revisions rather than file paths; `check_bank_names.py` calls its actual `regressions` implementation on the bank blob at HEAD and the new source without writing Git state. The coordinator still runs the normal staged hook when collecting this uncommitted change. The scoped build uses the explicit Git Bash executable because the batch launcher fails through this subprocess invocation. An automatic unrelated hatch-baseline rewrite during the first verification was retained in `automatic-hatch-diff.log` and restored to HEAD content. No shared header, shim, tooling, baseline or STL ledger/pin remains changed, so the change requires the scoped gate.
