# BfmeDelayedLuaEvent destructor owns the 67-byte body at 000ED4A0

??_GBfmeDelayedLuaEvent@@QAEPAXI@Z (0x000EE700) calls its complete destructor
through ILT 0x00041362 -> 0x000ED4A0 (tools/callees.py); DelayedLuaEventList's
exact constructor passes the same element destructor ILT to the vector
iterator. The 67-byte body (EH frame; releases the string at +0x10; re-seats
the offset-0 member's vftable 0x01073744) was ledgered address-derived as
??1Rva000ED4A0@@QAE@XZ in BigTwoMemberDtors.cpp. The scalar-deleting destructor
of a class calls that class's destructor, so it is ??1BfmeDelayedLuaEvent@@QAE@XZ.
