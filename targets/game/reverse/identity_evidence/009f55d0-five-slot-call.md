# 009F55D0 wrapper and 009F53D0 five-slot ABI view

## Native extents and physical call

The retail-1.03-unpacked baseline fixes the wrapper at RVA `009F55D0`,
28 bytes through its `RET` at `009F55EB`. INT3 padding surrounds the body.
The existing callee at `009F53D0` is 93 bytes through `RET` at `009F542C`,
also followed by INT3 padding. The recovery changes neither extent.

The wrapper is caller-cleaned. It reads its three incoming DWORD argument
slots at entry ESP `+0C`, `+08`, and `+04`, into EAX, ECX, and EDX. It then
pushes literal zero twice, pushes EAX/ECX/EDX, and calls `009F53D0` at
`009F55E3`. Its `ADD ESP,14h` and `RET` establish a five-slot call made from
a three-slot wrapper. All five outgoing argument slots and their order are
preserved by the ordinary typed C++ call.

An overinclusive scan of E8/E9 byte candidates in every executable PE
section finds this as the sole relative reference to `009F53D0`. The sole
candidate is an instruction inside the proven wrapper. There are no E9
candidates or literal references to VA `00DF53D0`. Thus no native
three-slot call site supplies an independent witness for the old name.

## Existing identity correction

The old row named `009F53D0` as the three-parameter specialization
`_STL::push_heap<S4SortElem24 *, S4Cmp009F4BF0>`, using
`stlport_push_heap_s4sortelem24.cpp`. That hand-written facade collapsed
the vendor helper boundary and supplied no source for the two trailing
arguments that the retail wrapper actually passes. There is no pin for
the old name. The only physical caller is the generated wrapper, which
cannot witness a semantic identity.

The vendor STLport `_heap.c`, lines 91–105, instead has three-argument
`push_heap` forward to five-argument `__push_heap_aux`, with both trait
pointer arguments zero. The auxiliary helper copies `last[-1]` and calls
`__push_heap`. This agrees closely with the native topology, and explains
why the old bank, which reversed that relationship, lost the two pushes.
It is a structural inference about the library family; it does not recover
the original native helper declaration or template arguments.

The existing matched partition-manager body at `009F5C00` uses `push_heap`
in its C++ source, but the retail body inlines that setup and calls
`009F4BF0` directly. It does not call `009F53D0` or `009F55D0`, so it cannot
establish either body's original name. The original three-parameter row
is retired as an unsupported identity and an insufficient typed call view.
This is not a claim that unused trailing slots mathematically distinguish
every possible historical C declaration.

The replacement uses the full-address name `Rva009F53D0` and a five-slot
C++ ABI view. Its two unused `void *` parameters express the two zero slots;
their original types remain unknown. The 28-byte caller is named
`Rva009F55D0`, with no claim that it was originally the public vendor
template. There is one replacement identity per address and no new pin.

## Callee behavior and limits of the type view

At `009F53D0`, entry slot `+0C` is forwarded to the already matched
`__push_heap` specialization at `009F4BF0`. Entry slot `+08` supplies the
end pointer, decremented by 24; six DWORDs from that last record are copied
onto the outgoing argument stack. Entry slot `+04` supplies the first
pointer. The body computes `(last-first)/24 - 1`, passes zero as the top
index, calls `009F4BF0`, cleans 40 bytes, and returns. It never reads entry
slots `+10` or `+14`. The corrected body retains these exact accesses and
the existing low-level callee spelling printed by `tools/callees.py`.

`S4SortElem24`, `S4Cmp009F4BF0`, and the inherited `m_key`/`m_values`
spellings are existing repository ABI views. Native operands establish
24-byte records and six copied DWORDs; they do not establish original
class declarations, semantic field names, comparator size, or padding.
The comparator parameter is represented with its existing MSVC argument
slot view. No new member, original vendor type, volatile qualifier,
barrier, dummy local, extra access, or address cast is introduced.

The two source files keep the caller's callee declaration separate from
the definition, so the normal compiler emits the existing call boundary.
No noinline attribute or artificial source operation is needed.

## Ownership and byte verification

Normal body claims cover `009F53D0` and `009F55D0`. A fresh active-claim
check found neither `family:stlport` (`FB5738E0`) nor the old identity's
link-queue key (`F4D8E67C`) held. Shared headers, STL family pins, and the
existing low-level body are untouched.

The first ordinary C++ probes are exact at 93/93 and 28/28 bytes, each with
one REL32 slot. Official `add_match.py` verifies the corrected callee
before the wrapper, then the source-scoped gates check the physical targets.
The 93-byte correction recovers zero new bytes; the wrapper recovers 28.
Scoped byte checks do not establish whole-program runtime behavior.
