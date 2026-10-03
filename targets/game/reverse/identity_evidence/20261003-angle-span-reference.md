# Angle-span initializer: six relocatable readonly references

The existing address-qualified initializer at RVA `0x008AC790` is 581 bytes,
ending at RET `0x008AC9D4` then INT3. Its six FSUB/FADD operands reference
VA `0x01136850`, which contains `DB 0F 49 40`. This was independently read
from Ghidra and the unpacked retail image during the earlier audit
(`e7177fd033`). The preexisting DIR32 anchor `Rva008AC750Span` independently
names the same address. No semantic identity is inferred from that name.

The earlier named-extern and volatile trials changed x87 scheduling. A
TU-local const float array containing `3.1415927f` instead preserves all 581
bytes and gives each of the six operands a genuine DIR32 relocation to
`_BfmeAngleSpan`. It retains the existing source identifier. The one-element
array is a reconstruction representation for the witnessed scalar storage,
not evidence that EA declared an array.

Independent object inspection follows all six relocations, including their
symbol offsets and addends, to the four-byte readonly `.rdata` datum and
compares `db0f4940` with each actual retail target. The corresponding operands
are at RVAs `008AC800`, `008AC81F`, `008AC857`, `008AC876`, `008AC8A0`, and
`008AC8B3`. All six match. The section is not writable.

The normal scoped gate also passes the complete function, 25 pooled float
references, and 22 external DIR32 references. Its external-reference count
excludes the six new local-array references, which is why the independent
window proof is required. No header, ledger row, pin, function identity,
extent, or coverage changes. No assembly or volatile access is introduced.
