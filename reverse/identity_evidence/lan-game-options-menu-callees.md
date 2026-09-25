# LAN menu callee evidence

Retail body `0x004CDA50` calls ILT `0x00039202` at offsets `+0x1D8`, `+0x2B1`, and `+0x377`. The thunk targets body `0x004CAF70`, which the matched function ledger names `rva004CAF70`. A scoped probe compiles `lanUpdateSlotList` to 108 bytes while retail body `0x004CAF70` is 125 bytes, so that source helper does not match the retail target.

Retail body `0x004CDA50` calls ILT `0x0001C9D6` at offsets `+0x1DD` and `+0x2B6`. The thunk targets body `0x004CC660`, whose matched row keeps the address-derived name `d_004cc660`. A scoped probe compiles `updateGameOptions` to 536 bytes while retail body `0x004CC660` is 468 bytes, so that source helper does not match the retail target. The converted caller uses the address-derived body names and makes no behavioral name claim.
