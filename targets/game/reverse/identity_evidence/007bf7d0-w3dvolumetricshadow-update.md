# 0x007BF7D0 W3DVolumetricShadow::Update(Bool) (758 B)

BFME 1 target evidence:
- `tools/ilt_oracle.py check '?Update@W3DVolumetricShadow@@IAEX_N@Z' 0x7BF7D0`:
  CONFIRMED (exact). The ledger's ZH spelling `?Update@W3DVolumetricShadow@@IAEXXZ`
  and the public/private Bool spellings are CONTRADICTED.
- Retail ends `ret 4` at +0x2F3 and +0x2DA; the stack byte is ORed into the
  +0x4900 byte when the shadow buffers 0x01306F1C/0x01306F20 are null, and
  ORed with that byte (then cleared) otherwise: one Bool argument.
- Callees: RenderObjClass::Get_Position (0x009202C0), TheTerrainLogic slot 6,
  TheTerrainRenderObject slot +0x248, updateOptimalExtrusionPadding
  (0x007BA590, matched), 0x007BF3C0 (dump, ILT 0x00039B35, one float),
  W3DBufferManager::getNextVertexBuffer (0x007B7CF0, matched).
- Function statics: guard 0x01307174 / origin vector 0x01307164..6C,
  currentTime 0x01307160, lastTime 0x0130715C.

Donor evidence (open-bfme-2 b5a7b8290, Code/GameEngineDevice/Source/W3DDevice/
GameClient/Shadow/W3DVolumetricShadowUpdate.cpp, BFME 2
`?Update@W3DVolumetricShadow@@QAEX_N@Z`, itself the ZH body with BFME deltas):
same pending-update byte, mesh-count gate on the X bound test and render-task
clearing loop. BFME 1 offsets differ (height-map slot +0x248, min height
+0x300C, buffer list +0x9000) and are read from BFME 1 retail.
