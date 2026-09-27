# 008BF100 typed relocation review

2026-09-27, GPT-6. Read-only dependency review and two scoped storage probes;
no conversion or new pin.

The preferred bank is native C++, with no asm, emit, naked function, or MMX
intrinsics. It reconstructs 178 string assignments, reference-count releases,
and hash-array allocation/zeroing. The transferred continuation index records
45 additional exhausted source variants, including a visible complete setter;
that history must be read alongside re_attempts.log before another attempt.

A fresh probe reproduces 18655 bytes, 1080 relocations, and the 15-byte residue
at the first destructor cleanup. The one shifted DIR32 store operand is at
compiled `9C`, retail `9B`; both instruction streams rejoin at `AE`. Moving the
four-byte string handles into a correctly typed `BfmeStrVKI[178]` declaration
instead of casting an eight-byte `BfmeStringData[178]` leaves the same 15-byte
residue. Giving the pool callback a StringData pointer rather than void pointer
also produces the same instructions. Neither is an allocation lever.

For independent audit only, mapping that one shifted operand explicitly gives:
178/178 REL32 calls to the existing 125-byte setter at `0089E680`; 178/178
compiled string contents, including terminators, equal the referenced retail
literals; and all non-string DIR32 operands select consistent bases:

| Storage | VA |
| --- | --- |
| 178 four-byte string handles | `01338480` |
| Eight-byte shared empty string header | `012D5298` |
| Pool callback-table pointer | `01337A30` |
| Allocation callback cell | `01337828` |
| Hash-array pointer | `01338470` |
| Hash count | `01338474` |

The remaining DIR32s are the expected FS exception-chain relocation (zero)
and the main EH handler. This audit is not an exact gate: its explicit operand
alignment adjustment is unacceptable for claiming a match.

The complete setter at `0089E680` confirms the eight-byte header and word
refcount, size, capacity, and fourth word. It returns with `ret 4`. The complete
22-byte release body at `00891B80` decrements the word refcount and invokes
pool+4 with caller cleanup. The initializer at `00894800` writes the allocation
callback-table address `01337828` to the pool pointer `01337A30`. This proves
the allocator cell is an ordinary callback, not an IAT import.

No new source shape explains the delayed EDI save at retail `AD` while keeping
the 178 EH lifetimes. The preferred bank is unchanged. Correcting the array's
storage type belongs in a future exact landing, with the same independent
DIR32 review repeated without an offset adjustment.
