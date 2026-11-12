# FESL accept: two native field-writer bindings

Only `game/GameEngine/Source/GameNetwork/Rva007F9FD0Accept.cpp` changes. Its
existing `Rva007FA2C0::onAccept(void*)` identity at `007F9FD0` retains the complete
401 B extent, signature, message storage, constructor/destructor, allocation,
base64 encoding, chunk bounds, callbacks and return value. This is caller-edge
repair, not a newly recovered body or a new EA class/member identity.

| Old undefined member | Existing compiled provider | Original physical route | Full extent |
| --- | --- | --- | --- |
| `Rva007E8810Message::addInt(const char*,int)` | `BfmeThingCIB::bfmeGoCIB(void*,void*)` | direct `007E88D0` | 44 B |
| `Rva007E8810Message::addString(const char*,const char*)` | `BfmeC994::addString(const char*,const char*)` | direct `007E8A10` | 44 B |

There is no ILT substitution: both calls already reached these actual complete
retail bodies directly. Existing provider units are `Common/BfmeConv606.cpp`
and `Common/BfmeConv607.cpp`. The string member's prior independent naming/
receiver evidence is `007e8a10-BfmeC994-addString.md`: actual buffer/capacity
fields at +10/+14, error word +24, matching constructor and witnessed FESL
NAME/P/UGID callers distinguish it from an equal tiny accessor.

## Pointer-only views and integer word

The consumer's old method declarations are removed and declaration-only views
of those existing public providers are called on the same `&message`. No layout,
size, inheritance, helper, wrapper, pin/alias, access bridge, macro or header/
provider edit is introduced. Existing message data members are untouched.

The integer provider's source currently spells its two arguments as void*.
That is not a reason to infer pointer semantics: the complete native 44 B body
loads both original stack dwords, forwards them unchanged to the independently
matched `Rva007EC5C0(char*,int,const char*,int)` at `007EC5C0`, and never
dereferences either argument. The lower writer's source in
`Libraries/Source/DirtySock/Y2Rva007EBAE0Module.cpp` formats that last integer in
signed decimal; its const name argument is read, not modified. Under the pinned
32-bit MSVC target, `reinterpret_cast<void*>(encodedLength)` preserves exactly
the former `(int)encodedLength` dword, including high-bit patterns. The `size`
key's const_cast changes no bits and authorizes no runtime write: both native
provider and lower writer only read that key. No 64-bit portability or general
pointer/integer identity claim is made.

The string provider independently forwards the two const string pointers to
actual `Rva007ECE60(char*,int,const char*,const char*)` at `007ECE60`. Both
44 B providers read buffer/capacity from receiver+10/+14, test the lower result,
write -100 at +24 on failure and finish with RET8. They consume exactly the
two original argument words, with no value conversion or hidden return object.
The lower writer extents are 355/629 B, comprising 330/604 instruction bytes
plus 25 B of embedded RTC frame/item metadata each, not all instructions. The
independent review checked those descriptor pointers, stack offsets and item
strings separately; no code-only decode of the whole extent is claimed.

## Complete native and object proof

`callees.py 0x007F9FD0 401` was read before editing. Additional strict diagnostics
compare the complete consumer and both complete 44 B providers with zero
masking and unresolved references. At direct REL32 operands +128/+137 hex,
the original stack-message receiver remains `lea ecx,[esp+24h]`. The integer
call pushes EDI (the original encoded-length word), then the original `size`
literal; the string call pushes EBP (the original part pointer), then the
original `data` literal. Both native routes and both provider lower calls are
unchanged. Normal complete consumer string-reference verification preserves
both literal identities, not just their bytes.

All six before/current COFF sections, every raw byte/relocation/characteristic
and every complete section auxiliary record (selection/checksum/association
included) match by exact definition/owner after ONLY these two external name
substitutions. All three external definitions—the same consumer and two
literals—remain unchanged, with exactly two undefined substitutions and no
weak external, alias/helper, extra code/data or lifetime/cleanup metadata.
Normalized all-section inventory SHA256:
`6880ecf84c86e430722ee05724d17413f6c0d80cf4890a6b33ee8d299f9177a8`.
This preserves object metadata/eligibility, not proof of an actual current-link
winner or whole-image layout under UNKNOWN.

## Reference and earlier attempts

Read-only donor revision `76f0baefa6f285d54bc1ca922397674312a5913f`,
`Code/GameEngine/Source/GameNetwork/V2FeslTxnRequests.cpp` and related narrow
FESL addInt/addString searches, retains a synthetic message API with these same
field-writing roles. Its comments contain BFME 1 addresses and explicitly
unproven message/parameter identities; these are leads, not independent BFME 1
proof. No donor layout, name, ABI, address, header or code is transferred. The
actual BFME 1 full bodies, lower writer contracts, existing string-member
identity evidence and this exact consumer establish the binding.

The two early anonymous `007F9FD0` blocked entries were reviewed; they predate
its existing matched `onAccept` reconstruction and are not repeated anonymous
identity attempts. No source-specific older donor history is asserted beyond
the available pinned shallow snapshot. Donor tree/gitlink remain untouched.

## Verification and accounting

Normal before/after unified gate: **3/3 functions across three consumer/provider
TUs**, two literals, zero skipped/unverified refs or baselined body findings.
`find_declared_unmatched.py` reports all definitions already matched. Actual
builds retain the original `/O2 /GX-` consumer context and approved private
WoW64 prefix, WINEARCH=win64, BUILD_POOL=2, WINEDEBUG=-all and empty desktop
displays; no compiler setting or shared build input changes.

Before scoped preview: **0/3 clean**, 193.8 s, 2 UNKNOWN / 1 independent-debt
verdict. After: **0/3 clean**, 188.6 s, all 3 UNKNOWN. All three selection sets
remain stale. Cold/changed unreadable object counts are 22,747 before and 22,738
after; this cache-state change is NOT evidence of a linked-byte gain. Historical
LINKED **88 -> 88** remains unchanged, not current confirmed coverage. Exactly
two old unresolved diagnostics disappear; every other selected diagnostic is
unchanged and none is added. No new matched bytes, confirmed current linked-byte
gain or closure is inferred. Existing constructor/message ownership and other
independent debts are not repaired or hidden by these two edges.

Private proof under `build/sol12h-bindings/`:
`fesl-accept-{before-build,after-build,link-before,link-after,routes,footprint}.log`,
`fesl-accept-{before.cpp,before.obj,callees.txt,native.txt,donor-context.txt,sources.txt}`,
`fesl-accept-footprint.json`, `check_fesl_accept_routes.py`,
`check_fesl_accept_footprint.py` and exact claim log.
