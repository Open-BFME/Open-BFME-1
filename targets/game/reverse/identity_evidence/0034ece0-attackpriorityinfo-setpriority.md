# 0x0034ECE0 - AttackPriorityInfo::setPriority

## Identity

The body is `AttackPriorityInfo::setPriority(const ThingTemplate *, Int)`.

Evidence:

1. **ILT pin.** `targets/game/reverse/symbols.csv` carries
   `?setPriority@AttackPriorityInfo@@QAEXPBVThingTemplate@@H@Z,0x0001600E,
   Open-BFME5 ILT to AttackPriorityInfo::setPriority body 0x0034ECE0`.
   `tools/pin_consistency.py --symbol
   '?setPriority@AttackPriorityInfo@@QAEXPBVThingTemplate@@H@Z'` resolves
   `0x0001600E -> 0x0034ECE0 extent=146` and reports `verdict: consistent`.
   The ILT is a real named reference, not a generated pin.

2. **Matched callers name the method and the signature.** Five call sites
   reach this body, all through an ILT thunk:

   - `?Rva0033e040@ScriptEngine@@IAEXPAVScriptAction@@@Z`
     (`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineSetPriorityThing.cpp`)
     twice, as `info->setPriority(thingTemplate, action->getParameter(2)->getInt())`;
   - `?getAttackInfo@ScriptEngine@@QAEPBVAttackPriorityInfo@@ABVAs`
     (`ScriptEngineAttackInfo.cpp`) once;
   - `?setPriorityKind@ScriptEngine@@QAEXPAVScriptAction@@@Z`
     (`ScriptEngineSetPriorityKind.cpp`) once;
   - `?xfer@AttackPriorityInfo@@MAEXPAVXfer@@@Z`
     (`AttackPriorityInfoXfer.cpp`) once, as `setPriority(thingTemplate, priority)`.

   `AttackPriorityInfoXfer.cpp` is a byte-matched landed body
   (0x0034EDA0) that declares
   `void setPriority(const ThingTemplate *thing, Int priority);` and calls
   `setPriority(thingTemplate, priority)` with exactly two arguments. That
   fixes the arity at two and the second argument as `Int`; `ret 8` in this
   body confirms the two stack arguments.

3. **Zero Hour twin.** `inputs/reference/CnC_Generals_Zero_Hour/Generals/Code/
   GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine.cpp:168` is EA's
   own `AttackPriorityInfo::setPriority`, with the same signature, the same
   `if (tThing==NULL) return;` guard, the same lazy
   `m_priorityMap = NEW AttackPriorityMap;`, and the same
   `(*m_priorityMap)[tThing] = priority` tail. This is the source the shape
   below reconstructs.

## Body shape

The 146 bytes decode as:

```
mov  eax, fs:[0]            ; SEH prologue, fs read FIRST
push -1
push 0x010190BB             ; scope-table handler
push eax
mov  fs:[0], esp
push esi
push edi
mov  edi, [esp+0x18]        ; the `thing` parameter, enregistered in EDI
test edi, edi
mov  esi, ecx               ; `this`
je   end                    ; if (thing == 0) return;
mov  eax, [esi+0xc]         ; m_priorityMap
test eax, eax
jne  0x58                   ; already allocated
push 0xc
call operator new           ; new AttackPriorityMap  (size 0xc)
add  esp, 4
mov  [esp+0x18], eax        ; park the raw pointer in the dead argument home
test eax, eax
mov  [esp+0x10], 0          ; EH state store #1
je   0x4b
mov  ecx, eax
call 0x000E9C30             ; AttackPriorityMap::AttackPriorityMap
jmp  0x4d
0x4b: xor eax, eax
0x4d: mov [esp+0x10], -1    ; EH state reset to -1
0x55: mov [esi+0xc], eax    ; m_priorityMap = ptr
0x58: mov ecx, [edi+4]      ; thing->m_nextOverride  (Overridable *+4)
test ecx, ecx
je   0x66
call 0x00087A80             ; Overridable::getFinalOverride
jmp  0x68
0x66: mov eax, edi          ; else arm: the key stays `thing`
0x68: mov ecx, [esi+0xc]    ; m_priorityMap
0x6b: mov [esp+0x18], eax   ; resolved key into the argument home slot
0x6f: lea eax, [esp+0x18]   ; &key
0x73: push eax
call 0x000EA510             ; std::map<ThingTemplate*,Int>::operator[]
mov  ecx, [esp+0x1c]        ; the `priority` argument
mov  [eax], ecx             ; *slot = priority
end:  mov ecx, [esp+0x8]
pop  edi
mov  fs:[0], ecx
pop  esi
add  esp, 0xc
ret  8
```

Three facts about this shape drive the source reconstruction, and each was
a separate blocker in earlier attempts:

1. **The `thing` parameter is never assigned.** It is loaded once into EDI
   and stays there. Every source variant that writes back to the parameter
   (`thing = ...`) makes MSVC treat it as a memory variable, which costs a
   `push ecx` frame slot and, per `docs/shape_levers.md`, flips the SEH
   prologue to the `push -1 / push handler / mov eax,fs:[0]` form. The
   reconstruction keeps the parameter read-only and introduces a separate
   block-scoped `key`.

2. **The key variable lives in the DEAD argument home slot `[esp+0x18]`.**
   Once EDI holds `thing`, its incoming stack home is free and MSVC reuses
   it for both the new-expression pointer and the resolved key. Declaring
   `key` at function scope instead costs a real frame slot; declaring it in
   its own `{ }` block after the allocation reproduces the reuse.

3. **The `?: ` result is phi-merged into EAX and stored once**, after the
   `mov ecx, [esi+0xc]` map reload. Every `if (n) key = ...; key = thing;`
   spelling stores twice instead and is 2 bytes long at 148. The temporary's
   type is what buys the phi: typed `const ThingTemplate *` (the map's own key
   type) MSVC stores the ternary result into the address-taken slot in EACH
   arm -- `mov [esp+0x18], eax / jmp / mov [esp+0x18], edi` -- because that is
   already the type the slot will hold. Typed at the base (`const void *`,
   cast to `const ThingTemplate *` only at the subscript) the value can stay
   in a register across the branch, and retail's four-instruction phi appears
   verbatim. This was the 14-byte residue of the previous 0.9041 bank.

## Callee ABI

Every name below is a name the compiled object actually emits, so the
rel32 slots resolve to the retail addresses instead of compiling to a zero
displacement. This was the last thing standing between this body and a byte
match: with a merely-declared callee of the wrong shape the body still
compiled to 146 exact bytes, but two relocations stayed at zero and the gate
refused it as `unresolved call(s)`.

- `0x00881F30` `??2@YAPAXI@Z` -- `operator new(unsigned int)`, size 0xc.
- `0x0000C928` `??0?$map@PBVThingTemplate@@HU?$less@PBVThingTemplate@@@_STL@@
  V?$allocator@U?$pair@QBVThingTemplate@@H@_STL@@@3@@_STL@@QAE@XZ` --
  `AttackPriorityMap::AttackPriorityMap()`, i.e. the map default constructor.
  `0x0000C928` is a 5-byte `E9` stub; `tools/pin_consistency.py --check` resolves
  it to `0x000E9C30`, a matched 54-byte row (`tg_000e9c30`) that allocates the
  0x18-byte `_Rb_tree` header and threads its three self/null links -- the
  shape of an empty STLport map. `__thiscall`, 0 stack slots, `void` result
  (the caller's `xor eax, eax` / `mov [esp+0x10], -1` pair is the null-check
  and EH-state reset around it).
  Two independent confirmations that this is the right name at this address:
  a full-image scan finds exactly ONE `E9` reaching `0x000E9C30`, and it is
  this stub; and `targets/game/reverse/dir32_addresses.csv:128` already
  records the same mangled name at VA `0x0040C928`, whose pin count rises
  3168 -> 3169 in `pin_consistency --check` when this row is added. The
  mangled name was read out of the compiled object, never out of the target.
- `0x000022BB` `?getFinalOverride@Overridable@@QBEPBV1@XZ` --
  `Overridable::getFinalOverride()`, already pinned (no new row needed).
  `__thiscall`, 0 stack slots, returns the resolved `const Overridable *` in
  EAX. **The declared return type is load-bearing**: `const Overridable *`
  mangles to `QBEPBV1@XZ` and hits that pin, while the also-reasonable
  `const void *` mangles to `QBEPBXXZ`, which no pin carries, and the
  relocation then compiles to zero. The method is declared and never
  defined in this TU, so the vendored `Common/Overridable.h:61` inline
  cannot unroll the recursive walk into the body.
- `0x00017111` `??A?$map@PBVThingTemplate@@HU?$less@PBVThingTemplate@@@_STL@@
  V?$allocator@U?$pair@QBVThingTemplate@@H@_STL@@@3@@_STL@@
  QAEAAHABQBVThingTemplate@@@Z` -- `std::map<const ThingTemplate *, Int>::operator[]`,
  `__thiscall`, 1 stack slot (the `const ThingTemplate *const &` key), returns
  `Int *` in EAX. Already pinned at 0x00017111 (E9 stub -> `dup_ea510` at
  0x000EA510).

## Class layout used

`AttackPriorityInfo` is `AsciiString m_name; Int m_defaultPriority;
AttackPriorityMap *m_priorityMap;` so `m_priorityMap` is at +0xc, matching
the `mov eax, [esi+0xc]` in the body and the `char m_prefix[0x0c]` shim
used in `AttackPriorityInfoXfer.cpp`.

`ThingTemplate` derives from `Overridable` whose `m_nextOverride` is at +4,
matching `mov ecx, [edi+4]`.
