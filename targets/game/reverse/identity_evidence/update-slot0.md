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

## ProneUpdate::update (002A00F0, 27 bytes; initial deferral)

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

## Direct BFME label and WorldBuilder alignment

BFME1's ShareExperienceBehavior update table at RVA `00CA60A8` contains ILT
`00015F0F` -> `002058F0` in slot zero and the same disabled-mask ILT
`0004985F` -> `0011A130` in slot one. Body `002058F0` pushes literal VA
`010A61B0` at `0020591F`: the retail bytes spell exactly
`ShareExperienceBehavior::update`. Its registered constructor `00205740`
stores the table at +0x10 at `002057AD`; the stub pointer occurs exactly once.
This is a direct BFME spelling anchor, independently of the generated name.

Both WorldBuilders retain that function label as well. The following are
RVAs (both image bases are 00400000):

| Image | Constructor | +0x10 vptr store | Update table | Slot 0 body | Label | Slot 1 body |
|---|---|---|---|---|---|---|
| BFME2 Worldbuilder.exe | 00DB48E0 | 00DB493D | 01ADD45C | 00DB4AB0 | 01ADD55C | 0087E3A0 |
| RotWK Worldbuilder.exe | 00DC5ED0 | 00DC5F2D | 01B37BFC | 00DC60A0 | 01B37CFC | 008811D0 |

The label references are `00DB4AF9` and `00DC60E9` (PUSH instructions).
Each labeled body pointer occurs once. Both constructors store the behavior
interface at +0x0C using table addresses exactly 12 bytes after the update
table, so these update tables contain three slots. Their second slot copies
a four-byte disabled mask to a hidden caller output pointer, returns that
pointer, and ends `ret 4`; this agrees with BFME1's second slot and the Zero
Hour `getDisabledTypesToProcess() const` declaration. Thus **WB slot 0 maps
to BFME1 slot 0, and WB slot 1 maps to BFME1 slot 1**. The additional WB third
slot does not shift these two slots; no identity for that extra slot is
claimed. In all three images the labeled update returns 3fffffff with no
stack arguments. The ZH interface supplies the public virtual non-const
`UpdateSleepTime update()` signature; the family alignment supplies the
exact method spelling even for BFME-only owners.

## AODCrushCollide::update (00216100, 72 bytes)

The registry's literal `AODCrushCollide` at `00C8FC78`, registration site
`0012FBC6`, and instance factory `0011EC20` establish the owner independently.
The factory calls ILT `0000F7DB` -> constructor `00215C50`; its final store
at `00215C9D` installs table VA `010A99F0` at complete-object +0x10.
Slot zero is ILT `00048400` -> body `00216100`, and slot one is the common
`0004985F` disabled-mask accessor. The slot-zero stub pointer occurs exactly
once, at table RVA `00CA99F0`. Therefore this is the same update family as
the directly labeled ShareExperienceBehavior table, with a distinct override.

The body tests a byte at interface +1C, compares a frame at +14, conditionally
clears Object+114 bit 100 and calls the already typed
`Object::notifyModelConditionChanged` through ILT `0002191D` -> `001BE1C0`.
It returns 1 on the active path and 3fffffff on the inactive path, ending at
`00216148` exclusive (RET at `00216147`, then INT3). The earlier RET at
`00216140` is not the end of the body. No stack arguments are consumed.

Replace the opaque `Rva00216100TimedCondition::update00216100` row with
`?update@AODCrushCollide@@UAE?AW4UpdateSleepTime@@XZ`. Preserve the existing
address-kept state view and its field spellings; this correction claims no
new field identities. A TU-scoped declaration describes the incoming update
interface receiver, not the complete object's layout. Include the surviving
UpdateModule header for its actual return type rather than inventing an enum.

## ShareExperienceBehavior::update (002058F0, 72 bytes)

In addition to the literal/slot proof above, the registered module literal
`ShareExperienceBehavior` at `00C904BC`, registration `0012E56B`, and factory
`00116BF0` identify the owner. The factory call at `00116C2B` uses ILT
`0001C3FF` -> constructor `00205740`. Its final +0x10 store at `002057AD`
installs table `00CA60A8`, and the sole absolute occurrence of slot-zero
stub VA `00415F0F` is that table entry. This is a distinct concrete override,
not a shared inherited body. Both WorldBuilder labels independently give the
same class and method spelling at the aligned slot (see the table above).

The 72-byte retail function conditionally emits a diagnostic carrying its
own `ShareExperienceBehavior::update` label, then returns 3fffffff. Its RET
at `00205937` is followed by INT3. It does not consume arguments or use the
incoming receiver; the old free-function reconstruction's byte match could
therefore not distinguish its calling convention. The interface supplies
public virtual non-const `UpdateSleepTime update()`, mangled
`?update@ShareExperienceBehavior@@UAE?AW4UpdateSleepTime@@XZ`.

Keep the existing diagnostic interface views and literal. Use the named
callees printed by callees.py: `_bfme_debugReportingEnabled` at `008896D0`
and `_bfme_debugRecordCallsite(int)` at `008896A0`. These are already matched;
no helper pin is added. Move only this method from BfmeConv1362.cpp into the
owner's Behavior TU; other functions still need that Common file and its
local diagnostic declarations.

## ClickReactionBehavior::update (001F79F0, 96 bytes)

Registered literal `ClickReactionBehavior` at `00C90CC0` and registration
`0012C722` select instance factory `00114CF0`. Its call at `00114D2B` uses
ILT `00025D01` -> constructor `001F7860`. The constructor replaces the base
update table with VA `010A32F8` at +0x10 (store `001F78CA`), alongside its
behavior table at +0x0C and additional subobject at +0x20.

Update table slot zero is ILT `00005E66` -> body `001F79F0`. That stub VA
occurs exactly once, at table RVA `00CA32F8`; slot one is the same common
`0004985F` -> `0011A130` disabled-mask accessor. Thus the direct BFME label
and both WorldBuilder alignments above apply without shifting either slot.
The body belongs to this concrete override rather than an inherited method.

There are no direct callees. Retail calls three existing virtual interfaces,
reads two counters at receiver +14/+18, and returns 1 or 3fffffff. The final
RET at `001F7A4F` ends the 96-byte body; INT3 starts at `001F7A50`. The first
RET at `001F7A48` is an early exit. No stack arguments are consumed.
The proven family signature is public virtual non-const
`UpdateSleepTime update()`, `?update@ClickReactionBehavior@@UAE?AW4UpdateSleepTime@@XZ`.

The replacement preserves the existing reconstruction and virtual-slot views,
giving unproven view types address-kept names. Existing opaque field and slot
spellings are retained; no identities for those slots or fields are claimed.
Only this update and its local views leave BfmeTwoHundredTwentyEight.cpp;
the unrelated matched add function remains in that Common source.

### ClickReaction view-name correction records

The removed `BfmeThingLJ` was an update-subobject layout view, not the actual
owner: the registered constructor and unique table prove that owner is
ClickReactionBehavior. The checker pairs that removed layout with the new
`Rva001F79F0State` view instead of with the new class declaring the recovered
method. The correction record disambiguates this pairing.

The other three old `Bfme...LJ` types were local indirect-call views, containing
unnamed spare virtual slots. Their only uses in this body are the object
pointer at receiver-8, that object's +204 pointer, and the module subobject
at receiver+10. No type identity was established for these invented spellings.
The new address-kept Host/Maker/Sub views preserve exactly those same fields
and virtual slots, without promoting the structural role to an EA identity.
The snapshot-specific correction entries cover these view renames only;
they do not exempt any future layout or identity change.

## PartTheHeavensUpdate::update (00299D30, 56 bytes)

Registered literal `PartTheHeavensUpdate` at `00C9060C`, registration
`0012DF92`, and instance factory `0011C530` independently identify the owner.
The factory call at `0011C56B` uses ILT `00024EC9` -> constructor `002999D0`.
Its final +0x10 store at `00299A10` installs table VA `010C0718`. Slot zero
is ILT `00032E5C` -> `00299D30`; that stub VA occurs exactly once, at table
RVA `00CC0718`. Slot one is common `0004985F` -> `0011A130`, so the direct
BFME spelling and the WB 0->0 update-family alignment above apply.

The body receives the +0x10 update subobject, tests its module-data pointer
at receiver-C, subtracts the timestamp at receiver+10 from the game frame,
and calls two existing primary-receiver helpers with ECX adjusted by -10.
It returns 3fffffff at early RET `00299D40` or 1 at final RET `00299D67`;
INT3 starts at `00299D68`, proving 56 bytes and no stack arguments.
The signature is public virtual non-const `UpdateSleepTime update()`,
`?update@PartTheHeavensUpdate@@UAE?AW4UpdateSleepTime@@XZ`.

Callee `000076E9` -> `00299BB0` already has the matched address-derived
`DecalCreate00299BB0::create()` identity (nonvirtual void thiscall, no stack
arguments). Use it rather than the old bfmeResetFV pin alias. Callee
`0003BDD6` -> `00299A80` remains the matched
`BfmePrimaryFV::bfmeAdvanceFV(int)` body in the original Common source;
its opaque name and typed ABI are retained without inventing a method name.
No new pin is required. Preserve the prior field-view spellings and receiver
arithmetic; only the update owner, virtual status, return type, and first
callee's existing ledger spelling change.

## SiegeDockingBehavior::update (00207260, 41 bytes)

Registered literal `SiegeDockingBehavior` at `00C90CA4`, registration
`0012C77A`, and instance factory `00114E00` establish the owner. The factory
call at `00114E3B` uses ILT `00004D36` -> constructor `002062C0`; its final
+0x10 vptr store at `0020631E` installs VA `010A6280`.
The only absolute pointer to slot-zero ILT `00043E5A` -> body `00207260`
is at table RVA `00CA6280`. Slot one is common `0004985F` -> `0011A130`,
establishing the same directly labeled and WB-aligned update family.

Retail tests a byte at update receiver+20, calls a primary-receiver helper
with ECX adjusted by -10, sets the byte on the first path, and returns 5 on
both paths. RETs occur at `0020727C` and final `00207288`; INT3 starts at
`00207289`, proving 41 bytes with no stack arguments. The return is
`UPDATE_SLEEP(5)` under the public virtual non-const UpdateSleepTime update
interface, not a guessed integer callback.

The two existing matched callees are `SiegeDockingBehavior::initializeBones00206CB0`
(ILT `0000F966` -> `00206CB0`, 657 bytes) and
`BfmeHostERP::bfmeSweepERP` (ILT `0001011D` -> `00206460`, 220 bytes).
Both retain their current void-thiscall, no-stack-argument declarations.
Use these ledger spellings instead of the old bfmeOneCFD/bfmeTwoCFD pin
aliases; the second helper's historical method identity is still unclaimed.
No new pins or field names are needed. Replace only the old update row and
remove its now-orphaned Common TU after exact verification.

## WeaponModeSpecialPowerUpdate::update (002B2DE0, 97 bytes)

Registered literal `WeaponModeSpecialPowerUpdate` at `00C90424`, registration
`0012E76E`, and factory `00119670` identify the owner. The factory's call at
`001196AB` uses ILT `00001C53` -> constructor `002B2BD0`; final store
`002B2C1C` puts table VA `010C540C` at +0x10. The only absolute pointer to
slot-zero ILT `00015EB0` -> `002B2DE0` is at table RVA `00CC540C`. Slot one
is common `0004985F` -> `0011A130`, independently anchoring this body to the
labeled/aligned update family, not merely to its earlier source filename.

The body loops over 29 mask bits, calls existing object-side helpers, invokes
an additional secondary interface slot, and returns 3fffffff. Its final RET
at `002B2E40` and INT3 at `002B2E41` establish the 97-byte extent. Incoming
ECX is complete-object +10; there are no stack arguments. Replace the
address-kept owner and enum with public virtual non-const
`?update@WeaponModeSpecialPowerUpdate@@UAE?AW4UpdateSleepTime@@XZ`.
The unrelated secondary-interface view at receiver+14 remains address-kept;
its slot spelling is not promoted to a recovered identity.

Direct callee routes were independently decoded:

- `00007513` -> `001C9B80` takes one four-byte integer argument (ret 4),
  forwards it to interface slot +158 and to WeaponSet::releaseWeaponLock
  through `0001192D` at Object+264; it never dereferences that argument.
  Retain the pre-existing `BfmeItem1005::bfmeDoD1005(int)` pin/declaration.
  The other matched reconstruction's synthetic void-pointer prototype is
  not used as a reason to cast the caller's literal 2 to a pointer.
- `000122AB` -> `001C9AC0` is matched `Gen001C9AC0::handle(int)`; use its
  existing address-derived name in place of actionB's alias.
- `0001EF9C` -> `001C1E30` is matched
  `BfmeOwnerXI::bfmeSendXI(BfmeMsgXI*)`; retain its opaque message-view ABI
  instead of the old void-pointer alias.

No new pin, field identity, or callee historical method name is asserted.
Only this verified update moves to the owner's TU; the old one-body TU is
removed after verification.

The snapshot-specific BfmeObjE10 -> Gen001C9AC0 correction records an alias
replacement, not a loss of an EA class identity. The old actionB symbol is
pinned only to ILT `000122AB`; independently resolving that E9 reaches the
existing matched `Gen001C9AC0::handle(int)` row at `001C9AC0`. Both use a
nonvirtual thiscall with one integer argument. The updated caller uses that
same existing body directly; neither spelling proves a historical class name.

## ProneUpdate helper access correction (002A0030 / 002A0090)

The earlier ProneUpdate deferral identified a concrete declaration defect,
not a code-generation mismatch. The surviving GeneralsMD ProneUpdate.h puts
both `startProneEffects()` and `stopProneEffects()` below `protected:`.
They are nonvirtual, non-const, void methods with no arguments; the correct
MSVC 7.1 suffix is `IAEXXZ`, not the local shim's former `AAEXXZ`.

Independent callers fix the methods to their retail bodies:

- Matched `ProneUpdate::goProne` at `002A0120` calls ILT `00042884` at
  `002A0161` -> `002A0030` on entering prone state, exactly as its ZH twin.
  This 73-byte helper sets the prone model-condition bit and no-attack status,
  ending with RET `002A0078` and INT3 at `002A0079`.
- The registered, unique ProneUpdate update-slot body `002A00F0` calls
  ILT `0004908F` at `002A0100` -> `002A0090` when the counter reaches zero,
  exactly where the ZH update calls `stopProneEffects`. This 75-byte helper
  clears the same condition/status and ends RET `002A00DA`, then INT3.

Both existing sources already reproduce those bodies. Their only direct
callees are `Object::notifyModelConditionChanged` via `0002191D` -> `001BE1C0`
and `Object::setStatus` via `000307E7` -> `001C7370`, and remain unchanged.
Correct the helper declarations and ledger access mangling, and update the
start-helper declaration in the goProne caller. No shared header, helper body,
field offset, or pin changes. Verify each helper independently at its original
extent; the pair is one small set/clear-pattern declaration batch.

## ProneUpdate update replacement after the helper repair

With both protected effect-helper declarations corrected and independently
verified, the earlier access blocker is resolved. The update replacement uses
the surviving ProneUpdate.h and explicitly includes the existing game
UpdateModule.h before it. No header is modified. This combination has update
receiver +14 and m_proneFrames +24, while retail has receiver +10 and field +20.
The receiver-relative field displacement is +10 in both layouts; the primary
helper receiver requires an explicit four-byte correction in this TU.

The ordinary ZH countdown body accesses the proven m_proneFrames field and
calls the corrected protected stopProneEffects. The explicit receiver
adjustment compiles to retail's add ecx,-10 rather than the mixed headers'
uncorrected -14. Name_oracle and constructor store 0029FEB4 independently prove
the retail field at complete-object +20. This is a scoped layout accommodation,
not a claim that the cross-game headers describe the complete BFME class.

Replace the earlier opaque row at its unchanged 27-byte extent with
`?update@ProneUpdate@@UAE?AW4UpdateSleepTime@@XZ` and remove the now-orphaned
BfmeConv496.cpp. This completes the historical evidence-only deferral, with
no duplicate alias or new pin.

## DelayedWeaponSetUpgradeUpdate update (0028C260)

Registry literal `DelayedWeaponSetUpgradeUpdate` at `00C90794`, registration
`0012DA6A`, factory `00117DC0`, and its call `00117DFB` through `0003006C`
identify constructor `0028C2D0`. Its final store at `0028C316` installs table
VA `010BD468` at complete-object +10. Slot zero is the sole absolute pointer
to ILT `00006F0A` -> `0028C260`; slot one is the established common
`0004985F` -> `0011A130`. Thus the labeled/aligned update-family prefix
proves `DelayedWeaponSetUpgradeUpdate::update`, public virtual non-const,
returning the four-byte UpdateSleepTime enum with no arguments.

The full body is `mov eax,1; ret`, six bytes, with RET at `0028C265` followed
by INT3. It accesses no receiver fields and has no callees; use the existing
UpdateModule.h enum and UPDATE_SLEEP_NONE. The former anonymous row was only
an alias to CommandLine.cpp's unrelated parseNoLogOrCrash constant body.
Replace that row with a dedicated owner TU; retain CommandLine.cpp for its
actual command-line functions. No field, callee name, or inherited identity
is inferred from the constant value. No shared header or pin changes.

## ContestableContain update (0021D4A0)

Registered literal `ContestableContain` at `00C90A18`, registration `0012D126`,
and factory `001165C0` (call `001165FE` via ILT `00033D48`) identify constructor
`0021BEE0`. Its final +10 vptr store at `0021BF1E` installs VA `010AB2E8`.
Slot zero uniquely contains ILT `000192D6` -> `0021D4A0`; slot one contains
the common `0004985F` -> `0011A130`. The proven labeled/aligned update family
therefore fixes this as public virtual non-const `ContestableContain::update`,
returning UpdateSleepTime. The body is a distinct override, not its inherited
GarrisonContain implementation. RETs at `0021D4EB` and `0021D4F8`, followed by
INT3 at `0021D4F9`, bound its 89 bytes.

The constructor calls at `0021BF0A` via `00037FAB` -> `00248F90`, the matched
HordeGarrisonContain constructor; that constructor calls at `00248FB9` via
`0001934E` -> `0021D820`, the matched GarrisonContain constructor. The new TU
preserves this inheritance chain as storage-free declaration views above the
real GarrisonContain header; no complete BFME derived layout is asserted.

Replace untyped thunk casts with the existing callee declarations:

- `0001B8C4` -> `0021F920`, matched GarrisonContain::update, receives the
  unchanged update-interface ECX and returns the four-byte enum. Its 158-byte
  interval ends at RET `0021F9BD` then INT3.
- `0002F919` -> `0021BCA0`, existing ContestableContain::updateContestStatus,
  receives complete-object ECX (update receiver -10). Its 92-byte interval
  ends at RET `0021BCFB` then INT3; no stack arguments.
- `000480CC` -> `0021D180`, existing opaque Rva0021D180::body, also receives
  complete-object ECX, has no stack arguments, and ends at RET `0021D2F6`
  then INT3 after 375 bytes. No historical helper name is proposed.

The headers' +14 update receiver is handled explicitly when reconstructing
retail primary pointers; raw list/cache offsets remain unchanged relative
to the incoming interface receiver. The secondary predicate retains its
address-derived view and receives no new semantic name. Exact verification
covers the replacement's complete 89-byte extent with no new pins or header
edits. Remove only the superseded one-body Rva0021D4A0ContestableState.cpp.
