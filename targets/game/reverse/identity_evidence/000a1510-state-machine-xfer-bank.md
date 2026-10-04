# StateMachine serialization: instruction-exact bank, ABI integration open

2026-10-04, base `73556d221323d95e61d7932aa5d1147124b56444`.
Native extent RVA `000A1510..000A178F`, 640 bytes, final `RET 4` at
`000A178D`; following bytes are padding. This is **not a landed conversion**.
The generated ledger row remains unchanged. No new pin, provider alias, header,
production source, vtable or verification-baseline change is part of this bank.

## Result

The bank compiles with original MSVC 7.1 to all 640 bytes and 19 relocation
sites in exactly the original positions. `tools/probe.py` reports EXACT modulo
relocations. Independent validation binds each of those 19 sites to its decoded
original destination and compares the complete resulting 640 bytes. It also
compares the compiler's natural four-record XferException graph against retail.
These are instruction/contract audits, not the production link/gate result:
two deliberately unpinned prototype declarations cannot yet resolve to honest
selected providers. The bank tool measures score1.0 from instruction bytes; that is not a matched
claim and does not resolve the two deliberately unpinned helper declarations.

Previous reconstructions remained 620/640 or 623/640 with hundreds of byte
differences. The successful source uses native STLport map iteration, the
canonical Xfer/Object/Coord3DBase/GameLogic lookup headers, returned-Xfer chains,
and the actual eight-byte **class** XferException with its variadic constructor.
No assembly, padding object, volatile/barrier trick, flag sweep, raw throw bridge
or invented provider pin was used.

The first new probe already had all 640 bytes and the correct 0x20 stack frame,
with only nine differences swapping the Version and final owner-ID homes.
Constructing a two-byte Xfer::Version-derived value with an inline `(1,2)`
constructor, rather than writing its two bytes at the call site, fixes all nine.
The function-scope owner-ID and block/loop ID scopes preserve the native throw
temporary homes. The Version wrapper does not add storage.

## Identity and layout

Base vtable VA `01080710` slot +0C resolves to this body. Independently
identified AttackContester vtable VA `01097310` slot +0C resolves to
`0016AC10`, which calls this body with unchanged `this` and one Xfer pointer,
then transfers Version `(1,1)`. Base constructor `000A1BD0` installs the native
base table. Its object is 0x44 bytes with one vptr.

The layout read here is: map +04 (12 bytes), owner +10, sleep-until +14,
default state ID +18, current State +1C, goal ObjectID +20, coordinates +24,
second ID-like value +30, second coordinates +34, flags +40/+41/+42.
State's ID read is +04. Constructor/state-transition/caller evidence establishes
these fields; the extra bundle and flag42 intentionally keep neutral names.

The historical `Gen000A1510::handle(FlagPairTarget*)` binding is retained in
the bank. Its old callers do not establish semantic identity, and no new
StateMachine alias is added. This local layout emits no vtable and is not a
substitute for the still-open coherent native StateMachine declaration.

GeneralsMD StateMachine::xfer supplies the core state-iteration algorithm but
not BFME's second bundle, flag42, owner transfer, light-CRC guard or Version
interface. Earlier log statements that this address is unrelated to StateMachine
are contradicted by the native vtable/caller/constructor chain.

## Exact call/relocation contract

Offsets below refer to operands in the 640-byte body (not instruction starts).
All calls use the original ILT/body destination; all DIR32 addresses are verified.

| Operand offsets | Kind | Native destination / contract |
|---|---|---|
| 091,189 | REL32 | ILT RVA000124D1 →000A1310; ECX machine, stack unsigned StateID, EAX State pointer, RET4 |
| 0C7,149 | REL32 | RVA0082B870; STLport `_Rb_global<bool>::_M_increment(node*)`, cdecl |
| 0F5,165,19D | REL32 | RVA009D6220; XferException variadic cdecl constructor `(this,5,NULL)` |
| 0FD,16D,1A5 | DIR32 | ThrowInfo VA011DFE5C |
| 107,177,1AF | REL32 | RVA009F6D00; native `_CxxThrowException`, never returns |
| 1C4,1DC,232,26F | REL32 | ILT RVA0000C9B4 →0010C3C0; cdecl `(Xfer*,ObjectID*)`, returns transferred Xfer in EAX |
| 238 | DIR32 | TheGameLogic VA012F0898 |
| 249 | REL32 | ILT RVA0001F253 →0009A510; canonical GameLogic::findObjectByID(int), RET4 |

Virtual calls are canonical Xfer slots: +10 light CRC, +28 Version, +74
unsigned, +04 loading predicate, +8C Bool, +78 int, +30 Snapshot and +60
Coord3DBase. Returned receiver chains after +28/+74 and ObjectID/+60/+8C are
observable in the original and reproduced by ordinary `operator==` chaining.

## XferException graph

All three native throw sites VA004A1616/004A1686/004A16BE use the same graph:

- ThrowInfo VA011DFE5C: attributes0; unwind ILT00440804→destructor00065C70;
  forward compatibility0; catchable array VA011DFE54.
- Array VA011DFE54: one catchable type, VA011DFE34.
- Catchable type VA011DFE34: properties0; descriptor VA012A704C; PMD
  `(0,-1,0)`; size8; copy ILT0044A26E→constructor00065C50.
- Descriptor VA012A704C: type_info vtable VA01145868, spare0,
  literal `.?AVXferException@@` (class, not struct).

The bank's naturally emitted 16/8/28/28-byte graph records equal all original
bytes after each independently checked pointer binding. Copy/dtor are external
canonical declarations, not manually synthesized exception machinery. The real
constructor writes text=null and tag=5 here; its optional format branch is not
used. The existing constructor/copy/dtor pins agree with the native routes.

## Why promotion is blocked

### ObjectID transfer provider needs a coordinated return-contract correction

Selected `0010C3C0/25` is currently
`void Rva0010C3C0(MidVirtualSlot90Receiver*,void*)` in
`Common/MidVirtualSlot90Forwarders.cpp`. Native code forwards literal
`"ObjectID"` at VA0108920C, data and width4 to virtual +90, then preserves EAX.
Native Xfer constructor `007E7660/9` installs VA01129258; +90 points directly
to `009D67B0`. That implementation restores `EAX=this` on every successful
size arm. The serializer consumes that return at two sites. The void provider
contract is incomplete and a new alias would conceal the mismatch.

There are 43 C++ TUs mentioning Rva0010C3C0 (140 textual occurrences), including
the provider. Additional established ILT spellings include void
`friend_xferObjectID`, `bfmeCalcTGC`, `bfmeHandOver_0000C9B4`, `bfmeThreeCGF`,
`bfmeXferObjectID`, and `xferObjectID0010C3C0`. Those must be inventoried when
choosing a single coherent repair; a naive declaration-only change to the bank
is insufficient. Other 59 forwarder definitions need not be renamed.

The canonical Xfer header currently calls +90 ReservedVirtual4 and +94 XferEnum;
independent retail evidence shows enum transfer at +90 and raw transfer at +94.
The bank does not modify this shared-header discrepancy; it uses the direct
ObjectID helper contract instead of dispatching either slot itself.

### State lookup provider masks a scalar ID and a native ErrorCode throw

Selected `000A1310/63`, BfmeConv2128.cpp, currently declares
`void *BfmeHostABB::bfmeFrontABB(BfmeIterABB)`. Its supposed iterator argument
is actually the scalar unsigned StateID. It takes that incoming argument's
address and calls ILT0004833D→000A0E20 with ECX=map at machine+04, an output
iterator pointer, and a key reference; the real helper returns with RET8.
Node+10 comparisons use JB/JAE (unsigned), and output is one node pointer.
After checking that result against the sentinel, lookup returns node+14 in EAX
and RET4. Native map and scalar-ID declarations must replace the misleading
aggregate contract before a canonical caller is promoted.

On absence, lookup throws ErrorCode(0xDEAD0003), not a returning diagnostic.
ThrowInfoVA011E0004 → array011DFFFC → type011DFFDC (properties1, size4,
no copy/dtor) → descriptor012A716C `.?AW4ErrorCode@@`. The old bfmeDiagABB
pin points directly to `_CxxThrowException`. No raw throw bridge or
BfmeIter-by-value cast is adopted by this bank.

## Reproduction and limits

Run probe on `targets/game/reverse/attempts/0x000a1510.cpp` using symbol
`?handle@Gen000A1510@@QAEXPAVFlagPairTarget@@@Z`, RVA0x000A1510, size640.
The bank's include flags are repository-relative and use canonical headers.
The two unpinned helper declarations are clearly labelled research contracts.
Do not add pins to them as a shortcut.

Actual read-only Ghidra MCP batches performed 29 calls, including 14 read_bytes
blocks all byte-equal to the original PE SHA256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Ghidra could not decompile copy/dtor entries00065C50/00065C70; those failures
were preserved and their native instruction bytes/ILT routes were checked.
Ghidra's guessed void return on0010C3C0 is superseded by the original consuming
caller and decoded slot+90 implementation, not taken as signature proof.

No add_match invocation, production whole-source gate, caller gate, header gate,
link closure or native vtable integration is claimed. Finish the two provider
contracts and coordinate class/map ownership before promotion.
