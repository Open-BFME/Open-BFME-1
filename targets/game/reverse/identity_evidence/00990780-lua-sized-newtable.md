# 0x00990780 is Lua's sized lua_newtable (lapi.c), not a game-side function

The row was `?bfmeGoUPC@@YAXPAUBfmeStateUPC@@H@Z` in
`game/GameEngine/Source/Common/BfmeConv1339.cpp`, a C++ body over a private
three-field copy of `lua_State`. Lua's own objects call the same address under
the C name `_bfmeGoUPC` (`lstate.c` f_luaopen, `ldblib.c` getinfo), which no
object defined, so Lua could not link without /FORCE
(`python3 tools/component_link.py lua`).

Evidence:

- Retail callers: `f_luaopen` 0x00996DD3 `e8 a8 99 ff ff` and ldblib `getinfo`
  0x00990D6F `e8 0c fa ff ff` both land on 0x00990780 with `(L, 0)`. Upstream
  Lua 4.0.1 calls `lua_newtable(L)` at both points (`lua_newtable(L);
  lua_ref(L, 1);  /* create registry */` in f_luaopen; `lua_newtable(L)` at the
  top of getinfo's result).
- Placement: 0x00990780 sits between `_lua_getref` (0x00990700) and
  `_lua_setglobal` (0x009907C0), both lapi.c rows, where upstream's lapi.c puts
  `lua_newtable`. No ledger row claims a one-argument `lua_newtable`.
- Body (59 bytes): `luaH_new(L, 0, n)` (0x00999610, ltable.c), stores it at
  `L->top` with tag 4 (LUA_TTABLE), then `if (L->top == L->stack_last)
  luaD_checkstack(L, 1)` (0x009959C0, ldo.c) and `L->top++`: upstream's
  lua_newtable with `api_incr_top`, the size argument passed through to EA's
  three-argument `luaH_new` (PROVENANCE.txt).

EA's name for the sized variant is not witnessed, so the row keeps the name its
callers already use, now with C linkage in lapi.c: `_bfmeGoUPC`.
