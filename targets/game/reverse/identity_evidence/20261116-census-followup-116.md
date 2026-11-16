# Confirmed full census after the first 116 continuation tasks

Successful run: [43936402752](https://github.com/Open-BFME/Open-BFME-1/actions/runs/43936402752).
Both artifact history and link-index metadata identify input `1ac768d4cf`,
resolving to `1ac768d4cfd5e6da3347628e22bde04216d964a0`. This is the
first116-task publication. Tasks117 onward are later inputs, not measured here.

| Metric | Prior43870552474 /2a7328eb57 | New43936402752 /1ac768d4cf | Delta |
|---|---:|---:|---:|
| LINKED bytes | 3,094,682 | 3,095,420 | +738 |
| Link-clean source files | 15,524 | 15,535 | +11 |
| Original200-source cohort link-clean | 152 | 152 | 0 |

Every original200-cohort source is present. There are no newly blocked files
in that cohort or anywhere in the complete status comparison. The48 previously
blocked cohort files remain blocked. This is not200/200 link-clean.

## Exact byte accounting and attribution

- `Rva003BF010.cpp`:303B, with its original export/ILT-proven Base isEmpty route.
- `BfmeTimerAZTick.cpp`:108B, and `BfmeConv1713.cpp`:64B, with the original
  GlobalWeatherSystem::setWeather route. These three measured caller gains total475B.
- `Water/Rva00C6B810StaticInit.cpp` was already clean; its linked ownership grows
  from36B to56B when the existing20B cleanup is rehomed beside its initializer.
  These495B correspond to this continuation's measured binding/ownership repairs.
- Eight FX destructor files become clean: one33B CategoryModuleTemplateBase<0>
  destructor plus seven30B scalar-deleting wrappers, totaling243B. Separate
  provider corrections by Yannick Molinghen are present between the inputs,
  including766ff25d8e4, e5bbaf440bc andbe0e70026ae. Their contribution is project
  progress, not an additional task or byte gain credited to this500-task counter.

The eleven newly clean files contribute718B; the already-clean Water owner
adds20B, exactly accounting for738B. The old index shows the wrong duplicate
CategoryModuleTemplateBase<0> copy in fx_particle_system.obj; the new index
retains the existing retail provider and omits that wrong copy.

This confirms full-census linkability, not newly reconstructed authored bytes,
whole-game correctness, successful startup, memory savings or crash fixes.
The local retained-body/layout proofs and later adoptions are separate evidence.

Artifacts14274959952 and14276680136, raw status/history, both index snapshots
and the complete JSON comparison are preserved under
`W:/OpenBFME/diagnostics/continue-20261116-fivehundred/` as
`census-43936402752`, `census-index-43936402752` and
`census-followup-43936402752.json`.
