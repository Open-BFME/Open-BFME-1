// Two incremental-link thunks that were filed as PrimitiveAnimationChannelClass
// <float>/<Vector3>::operator=. Neither leads to an assignment: 0x0001DB6F reaches
// an _Rb_tree destructor (-> 0x000A4B60 -> 0x00009895 -> 0x000A3C70) and 0x000026AD
// reaches AsciiString's buffer release (-> 0x00439140 -> 0x00887940), and retail
// jumps to both from unwind funclets. Claimed by address, as the ILT convention says.
// Under /O2 a tail call with no arguments is exactly `E9 rel32`.

void j_000a4b60();
void j_00439140();

void j_0001db6f() { j_000a4b60(); }
void j_000026ad() { j_00439140(); }
