# Address-derived views for RVA 0x000D22A0

The two matched callers in `game/GameEngine/Source/Common/BfmeConv830.cpp` call `BfmeObjNotify3F0::notify` with a name and flags 0 or 1. The incremental link table (ILT) pin at `0x259FA` resolves to the 332-byte body at RVA `0x000D22A0`, so those callers and that pin prove the method identity.

The bank used descriptive names for local owner, team, iterator, and override layouts. The callers do not identify those helper types as game classes. The new source therefore gives those views address-derived names and keeps field names that shared headers prove.

The new source includes `GameLogic/Object/object.h` and uses its shared `Object` definition. `Object` inherits `Thing`, whose shared header places `m_template` at offset `0x04`. The local `Rva000D22A0ObjectView` adds a template accessor and does not define another `Object` layout.

`targets/game/reverse/name_corrections.json` binds each correction to the exact before and after source digests. These corrections explain why the bank's helper names do not establish retail class identities.
