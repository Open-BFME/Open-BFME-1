# UpdateModuleInterface slot 0: update overrides

Image: `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`,
SHA-256 `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Addresses in the following tables are RVAs. Add image base `0x00400000`
to obtain VAs. Read with pefile and Capstone, independently of ledger names.

## Slot and owner evidence

`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` declares
`UpdateModuleInterface::update()` first and `getDisabledTypesToProcess() const`
second. The first returns `UpdateSleepTime`; both are public virtuals.
The surviving per-class twins are in the same upstream tree:

- `AssistedTargetingUpdate.h:72` and
  `Source/GameLogic/Object/Update/AssistedTargetingUpdate.cpp:145` declare and
  define `update`. BFME removes the two laser-template lookups and returns
  `UPDATE_SLEEP_FOREVER` directly.
- `DefaultProductionExitUpdate.h:97`, `SpawnPointProductionExitUpdate.h:88`,
  and `SupplyCenterProductionExitUpdate.h:94` each define their own inline
  public virtual `update()` returning `UPDATE_SLEEP_FOREVER`.

Mechanically enumerating registered constructors' final constant vptr stores
at object offset `+0x10`, then resolving both entries through their `E9 rel32`
stubs, finds the tables below. Every second entry is the **same** stub RVA
`0004985F` -> body `0011A130`, UpdateModule's hidden-buffer-return disabled
mask accessor. Each first-entry stub occurs as an absolute pointer exactly
once in the mapped image, at its listed table. There is no shared/inherited
first-entry body in this batch. The constructors first install base table VA
`0109CBA0` at `+0x10`, then replace it with their class's table.

| Owner | Constructor | Final +0x10 store | Update table | Slot 0 ILT | Slot 0 body |
|---|---|---|---|---|---|
| AssistedTargetingUpdate | 0027FB60 | 0027FBC6 | 00CBAC00 | 0003901D | 0027FB10 |
| DefaultProductionExitUpdate | 002CFD40 | 002CFD9E | 00CCB544 | 000168F6 | 002CFE40 |
| SpawnPointProductionExitUpdate | 002D1480 | 002D14F6 | 00CCB7DC | 0002B85A | 002D1700 |
| SupplyCenterProductionExitUpdate | 002D22F0 | 002D234E | 00CCB920 | 00040395 | 002D23F0 |

Owner identification is independent of destructor labels: the module registry
links these literal names to factories and constructors. The registry's sites
are directly checkable in retail:

| Owner | Registration site | Name literal | Instance factory |
|---|---|---|---|
| AssistedTargetingUpdate | 0012D8B2 | 00C9080C | 00117C40 |
| DefaultProductionExitUpdate | 0012E996 | 00C902E0 | 00117D40 |
| SpawnPointProductionExitUpdate | 0012E9D3 | 00C902B8 | 0011B470 |
| SupplyCenterProductionExitUpdate | 0012EB07 | 00C90234 | 0011B7E0 |

The instance factories call constructor ILTs `0000BAF0`, `00025581`,
`00023858`, and `00027B06`, respectively; each resolves to the listed
constructor. AssistedTargeting's registration writes factory ILT VA
`00427D54` at RVA `0012D8EA`. The other three registrations push factory
ILTs `00045822`, `00035427`, and `000333DE`, which resolve to the listed
instance factories. Thus neither body shape nor a ledger destructor supplies
the class name.

## Boundary, ABI, and correction

Each of the four bodies is exactly `B8 FF FF FF 3F C3` (6 bytes), followed by
INT3 padding. It returns the 32-bit `UpdateSleepTime` value `0x3fffffff`,
accepts no stack arguments, and does not access the receiver. The independently
proven virtual, public, non-const method signature is
`?update@<Owner>@@UAE?AW4UpdateSleepTime@@XZ`.

The old AssistedTargeting/SupplyCenter rows are generated integer-return shims.
The Default/SpawnPoint rows are anonymous aliases to a free constant-return
function; those rows identify no owner or method. Replace the generated rows
and correct the two aliases to the independently proven class methods. Keep
the old common constant source because other rows still use it. No member or
field identities are inferred from the constant-return byte match.

## DeletionUpdate::update (0028C740, 21 bytes)

The registry names `DeletionUpdate` at literal RVA `00C90780`, registered at
`0012DAC2`. Its instance factory `00117EF0` calls ILT `00016C52` -> constructor
`0028C520`. At `0028C583` that constructor stores table VA `010BD5C8` at
`[esi+0x10]`, replacing the base update table. Slot zero is ILT `0003466C` ->
body `0028C740`, and slot one is the common `0004985F` disabled-mask accessor.
The slot-zero stub VA occurs exactly once as an absolute pointer in the image,
at table RVA `00CBD5C8`. This proves the concrete override owner.

`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DeletionUpdate.h:80`
explicitly declares the public non-const virtual `UpdateSleepTime update()`.
The release twin in `Source/GameLogic/Object/Update/DeletionUpdate.cpp:104`
calls `TheGameLogic->destroyObject(getObject())` and returns
`UPDATE_SLEEP_FOREVER`. Retail does precisely that:

```
0028C740  mov eax,[ecx-8]
0028C743  mov ecx,[012F0898]
0028C749  push eax
0028C74A  call 0041D0DE
0028C74F  mov eax,3FFFFFFF
0028C754  ret
```

Incoming ECX is the update subobject at complete-object +0x10, so ECX-8 is
ObjectModule's object pointer at complete-object +8. ILT `0001D0DE` reaches
the independently matched 190-byte `GameLogic::destroyObject(Object*)` body
`0038B0C0`; its existing typed declaration and pin suffice. No pin is added.
The RET ends the 21-byte body and INT3 follows. The old
`BfmeThing940E::bfmeGo940E` opaque reconstruction has the same behavior but
no recovered identity and an integer return type. Replace it with
`?update@DeletionUpdate@@UAE?AW4UpdateSleepTime@@XZ` in DeletionUpdate.cpp,
using the real headers, and remove the old orphaned local-view implementation.

## ProneUpdate::update (002A00F0, 27 bytes; rename deferred)

The literal at `00C901B4` is `ProneUpdate`; registration `0012ECEF` selects
instance factory `0011AD30`. Its call at `0011AD6B` uses constructor ILT
`000425DC` -> `0029FE70`. The constructor's final +0x10 store at `0029FEAD`
installs table VA `010C1324`. Slot zero is ILT `0002701B` -> `002A00F0`,
whose stub pointer occurs exactly once, at table RVA `00CC1324`. Slot one is
the common disabled-mask ILT `0004985F` -> `0011A130`.

`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProneUpdate.h` declares
public virtual non-const `UpdateSleepTime update()`; its source twin at
`Source/GameLogic/Object/Update/ProneUpdate.cpp:78` decrements positive
`m_proneFrames`, calls `stopProneEffects` only on reaching zero, and returns
`UPDATE_SLEEP_NONE` (1). Retail reads the count at interface ECX+0x10
(complete-object +0x20, independently witnessed by name_oracle), adjusts ECX
by -0x10 for the nonvirtual effect-helper call, and returns 1. The RET at
`002A010A` ends the 27-byte body; INT3 begins at `002A010B`.

The only callee, ILT `0004908F` -> `002A0090`, is the matched
`ProneUpdate::stopProneEffects`. Its current source and ledger incorrectly
use a private (`AAE`) declaration, while the Zero Hour header declares both
`startProneEffects` and `stopProneEffects` protected (`IAE`). A rename using
the real header therefore needs a coordinated callee-declaration repair.
The shared helper TU emits both methods, and `goProne` also declares the
start helper private. Do not add a second identity or an alias pin merely
to bypass these declarations. The current update placeholder is untouched;
this section records its independently proven identity and the remaining
repair, not a newly verified conversion. No candidate source was written.
