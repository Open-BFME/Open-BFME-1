# MemoryPoolObject deleting-destructor claim binds a vtable to zero

Severity: **WRONG**, pending retirement/rehome with ledger integration.
RVA `0x00712E80`, 11B, row `??_GMemoryPoolObject@@MAEPAXI@Z`, source
`game/GameEngine/Source/GameClient/MessageStream/MetaEvent.cpp`.

`docs/matching.md` requires checking what DIR32 references point at;
`tools/null_reloc.py` explains that a linked absolute address is never zero.
A matching instruction stream cannot establish this vtable initialization.

The fresh, input-witnessed COFF has a DIR32 at body+4 naming the defined
`??_7MemoryPoolObject@@6B@` in .rdata. The independently read retail body is:

```
8B C1             mov eax,ecx
C7 00 00000000    mov dword ptr [eax],0
C2 0400          ret 4
```

Ghidra MCP VA `0x00B12E80` agrees with the unpacked PE on all16bytes,
including five following INT3 bytes at RVA712E8B. RET4 begins at712E88;
the claimed11B boundary is intact. `callees.py` finds no direct calls.
Canonical `null_reloc.scan([row])` independently returns precisely this
finding with zero unreadable rows. It is not a TIB __except_list relocation:
the source target is an actual local vtable, while retail stores integer0.

The shared sweep header Common/GameMemory.h declares a virtual
MemoryPoolObject destructor and produces this vtable-bearing emission.
That C++ body cannot be represented by retail's literal-zero initialization,
regardless of the passing branch-local relocation-aware function gate.
No alternate semantic identity or correct destination is inferred here.

Both current origin/master and this worktree also carry an11B copy-constructor
claim `??0MemoryPoolObject@@QAE@ABV0@@Z` at the same address from
ThingTemplate.cpp, with obsolete ICF wording. This note does not assert that
second object's current bytes have been verified: its source was outside the
fresh corpus. The independently contradicted deleting-destructor claim is
sufficient for this finding; the competing name is not automatic proof of
the right identity. The retail no-ICF rule also prohibits keeping two real
identities at this one body after adjudication.

Origin/master still contains both rows and identical MetaEvent.cpp source.
The bounded12-second pickaxe is not treated as introduction-date proof;
both names survive in the August1 cohort. The fresh source audit passes
7/7 branch-local function/reference comparisons. Normal null-relocation
verification belongs to the whole gate and needs readable objects for the
whole ledger; do not shrink its53-row/19-body baseline using this sample.

Retire/rehome the contradicted claim through the normal ledger and identity
workflow once the inherited alias dependency is integrated. Do not invent a
fallback, pin this vtable to zero, rename either old claim merely from the
other label, or change a shared class to make the false claim pass.
No production, pin, ledger or baseline change is made here.
Evidence: `build/audit_v3/s6_pool_zero_proof.json`, current compile proof and
source verification in `s6_medium_t/compile_inputs.json` and `07.log`.
