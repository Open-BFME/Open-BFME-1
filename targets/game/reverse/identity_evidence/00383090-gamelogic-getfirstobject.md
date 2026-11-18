# 0x00383090 GameLogic::getFirstObject

Previously the generated shim `?m@Gen_00383090@@QAEHXZ` (game/gen_small/fun_002.cpp,
skeleton getter-d32). Now `?getFirstObject@GameLogic@@QAEPAVObject@@XZ` in
game/GameEngine/Source/GameLogic/System/GameLogic_getFirstObject.cpp.

BFME 1 target evidence:
- Body: `mov eax,[ecx+0xA8]; ret` (7 B).
- `tools/ilt_oracle.py check ?getFirstObject@GameLogic@@QAEPAVObject@@XZ 0x358BE`:
  CONFIRMED (exact, p_false 2.0e-4). ILT 0x000358BE jumps to 0x00383090.
- Every placeholder caller loads TheGameLogic (0x012F0898) into ecx and walks
  the returned pointer as the object list through Object::getNextObject
  (Bridge.cpp, Rva00259160FilteredModelCondition.cpp,
  ScriptEngineRva00349A30RebuildNamedObjects.cpp). The matched
  GameLogicLoadPostProcess.cpp and GameLogicPrepareObjectLoad.cpp views
  hold the list head at GameLogic+0xA8.

Zero Hour reference: GeneralsMD GameLogic.cpp
`Object *GameLogic::getFirstObject( void ) { return m_objList; }`.

Link-queue row #36 (census 6c4dd9e650): GameLogicLoadPostProcess.cpp's call
was satisfied by GameLogic.cpp's Zero Hour copy, now under #if 0.
