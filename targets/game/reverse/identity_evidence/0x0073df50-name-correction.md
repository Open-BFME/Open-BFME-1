# 0x0073DF50 naming correction

The previous attempt used BfmeHostEUF, BfmeCamEUF, and BfmeSphereEUF as local layout/shape shims. Those names were not obtained from the retail symbol table or an owning-class witness.

For 0x0073DF50, the independent audit found no named direct caller and no installed vtable slot. The body supports an ECX receiver, two stack arguments, and a camera pointer at receiver offset +0x104. Nearby W3DView layout shims support that field being a camera pointer, but do not prove the target's owner. The source therefore uses Rva0073DF50 for the unproven owner and Rva0073DF50Camera for the local layout view.

The old BfmeSphereEUF aggregate was also replaced by the repository's actual SphereClass type from WWMath/sphere.h. The detector's sphere-to-camera pair is a declaration-alignment artifact: the new camera layout view is a separate declaration, while the sphere local is now SphereClass.

Evidence: the audit is recorded in targets/game/reverse/re_attempts.log at 0x0073DF50; docs/naming_evidence.md requires address-bearing names when a shape is known but identity is not. The ret 8 boundary and the +0x104 field access do not establish the owner name.
