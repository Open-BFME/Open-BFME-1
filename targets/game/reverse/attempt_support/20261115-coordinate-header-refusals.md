# Coordinate header adoption: bounded refused trials

Session input: BFME1 `8a6eec11f92fc6299c09a01d046927a00dffbec5`.
Read-only BFME2 reference: `f6c3838e7b58025531e09913bc42b810f1a01216`.
Use the existing canonical registry and Coord2D/Coord3D contracts, not another
private coordinate definition. No header, contract, compiler option or source
change from these trials was applied. None counts as a completed source task.

Forty reserved source units were tested with private VC7.1 compiler controls
under their original flags and include context. The first pass accepted zero.
All 44 reservations were released. Local originals, candidate sources/objects,
per-source diagnostics and prior-attempt filters are retained in
`W:/OpenBFME/diagnostics/continue-20261115-twohundred/coordinate-initial-refusal/`
and `build/codex-20261115-twohundred/coordinate-initial-refusal/`.

Concrete independent blockers:

- `PhysicsBehaviorApplyZeroMotiveForce.cpp`, RVA `0x0029B310`: removing the
  private field-zeroing Coord3D constructor changes the 40-byte retail body
  into a non-retail 29-byte body. The original expression is `&Coord3D()`;
  merely adding aggregate initialization to named locals does not address it.
  Preserve temporary construction and field-store ordering before retrying.
- `RayEffectSystemConstructor.cpp`: the data-only header lacks `zero()` calls
  on `m_effectData[i].startLoc` and `.endLoc`. A simple-variable helper rewrite
  does not cover these compound expressions. A future helper must preserve
  single evaluation, field order and every original ordinary code byte/target.
- `Coord3DVectorDefaultResizeThunk.cpp`: dropping the local constructors also
  removes an existing retail-correct constructor COMDAT. The scoped proof
  deliberately refuses this; a correct provider/closure must be established
  before removing a retail-correct definition.
- Several FXParticleSystem units contain nested coordinate types. A same-name
  nested type is not proof of the global canonical type. Check the fully
  qualified CodeView identity, layout and caller ABI before any adoption.
- Three-float construction, explicit copy constructors and other private
  methods require separate supported source adaptations. A successful compile
  alone does not preserve return conventions or copy/EH code.

One comparison limitation was independently resolved without modifying any
repository verifier: `W3DRadar_setShroudLevel_Thunk.cpp` has disconnected local
sections with no unique rooted mapping. Its private before/after complete
ordered runtime inventory is identical, including local section/offset targets,
section flags, bytes, external definitions and weak contracts. A strict ordinal
identity proof accepts that specimen; deliberately changing each of two
disconnected table sections is rejected. This does not constitute adoption:
its per-unit layout, normal native build, linking and publication gates remain
required. It is the only coordinate candidate reopened by that evidence.

Canonical AsciiString/StringBase adoption continues separately. Scalar null
constants emitted by StringBase::str are original exported data, not callable
functions: any separate diagnostic admission requires both the actual original
PE export directory and the recorded export RVA, readonly non-executable1/2B
extent, no relocations and exact initial bytes. It does not accept function
identity from a candidate pin. The earlier refused string specimens still had
other failures after this data evidence was considered; they were not counted
or blindly retried.

## Subsequent bounded helper investigation

Later existing private compiler specimens showed `_STL::_Destroy<AsciiString>`
as the same9B instruction stream in both controls, with a tail jump changing
from StringBase<char>::releaseBuffer to AsciiString::~AsciiString. The original
PE independently shows that destructor as a bare5B jump to the same release
entry. This isolated edge has equivalent machine-state forwarding; it does
not prove the whole candidate or its retained/native linking closure.

A diagnostic prototype checked that edge for existing unowned helpers while
still comparing their ordinary graph. None of17 refused specimens became
acceptable: other bodies remained wrong/unknown, or other targets changed.
The prototype was therefore isolated as
`diagnostics/continue-20261115-twohundred/semantic-tail-prototype.py`; the
active acceptance method continues to require native retail ownership/proof
for changed callable implementations. No task was counted from this study.

Explicit two-argument StringBase<char>::set/concat qualification is a separate
supported adaptation, demonstrated by the earlier assignRandomStillImage fix
and the concurrently landed AI_crc/DataChunkOutputDestructor sources. It is
tried only after a compiler arity refusal and still needs all ordinary byte,
target, layout, provider and linking gates. Most refused specimens retain
additional independent blockers; a fixed compile is not a completed task.
