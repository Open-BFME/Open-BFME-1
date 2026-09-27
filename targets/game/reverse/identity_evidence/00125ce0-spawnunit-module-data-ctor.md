# SpawnUnit module-data constructor at RVA 0x00125CE0

The retail module registry distinguishes the two names that previously claimed this constructor.

In `ModuleFactory::init` (RVA 0x0012C2E0), +0x08BA pushes VA 0x01090B8C, whose bytes spell `SpawnUnitBehavior`. The registration stores data-factory VA 0x0043F611 at +0x08F8. That ILT thunk jumps to RVA 0x00125D70, whose constructor call reaches RVA 0x00125CE0.

The next registration pushes VA 0x01090B68 (`OathbreakersFadeAwayBehavior`) at +0x0912 and stores data-factory VA 0x00442078 at +0x0950. Its ILT thunk jumps to RVA 0x001246F0, a different factory. These literal and pointer values were independently read from the retail image; `module_factory.cpp` and `dir32_addresses.csv` corroborate them.

The constructor installs vtable VA 0x0108E890 at +0x24. Slot zero points to ILT RVA 0x0002A78E, which jumps to RVA 0x00126ED0 (VA 0x00526ED0), the already matched SpawnUnit scalar-deleting destructor. It calls complete destructor RVA 0x00126F00, releasing the same strings at +8 and +0xC. This corroborates the registry identity without treating identical lifted bytes or the duplicate factory claims as proof.

Retire only the stale Oathbreakers constructor claim at this address and its naked source, replace the SpawnUnit naked source with verified native C++, and leave broader factory corrections to their separately verified change. The native constructor reproduces both string-set calls followed by zero stores at +0x14,+0x18,+0x10,+0x1C.

Commands: `tools/dis_retail.py 0x0012C2E0 18040`, `tools/dis_retail.py 0x0003F611 5`, `tools/dis_retail.py 0x00042078 5`, `tools/dis_retail.py 0x00125CE0 114`. VA = RVA + 0x00400000.

The stale Oathbreakers factory claim at RVA0x00125D70 must move with this correction: retaining it would preserve its call to the refuted constructor. Recover its real57-byte factory at RVA0x001246F0 from the existing native body formerly named bfme5MakeParseNodeC, and bind its field parser to ILT0x0002AEF5 (VA0x0042AEF5). The registry and raw factory agree; SpawnUnit instead uses ILT0x0000A727. Durable tombstones retire both superseded claims.

Unwind parentage is independently encoded in retail: factory0x00125D70 pushes handlerVA0x0100181B. That handler loads FuncInfoVA0x011EFE28 (magic0x19930520, maxState1, unwindMapVA0x011EFE20); the map entry is {toState=-1, action=VA0x01001810}. Thus funcletRVA0x00C01810 belongs to the SpawnUnit factory. The compiled SpawnUnit factory object emits the matching11-byte cleanup as$L351. This proof uses the handler and map, not adjacency.

The name-regression detector also pairs the moved12-byte parse record with the unrelated12-byte Bfme5RefNode at the top of Bfme5NodeMakers.cpp. That reference-counted node and its m_bfmeRefCount/m_bfmePad members remain unchanged. The actual moved Bfme5ParseNode12 already named its fields m_bfme04/m_bfme08, and the corrected factory preserves those names and stores. The registry-proven Oathbreakers record uses vtableVA0x0108D748 and writes1 at+8; the unchanged Bfme5RefNode uses g_bfme5RefVtable, initializes its reference count at+4, and increments it. They are different objects. Exact content-bound corrections record this false cross-type association; no established member name was removed.
