# CConstantTable::AddRef at RVA 00A5627E

The unchanged native `CConstantTableQueryInterface.cpp` defines
`D3DXShader::CConstantTable::QueryInterface` at 00A56226. Its source names
virtual stdcall `AddRef` in slot 1. Fresh scoped verification reproduced all
88 bytes and all three DIR32 references. Retail A56264 loads the receiver,
A56269 reads its vptr, A5626B pushes the receiver, and A5626C calls `[eax+4]`.
Thus a matched caller names this operation independently of its short body.

Constructor A56DFE installs table VA 0114D7C8 at A56E11, and destructor
A55206 reinstalls the table at A5520D. The constructor initializes dword +4
at A56E17 to one. Slot 1 at VA 0114D7CC contains VA 00E5627E. This provides
the receiver/table/caller route to the body, not a generic COM-name guess.
Ghidra memory and the retail baseline independently agree on the table entry
and complete 13-byte body `8b442404ff40048b4004c20400`, ending RET4 at A56288.

The public virtual stdcall unsigned-long ABI gives
`?AddRef@CConstantTable@D3DXShader@@UAGKXZ`. Native C++ uses an ordinary
increment and a volatile readback to preserve retail's memory INC followed by
a separate load. The qualifier does not establish an original volatile field.
No alias, callee pin, relocation workaround, or semantic getter name is added.
