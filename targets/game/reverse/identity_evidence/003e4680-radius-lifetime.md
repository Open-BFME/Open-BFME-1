# RVA 003E4680: sibling radius lifetime

Retail starts after INT3 at 003E4680 and ends RET12 at 003E4932 (+2B2),
followed by INT3 at 003E4935: the complete extent is 693 bytes. The bank's
copied heading incorrectly described its 003E49F0 sibling; this audit uses
the actual 003E4680 bytes and body. Ghidra agrees with the loop and extent.
The independently matched Rva0023BE60NearbyObjectsCheck caller passes Object,
position and output IDs through ILT00027AB6 from the AI pathfinder pointer.
The owner is Pathfinder; no semantic member name is established.

The preferred bank measures exactly 693 bytes with 29 stack displacements
different. As in the separately completed 003E49F0 sibling, exposing the
actual 297-byte getRadiusAndCenter and replacing the artificial two-integer
radius array with one scalar makes all 693 bytes exact. Native Object/Thing
and Coord3D headers are reused. Both siblings now share the same translation
unit, declarations and verified radius helper. No shared header is edited.

The algorithms and callees remain distinct. This body scans the whole
footprint rather than its expanded border. Its layer branch compares the
goal ID at cell-info+14, but stores the occupant ID at +18; the ground branch
compares and stores +14. The source preserves that independently decoded
asymmetry. Its layer accessor is 003FBAB0 through ILT000105CD, the existing
matched PathfindLayer::getCell, not its equal-byte 003FBB20 sibling used by
003E49F0. A separately inlined accessor keeps those call bindings distinct.
No new pin is needed.

The strict gate verifies both full scans together, all direct calls, eleven
float constants and 21 DIR32 references. The unchanged radius helper is also
verified separately against its 297-byte retail body and references.
Only the generated d_003e4680 row is replaced. The original bank is preserved
unchanged in 003e4680-original-bank.cpp.txt, including its historical heading.

The source comparison pairs the bank getCell with the pre-existing sibling
accessor calling rva003FBB20. This is a comparison artifact: the new scan
still calls PathfindLayer::getCell at 003FBAB0, and the 003E49F0 accessor
retains its previously verified 003FBB20 binding. The narrow snapshot-bound
correction records that pairing; it does not rename the native getCell.
