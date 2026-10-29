# Refresh 0x009EFF50: count-tail bank improved from 14 to 12 differences

The interrupted two-agent queue run improved the preferred candidate; this is
banked work, not a recovered game body. No functions.csv or game source changed.

## Target evidence and verification

BFME 1 starting revision: fbfea42889. Identity and layout evidence remain in
`targets/game/reverse/identity_evidence/009eff50-refresh-reverify-20261013.md`
and the prior handoff `20261025-refresh-reference-order.md`. Five matched callers
establish the existing Q1Receiver0134FAAC::refresh identity. Retail RET +0xC71
and INT3 +0xC72 establish 3186 bytes (the queue brief's 3177 was incorrect).

Revalidated on 2026-10-29 with:

```sh
python3 tools/probe.py targets/game/reverse/attempts/0x009eff50.cpp '?refresh@Q1Receiver0134FAAC@@QAEXXZ' 0x009EFF50 --size 3186 --shape
```

Result: 3186/3186 bytes, 39 relocations, 12 differing non-relocation bytes,
normalized shape 1.000. Score is 1 - 12/3186 = 0.9962335. This is a masked
compiler comparison; it does not prove relocation targets or linking.
First difference is +0xB2A in the load at +0xB28: retail reads +0xB0,
candidate +0x88. At +0xB30 retail subtracts +0xB4, candidate +0x8C;
+0xB36 and +0xB41 exchange the complementary loads. The second arm retains
another deque-size operand permutation starting at +0xB9B. The common node-term
hoist remains intact. The only body change from the previous preferred bank is
pass 1's sum order: queues[1] + queues[0] + queues[2] - m_field1e0.

## Donor evidence and unsuccessful trials

The interrupted agent reviewed the BFME 2 AssetManagerImplRefresh.cpp mechanism:
local r1-before-r0 declaration order and per-arm addressing. Checkouts available
to the run were sibling ../Open-BFME-2 at
637ab50faba045d2507eb3c3744fd136dff2f8c0 and pinned reference at
beed8a16790a6812231ac7b05e3e6893e4cb5d1b. Prior donor provenance and compile-context
limitations remain in the 20261025 handoff. This continuation did not advance
either donor checkout or the pre-existing dirty submodule pointer.

The reported direct adaptation emitted 3169 bytes with 296 differing bytes;
it is not a BFME 1 solution. The agent also ruled out deque-1-first and
reparenthesized pass-0 sums (lose hoisted node terms, 3232 bytes or more),
braced/temporary/assignment-chain forms, branch-polarity swap, all r0/r1/r2
declaration orders and late declarations. These are recovered agent findings;
the continuation independently recompiled the retained 12-difference bank only.
Compiler flags and includes are preserved in that bank: MSVC 7.1, STLport,
/DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
/D_STLP_NO_EXCEPTIONS with normal probe defaults.

## Remaining prerequisite

Find an evidence-backed upstream compiler-context change that alters the two
count-tail load orders without breaking the shared node-term hoist. Native
container specialization and relocation/provider concerns documented in the
previous handoff also remain. No mismatching reconstruction was retained in
game/. The BroadcastStealthUpdate task made no improvement and is not included
in this commit.
