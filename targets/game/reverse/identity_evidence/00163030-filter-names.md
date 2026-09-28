# 0x00163030 AIPlayer::isLocationSafe: filter class names

Each of the six inline filter temporaries is named by the vtable it installs:

| vtable (VA) | name used | why |
|---|---|---|
| 0x0109689C | PartitionFilterPlayerAffiliation | `symbols.csv` pins `??_7PartitionFilterPlayerAffiliation@@6B@` at RVA 0x00C9689C |
| 0x0109686C | PartitionFilterRejectByKindOf | pinned `??_7PartitionFilterRejectByKindOf@@6B@` (RVA 0x00C9686C) |
| 0x01083B80 | Rva01083B80Filter | only address-keyed pins (`Rva0025ED50RootFilter`); no class name witnessed |
| 0x010956E4 | Rva010956E4Filter | no vtable pin |
| 0x0109685C | Rva0109685CFilter | no vtable pin |

The banked stash called 0x01083B80 `PartitionFilterAlive` and 0x010956E4
`PartitionFilterInsignificantBuildings`. Those are Zero Hour names that no BFME witness
supports, so they give way to address names until a vtable or RTTI witness names them.
`m_bfmeBeforePlayer` and `m_bfmePad` were padding placeholders, now `m_unmodelled000`.
