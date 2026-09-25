# Distinct owning-string record operations

The complete41-byte functions at0075E980 and00764790 copy DWORDs0,4,8 from
the incoming record, then operate on a four-byte owning string at+0x0C.
Both return their receiver and pop4 bytes. The direct call at+0x1E reaches
00887C90 in the first body and00887B60 in the second, independently decoded
from retail and confirmed by callees.py. The former is StringBase<char>::set,
which handles an already live destination; the latter is the copy constructor,
which initializes a new destination. Existing verified canonical StringBase
bodies and AsciiString forwarding declarations establish these contracts.

The reference MixFileCreator::FileInfoStruct assignment declared StringClass
for both and therefore emitted the wrong call target. Separate address-derived
record types preserve the unknown game identities and distinguish assignment
from construction. DWORD field names retain offsets; no extra layout or member
semantics are inferred. Original dup ledger tokens and41-byte extents remain.
No pins are needed. These repair existing failed claims, not new coverage.
