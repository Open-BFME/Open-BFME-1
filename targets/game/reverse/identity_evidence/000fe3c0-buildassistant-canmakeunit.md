# BuildAssistant::canMakeUnit at 0x000FE3C0 (identity only)

The 411-byte body at 0x000FE3C0 is still the generated dump `?d_000fe3c0@@YAXXZ`.
Earlier sessions blocked it on "callback and owning-class contract". This note
records the identity. No ledger row changes.

## Facts from retail 1.03 (`lotrbfme.exe`, image base 0x400000)

- ILT 0x00047672 jumps to 0x000FE3C0. Its VA 0x00447672 appears once in data:
  at 0x01086118, slot 16 (+0x40) of BuildAssistant's table 0x010860D8. For the
  table's owner and full slot map see
  `000febe0-buildassistant-update.md` and
  `000fc010-buildassistant-buildtiledlocations.md`. BFME drops ZH's line-build
  virtuals, so slots 16/17/18 are ZH's `canMakeUnit`, `isPossibleToMakeUnit`,
  `sellObject`. Slot 18 is the matched `BuildAssistant::sellObject`.
- The body returns only ZH CanMakeType values (`CANMAKE_OK`=0, `NO_PREREQ`=1,
  `NO_MONEY`=2, `FACTORY_IS_DISABLED`=3, `MAXED_OUT_FOR_PLAYER`=6), plus a BFME
  value 7. It makes Zero Hour's `BuildAssistant::canMakeUnit` checks; BFME reorders a
  few:
  - builder (first argument) null -> `mov eax,1` (NO_PREREQ). BFME adds a third
    argument: a null template with third argument -1 also returns 1.
  - `test byte [builder+0x343], 3` -> return 3 (ZH: script-disabled or
    script-unpowered status bits -> FACTORY_IS_DISABLED).
  - `mov eax,[ecx]; push edi; push edx; push esi; call [eax+0x44]` on `this`:
    slot 17 with (builder, template, third), and a false result returns 1. This
    is ZH's `if (!isPossibleToMakeUnit(builder, whatToBuild)) return
    CANMAKE_NO_PREREQ;`, and it ties slot 17 to isPossibleToMakeUnit.
  - `Object::getProductionUpdateInterface` (0x001BF570), then a virtual on it
    (ZH `pu->...`), `getControllingPlayer`, a player test returning 2 (ZH's
    NO_MONEY value), and
    `Player::countObjectsByThingTemplate` (0x000CDD50) returning 6 (ZH's
    `canBuildMoreOfType` -> MAXED_OUT_FOR_PLAYER).
  - Every exit is `ret 0x0C`: three stack arguments (ZH has two; BFME adds one).

## Conclusion

0x000FE3C0 is `BuildAssistant::canMakeUnit` (a const public virtual in ZH),
with a BFME third argument whose type the converter must establish from the
callers. 0x000FDBF0 (slot 17), which it calls, is
`BuildAssistant::isPossibleToMakeUnit`.

## Independent re-derivation (sol/w3 7851e26ee4)

A separate session reached the same identity from the subsystem
registration rather than the slot map. Facts it adds:

- GameEngine::init calls ILT 0x000463A8 -> constructor 0x000FDA80 at VA
  0x00479B22, pushes literal 0x01076388 (`TheBuildAssistant`) at 0x00479B36
  and global 0x012ED83C at 0x00479B44 before initSubsystem at 0x00479B49.
  The constructor stores table 0x010860D8 at VA 0x004FDAA5.
- Extent: final `ret 0x0C` at +0x198, INT3 at +0x19B (411 bytes).
- The third argument is an integer identifier: -1 selects the template path,
  other values use the record at Player+0x684. The limit check compares the
  object count with ThingTemplate+0x480 and then counts queued production
  through the Player::iterateObjects callback.
- Conversion blockers it recorded: the callback at 0x000FC2A0 still has an
  int-return synthetic-object declaration where the Player walk expects
  `void(Object*, void*)`, and BuildAssistant's header needs the BFME
  three-argument declaration.
