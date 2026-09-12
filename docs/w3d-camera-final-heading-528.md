# Camera path final heading: 528-byte recovery

The complete `W3DView::cameraModFinalLookToward(Coord3D*)` body at RVA
0x007401A0 is now clean C++, exact over all 528 bytes and 16 relocations.
The source gate passes 1/1 with the full terminal `ret 4` at +0x20D. All
twelve DIR32 operands name numeric pools whose actual retail bits were
checked; the adjacent JSON records those checks and the source/object hashes.

The bank's remaining fourteen differences were temporary allocation, not a
different interpolation algorithm. Using the genuine Vector2 definition and
one scalar for successive squared-length, heading and normalized-delta
lifetimes produces the retail x87 stack slots. The implementation uses the
existing upstream WWMath operations. It adds no assembly or math shim.

The primary W3DView vtable at VA 0x011217A0 has this operation at slot 37:
its VA 0x00437646 entry jumps to VA 0x00B401A0. The old bank's 38-slot
declaration was corrected. The matched 211-byte ScriptActions
`doModCameraFinalLookToward` caller at 0x002F8D70 dispatches through slot
+0x94 at +0xC3. The canonical upstream camera-path operation
agrees with the BFME fields and interpolation, while BFME's movement mode
is tested against 1. All three heading-normalizer calls reproduce the
existing fastcall ABI at 0x0073A900. The final PI/2 subtraction now uses its
actual float value instead of an opaque mutable global alias.

This TU uses one contiguous 259-element record-storage ABI view. The matched
constructor actually initializes separate 255-record and four-record regions;
the view is not a claim that the original declaration used one array. This
function emits no constructor or destructor. The view preserves their exact
combined layout and avoids relying on an unproved neighboring-point bound
at the end of the first region.
