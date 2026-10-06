# 0093DD20: byte-storage copy provider

The complete retail body is 25 bytes at RVA 0093DD20. It is a cdecl routine
with destination and source pointers on the stack and a plain `ret`. It tests
the destination before loading the source pointer. For a non-null destination,
it copies a word from offset 0, then a DWORD from offset 4. Bytes 2 and 3 are
untouched. The following bytes are padding, outside this existing 25-byte
ledger extent.

This proves the storage operation and its ABI, not an original STL mapped type
or a constructor's declaring identity. The address-qualified
`Rva0093DD20Copy` therefore accepts unsigned-character storage views. Its two
local unsigned temporaries and constant-size `memcpy` operations impose no
alignment requirement on the supplied storage and preserve the observed
read/write ordering even when the ranges overlap. A null destination performs
no source access. For other calls, both pointers must designate at least eight
bytes of storage, with the destination writable. No typed-object lifetime is
claimed to begin here.

## Existing owner and caller boundaries

The old row `Gen_treeraw_0093dd20` uses an emitted
`_STL::_Construct<pair<const unsigned short, int>, ...>` object symbol from
`game/gen_small/fam_006.cpp`. Its complete 25-byte body already matches retail.
The generated source and all its emitted definitions remain unchanged; only
this row moves to the explicit storage contract. This is a physical-provider
and identity correction, not newly recovered machine-code-to-C++ bytes.

The existing integer-pair constructor spelling resolves through the ILT at
0002BCE2, whose five bytes jump to 0037B0B0. Its physical copy in the generated
object does not establish that the same original specialization also owns
0093DD20. No second-address pin or symbol alias is added.

Three observed direct calls reach this body: 0093E9A3 in the 33-byte node
creation body at 0093E990, and 0093FDBA/0093FDE1 in the 178-byte insertion body
at 0093FD80. Each call supplies a fresh 24-byte allocation's value storage at
node+16 and a source-value pointer. Their source declarations, existing pins,
and generated physical definitions are preserved. No caller binding or linked
byte gain is claimed by this change.

The existing 0093FD80 source models its value as a const-key pair with a
six-byte opaque field. Replacing its nominal construction call with byte
transfer would require a separate lifetime/representation repair; this change
does not make that substitution. The 601-byte insertion family's downstream
binding debt is likewise outside this unit.

## Verification

The original MSVC 7.1 compiler emits one function of exactly 25 bytes, with no
relocations, helpers, EH data, or vtables. All 25 bytes equal retail without
masking. Before the row replacement, the unchanged generated donor passes all
12 ledger rows. Final checks cover the new provider and every remaining donor
row, preserve the donor source/object contents, and confirm one ledger owner
for this address. No baseline, compiler, hook, or verifier change is needed.
