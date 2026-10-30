# 0x0043E260: bank name testPoint@Rva0043E260Owner -> rva0043e260@InGameUI

The banked attempt previously spelled the body
`?testPoint@Rva0043E260Owner@@QBE_NPBH@Z`, an attempt-local placeholder.
The pinned name is `?rva0043e260@InGameUI@@QAE_NPBUICoord2D@@@Z`
(symbols.csv: "InGameUI lasso point test: thiscall ret 4 reading ICoord2D
x/y against the +0x1308 region and +0x1304 points"), and the matched caller
InGameUIRva00442FD0.cpp (?rva00442fd0@InGameUI, landed) calls it under that
name; link queue #67 is that call being unresolved. The body reads
InGameUI's lasso region at +0x1308..+0x1314 and lasso point list at
+0x1304. The bank now uses the pinned spelling so it can land under the name
its caller links against; neither name is an EA name.
