# W3DView camera-transform builder: 1322-byte recovery

`W3DView::buildCameraTransform(Matrix3D*)` at RVA `0x00741D30` now has a
complete clean C++ owner. The fresh final object is exactly 1322 bytes; the
ordinary resolver reports zero differences, no unresolved symbols and no
masked fallback. The source gate passes 1/1. The adjacent JSON records source
and object hashes and every one of the 31 relocation operands.

The full retail extent ends in `ret 4` at +0x527, followed by 24 bytes of INT3
padding. Named `setCameraTransform` (0x007423B0) and `resetCamera`
(0x00743640) callers call the private builder through ILT 0x0000A8DF, whose
E9 reaches 0x00741D30. The first caller also has an existing byte-matched
object with the private-symbol relocations; that object was an identity
witness, not a claim of a fresh caller gate.

The principal missing shape was a real automatic 0xD8 camera context. Its
matched constructor is 0x006DFC60; the normal and exceptional destructor paths
both reach 0x00740C80 through ILT 0x000084EA. Retail FuncInfo at RVA 0x00E3D678
has one state and no try blocks. Its unwind map at 0x00E3D670 changes state 0
to -1; the action at 0x00C4DB10 uses `lea ecx,[ebp-0xE4]` before the same
destructor jump. The TU adapter preserves that existing owner and does not
duplicate its two handle releases.

Those handles are **narrow strings**. The destructor releases +0xB0 and +0xAC
through `StringBase<char>::releaseBuffer` at 0x00887940. Both assignments call
the actual `StringBase<char>::set` specialization at 0x00887C90. A historical
UnicodeString alias at that address is not evidence for wide strings; its
ledger object-symbol also names the char specialization.

DIR32 operands were audited separately because the regular resolver copies
their retail values. All eleven floating-pool uses have the actual expected
bit patterns, including the angle factor `0x42652EE0`. The four `__except_list`
operands are FS:0. TheGameLogic and TheGameClient agree with their existing
global identities. The remaining data identities are:

| Actual VA | Evidence |
| --- | --- |
| 0x012BB214 | Float; independent x87 loads at RVAs 0x007D4AF3 and 0x007D95B3. Semantic name remains unknown. |
| 0x012F9DBC | Float; x87 load, reset and angle addition at 0x00744083. Semantic name remains unknown. |
| 0x012A79D0 | StaticNameKey whose name pointer addresses `cameraYawAngle`; canonical `key()` is ILT 0x00009304 to 0x00090290. |
| 0x012ED5E0 | Direct world Dict object; matched `freeListOfMapObjects` at 0x00746E90 also calls Dict::clear on it. Upstream names it MapObject::TheWorldDict. |

The world property setter is the genuine `Dict::setReal(NameKeyType,float)`
at 0x00068830 through ILT 0x00048FA4. The camera-state receiver at W3DView+0xB4
uses a neutral address-derived declaration pinned to the actual 0x006E0580
body; the resolver reproduces its ILT 0x000035B7 call without assigning a
speculative semantic name. Every new data pin is an RVA, not its absolute VA.

The reconstruction also restores the complete context transfers, corrected
height smoothing, constrained-region copy, object-position value copy and
world yaw update. The old bank's absent EH and ABI/type mistakes were fixed
from retail evidence. No shared header or generated body was changed.

The widened caller gate found a stale `d_0073a9b0` call in `resetCamera`.
That address already has the exact `getHeightAroundPos(float,float)` owner,
so the caller now uses that genuine declaration directly. Its fresh source
gate passes all 434 bytes; no compatibility alias was added.
