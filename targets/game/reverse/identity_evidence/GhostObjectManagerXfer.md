# `GhostObjectManager::xfer` at RVA `0x001B3B00`

The constructor at `0x001B3AA0` installs vtable `0x0109CE28`. Slot 3 points to ILT `0x00024230`, which jumps to `0x001B3B00`. `GhostObjectManager` overrides `Snapshot::xfer` in slot 3, after the two destructor slots and `crc` in slot 2.

The body passes its `Xfer *` argument to slots `+0x28` and `+0x78`. The second call reads `this + 4`, and `name_oracle.py` identifies `GhostObjectManager + 4` as `m_localPlayer`. These retail references identify the body as `GhostObjectManager::xfer`.

The existing ledger row called this address `bfmeSeed@Gen_001B3B00`. The constructor vtable and the field transfer identify the owning method, so this record supports replacing that name.
