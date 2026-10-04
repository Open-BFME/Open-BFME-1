# AI::findClosestRepulsor, RVA 0x0014B090

The complete 154-byte body ends with `ret 8` at RVA 0x0014B127 and INT3
padding at 0x0014B12A. Ghidra, decoded retail instructions and the unchanged
boundary check agree. The early return is at RVA 0x0014B0C2.

## Independent identity and ABI

- The byte-verified AIIdleState::update at RVA 0x00188090 (404 bytes) names
  AI::findClosestRepulsor in its REL32 at +0xD7. It reaches ILT 0x0002BDB4,
  then RVA 0x0014B090. Four other typed AI-state callers independently agree.
- The method reads AI data at this+0x14 and m_enableRepulsors at data+0x64.
  The latter field is witnessed by name_oracle; no name is invented for +0x14.
- Its constructor call reaches ILT 0x00046A97, then the matched 87-byte
  Rva001DCBB0Filter constructor at RVA 0x001DCBB0. Retail independently
  establishes its thiscall Object*/byte arguments, ret8, next+4, player+8,
  byte+0xC and vtable VA 0x0109685C. Its semantic identity remains opaque.
- The repulsor temporary installs vtable VA 0x01095704, with next+4 and self+8.
  The second vtable slot reaches the independently matched
  PartitionFilterRepulsor::allow at RVA 0x001DDB10 through ILT 0x0001CC6F.
  That method's first instruction reads self at this+8.
- The complete 46-byte PartitionFilter::link at RVA 0x009F2AE0 walks next+4,
  appends one pointer, returns its receiver and uses ret4.
- The 33-byte PartitionManager wrapper at RVA 0x009F26A0 forwards the four
  incoming position/range/mode/filter arguments, inserts a null optional
  argument, loads its subordinate receiver at this+0xC and uses ret16.
  Existing typed pins for both wrappers pass pin_consistency.

## Source structure and headers

The exact source keeps both filters as full-expression temporaries in the
getClosestObject query. The constructor result remains live through link;
VC7.1 emits the observed argument sequence and EH states. Named local filters
in the old bank did not reproduce that sequence.

Canonical Object/Thing is included. THING_TU_MEMBERS adds the witnessed native
position accessor. No game header defines TAiData, PartitionFilter,
PartitionFilterRepulsor or PartitionManager. The AI declaration in
`game_engine_subsystems.h` is explicitly only a registration stub.
The vendored ZH filter lacks BFME's virtual destructor, next pointer and link
method, and its manager consumes a filter array plus optional outputs. These
BFME-specific TU views are therefore required. Header-adoption checks report
no offender; name_oracle reports no conflict.

## Retired constructor alias at RVA 0x00087A50

The old ai.cpp fallback emitted a ZH PartitionFilterRepulsor constructor, and
its ledger row claimed these 18 bytes as an ICF alias of StaticNameKey:

    8B C1 8B 4C 24 04 C7 00 00 00 00 00 89 48 04 C2 04 00

Retail stores literal zero at +0, stores the sole argument at +4, returns
this and ret4. It has no vtable address and never writes +8. It cannot be the
BFME repulsor constructor proven above. The reference StaticNameKey initializer
in Common/NameKeyGenerator.h instead stores NAMEKEY_INVALID and its name
pointer in those two fields. Its existing matched owner in WorldHeightMap.cpp
was independently rebuilt and verified again at RVA 0x00087A50.

Only the contradicted Repulsor alias is retired, with a durable tombstone.
Other historical aliases at the address are untouched. Previously retired
SameMapStatus, PolygonTrigger and SamePlayer filter aliases document the same
zero-versus-vtable contradiction. No verifier logic or retail byte is changed.
The measured duplicate-identity and null-relocation row ratchets each tighten
by one for this retired alias.
This retirement removes one duplicate identity and zero unique covered bytes.

## Verification

The production add_match gate verifies 154/154 bytes with existing resolved
callees and globals. Independent strict checking reports zero unresolved
symbols, no masking fallback, two checked DIR32 references, three consistent
global symbols and a successful no-op patch. No new pins, address literals,
aliases, assembly, shared header changes or copied retail bytes are added.
The old ZH filter-array body is replaced by a redirect comment; the remaining
ai.cpp rows and the new TU are verified together after the false alias retires.

Net new clean C++ coverage is 154 bytes; the constructor retirement loses no
unique byte coverage. Linkability is a separate census result, not asserted here.
