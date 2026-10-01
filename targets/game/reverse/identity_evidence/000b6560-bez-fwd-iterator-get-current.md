# Identity correction at 0x000B6560

`BezFwdIterator::getCurrent` names the four-byte body at RVA `0x000B6560`.

The retail `BezierSegment::getSegmentPoints` body at RVA `0x000B7D30` calls ILT `0x00028655` at VA `0x004B7DC6`. This is the only call to that ILT in the retail executable.

At that call, `ECX` points to the stack iterator. The next three loads read the returned address.

`BezFwdIterator` declares two integers and a four-point `BezierSegment` before `mCurrPoint`. The field starts at offset `0x38`. The repository name oracle, `tools/name_oracle.py`, reports `mCurrPoint` at that offset.

The body at RVA `0x000B6560` contains `lea eax,[ecx+0x38]; ret`. This instruction returns a `Coord3D` reference, matching the source declaration `const Coord3D& getCurrent() const`.

The previous ledger row named the body `Thing::getPosition` and noted its cached-position field. Both that field and `mCurrPoint` start at `+0x38`. The only retail call passes a `BezFwdIterator`, which identifies this body as `getCurrent`.
