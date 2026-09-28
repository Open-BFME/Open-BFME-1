# Weapon.cpp `setTransformMatrix -> rva00132200` is a callee view, not a rename

Weapon::positionProjectileForLaunch (0x001E37F0, 224 bytes) calls ILT 0x000361CE,
which reaches 0x00132200 (`tools/callees.py 0x001E37F0 224`). The ledger names
that body `?rva00132200@Thing@@QAEXPBVMatrix3D@@@Z` and puts
`?setTransformMatrix@Thing@@QAEXPBVMatrix3D@@@Z` on the different body at
0x00132350 (ILT 0x00023D49). The TU-local `#define setTransformMatrix rva00132200`
around PreRTS.h binds the ZH `projectile->setTransformMatrix(&worldTransform)`
call to the ledger name of the body retail really calls. No definition was
renamed.

Open identity debt, same as
`gap_seat_051426_2_callee_views.md`: 0x00132200 has 17 named callers, all
ZH setTransformMatrix call sites (Thing::setPosition/setPositionZ,
Drawable::xfer/updateDrawable/loadPostProcess, ToppleUpdate::update, ...) and
its body is the ZH GeneralsMD Thing.cpp:250 setTransformMatrix body.
0x00132350 has no named caller. The two ledger names probably belong swapped;
that fix spans the ledger, the 0x00023D49 pin, Thing.cpp and
Rva00132200ThingTransform.cpp and is not made here.
