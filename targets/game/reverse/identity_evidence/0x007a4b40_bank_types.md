# 0x007A4B40 bank: water-grid helper type names

The banked attempt for 0x007A4B40 (shoreline, not landed) declared its local
helper types as `BfmeWaterGridPoint2`, `BfmeWaterGridPoint3` and
`BfmeWaterGridPolygon`. Those names were invented for the bank: no ledger row,
pin or Zero Hour header carries them. The same layouts are already landed on
master as `Rva0079E560Point2`, `Rva0079E560Point3` and `Rva0079E560Polygon`
(game/GameEngineDevice/Source/W3DDevice/Common/System/Rva0079E560WindingContains.cpp),
so the gpt-6-astra seat re-banked the attempt with those existing names to keep
one spelling per layout. No identity was renamed.
