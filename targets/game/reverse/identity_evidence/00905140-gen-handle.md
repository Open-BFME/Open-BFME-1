# `Create_Render_Target` returns `Gen_005D2040`

The bank at `targets/game/reverse/attempts/0x00905140.cpp` declares `Create_Render_Target` as returning `RefCountPtr<TextureClass>`. The matched caller in `game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterRenderObjReAcquireResources.cpp` declares the method as returning `Gen_005D2040`. It stores that result in `m_pReflectionTexture`, whose declared type is also `Gen_005D2040`.

The `symbols.csv` pin at `0x00905140` records the same hidden-sret return type. `pin_consistency.py --symbol` passes for that pin. The matched caller's declared method signature and destination field refute the bank's `RefCountPtr<TextureClass>` return type.
