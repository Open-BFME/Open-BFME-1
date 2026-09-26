# 0x0029A7D0 / 133-byte PhysicsBehavior body

Retail `0x001CDE30+0x71` loads `Object+0x208` into EBX, checks its byte at
`+0x5C`, and at `+0xFA` passes EBX in ECX to ILT `0x00029B68`, which jumps to
`0x0029A7D0`. The independently matched
`game/GameEngine/Source/GameLogic/Object/Object_rva001C7CF0.cpp` identifies
`Object+0x208` as `PhysicsBehavior*`; its own retail body uses that field for
`PhysicsBehavior::applyMotiveForce`. Matched constructor `0x0029A880` and
destructor `0x0029AA30` establish the compact 0x60-byte module with module
data at `this+0x04` and Object at `this+0x08`. This proves the owner and
thiscall ABI, but does not prove a descriptive method name. The source keeps
`rva0029A7D0`.

The complete retail body has prologue `push ebx; push esi; push edi; mov
edi,ecx`, no stack arguments, and terminal `pop edi; pop esi; pop ebx; ret`
at `+0x84`. Its four calls are ILT `0x000022BB` twice (matched
`Overridable::getFinalOverride`, body `0x00087A80`), ILT `0x0002191D`
(`Object::notifyModelConditionChanged`, body `0x001BE1C0`), and ILT
`0x000157DA` (`UpdateModule::setWakeFrame`, body `0x002B2040`). These physical
routes are existing pins; no new callee identity was invented.

Retail reads the Object's template at `+0x04` and its contained-by Object at
`+0x214`, resolves either template's optional override at `+0x04`, and rejects
the unnamed byte at template `+0x4B0`. It tests/sets mask `0x02000000` in
the model-condition dword at Object `+0x11C`, then notifies only on a newly
set bit. The 40-byte condition field starts at Object `+0x110`, so this is
bit 121; the shipped name table at VA `0x012A6918` calls index 121
`STUNNED`. The body then sets its own byte `+0x5C`, copies module-data dword
`+0x20` to its own `+0x58`, and calls `setWakeFrame(object, 1)`. The exact
names of those three stored fields are not established by these observations.

The first raw-word C++ probe matched through the two template checks but
compiled to 134 bytes: VC7.1 used immediate `test/or` on the model-condition
word. The repository's documented bitset accessor layers generated retail's
`mov eax,0x02000000; test eax,ecx; or ecx,eax` sequence and yielded a
133/133 exact masked probe with four relocations. The strict byte/relocation
gate is required separately before claiming coverage.
