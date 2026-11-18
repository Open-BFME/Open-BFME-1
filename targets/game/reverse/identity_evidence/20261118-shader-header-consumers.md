# Two ShaderClass consumer reconciliations

Tasks 582-583 use the existing BFME1 shader.h in two independently checked
consumers. The header is unchanged; no function, datum, alias or pin is added,
removed or rebound. These are source/type reconciliations, not new authored
function bytes or a crash, memory, FPS or runtime fix.

Native class_contract establishes a four-byte class with uint ShaderBits at
offset zero, no bases and no virtual state. Matched by-value ShaderClass users,
the four-byte vector element stride and the existing 0010441B default stores
independently corroborate the storage contract. The fresh twelve-view inspection
agrees with the existing header and read-only BFME2 reference context at
0630f0ef47d0a818bb2e97583b43cfb1ecd35491. Donor offsets or bodies are not imported.

The canonical header adds existing static member declarations to the type view.
They allocate no storage here and are not new claims about target definitions:
the complete ordinary COFF inventories, including raw directives, code, data,
relocations, external definitions, weak contracts and aliases, remain identical.
Both views retain one uint at offset zero and size four. Every other original
complete CodeView class contract remains identical. Real include tracing proves
the intended existing BFME1 header is used.
The normal providers/consumers gate passes 95/95 rows across 3 sources
and 285 DIR32 references, including decalmsh.cpp. The consumer-only ordinary
commit and push gates remain required. Linking status is a separate current
preview against the full provider inventory, not a new full-image census.

| Task | Consumer | Retained rows | Retained bytes |
|---|---|---:|---:|
|582|`game/Libraries/Source/WWVegas/WW3D2/DX8Wrapper_DrawPrimitives.cpp`|5|1950|
|583|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBufferRva0071EEC0.cpp`|1|4131|
