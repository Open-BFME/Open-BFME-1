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
