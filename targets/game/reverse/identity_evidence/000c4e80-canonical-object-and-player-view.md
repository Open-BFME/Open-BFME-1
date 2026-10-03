# Supply-transfer provider and offset view

The canonical `Object` declaration in `inputs/reference/shims/sweep/GameLogic/Object.h` declares `Player *getControllingPlayer() const` and `ObjectShroudStatus getShroudedStatus(Int) const`. The retained C4E80 caller now includes that declaration; the old linker aliases and duplicate Object/Player/NameKeyGenerator declarations are removed. Player remains the canonical returned pointer identity.

Retail ILT 20824 jumps to 1BE3F0: its 18-byte body reads Object+23C and tail-calls the team player getter, or returns null. ILT 2B81E jumps to 1C7B30: its 59-byte body uses ECX receiver and one stack index, returning shroud status with RET4. Existing matched Object.cpp rows are their sole identities. Pin consistency independently re-derived both routes.

Native C4FFC calls the controlling-player route; C5005 reads the returned pointer+2C and tests zero; C500C reads pointer+24 and pushes that word into the canonical shroud call at C5012. These exact field accesses are preserved in Rva000C4E80PlayerView. This partial offset view does not declare Player or claim to replace its identity. The naming checker pairing removed Player to this view is a false correspondence, covered only by the exact source snapshot hashes recorded in name_corrections.json.

Native FuncInfo DE6D30 has two unwind states, both predecessor -1, whose actions are BF9420/BF942E. Each is exactly 14 bytes ending RET, with DIR32 offsets 1 and 9 referring to the same guard VA012ED70C and masks ~1/~2. The retained provider naturally emits both; the existing rows keep symbols, extents and parent while changing source provider. No synthetic anchor or new body was added.

Strict validation covers 45 rows across donor, keeper, warehouse caller and dock predicate, including these two actions. The 76-line unmatched donor definition is removed, together with the pre-existing stale present-unmatched comment on the ledger-backed canBribeUnit object symbol, as required by the normal hook. All other donor bytes and mixed line endings remain intact. No header, pin, reference or optimization flag is changed. Census estimates are stale and are not whole-program link proof.
