# Window vector update at RVA 0x004B19E0

The complete 342-byte body is reconstructed as the existing address-derived `Rva004B19E0::apply(void *)`. Its owner remains unidentified. The existing pin routes that exact method spelling through ILT RVA 0x00034B58, whose complete instruction is a jump to the target. No RadialWindowController identity is asserted.

## Retry hypothesis and measurements

The earlier declaration blocker can be addressed without changing a shared header: the existing `inputs/reference/shims/gamewindow/GameClient/GameWindow.h` declares `winIsHidden`, `winGetStatus`, `winSetSize`, `winSetPosition` and `winSetStatus` with the decoded return types. Native STLport 4.6 supplies the vector erase and swap implementations. This hypothesis would be refuted by a compile failure with that header or by a mismatch in those native operations after the ABI and layout were established.

The first complete native trial emits 342 bytes with eight differences, all zero-store field offsets after the swap. The generated adjacent-store family exhausts four candidates with eight, eight, fifteen and fifteen differing bytes. Splitting chained assignments into individual stores in retail order produces an exact 342-byte masked probe. Replacing the old byte-result comparator alias with the existing canonical `bfmeSameAH` declaration and a conversion of its result to an unsigned byte preserves that exact result. Declaring the native allocator-proxy swap specialization externally also preserves it. The individual helper probes reproduce the complete 31-byte swap and 13-byte copy bodies; those probes are supporting evidence, not additional recoveries.

## Boundary and target ABI

The target starts at RVA 0x004B19E0 and ends after `ret 4` at RVA 0x004B1B33. Every direct conditional branch stays inside that extent, every ordinary path reaches that return, and the following bytes through the next ledger body are `int3` padding. There is no tail jump, hidden return-storage parameter, exception registration or target virtual call. ECX is the unchanged receiver. The single stack argument is an address of writable vector storage. EAX is unused by all three complete callers.

The three instruction-aligned incoming sites are RVA 0x004A6330 in the complete 1381-byte caller at 0x004A5E30, RVA 0x004AF1DE in the complete 1188-byte caller at 0x004AEE00, and RVA 0x004AF8B0 in the complete 627-byte caller at 0x004AF6A0. Each loads the receiver from ControlBar storage at +0x2F0 and pushes the address of its local three-word vector before calling ILT 0x00034B58. The first and third callers have landed C++ using `apply(void *)`; the second is a byte lift and its ledger advertises an Image-only signature despite a decoded `ret 8`. Its advertised identity is not used as evidence for this reconstruction.

## Payload and ownership

The caller at 0x004AF6A0 constructs the incoming storage with three zero dwords at frame +0x18, +0x1C and +0x20. Its fast insertion at 0x004AF7E4 copies the window pointer from the ControlBar command-window slot directly into exactly one dword at the finish pointer, then advances finish by four. The growth path calls ILT 0x000056CD, which jumps to the complete 265-byte body at 0x00483A10. That body reads exactly one dword from the value reference at 0x00483AA2 and writes exactly one dword to each new element at 0x00483AA4. It reads no second field and invokes no value constructor, refcount operation or element destructor. Its other copies move complete four-byte-element ranges with imported memmove. Allocation and deallocation concern the vector buffer. It returns with `ret 0x14` after updating start, finish and capacity.

The other two callers copy the same command-window pointers into the same three-word local storage, both in their fast paths and through the same growth helper. The target treats each element as a nullable GameWindow receiver and calls the independently decoded window methods on it without a receiver adjustment. This establishes a vector of GameWindow pointers from actual field accesses and value copies, independently of allocation size or template pins. There is no container key and no small pair payload. Erasing an element does not destroy its GameWindow. On replacement, the receiver's vector exchanges buffer ownership with the caller's local vector; callers subsequently free the old buffer without destroying window objects.

The receiver's first vector is at +0x0C, with start at +0x0C, finish at +0x10 and capacity at +0x14. The target sets the byte at +0x08 and clears the pairs at +0x20/+0x24 and +0x28/+0x2C, then fields +0x30 through +0x40. These offsets agree with the landed reset at 0x004B19A0, the clear at 0x004B1720 and the animation update at 0x004B1C80. The target does not establish the receiver's first two words or the later map payload. The declaration leaves those untouched regions opaque and retains the existing descriptive names used by the reset and clear family.

## Callee contracts and bindings

| Retail call route | Complete body | Verified contract |
| --- | --- | --- |
| ILT 0x0003A5B7 | 0x00478410, 10 bytes | GameWindow receiver in ECX; hidden status bit from +8; result is exactly zero or one; caller consumes AL. |
| ILT 0x00023DDA | 0x00478480, 4 bytes | GameWindow receiver in ECX; full unsigned status result in EAX. |
| ILT 0x000482AC | 0x00478250, 63 bytes | `winSetSize(int width, int height)`; two four-byte arguments; `ret 8`; returns integer zero. The indirect manager call takes window, message, width and height in that order through vtable +0xD4. |
| ILT 0x0001949D | 0x004780D0, 85 bytes | `winSetPosition(int x, int y)`; two four-byte arguments; `ret 8`; returns integer zero. The optional anchor call uses ECX from receiver +4 and virtual slot +8 with old x, old y, new x and new y. |
| ILT 0x00013C78 | 0x004B01D0, 75 bytes | Existing `bfmeSameAH(const BfmeRunAH *, const BfmeRunAH *)`; cdecl; compares two start/finish ranges by every four-byte element; both return paths set full EAX to zero or one. Converting that result to an unsigned byte reproduces the target's AL test. |
| ILT 0x00033F19 | 0x004B1720, 142 bytes | Existing `Gen_004B1720::bfmeClear()`; receiver unchanged; clears the vector at +0x0C and the tree storage at +0x44. |
| ILT 0x000277A5 | 0x004B0130, 31 bytes | Cdecl swap of two four-byte allocator-proxy references; two caller-cleaned stack slots; no return value used. |
| ILT 0x00033523 | 0x00478420, 19 bytes | Existing unsigned `winSetStatus(unsigned)` binding; `ret 4`; ORs the argument into status at +8 and returns prior status in full EAX. |
| IAT VA 0x0135945C | MSVCR71.dll memmove | Cdecl destination, source and unsigned byte count; pointer returned in EAX; target discards it. |

Every helper extent above was decoded completely and checked with `checked_callees.py`. No conditional branch or tail jump leaves any of those helper extents. The window methods' indirect calls were inspected separately; their canonical declarations and already-landed sources are reused, rather than the old void-return aliases.

## Native proxy-swap pin evidence

Retail swaps the first two vector storage pointers inline and calls 0x004B0130 on the capacity proxies at offset +8. The complete swap body first calls ILT 0x00031296 to the complete 13-byte copy helper at 0x004AFCF0. That helper reads the single dword at source +0, writes it to destination +0, returns the destination in EAX and performs `ret 4`. The swap then reads the right-hand single dword, writes it to the left-hand proxy, and writes the saved temporary to the right-hand proxy. There is no allocator payload, additional field, destructor or unwind state.

`inputs/vendor/stlport/stl/_vector.h` implements vector swap by swapping start, finish and `_M_end_of_storage` in that order. `_alloc.h` defines `_STLP_alloc_proxy` as an allocator base plus the single `_M_data` word, and `_algobase.h` implements its swap as copy construction followed by the two assignments. `_config.h` identifies the supplied headers as version 0x460. For the independently established GameWindow-pointer element type, compiling those actual templates reproduces the swap and copy bodies completely. The added native proxy-swap pin is an independently checked typed binding for the callee used by this target; it does not rename or convert either helper's existing generated ledger row.

The pin hypothesis would be refuted by another field accessed in the actual copy helper, a nonempty allocator state, different stack cleanup, a different routed call target, or a target swap that performs element operations. None occurs in the complete decoded bodies. The declaration-only specialization keeps those already-owned helpers external and adds no duplicate strong definition.

## Reproduction evidence

Trial sources, raw probes, complete decoded bodies and checked-callee outputs are preserved under `build/004B19E0-run/`. `probe02.txt` is the first exact target experiment, `probe03.txt` uses the canonical comparator and external swap, and `probe-swap02.txt` and `probe-copy02.txt` contain the helper experiments. `store-search.txt` and `build/shape_search/65b4927acfc347c19de0aeb102c83974/result.json` retain the rejected generated store alternatives. The strict add_match build in `add-match.txt` and the scoped build in `scoped-gate-bash.txt` both pass byte, relocation, source-claim and body checks. `find-declared.txt`, `class-gate.txt` and `pin-check.txt` retain passing declaration, canonical-class and pin checks. No shared header or shim was changed, so this change requires the scoped gate rather than a full gate. `check-csv.txt` fails only because the new source is not yet tracked; staging is reserved to the coordinator. The source and all strict landing checks must be reviewed together; masked equality alone is not acceptance.
