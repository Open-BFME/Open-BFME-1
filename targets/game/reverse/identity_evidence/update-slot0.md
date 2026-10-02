# UpdateModuleInterface slot 0: constant-return overrides

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
