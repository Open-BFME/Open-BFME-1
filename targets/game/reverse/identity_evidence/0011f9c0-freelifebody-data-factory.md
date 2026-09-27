# 0x0011F9C0 is FreeLifeBody's module-data factory

Four ledger rows name this 110-byte factory: `friend_newModuleData` of MissileAIUpdate,
SpyVisionSpecialPower (ModuleFactory.cpp), W3DModelDraw and W3DOverlordAircraftDraw
(W3DModuleFactory.cpp).

ModuleFactory::init registers it exactly once. At 0x0012FF96 it pushes the string
"FreeLifeBody" (0x0108FB24). At 0x0012FFAD/0x0012FFB2 it pushes createDataProc ILT
0x00003C60 (-> 0x0011F9C0) and createProc ILT 0x0004A002 (-> 0x0011F940, matched as
`friend_newModuleInstance@FreeLifeBody`). It then calls addModuleInternal (0x00129AC0).
The image holds no other reference to 0x0011F9C0 or its ILT.

The strings "W3DModelDraw", "W3DOverlordAircraftDraw", "MissileAIUpdate" and
"SpyVisionSpecialPower" do not occur in the image, so BFME registers none of those
modules. The two W3D rows are retired. Their DIR32 operand made
`W3DModelDrawModuleData::buildFieldParse` look like ILT 0x000392CF (-> 0x00213280), which
contradicted the ledger row at 0x0077D380 that W3DTruckDraw's builder calls through ILT
0x00022584.

The ModuleFactory.cpp names are also wrong. They are left in place so the body stays
claimed until a FreeLifeBody source reproduces it.
