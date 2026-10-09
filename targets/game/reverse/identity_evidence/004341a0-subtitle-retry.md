# Subtitle virtual slot 1 at RVA 004341A0

The retained body is a partial. It preserves the bank's address-qualified names and reconstructs the complete target in C++. No function row or pin is changed. Measurements use revision `97c5d7862c9bdb647de0fa253eeb02a1adc9d040`, the retail baseline and an explicit extent of 508 bytes. The final source is banked at `targets/game/reverse/attempts/0x004341a0.cpp`.

## Retry hypothesis and refutation

The previous bank describes a register-allocation and layout problem, but decoded instructions contradict its control flow, helper arguments, color-argument order and cached values. The new hypothesis is that correcting these declarations and expressions will remove most of the mismatch before changing registers. It would be refuted if the corrected body were no closer than the saved body. The current landed broadcaster `game/GameEngine/Source/Common/Rva0081D520Owner.cpp` supplies an independent six-argument virtual-call contract that earlier verdicts lacked. Its complete retail body was checked rather than trusting its source names.

The hypothesis survives the measurements. `build/target-004341a0/00-saved-probe.txt` records the original bank. `01-corrected-probe.txt`, `02-alpha-before-probe.txt`, `03-verified-types-probe.txt` and `06-final-bank-probe.txt` in the same directory retain the complete, unedited probe outputs. `measurements.jsonl` indexes the subsequent probes. The corrected frame guard and shared fade calculation reproduce the leading instructions. Moving the alpha shift before the size query removes the scheduling difference introduced by the initial correction.

## Boundary and receiver

`build/target-004341a0/retail-decode.txt` decodes the entire target, both coordinate helpers, the matched constructor and the three relevant ILT thunks. The target's two return paths are at RVA 00434318 and 00434399, both `ret 0x18`. The latter ends at 0043439C, followed by INT3 padding. All conditional branches remain inside the extent; there is no target tail jump or exception frame. The receiver enters in ECX and is retained in ESI without adjustment.

Vtable VA 010F3920 slot 1 contains VA 004460A6, whose complete five-byte jump reaches RVA 004341A0. The matched constructor at RVA 00434810 installs this vtable and initializes the three display-string pointers at offsets 0x24, 0x28 and 0x2c and the count and capacity at 0x30 and 0x34. Its base constructor supplies the fields used by this target: color at 0x08, style at 0x0c, alignment at 0x10, line at 0x14 and frame bounds at 0x18 and 0x1c. The reconstruction is an opaque access view, not a claim about the original method spelling or the text member's ownership. Constructor unwinding is not reconstructed by this target.

`build/target-004341a0/actual-caller-decode.txt` and `checked-actual-caller.txt` retain the complete broadcaster at RVA 0081D520. At RVA 0081D55A it dispatches through listener slot 1 with an integer value, its own receiver as the owner pointer, and four 32-bit coordinate slots. Its caller at RVA 006EE0C0 converts display dimensions to floats and forwards the video-frame result. The target forwards coordinate pairs to helpers that read them with x87 `fld` and `fsub`, independently establishing their float representation. The broadcaster's loop receiver is an entry from its pointer range at offsets 0x14 and 0x18; the factory and installed entry vtable anchor the applicable subtitle listener. No direct named call identifies the original method name.

## Direct helper contracts

ILT RVA 00029780 jumps to the already-matched alignment helper at RVA 00433FC0. Each target call pushes alignment, width, the unused owner-sized slot and two floats. The helper consumes five stack slots, returns its integer in EAX and uses a plain `ret`; the target performs caller cleanup. The canonical existing declaration `bfmeAlignVIL(Int, Int, Int, Real, Real)` is retained.

ILT RVA 0002F040 jumps to RVA 004340C0. The complete helper has two return paths and a backward internal branch after its final clamp block; all are inside the recorded extent. It consumes an integer index, owner pointer and two float slots, returns an integer in EAX and uses plain `ret`. The target defers cleanup of the alignment call and coordinate call until their combined 0x24 bytes are removed. The callee inventory's nine-slot hint conflates that deferred cleanup; it is not the coordinate helper's arity.

The coordinate helper reads the owner byte at 0x60. Its alternate path multiplies a float coefficient from `owner + 0x24 + index * 4`. The bank's `m_lineCoordinates` and `m_alternateMode` names are retained on that owner view. These fields do not extend the subtitle-entry receiver beyond the factory's 0x38-byte object. The normal path clamps the integer index and uses the absolute coordinate difference divided by fifteen. No STL type is inferred or changed.

Both main loops add the loop index to the line field and pass the owner argument to the coordinate helper. The background loop stores its index in the dead incoming frame slot. Treating that stack location as the original frame was a bank error. Both loops reload the count and display-string pointer after calls, as retail does. The leading fade path also multiplies by eighteen and clamps; the original bank multiplied by nine without a clamp.

## Virtual contracts

`build/target-004341a0/display-vtable.txt`, `displaystring-vtable.txt`, `abi-decode.txt` and `checked-abi.txt` retain the slot routes, full decodes and checked inventories. These establish the following physical contracts without guessing missing virtual names.

| Target slot | Actual retail route | Verified contract |
|---|---|---|
| DisplayString 0x28 | ILT 0003B24B to 006F4690 | Two color words, text color first and zero drop color second; `ret 8`. |
| DisplayString 0x34 | ILT 0000FF42 to 006F4990 | Two integer coordinates; `ret 8`; forwards through slot 0x38 with two zero color words. |
| DisplayString 0x3c | ILT 000401A6 to 006F49B0 | Two integer output pointers; width receives member 0x1f0 and height member 0x1f4; `ret 8`. |
| DisplayString 0x40 | ILT 00028876 to 006F53A0 | One signed character-position argument, EAX width result, `ret 4`. |
| Display 0xb0 | ILT 000096F6 to 006E9B70 | No stack arguments; loads the renderer receiver at 0x164 and tail-jumps to the complete Reset body 00934820. |
| Display 0xc0 | ILT 0000A06A to 006EA050 | Four floats followed by a packed color word; both exits use `ret 0x14`. |
| Display 0xdc | ILT 00008265 to 006E9B80 | No stack arguments; adjusts the receiver by loading member 0x164 and tail-jumps to 00934940, whose complete decode has a plain return and no outgoing jump. |

The W3DDisplay table at VA 0111EDD0 and W3DDisplayString table at VA 0111FEA8 supply these routes. Existing matched sources were opened and compared to the retail instructions. `TheDisplay` retains the existing `Display *` declaration and recorded DIR32 identity at VA 012F1270. No private canonical `Display` declaration or shared header is introduced.

## Remaining mismatch and rejected shapes

`build/target-004341a0/final-scoped-gate.txt` is the authoritative scoped result for the final candidate. The body has the retail extent and no boundary issue. Eight non-relocation bytes differ at offsets 0xec, 0xf2 and 0xfa through 0xff. All relocation sites align. Retail loads `TheDisplay` into ECX, loads its table through ECX, stores the coordinate result and copies ECX to EDI just before the 0xb0 call. The candidate loads the singleton into EDI, loads its table through EDI and copies EDI to ECX before storing the coordinate result. This is the remaining register-allocation and adjacent-instruction-order problem.

The source-family generator found no applicable register, copy or frame choice. A finite explicit search then tested moving the width conversion before the local display declaration and combining the display assignment with its first virtual call. Both emitted the unchanged eight-byte mismatch; further unchanged register experiments were stopped. The raw search output is `build/target-004341a0/receiver-search.txt`. Its immutable trial sources and measured manifest are under `build/shape_search/4f89069c79054feb9bcd6dce4667ce10/`. Correcting the no-stack virtual's return declaration to void and moving the coefficient fields to the actual owner also retained this shape.

The ordinary symbol resolver recognizes the alignment call and its ILT but does not recognize the bank's typed `rva004340C0SubtitleCoordinate` declaration at its two call sites. The bank retains its original linker alias to the existing opaque thunk; that alias is not accepted as a strict resolver binding. No pin was added because the body still differs. Reopening needs a new receiver-access or inline-helper hypothesis grounded in real declaration context, together with a strict binding for this independently decoded coordinate helper. Repeating either tested local-order variant is not justified.

The final candidate is an improved bank, not a verified source recovery. CSV consistency, pin consistency and the class gate pass. The source-level naming comparison uses `name_regression.regressions` because this checkout's command-line interface expects Git revisions instead of the file operands in the brief; it reports no descriptive-to-placeholder substitution. The declared-unmatched check rejects an explicitly passed scratch source for having no matched ledger row, which is expected for an unlanded partial. No game source, function ledger, symbol pin, policy or tooling is changed; a full gate is not required by these evidence-only changes.
