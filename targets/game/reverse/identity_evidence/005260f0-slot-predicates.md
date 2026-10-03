# 0x005260F0: correct the bank's predicates before tuning registers

The retail body spans 583 bytes: RVA 0x005260F0 through RET at
0x00526336 (+0x246), followed by INT3 at +0x247. Ghidra's decompilation
at VA 0x009260F0 and independent Capstone decoding of the unpacked retail
image agree on the branches below.

The existing matched caller `SkirmishScreenState::flushPendingUpdates`
(0x0052AD00, `SkirmishScreenStateFlushPendingUpdates.cpp`) calls
`bfmeFlush15` when its +0x15 pending flag is set. Its existing pin is ILT
0x00013025, targeting this body. This preserves the caller's established
opaque method spelling; it does not infer an EA descriptive method name.
The owner/field views follow the already matched SkirmishScreenState siblings.
GameSlot +0x14 is witnessed as m_playerTemplate by name_oracle; MapMetaData
+0x20 follows the existing map metadata view and GeneralsMD member layout.

## Corrected behavior

The old bank's initial predicate used a conjunction of negated isAI/isOpen
checks. Retail counts a non-null slot when isAI OR isOpen OR
(isHuman AND playerTemplate != -2): JNE at 0x00526178 and 0x00526183
both reach the count increment at 0x00526196. The first two descending
passes test isOpen and isAI respectively, not isOpen twice. The third
requires playerTemplate != -2 (JE at 0x0052624B skips the mutation).
Every descending pass terminates at a negative index (JNS back edges at
0x005261DE, 0x0052620E, 0x00526259).

Spelling the index bound first in each loop condition reproduces the
retail bottom index check and top player-count check. The two increasing
passes likewise test index < 8 first. Combined with the actual predicates,
this changes the bank from 586 bytes / 364 positional differences to all
583 bytes, including the retail receiver/zero registers and loop padding.
No register forcing, flags change, volatility, or assembly is required.

## Callee bindings

All direct dependencies already have matched rows. No new pins are added.

| ILT RVA | Body RVA | Existing declaration |
| --- | --- | --- |
| 0002F28E | 00098E70 | GameInfo::getMap, by-value AsciiString |
| 00019880 | 00454500 | MapCache::findMap, by-value AsciiString |
| 0001EC18 | 0061E8B0 | GameInfo::getSlot(int) |
| 000422DF | 0061E5C0 | GameSlot::isAI() const |
| 00011C43 | 0061E630 | GameSlot::isOpen() const |
| 000279CB | 0061E580 | GameSlot::isHuman() const |
| 0003B61A | 00525080 | Rva00525080SkirmishScreenState::rva00525080(int,int) |
| 0002BEDB | 00523460 | Rva00523460Owner::rva00523460(int,int) |
| 000439C3 | 004B3C70 | GadgetComboBoxSetSelectedPos(GameWindow*,int,bool) |

The three slot predicates independently read m_state at +4: isAI recognizes
2/3/4, isOpen recognizes 0, and isHuman recognizes 5. Their existing native
GameInfo.cpp definitions establish their bool return contracts. The two
mutating helper calls use the existing address-derived owners, replacing the
bank's unsupported setSlotState linker alias. The inherited setSlotState
spelling remains only as an inline forwarding adapter, without a new pin. The virtual owner +0x24 test
retains the ABI/layout already used by matched SkirmishScreenState siblings;
no new virtual-slot identity is claimed. Canonical ascii_string.h is included.
