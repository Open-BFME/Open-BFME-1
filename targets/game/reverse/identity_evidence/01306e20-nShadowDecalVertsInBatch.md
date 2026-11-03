# nShadowDecalVertsInBatch storage at VA 0x01306E20

The decorated identity `?nShadowDecalVertsInBatch@@3HA` owns one four-byte integer at VA 0x01306E20 in retail `.data`. Its initial value in retail `.data` is 0.

## Retail facts and contract

`nShadowDecalVertsInBatch` is declared and defined in `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadow.cpp` (matching Zero Hour `W3DProjectedShadow.cpp`) as `int nShadowDecalVertsInBatch = 0;`. It tracks the count of shadow decal vertices in the active batch. Retail `.data` places it at 0x01306E20 following `nShadowDecalPolysInBatch` (0x01306E1C). The address falls in the section's zero-filled virtual tail (`.data` raw size ends at VA 0x012EE000 while its virtual size ends at 0x01358000), so retail holds 0 at the address with no file bytes.

## Extent and all users

4 bytes at VA 0x01306E20. Users: the definer TU `W3DProjectedShadow.cpp` (batch resets, index accumulation and draw calls) and `extern int nShadowDecalVertsInBatch;` at `W3DProjectedShadowManagerRva007B14A0.cpp:346`.
