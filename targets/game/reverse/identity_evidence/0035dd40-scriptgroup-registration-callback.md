# 0x0035DD40: ScriptGroup registration callback route

The authentic C++ callback class/method spelling is unresolved. This records a
native registration association, without renaming the member as ScriptGroup's
upstream static parser.

Retail-1.03-unpacked bytes independently show ILT RVA `0x00005C6D` reaches
this 363-byte body. The only absolute stub-VA word is VA `0x010E8584`, slot 1
of the two-entry table VA `0x010E8580`; slot 0 reaches deleting destructor
RVA `0x00352B70`. No direct caller to the stub names this callback.

The independently matched address-derived constructor
`Rva00352AB0ParserRegistration::Rva00352AB0ParserRegistration`, RVA `0x00352AB0`,
installs that final table at `0x00352B2F` (`mov [esi],0x010E8580`). It constructs
the native `ScriptGroup` literal at VA `0x010E8478` (push at `0x00352ADB`) for
its DataChunkInput parser registration. At `0x00352B28` and `0x00352B35` it
stores the supplied context and list at receiver `+0x0C/+0x10`. The candidate
uses that context at `0x0035DD73` before calling private helper `0x0035A060`.
These independent constructor and table facts tie the member to the registered
ScriptGroup parser object; the generic role is not its original type spelling.

The constructor's clean source is
`game/GameEngine/Source/Common/ScriptGroupParserRegistrationConstructor.cpp`.
Matched `ScriptListParseScriptListDataChunk.cpp` constructs this registration
object with its new list/context, corroborating the ScriptGroup dispatch role.
The upstream `ScriptGroup::ParseGroupDataChunk` is static and has a different
ABI, so its name is not borrowed for this member.

Final RET 4 at RVA `0x0035DEA8` and INT3 at `0x0035DEAB` establish 363 bytes.
The ECX/stack/caller-cleanup contract of `0x0035A060` still needs genuine parent
code generation before a clean conversion can be claimed. No new callee pin or
cast-to-address adapter is introduced.
