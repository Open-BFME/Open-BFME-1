# Repair include inventory in Rva002C4EA0RepairContained

Source `game/GameEngine/Source/Common/Rva002C4EA0RepairContained.cpp`. Remove only the redundant whole-checkout `/I.` search
root and anchor existing root-spelled includes relative to this source. Every
resolved dependency path and digest is unchanged. Optimization, ABI switches,
headers, hatches, aliases, native pins, ledgers and baselines are unchanged.

Native normal/frozen/EH checks pass for 1 existing function/EH rows.
All 11 retained external code bodies and relocations, named
TU-local code and every non-debug section including linker directives remain
exact. No external code is added or removed. This is compiler-input receipt
maintenance, not new native coverage or a runtime/RAM/crash/FPS improvement.

Header mappings:

- `game/GameEngine/Source/GameLogic/Object/object.h` -> `../GameLogic/Object/object.h` (same resolved file).
- `game/GameEngine/Source/GameLogic/command_source_type.h` -> `../GameLogic/command_source_type.h` (same resolved file).

Final native receipt stability and bounded link-preview results are in the batch evidence.
