# 0x00454760 ParseObjectDataChunk (605 B): 43 -> 4 diffs (s509, claude-opus-5-5)

Bank: targets/game/reverse/attempts/0x00454760.cpp (same flags and pins as the 2026-10-16 bank,
see re_attempts.log; twin reader 0x00088B70 in game/GameEngine/Source/Common/MapObject.cpp).

Levers that moved bytes (both are the "read first through volatile" lever recorded in
docs/shape_levers.md for 0x002593F0):
- Template branch argument copy (43 -> 13): retail preloads loc.x into ECX and loc.y into EDX
  around the argument pushes, then stores x, z, y. A TU-local `Vector3(const Coord3D &, int)`
  constructor reading x and y through `*(const volatile unsigned *)`, storing x, then z (plain
  read), then y, used only in that branch, reproduces it. Reading only y volatile (30), Real
  temps (48), store order alone (43) do not.
- Waypoint store `m_waypoints[name] = loc` (13 -> 4): retail loads x, y, stores x, loads z,
  stores y, z. A static inline `assignWaypoint(value &, const Coord3D &)` with volatile x/y/z
  reads and volatile stores in that order is exact for the block; plain stores (7), barriers
  instead of volatile (7-13), volatile z read with plain stores (13) are not.

Remaining 4 bytes: one scratch-rotation step later, `lea edx` (retail) vs `lea eax` for the
tech-position push_back at +0x20F and `mov eax,[esi]` vs `edx` for the virtual delete at +0x222.
They matched before the waypoint helper. Inert: rotation_sweep single and --pairs (all 4),
identity copies at five points in the helper, pointer forms of the helper arguments,
__forceinline, pointer-form push_back. Implicit Vector3 copy ctor: 247 (597 B).
Next idea: a waypoint spelling that keeps the block's bytes with fewer IR temps (e.g. a
Coord3D-typed map value with a user operator= that reads in this order).
