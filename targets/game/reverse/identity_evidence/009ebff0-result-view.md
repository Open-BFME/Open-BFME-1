# Retail 0x009EBFF0 result view and 0x009EF750 interface

Baseline: `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`.
This is the adjacent form of the published 0x009EBF90/0x009EF6D0 recovery;
`009ebf90-result-view.md` describes the same native result view and the
ordinary memset store-order lever. No volatile qualifier is introduced.

## Boundaries and physical ABI

0x009EBFF0 is a complete 82-byte body. Its NULL branch returns at +0x45,
and its non-NULL branch starts at +0x46 and returns at +0x51; padding starts
at 0x009EC042. The output pointer is at `[entry ESP+4]` and is returned in
EAX. The non-NULL branch loads ECX from the canonical global VA 0x0134FAAC
and passes the same output pointer on the stack to 0x009EF750.

0x009EF750 begins its own EH frame and ends with RET 4 at +0x6E, for a
complete 113-byte extent. Padding begins at 0x009EF7C1. The receiver enters
in ECX, the output pointer enters at `[entry ESP+4]`, and four stack bytes
are cleaned. The native lock is at receiver +0x2C and the copied tree is at
receiver +0x190. The adjacent 0x009EF6D0 instead copies receiver +0x1CC.

An independent read-only audit found no direct E8/E9 or literal-VA references
to the wrapper and exactly one direct reference to 0x009EF750: the CALL at
0x009EC037. No native method or original class declaration is established.
The `AssetRegistry` spelling remains the existing repository ABI receiver
view from its canonical global and other matched wrappers. The method keeps
its full RVA. Hidden aggregate return versus explicit output parameter is
not independently known.

## Output and separately allocated header

The default path writes output +0 (header pointer) and +4, initializes the
separately allocated 0x14-byte tree header at its +0/+4/+8/+0x0C fields, then
writes DWORD zero to output +0x0C and byte one to output +0x10. There is no
output +8 write. The copy path passes its output address as the ECX receiver
of the native 199-byte STLport tree copy constructor at 0x009EE8E0, then
writes output +0x0C/+0x10. Its source argument is receiver +0x190.

These operands support the same native 12-byte tree plus trailing word and
byte ABI view as the adjacent wrapper, modeled with natural size 20. Native
receiver constructor 0x009F2140 repeats these groups at +0x190/+0x1A4/+0x1B8/
+0x1CC, independently corroborating 0x14-byte spacing. Unwritten padding,
original complete type, field names, lifetime and output allocation remain
unknown. Existing result-view names do not claim original field identities.

The old `copy@Rva009EF750` interface typed its output as the registry-sized
receiver, then cast it to a separate result and constructed its tree through
a guessed private STLport facade. The corrected typed value view uses the
real STLport header, the existing result type, the native CRITICAL_SECTION
and the native tree member at +0x190. The old cast/helper and artificial
volatile dummy are removed. The existing copy-result store-order barrier
is reused; no new ordering constraint or assembly is added.

## Actual operand bindings and verification

Wrapper operands:

- +0x03 DIR32: canonical global, native VA 0x0134FAAC.
- +0x1C REL32: existing native node allocator, native RVA 0x0082E540.
- +0x48 REL32: corrected result-producing method, native RVA 0x009EF750.

Callee operands:

- +0x2C DIR32: EnterCriticalSection IAT slot VA 0x01358D18.
- +0x46 REL32: native tree copy constructor, native RVA 0x009EE8E0.
- +0x58 DIR32: LeaveCriticalSection IAT slot VA 0x01358E74.

Both new bodies probe exact at 82/82 and 113/113. The two existing functions
in this source remain exact at 82/82 and 113/113; the actual emitted existing
tree copy remains 199/199. No global definition, pin, shared header, generator
source or baseline is edited. Only the wrapper's 82 bytes are new C++
recovery; the repaired 113-byte callee and existing tree copy add no credit.

## Exact source-comparison pairings

The naming guard compares the old standalone 0x009EF750 source with the
shared destination TU. Its token alignment pairs old `copy` with the
already-published `Rva009EF6D0` method and old output parameter `out` with
result type `Rva009EF6D0Output`. Those are not native identity or source
variable renames. The existing 0x009EF6D0 body remains byte exact and the
actual 0x009EF750 replacement is the separate `Rva009EF750` method, with its
own same-address ledger correction. The explicit output parameter is
removed by the typed aggregate return view, not renamed to a type. These
source-snapshot pairings have exact hash-bound corrections; no naming
baseline or tool rule is expanded.
