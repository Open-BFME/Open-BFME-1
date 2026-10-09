# 0x00077A90 reconstruction

The complete `Rva00077a90::grow(InputArg *)` candidate matches all 373 retail bytes outside its 18 relocation operands. It is a partial, not a landed recovery. The strict gate fails on eight unresolved STLport symbol names, whose eleven call sites cannot be bound while the STLport family is paused. The two inline assembly marker blocks remain from the earlier bank. No real owner name is established.

## Retry hypothesis and measurements

The earlier bank contained only two marker blocks and an unused argument load. The current ledger supplies `bfmeTreeYK`, `bfmeTreeYL`, `bfmeTreeYM`, `bfmeTreeYN`, the one-word copy at 0x00072510, unsigned tree insertion at 0x00076F80 and 0x00077040, and their node insertion helpers. These provide a new experiment: reconstruct the complete interior with native `set` and `map` operations, explicit pair locals, and unoptimized compilation. A result no closer than the saved bank, after counting every absent retail byte as wrong, would refute this lever.

| Source under `build/77a90-retry/` | Compiled bytes | Probe differences | Absent retail bytes | First difference | Raw probe |
|---|---:|---:|---:|---|---|
| `old-bank.cpp` | 57 | 56 | 316 | +0x0000 | `probe-00-bank.txt` |
| `trial-01-native.cpp` | 364 | 124 | 9 | +0x0045 | `probe-01-native.txt` |
| `trial-02-named-pairs.cpp` | 373 | 10 | 0 | +0x006F | `probe-02-named-pairs.txt` |
| `trial-03-lifetime.cpp` | 373 | 0 | 0 | None outside relocations | `probe-03-lifetime.txt` |
| `best-body.cpp` | 373 | 0 | 0 | None outside relocations | `probe-03-best-body.txt` |
| `trial-04-without-markers.cpp` | 319 | 233 | 54 | +0x0009 | `probe-04-without-markers.txt` |

Probe byte counts mask object relocation operands. Earlier trials with different instruction lengths also report relocation layout drift, so their counts are diagnostic. The final candidate has the same instruction lengths and relocation operand positions as retail. The saved bank's measured fraction, including its absent tail, is 1/373; its old 0.10 header was an author estimate.

The named pair locals recover three missing `lea` instructions. Hoisting the uninitialized `array` declaration to the outer scope and giving `firstPair` its own inner scope then reproduces all local offsets. Retail and candidate place `found`, `base`, `array`, `secondPair`, `recordPair`, and `firstPair` at -4, -8, -12, -20, -28, and -36 respectively. The remaining compiler temporaries and receiver spill also match. The register/frame hypothesis generator reported no applicable source lever; the scope experiment follows the measured compiler listing instead. No unchanged register experiment was repeated.

Removing both marker blocks produces the complete 319-byte C++ interior and the expected 54-byte loss. This rejects that clean candidate as an exact reconstruction under the tested flags. It does not prove that every possible source spelling fails, nor establish that inline instrumentation is acceptable for landing.

## Boundaries, identity and ABI

The retail extent is [0x00077A90, 0x00077C05). The conditional branch at +0x61 reaches the shared marker and epilogue at +0x154. There is one `ret 4`, no outgoing conditional branch or tail jump, and no EH registration or unwind map in this target. The receiver is spilled at -0x60 but never read. It remains a member only to preserve the bank's existing address-derived class and signature.

The complete 502-byte caller at 0x00078640 calls ILT 0x00043897 at caller +0x1D6. That thunk decodes to a jump to 0x00077A90. The caller passes the address of an eight-byte local record on the stack and a byte-sized stack receiver in ECX. The two record words are addresses 0x012A7248 and 0x012A7244. It consumes no target return value. The target's `ret 4` agrees with one pointer argument and callee cleanup. The caller is still a generated dump, so it supplies ABI evidence and no real owner identity.

The incoming request has a record pointer at +0 and an array output pointer at +4. The target reads the separate pointed-to record's dwords at +8, +0x10, +0x14, +0x1C, +0x28, and +0x2C, and writes a pointer at +0x24. In particular, +0x2C is an array index, not a destination pointer. The source declaration is a partial address-derived field view; it does not claim the complete record's size or semantic owner. The related body at 0x00077CE0 accesses +0x30, beyond this target's view.

All helper return paths and stack cleanup used in the reconstruction were decoded. The lookup wrappers take hidden iterator storage first and a key reference second, return that storage in EAX, and end with `ret 8`. The end helper at 0x00072510 copies one word into its output, returns its address, and ends with `ret 4`. The iterator comparison at 0x00061B60 compares one word and returns a Boolean in AL. Each insertion wrapper takes hidden eight-byte result storage first and a value reference second, returns the storage address, and ends with `ret 8`. The deeper insertions write a four-byte iterator at result +0 and a one-byte success flag at +4. Pair constructors return ECX through EAX and clean their one or two reference arguments. Array allocation takes one unsigned byte count through the cdecl stack and returns a pointer in EAX. There are no indirect or virtual calls in the target.

## Container evidence

The generated `hash_map::equal_range` labels at 0x000762B0, 0x000774F0, and 0x00077510 do not describe the actual operations reached here. Their decoded call chains reach 0x00072D70 (unsigned-key tree lookup), 0x00076F80 (unique tree insertion), and 0x00077040 (unique tree insertion). The candidate uses the corresponding native operations instead of borrowing those generated names.

The first insertion constructs two words from `base + 8` and `&base`. The complete 22-byte helper at 0x0006B520 reads the first referenced dword and the second referenced pointer value and writes them at +0 and +4. The complete 19-byte helper at 0x0006C5A0 copies precisely those two words into the const-key pair. The actual node constructor reached through 0x00076F80 -> ILT 0x0002E122 -> 0x000768D0 calls ILT 0x00004A61 -> 0x00072390. Its complete 23-byte body checks its destination, copies source +0 and source +4 to destination +0 and +4, and returns. Thus the node value includes a key word and the pointer to the record, with no additional payload fields copied.

The other insertions construct two words from `base + 0x10` or `base + 0x14` and `base + 8`. The complete 22-byte helper at 0x0006B500 reads one dword from each referenced field and writes pair +0 and +4. The complete 19-byte helper at 0x0006C5C0 copies both fields. The node path 0x00077040 -> ILT 0x00045223 -> 0x000769B0 calls ILT 0x0003853C -> 0x000723B0. The complete 23-byte value construction helper again copies only the two words, after the destination check. These are two-word values, independently of the 0x18 allocation size.

The membership singleton at 0x000779E0 is independently initialized as a tree with root/header links. Its scalar value is corroborated by the complete related caller at 0x00077C70, whose insertion chain is ILT 0x0001DB29 -> 0x00076E10 -> ILT 0x00012B9D -> 0x00076190 -> ILT 0x0002AD10 -> 0x00072C90. The full 179-byte node insertion body copies only one dword from the incoming value to node +0x10 on both allocation paths. Its unsigned comparisons and those in lookup establish the key's comparison representation. Whether these key words are actual pointers, integer identifiers, or another unsigned four-byte type remains unresolved. Existing donor names alone do not resolve that distinction. The bank uses an unsigned dword view and retains address-derived identities.

## Required bindings and remaining blockers

The strict gate's exact eight unresolved decorated names are retained verbatim in `build/77a90-retry/scoped-gate.txt`. They are `set<unsigned int>::find` at 0x000762B0, its `end` at 0x00072510, `map<unsigned int, Rva00077a90Record *>::insert` at 0x000774F0, `map<unsigned int, unsigned int>::insert` at 0x00077510, the corresponding two-word construction at 0x0006B520 and 0x0006B500, and the const-key conversion constructors at 0x0006C5A0 and 0x0006C5C0. The eleven unresolved relocation operands start at +0x3F, +0x4F, +0xC4, +0xD0, +0xE4, +0xFA, +0x106, +0x11A, +0x130, +0x13C, and +0x150. Existing singleton, iterator comparison, and array allocation bindings resolve. No symbol pin or ledger row was added.

Reopening is justified when the STLport header transition and family pause permit independently reviewed bindings, or when a producer establishes more precise key types. The exact candidate still requires a decision on the retail instrumentation; it cannot be called a clean C++ recovery with those assembly blocks unresolved by policy. No full gate was required for this bank-only change.

CSV and pin consistency pass. The class gate passes for the trial, and the name-regression source comparison reports no substitutions. `find_declared_unmatched.py --fail` rejects the scratch candidate because it has zero ledger rows; that expected refusal is retained, not bypassed. The strict scoped function gate fails 1/1 on the paused bindings. Complete raw instruction decoding and checked-callee output are retained in `build/77a90-retry/decoded-all.txt` and `checked-all.txt`. Every trial source and unedited probe log remains under that folder. The tested revision is `dbfea2ff0cfbd7707f89cdc5cea96c69a4446798`; the actual model is `gpt-6.1-sol`.
