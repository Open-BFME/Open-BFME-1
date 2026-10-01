# Retail 0x009EBF90 result view and 0x009EF6D0 interface

Baseline: `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`.

## Complete boundaries

The generated row at 0x009EBF90 has a complete 82-byte body, excluding INT3
padding starting at 0x009EBFE2. Its NULL-registry branch returns at +0x45;
its non-NULL branch starts at +0x46 and returns at +0x51. No branch leaves
this extent. The function receives one incoming pointer at `[entry ESP+4]`
and returns that pointer in EAX. It loads the canonical registry global at
VA 0x0134FAAC, constructs the output directly when that global is NULL,
and otherwise passes the same output pointer to 0x009EF6D0 in ECX/stack form.

0x009EF6D0 is the existing 113-byte function, beginning with its own EH
registration and ending with RET 4 at +0x6E. INT3 padding begins at +0x71.
The independently documented 30-byte predecessor at 0x009EF6B0 returns before
the padding at 0x009EF6CE..CF; the predecessor is not part of this body.

## Independently witnessed output and receiver

The 0x009EBF90 NULL branch allocates 0x14 bytes for a separate STLport tree
header. It writes output +0 (the allocated header pointer) and +4, then
initializes the allocated header's +0/+4/+8/+0x0C fields. It does not write
output +8. Finally it writes zero to output +0x0C and one byte to +0x10.
These are distinct output and allocated-header address bases. The native
12-byte tree and trailing word/byte support the natural-size 20-byte C++
result view also matched at 0x009EC050 and described in
`009ef6b0-construction.md`; original padding, complete type, lifetime and
output allocation are not independently recovered. The native receiver
constructor at 0x009F2140 repeats this field pattern at +0x190, +0x1A4,
+0x1B8 and +0x1CC, corroborating the 0x14-byte spacing. This does not settle
the original hidden-return versus explicit-output declaration.

The 0x009EF6D0 body locks receiver +0x2C through the native
EnterCriticalSection import, passes receiver +0x1CC to the independently
matched 199-byte STLport tree copy constructor at 0x009EE8E0, constructs its
result tree at the output pointer, writes output +0x0C/+0x10, and calls the
native LeaveCriticalSection import. Native STLport `<set>` supplies the
12-byte tree layout; compile-time checks require a 12-byte tree, 20-byte
result and 24-byte critical section.

The old signature `copy@Rva009EF6D0` claimed that the output pointer referred
to the registry-sized receiver type, then cast it to a separate 20-byte type.
The actual wrapper constructs and returns the 20-byte result. The correction
uses one typed result throughout and reproduces both complete native bodies.

`AssetRegistry` reuses the existing receiver spelling of the canonical
`g_theAssetRegistry` declaration, also used by the matched 0x009EC050 and
Add_Prototype wrappers. This is a repository ABI view, not a newly recovered
native class declaration. No export, vtable or original header establishes
the original declarations or method name; the method therefore retains the
full RVA as `Rva009EF6D0`. The original distinction between a hidden aggregate
return parameter and an explicit output pointer is not independently known.
The by-value C++ view reproduces the native direct construction, pointer
return, ECX receiver, stack argument and RET cleanup without a cast or adapter.

## Operands and verification

The recovered wrapper has these three actual COFF relocations:

- +0x03 DIR32: `g_theAssetRegistry`, native VA 0x0134FAAC.
- +0x1C REL32: native STLport node allocator, native RVA 0x0082E540.
- +0x48 REL32: the corrected result-producing method, native RVA 0x009EF6D0.

The callee's native import operands are +0x2C (EnterCriticalSection IAT
VA 0x01358D18) and +0x58 (LeaveCriticalSection IAT VA 0x01358E74); its tree-copy
REL32 operand is +0x46, targeting 0x009EE8E0. FS exception-list relocations
still refer to native zero slots and the existing EH handler is checked by
the normal build gate. No new pin or global definition is added.

The new body probes 82/82 bytes exactly outside relocations. The existing
callee probes 113/113, and this source's actual emitted native tree-copy
constructor also probes 199/199 against its existing ledger extent. The
explicit output-pointer reconstruction with native headers instead emitted
133/82 and 126/113, and the value-return callee retaining the old artificial
volatile dummy emitted 109/113. Removing that dummy restores the native
113-byte EH shell; the existing compiler store-order barrier is retained.
Neither the new wrapper nor the callee uses assembly, a new barrier, a new
facade for STLport, or a fabricated callee. The 113-byte callee and the
199-byte generated tree constructor are existing code, not new recovery
credit. Only the 82-byte wrapper is newly recovered C++.

## Default-constructor store order

A review identified that the first exact default-constructor spelling used a
volatile local reference to the word at result +0x0C. This qualifier was not
recovered from a native declaration. It was removed before publication.

The ordinary assignment `m_value = 0; m_active = true;` emits 82 bytes with
exactly six differing instruction bytes: VC7.1 moves `ADD ESP,4` at +0x39
before the word store at +0x36. Initializer-list forms (all members, word
only, and explicit tree), reversed source stores, an inline clear method,
a chained assignment/comparison, an explicit receiver and an inline word
clear helper all retain precisely that adjacent swap. None is byte exact.

The ordinary source operation `memset(&m_value, 0, sizeof(m_value))` before
the flag assignment emits the native order and matches 82/82. The compiler
inlines this four-byte zeroing operation into the same single DWORD store;
there is no memset call, additional load or store, volatile qualifier, or
new barrier in the recovered wrapper. The existing store-order barrier in
the 113-byte copy-result constructor is retained and remains separately
documented. No original native member qualifier is claimed; existing
`m_value` and `m_active` names denote this result view and do not establish
an original field identity.
