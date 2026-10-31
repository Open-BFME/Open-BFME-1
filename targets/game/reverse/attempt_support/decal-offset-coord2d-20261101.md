# Dynamic decal offset: canonical Coord2D with unchanged volatile stores

Base `efd10ae2e1`; claimed constructor `00428FA0`, 130 bytes. Replace the
private two-volatile-float Coord2D with the existing registered eight-byte
struct and declare the offset member `volatile Coord2D`. Its accesses stay
volatile, preserving the native constructor's interleaved store order.

Normal verification and owning Coord2D acceptance pass. All seven retained
external code bodies/relocations and all nine non-debug sections are
identical; no code definition is added or removed. The target contract fixes
float x/y at +0/+4 and the existing constructor fixes the offset's location.
The pinned BFME 2 Coord2D header is class-key class with additional methods;
its different interface is not imported. BFME 1's registered struct is used
unchanged. No shared header, pin, alias, flag or baseline changes.

This removes one private type copy, not a runtime crash or memory-leak fix.
BFME 1's acceptance validates but does not retire historical queue rows.
The default link queue's RefHandle destructor variants were reviewed against
the existing tracked attempts; no changed prerequisite makes their old
parent/EH mismatch worth repeating. Final bounded previews are recorded
with the batch, separately from census/full-image/runtime evidence.

Controls: ignored `build/six-each-no-qwen-20261101-0015/b1-01-*` and the
matching diagnostic package. Qwen stays off; shared build cap remains ten.
