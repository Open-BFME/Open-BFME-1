# Repair include inventory in RoadShaderPixelShader_init

Source `game/GameEngineDevice/Source/W3DDevice/GameClient/RoadShaderPixelShader_init.cpp`. Remove only the redundant whole-checkout `/I.` search
root and anchor existing root-spelled includes relative to this source. Every
resolved dependency path and digest is unchanged. Optimization, ABI switches,
headers, hatches, aliases, native pins, ledgers and baselines are unchanged.

Native normal/frozen/EH checks pass for 2 existing function/EH rows.
All 31 retained external code bodies and relocations, named
TU-local code and every non-debug section including linker directives remain
exact. No external code is added or removed. This is compiler-input receipt
maintenance, not new native coverage or a runtime/RAM/crash/FPS improvement.

Header mappings:

- `game/Libraries/Source/WWVegas/WWLib/wwstring.h` -> `../../../../Libraries/Source/WWVegas/WWLib/wwstring.h` (same resolved file).

Final native receipt stability and bounded link-preview results are in the batch evidence.
