# 0x000CF880 / 0x000D3230: list<TeamPrototype *> members

Both bodies were rowed under placeholder element types
(`list<Rva000CF880Target *>::_M_insert_dispatch` and the gen-tgrid
`list<Gen_t_000d3230_p4cd>` copy constructor). BFME 1 target evidence:

- `Player::update` (0x000D9A80, matched in
  `game/GameEngine/Source/Common/RTS/Player_update_Thunk.cpp`) copies the
  list at Player+0x288 through ILT 0x00047CAD, which jumps to 0x000D3230.
  Zero Hour's `Player::update` iterates `m_playerTeamPrototypes`, a
  `std::list<TeamPrototype*>` (`Player.h` `PlayerTeamList`), and the body
  dereferences each element +0x274 as the prototype's team instance list.
- `tools/ilt_oracle.py check` CONFIRMS
  `??0?$list@PAVTeamPrototype@@...@QAE@ABV01@@Z` at ILT 0x00047CAD
  (p_false 3.3e-4, exact) and
  `??$_M_insert_dispatch@...PAVTeamPrototype...` at ILT 0x000129E0
  (p_false 3.9e-4, exact), the thunk the copy constructor calls.
- `template std::list<TeamPrototype*>::list(const std::list<TeamPrototype*>&);`
  in `Player.cpp` compiles to the retail 111 bytes; the 0x000CF880 body is
  unchanged by the element rename (a pointer element is a plain store).
