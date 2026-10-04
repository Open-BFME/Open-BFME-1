# 0x00013101 carries the exported DefaultModuleTemplate<6> destructor

## Export proof

`targets/game/reverse/exports.csv` line 430:

```
429,0x00013101,0x005D5760,.text,code,??1?$DefaultModuleTemplate@$05@FXParticleSystem@@UAE@XZ
```

Retail exports the name `??1?$DefaultModuleTemplate@$05@FXParticleSystem@@UAE@XZ`
at stub RVA 0x00013101, routed to body RVA 0x005D5760.

## Stub proof

Retail bytes at 0x00013101 (image base 0x400000,
`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`):

```
E9 5A265C00
```

`E9` with displacement `0x005C265A` targets `0x00013101 + 5 + 0x005C265A =
0x005D5760`, exactly the export's target body. The 5-byte ILT stub is the
exported name's entry point, not a HashTemplate body.

## Body proof

0x005D5760 is the 50-byte `DefaultModuleTemplate<6>` empty dual-vtbl
destructor, matched by ledger row 6248
(`DefaultModuleTemplate05DestructorThunk.cpp`, scoped byte-verified).
Setting that row's `export_rva` to 0x00013101 records the proven link,
following the `StringBase` precedent (e.g. `??$?MG@@...` carries
`export_rva=0x00005D94` for its ILT stub).

## Refuted claims

Five `HashTemplateClass<StringClass, ...>::Entry::~Entry` rows claim
`target_rva=0x00013101` (size 5). None is exported there (no
`HashTemplateClass@VStringClass` name appears in `exports.csv`), and
`tools/one_identity.py --callers` reports "no C++ caller names a row" for
0x00013101. Their only pins are `pinharvest` rows in `symbols.csv`, which
propose a name and prove nothing (AGENTS.md). The thunk TU
(`HashTemplateEntryDestructorThunk.cpp`) emits a single COFF symbol; the four
sibling rows are ledger-only `object-symbol=` aliases. All five are
over-claims on an ILT stub whose exported identity is proven above, and are
retired with this note as their tombstone reason.
