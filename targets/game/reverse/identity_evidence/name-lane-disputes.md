# Names the naming lane landed and a review disputed

- `game/GameEngine/Source/GameNetwork/V2FeslArrayBlocks.cpp|member||m_value0c`: `m_name` back to `m_value0c`. The file only constructs and destroys these members; nothing in the code shows they hold a name or a locale. Two models shared a guess from the file name.
- `game/GameEngine/Source/GameNetwork/V2FeslArrayBlocks.cpp|member||m_value14`: `m_locale` back to `m_value14`. The file only constructs and destroys these members; nothing in the code shows they hold a name or a locale. Two models shared a guess from the file name.
- `game/GameEngine/Source/Common/BfmeConv1838.cpp|function|BfmeHolderXB@|bfmeOnXB`: `DoXfer` back to `bfmeOnXB`. The body marks the item, then adds and links it into the holder's base; nothing is serialized, which DoXfer means in SAGE. Fable and Grok likely both read the placeholder's XB suffix as Xfer.
