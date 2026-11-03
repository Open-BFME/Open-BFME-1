# Repair include inventory in WaterShader007A6AA0

Source `game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterShader007A6AA0.cpp`. Remove only the redundant whole-checkout `/I.` search
root and anchor existing root-spelled includes relative to this source. Every
resolved dependency path and digest is unchanged. Optimization, ABI switches,
headers, hatches, aliases, native pins, ledgers and baselines are unchanged.

Native normal/frozen/EH checks pass for 1 existing function/EH rows.
All 14 retained external code bodies and relocations, named
TU-local code and every non-debug section including linker directives remain
exact. No external code is added or removed. This is compiler-input receipt
maintenance, not new native coverage or a runtime/RAM/crash/FPS improvement.

Header mappings:

- `game/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h` -> `../../../../../Libraries/Source/WWVegas/WW3D2/dx8wrapper.h` (same resolved file).

Final native receipt stability and bounded link-preview results are in the batch evidence.
