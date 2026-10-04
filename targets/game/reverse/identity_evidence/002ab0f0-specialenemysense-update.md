# 0x002AB0F0 SpecialEnemySenseUpdate::update

Retail 0x002AB0F0..0x002AB314 (549 bytes, `ret` at +0x224, then int3).

## Identity

- The only reference to the body is ILT 0x00043CB1, and the only reference to
  that thunk is the dword at 0x010C3880: slot zero of the second interface
  table of SpecialEnemySenseUpdate (`??_7SpecialEnemySenseUpdate@@6BSESU_Iface2@@@`
  in dir32_addresses.csv), installed at +0x10 by the matched constructor
  0x002AAF30.
- The receiver is that +0x10 interface: the body reads module data at -0x0C
  and the object at -0x08, the UpdateModule layout. Slot zero of the
  UpdateModuleInterface is `update()`, and the body returns the module data's
  dword at +0x10 as the sleep time. The withdrawn row's destructor name is
  refuted by both.

## Filter class names

The stack filter whose table is 0x01083B80 is recorded in dir32_addresses.csv
as `??_7Rva0025ED50RootFilter@@6B@`, the spelling the matched
AutoPickUpUpdate::update (AutoPickUpUpdateUpdate.cpp) uses. The banked
attempt's `PartitionFilterBase` was a convenience name with no witness; the
DIR32 gate needs the recorded vtable symbol, so the source uses that name.
