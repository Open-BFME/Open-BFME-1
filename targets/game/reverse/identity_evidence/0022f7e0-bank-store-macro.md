# 0x0022F7E0 GarrisonContainModuleData constructor: bank names were a store macro

The banked attempt (`targets/game/reverse/attempts/0x0022f7e0.cpp`, score
0.5882) wrote every derived default through `S32(offset, value)`, a local
`#define` for a volatile store at a raw offset, and declared the storage as
`m_storage` (base) and `m_tail` (derived). None of these is a member name:
`S32` is the macro, and the two arrays were byte padding standing in for an
unknown layout.

The landed source `game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainModuleDataCtorThunk.cpp`
replaces them with typed, offset-named members (`m_2F4[10]`, `m_31C` ...
`m_338`) because no evidence names any BFME GarrisonContainModuleData field
(`tools/name_oracle.py --class GarrisonContainModuleData` has no witness).
The volatile macro was also the reason the bank missed: it kept MSVC from
hoisting the 1.0f register load ahead of the zero stores. The typed body is
byte-exact (`tools/add_match.py`, 153/153).

So the name_regression findings `S32 -> m_*`, `m_storage -> m_pad` and
`m_tail -> m_2F4` pair a macro and padding with offset names; nothing
descriptive was lost.
