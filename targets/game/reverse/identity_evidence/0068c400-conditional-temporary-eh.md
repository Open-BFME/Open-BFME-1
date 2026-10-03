# LAN join-request handler: separate locals from unwind pointers

RVA `0x0068C400`, retail-1.03-unpacked, 2,248 bytes. The dispatcher passes
message type 3 through ILT `0x00006A87`; the body ends in RET8 at
`0x0068CCC5`, then INT3. Ghidra 12.1.2 through pyghidra-mcp and an independent
PE/Capstone decode agree on these bytes. This audit does not establish a new
source identity or an exact conversion.

## The local is already at the correct offset

The claim in b260b0f599d68088e1fb5e350eefaea2f658a534 that retail's
LANGameSlot local is at EBP-616 confuses an indirect construction pointer with
the object. FuncInfo VA `0x0123662C`, selected by EH handler `0x01046B7A`, has
12 unwind states:

| State | Funclet VA | Receiver instruction | Meaning |
| --- | --- | --- | --- |
| 0 | `0x01046AF0` | `8D 8D 90 FD FF FF`, LEA ECX,[EBP-0x270] | serial local, -624 |
| 3 | `0x01046B11` | `8D 8D B0 FD FF FF`, LEA ECX,[EBP-0x250] | LANGameSlot local, -592 |
| 5 | `0x01046B27` | `8B 8D 98 FD FF FF`, MOV ECX,[EBP-0x268] | saved outgoing construction pointer |
| 6 | `0x01046B32` | same MOV, then ADD ECX,0x44 | its partially constructed LANPlayer member |

State 3 jumps through VA `0x00429A69` to the LANGameSlot destructor at RVA
`0x006858A0`. State 5 protects its GameSlot base through VA `0x0040B988`;
state 6 protects its LANPlayer member through VA `0x004240FF`.

The normal path takes the local's address at stable-frame ESP+0x3C at VA
`0x00A8C972`. It allocates the outgoing 0x68-byte argument at `0x00A8CA1B`
and saves the construction receiver at `0x00A8CA31`. The bank's /FAsc listing
already places newSlot at -592. Moving that object by 24 bytes is unsupported.

## The entry zero is not serial construction

VA `0x00A8C41E` writes zero to [ESP+0x10] **before** the PUSH EDI at
`0x00A8C426`. Its stable-frame location is therefore ESP+0x14. The duplicate
name condition loads it at `0x00A8C792`, ORs bit 1 at `0x00A8C79A`, tests the
bit at `0x00A8C7B2`, and clears it at `0x00A8C7BD` before destroying the
conditionally constructed name at ESP+0x18. The player count later reuses
the bitmap slot at `0x00A8C847`.

Serial is separate: `0x00A8C5D0` initializes stable ESP+0x1C, and EH state 0
destroys EBP-0x270. The bank agrees on that local and initialization point.
Its bitmap instead occupies ESP+0x2C. The remaining mismatch concerns the
conditional temporary's EH state and register/slot allocation, not an early
serial lifetime. Retail keeps unwind state 0 during the name comparison;
the bank introduces an additional state.

## An explicit empty destructor creates the extra store

The bank's handler offset +0x6D6 is a relocated vptr store, not a reset
temporary. /FAsc identifies `C7 44 24 3C 00 00 00 00` as a store of
`??_7LANGameSlot@@6B@` to newSlot. Relocation masking makes it look like zero.
Retail finishes its empty-response copy at VA `0x00A8CAB2` and immediately
computes the serial member's destruction receiver at `0x00A8CAB6`; it has no
derived-vptr reinstall.

The bank defines `~LANGameSlot() {}`. The vendored GeneralsMD LANGameInfo.h
declares no derived destructor. Removing only that explicit destructor,
retaining the polymorphic class and implicit member/base cleanup, removes
exactly eight bytes and one relocation: 2,288/67 -> 2,280/66. Normalized
structural differences decrease from eight to seven. It remains non-exact;
its raw byte score is lower because the remaining differences shift position.
The better-scoring preferred bank is deliberately preserved, with this
alternative retained in attempt history.

## Native layout and ownership are not the remaining blocker

Constructors/copy bodies at RVAs `0x0068E890`, `0x00686D50`, and `0x006869C0`
prove GameSlot size 0x44, LANPlayer size 0x1C, and LANGameSlot size 0x68,
with serial at +0x60 and lastHeard at +0x64. Vtable VA `0x0111B6A0` has three
entries, none a destructor. Do not remove polymorphism to suppress the store.
LANGameInfo::setSlot at RVA `0x0068EA70` destroys the by-value argument via
VA `0x00429A69` and ends at VA `0x00A8EAE4` with RET0x6C (slot plus object).
The bank's caller-construction/callee-destruction contract is correct.

## Bounded visibility experiments, 2026-10-03

The starting bank needs its four StringBase specializations placed before
ascii_string.h/unicode_string.h to avoid C2908. This inclusion-order repair
reproduces the established 2,288-byte, 1,091-difference, eight-structural-diff
baseline. No shared header was changed.

Saving a new alternative exposed a tooling blocker: the retained, uncorrected
bank fails with C2908, and the measurement classifier treated that known source
error as unavailable infrastructure. [Microsoft documents C2908 as specialization
after instantiation](https://learn.microsoft.com/en-us/cpp/error-messages/compiler-errors-2/compiler-error-c2908).
The narrow classifier correction measures that source failure as zero; mixed
compiler/runtime failures still remain unavailable and cannot replace evidence.
Regression tests cover both cases. The supported banking tool first archives
the original bytes and installs the header-order-only repair at tool-measured
score 0.5074, then retains the implicit-destructor alternative at 0.5013.
There is no function-ledger body row at this RVA, only its ILT. The bank scorer
therefore invokes probe without an extent and compares each candidate's own
length, including trailing retail padding. These scores are ranking receipts,
not proof of the 2,248-byte boundary. All counts in the experiment discussion
above and below explicitly pass `--size 2248`. The preferred compiled
instruction stream remains unchanged.

* A visible noinline StringBase<unsigned short>::compare(const ushort*) and
  its length-aware forwarding body reproduce the matched 81-byte callee
  modulo relocations, but leave the handler unchanged. The opaque wide-length
  helper still prevents a complete nonthrowing proof.
* Exposing the load/arithmetic-only wide-length helper as well removes that
  opacity. Combined with implicit LANGameSlot destruction, the handler emits
  2,244 bytes but has 1,585 differing bytes and 37 structural differences.
  An actual-compare `__declspec(nothrow)` declaration produces the same result.
  This is a diagnostic contract, not a proposed new pin or callee owner.
* A scratch inherited UnicodeString control, including its direct native
  pointer-compare overload, is byte-identical to the corresponding wrapper
  forms. It does not justify a shared-header change.
* Const pointer/reference sender controls leave that 2,244-byte result
  unchanged. Exposing getName also leaves it unchanged. Exposing the real
  isHuman leaf (alone or with isOpen/isOccupied) emits 2,229 bytes with 39
  structural differences and is worse.

No generated body, production C++, function row, callee pin, or shared header
was changed. The remaining problem is conditional-temporary EH plus global
register allocation; the disproved 24-byte local relocation and serial-scope
stories should not be repeated.
