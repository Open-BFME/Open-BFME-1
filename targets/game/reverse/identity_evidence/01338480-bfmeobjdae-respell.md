# VA 0x01338480: one storage, read by its defined name

- `targets/game/reverse/dir32_addresses.csv` records `_g_bfmeRouteKeys1282`,
  `?g_bfmeRouteKeys1282@@3PAHA`, `?g_bfmeValues1220@@3PAHA` and `_bfmeObjDAE`
  at the same VA 0x01338480.
- Only `_bfmeObjDAE` is defined by any object
  (`game/GameEngine/Source/Common/Rva00C6DC90ArrayInit.cpp`): retail's .CRT
  initializer 0x00C6DC90 runs the vector constructor iterator over this VA with
  stride 4 and count 178, and cleanup 0x00C70F60 destroys the same array.
- Link queue rows #326 (`_g_bfmeRouteKeys1282`, BfmeConv1569.cpp) and #349
  (`?g_bfmeValues1220@@3PAHA`, Rva008981TaggedRecords.cpp) were unresolved
  because nothing defines those spellings.
- The callers keep their descriptive macro names
  (`#define g_bfmeRouteKeys1282 __identifier("bfmeObjDAE")`) and now reference
  the one defined symbol. Bytes are unchanged (scoped gates). No data_rows row
  is added for `_bfmeObjDAE`: `?g_01338524@@3URva008A9A70Str@@A` already owns an
  element inside the array, so add_data_match refuses the 712-byte extent.

The remaining nine authored route-key users keep their existing descriptive spelling through the same compile-time identifier binding. The array's provider and 178-element lifetime are unchanged. All 21 scoped code rows verify, with 17 DIR32 name substitutions and the same retail targets. Generated references are outside this source repair.
