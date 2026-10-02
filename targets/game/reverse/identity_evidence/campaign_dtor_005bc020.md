# Campaign::~Campaign at RVA 0x005BC020

Retail spans 186 bytes through `ret` at +0xB9 followed by INT3. The matched
Campaign constructor at 0x005BBF40 stores vtable VA 0x0110F65C at
0x005BBF61. Independently reading table slot zero gives ILT VA 0x004354DB,
which reaches the matched scalar-deleting destructor at 0x005BC790. That
wrapper calls ILT 0x00025220 -> 0x005BC020, conditionally deletes the object
for flag bit zero, and returns the saved receiver with `ret 4`.

The direct Zero Hour source twin is `Campaign::~Campaign` in
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/System/CampaignManager.cpp:131`.
Its loop saves each Mission pointer, erases its list node, then calls
`deleteInstance` for a nonnull mission. The corresponding header at
`GameEngine/Include/GameClient/CampaignManager.h:91` declares Campaign,
its `list<Mission*>`, and the string members in the observed order.
`Common/GameMemory.h:623` expands its memory-pool glue to a **protected
virtual destructor**, supporting `??1Campaign@@MAE@XZ`. The older deleting
wrapper's public declaration has the same machine calling convention but
is not the source access level used for this body.

BFME's matched constructor and destructor establish its shorter layout:
strings at +4, +8, +0xC and +0x14, with the list at +0x10. The extra Zero
Hour challenge-campaign fields are not added to this BFME view. EH handler
0x00C39627 / FuncInfo 0x00E28A24 independently supplies five unwind states
for those members in declaration order. The normal path destroys them in
reverse order after clearing the owned missions.

The bank redeclared AsciiString with an out-of-line destructor. Including
the repository's real `ascii_string.h` instead exposes its native inline
StringBase lifetime and changes the receiver register from EBP to the
retail EBX. No register forcing or compiler barrier is needed; the original
loop and all 186 bytes then match.

## Scoped list-base dependency

The only missing relocation was the native STLport
`_List_base<Mission*, allocator<Mission*> >` destructor. The retail call
at body +0x7A goes through ILT 0x00008FFD -> RVA 0x005BBC50. Independently
decoded, that entire 66-byte callee traverses 12-byte list nodes, frees
each through the node allocator, resets the sentinel links, and frees the
sentinel. Native compilation of this exact STLport specialization matches
all 66 bytes and both allocator calls. The Campaign header witnesses the
element type independently of that byte match.

One pin therefore names the actual body 0x005BBC50, with its called-via
route recorded. The existing opaque ledger row `tg_005bbc50` remains its
single source claim; its older list<int> object-symbol is a byte-equivalent
emitter, not evidence that Campaign's list holds integers. No second body
identity or claimed conversion is added for the dependency. Pin consistency
passes after the addition, and the full Campaign source gate resolves all
calls and its vtable reference.

No shared header, generated source, baseline, or assembly was changed.
