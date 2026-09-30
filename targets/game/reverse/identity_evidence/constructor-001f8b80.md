# Constructor identity at RVA 0x001F8B80

Retail evidence, read directly from `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`:

1. The unique ASCII `DynamicPortalBehaviour` string is at VA `0x01090B3C`. Its direct `.text` references are RVAs `0x0012CC9F`, `0x001F8AE2`, `0x001F8C11`, and `0x001F8CB1`.
2. The module-registration sequence at `0x0012CC9F` constructs that string, derives its module name key, then stores ILT `0x00011A59` as the instance factory at `0x0012CCD6` and ILT `0x0000773E` as the module-data factory at `0x0012CCDC`.
3. ILT `0x00011A59` routes to `0x001156B0`; that factory calls ILT `0x0002D40C` at `0x001156EB`; the ILT routes to the 107-byte constructor at `0x001F8B80`.
4. The constructor stores primary vtable VA `0x010A397C` into `[this]`. Its slot 2 routes through ILT `0x0000DA0D` to `0x001F8C10`, a six-byte getter returning the `DynamicPortalBehaviour` string. Slot 4 routes through ILT `0x0001383B` to `0x001F8C80`, whose name-key function hashes that same string.

The constructor's owner is therefore `DynamicPortalBehaviour`; this argument does not use any contested `dir32_addresses.csv` or `symbols.csv` name. Keep its one 107-byte matched row and retire the `QueueProductionExitUpdate` and `RebuildHoleBehavior` aliases at that RVA. The range remains covered.

`QueueProductionExitUpdate` has separate retail evidence: its unique ASCII string is VA `0x01090470`. The registration at `0x0012E6B8` stores instance-factory ILT `0x0004A859`, routing to `0x0011AE40`. That factory calls ILT `0x00004C9B`, routing to the 125-byte constructor at `0x002D0620`. The constructor stores primary vtable `0x010CB764`; slot 2 routes through ILT `0x00001C76` to getter `0x002D06C0`, which returns `QueueProductionExitUpdate`. The current ledger instead calls `0x002D0620` `CleanupHazardUpdate`; that separate identity correction needs coordinated review. Neither Queue's distinct constructor nor its registration supports the alias at `0x001F8B80`.

`RebuildHoleBehavior` has no ASCII or UTF-16 occurrence in the retail image. That negative observation alone does not determine whether the class exists; the positive factory/vtable chain above rules out its constructor identity at `0x001F8B80`.

The same registration chain independently refutes the two Queue factory aliases at `0x001156B0`: `friend_newModuleInstance@QueueProductionExitUpdate` and `emit_QueueProductionExitUpdate@ModulePoolGlueBulk`. The retained `DynamicPortalBehaviour` factory covers the complete 96-byte range. These were the two matched consumers of the removed Queue constructor pin. Other destructor aliases remain a separate audit.

The factory's exception metadata independently establishes cleanup parentage: `eh_info.py 0x001156B0` reads handler RVA `0x00BFE5CB`, FuncInfo RVA `0x00DEBF54`, and its sole state-0 cleanup at `0x00BFE5C0`. The 11-byte opaque cleanup is now compiled from the established DynamicPortal factory source, whose unique cleanup calls `operator delete`. Its former Queue parent annotation was false; this correction does not infer parentage from adjacency.
