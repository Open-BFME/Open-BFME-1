# Full census confirms the preceding 450-byte preview

Run [43711614660](https://github.com/Open-BFME/Open-BFME-1/actions/runs/43711614660)
completed successfully on 2026-11-15 at 13:51 UTC, measuring input
`7c314a3e6cbd63b2ee6d6a7f0aa68c8bc6e68432`. Its published census commit is
`04cca8eaf63542ad135f7dc906cc2e5a09ade851`.

The prior census measured `1a248a7b47` on 2026-11-14. Per-file status changes:

| Source | Earlier | New full census | Existing authored bytes |
|---|---|---|---|
| game/GameEngine/Source/Common/Rva008B2EA0Factory.cpp | no;2 unresolved | yes; all blockers0 |184|
| game/GameEngine/Source/Common/Rva008AAEC0MakeString.cpp | no;3 unresolved | yes; all blockers0 |266|

Both files are now LINKED, exactly184+266=450 bytes. The predicted sizes were
recorded in 20261115-next-eighty-1.md; their source and function extents did not
change between prediction and this input. The new measurement includes all
previously published corrections through the cited input, not this new
header-adoption round.

Total confirmed LINKED bytes rise from3,086,248 to3,088,824, an increase of2,576;
LINKED files rise from15,516 to15,522. These totals include earlier work too.
Six files become linked and none loses LINKED status. The selection link on
22,993 objects exits0. Per-file LINKED status still applies the stronger selected
provider and COMDAT truth checks: the run also reports5,269 wrong selected names
and4,745 unproven selected names. This is not proof of a complete reconstructed
runtime image, game start, memory optimization, higher FPS or a crash fix.

Sources: the old/new tracked link_status.csv and link_census_history.csv at the
cited revisions, plus the completed run's native log. Local full comparison
records are preserved with this working round's diagnostics.
