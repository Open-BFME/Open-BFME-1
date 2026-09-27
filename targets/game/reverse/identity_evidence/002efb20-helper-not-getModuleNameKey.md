# 0x002EFB20: the FlammableUpdate getModuleNameKey lift name is refuted

The 146-byte body at 0x002EFB20 was carried as
`?getModuleNameKey@FlammableUpdate@@UBE?AW4NameKeyType@@XZ` by a
`__declspec(naked)` `__emit` copy of retail. That decoration is wrong in four
independent ways, so the conversion lands the body under the address-keyed name
the house convention uses for a free function of unknown owner.

## The decoration is refuted

1. **It is not virtual.** `python3 tools/vtable_lookup.py --target 0x2EFB20`
   reports that no installed vtable reaches this body within the slot cap, so
   no vtable slot names it. `Module::getModuleNameKey` is virtual (the
   `MAKE_STANDARD_MODULE_MACRO` in `game/GameEngine/Include/Common/Module.h:143`
   declares it `virtual`, and every other module class has its own vtable slot:
   the 185 `?getModuleNameKey@...` rows are all vtable targets).
2. **It is not thiscall, and not zero-argument.** Both callers push two explicit
   stack arguments and clean them afterwards, and the body reads the object
   from `[entry_esp+4]` (`mov ecx, [esp+0x10]` at +0054, where the SEH frame
   accounts for the 12-byte offset) and the flag from `[entry_esp+8]`
   (`mov al, [esp+0x14]` at +0064, read as a byte). `ecx` is dead at entry: it
   is overwritten by `mov ecx, [0x12ed600]` at +002A before the first call.
   - 0x002EFBE0 `?bfmeLookupAndExecFBE@@YGXPAX0@Z` (`BfmeConv827.cpp`), whose
     call at +001A is `push ecx; push eax; call; add esp,8; ret 8`.
   - 0x002F5100 `?d_002f5100@ScriptActions@@IAEXABVAsciiString@@_N@Z`
     (`ScriptActionsTeamScriptStatus.cpp`), whose call at +0040 is
     `push eax; push esi; call; add esp,8`, where `[esp+0x1c]` is that
     method's `Bool` parameter.
3. **The return type is void, not `NameKeyType`.** None of the three exits
   (+0071, +0084 and the `je` at +0062 that lands on +0084) loads the
   function-local static into `eax`; each returns whatever the last `void`
   call left there. A `NameKeyType` return would reload the static on every
   path, as the 104-byte `getModuleNameKey` bodies do at +0058.
4. **The extra 42 bytes are not part of a name-key getter.** The 104-byte
   `?getModuleNameKey@...` bodies (all in
   `game/GameEngine/Source/Common/Thing/ModuleNameKeys_*.cpp`, all matched)
   end with the static's `return nk`. These 42 bytes call `findModule` on the
   object and then one of two `void` members on its result.

The two callers, not the lift, are the only evidence for the name, and both are
address-keyed or shim names themselves; neither names this body.

## What the body does

A function-local `static NameKeyType` is initialised once from
`TheNameKeyGenerator->nameToKey("FlammableUpdate")` -- the identical prologue
and EH shape of the 185 matched `getModuleNameKey` bodies, plus the
`mov [esp+8], -1` state reset that appears only when a throwing call follows
the initialisation. The static is then passed to `Object::findModule` on the
object, and on a non-null result the flag picks between two `void` members
called on the same pointer: `FlammableUpdate::tryToIgnite` (flag set, reached
through ILT thunk 0x000322D6) and the flame-cleanup `apply` at 0x00293E50
(reached through thunk 0x0002F360, the already-matched clean-C++ body
`FlameCleanup00293E50.cpp`). No class or method name is claimed for the
function itself: `?helper@Rva002EFB20@@YAXPAX_N@Z`.

## Calibration

The boundary is exact: the body runs from +0000 to the `ret` at +0091
(146 bytes) and 0x002EFC66 onwards is `int3` padding, so the claimed extent
is right and no `--boundary-evidence` is needed. The `findModule` callee keeps
the shim spelling the verified sibling `FlameCleanup00293E50.cpp` already
uses, so it encodes the same thunk 0x0002AE23, and no new pin is added.
`python3 tools/pin_consistency.py --symbol '?bfmeHelperB20@@YAXPAX0@Z'` was
`consistent` before the change and is unchanged by it: that pin keeps naming
this address for the two callers' declarations, which is its only job.
