# Retire obsolete Render2D provider

Queue9 d1c221c3d8 keeps the incompatible ZH Render2DClass::Render from
render2d.cpp ahead of the real2015-byte body in Render2DRenderThunk.cpp.
No ledger row owns the ZH Render body; the existing canonical row owns
00933E50..0093462F. Remove only the obsolete body and its marker.

The initial normal paired gate identifies three dependencies whose emission
was tied to that obsolete body: Get_Transform005F0F00/854,
Set_Transform006DB7D0/1057 and Set_View_Identity0078AED0/187.
The canonical renderer naturally emits all three from its existing DX8
header and uses them for the same render state transitions. Private probes
match every instruction modulo relocation slots for all three. Repoint only
these existing identities/extents through normal add_match verification;
no retention fixture, pin, alias, header, class or compiler-setting edit.
The final paired normal gate establishes full relocation and data bindings.

BFME2 reviewed76f0baefa6f285d54bc1ca922397674312a5913f,
Code/Libraries/Source/WWVegas/WW3D2/Render2DClassRender.cpp and the
existing local renderer donor provenance. BFME2 differs in render mode and
layout; those differences remain in the existing proven BFME1 source.
Its source-only complete renderer supports retiring a stale inherited
implementation, not transferring any donor address or identity.

Diagnostics: build/queue10-20261113/render-{before,after,gate}.log and
obsolete-render.cpp.txt. Frozen census90c15cdeca is a preview, not current
closed-strict placement. No recovered-byte gain is claimed.

Final paired gate15/15,6 floats203DIR32 references, no baseline findings.
Raw COFF confirms the obsolete unit no longer defines Render and the
canonical unit does. The frozen-census after preview still attributes
the deleted Render copy to the old index, so its duplicate/selected
verdict cannot establish current closure. No linked-byte delta is asserted.
