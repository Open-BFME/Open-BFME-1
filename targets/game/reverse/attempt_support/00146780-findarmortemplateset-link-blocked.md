# Link queue #9: findArmorTemplateSet wrong_selected — provider intact, blocked on census reloc resolution

Queue: `?findArmorTemplateSet@ThingTemplate@@QBEPBVArmorTemplateSet@@ABV?$BitFlags@$0L@@@@Z`
(0x00146780, 73 B), sole blocker of `ActiveBody_attemptHealing.cpp` and
`ActiveBody_validateArmorAndDamageFX.cpp` (798 B). Live index kind is
`wrong_selected` (published CSV says `losers`; kinds differ, same root cause):
the census copy-verdict for `ThingTemplate.obj`'s copy is `wrong`.

## What was proven this pass (no source edit warranted)

- `./build.sh '?findArmorTemplateSet@...'` → Functions OK 1/1 matched; body
  guard, DIR32, string/constant checks all OK. Current source emits retail's
  bytes; any "fix" to the provider would break a verified match.
- `dis_retail.py 0x00146780 73` shows retail calling through the same three ILT
  thunks our copy uses: `0x0000AE20`, `0x0002AFA4`, `0x00036C0A`.
- All three ILT route targets carry matched rows at exactly the retail RVAs:
  `0x001412A0` (Weapon map `_M_find`), `0x00144300` (Armor `findBestInfoSlow`),
  `0x001451E0` (Weapon map `operator[]` in `ThingTemplate.cpp` itself).
- `ThingTemplate.cpp` and both consumer files are unchanged since census
  `31c8ddea62`, so the verdict was computed on current bytes.
- Local `link_check.py` on the consumer can only report LINKED PREVIEW UNKNOWN
  (selection census stale for this symbol); per repo rules that is unknown, not
  proof of a fix.

## Conclusion

The `wrong` copy-verdict is a relocation-resolution artifact in the census, not
a body defect: identical bytes and identical ILT routing verify clean. Do not
touch `ThingTemplate.cpp`'s body or the two consumers for this item.

## Next leads (not tried)

- Fresh census (`link_census.py --build`, ~35 min) or a targeted reloc audit of
  the copy's three ILT referents under `bind_weak_relocations` to find which
  referent fails `_lands`.
- BFME 2 donor sweep for this provider/consumer set before any new hypothesis
  (linking-first rule); submodule was not initialized this pass.
- Note: ledger carries two real names at `0x00146310` (Armor vs Weapon
  `findBestInfo`, rows 51565/51566) — a possible over-claim to reconcile via
  `one_identity.py`, but it is a separate lane from this queue item.
