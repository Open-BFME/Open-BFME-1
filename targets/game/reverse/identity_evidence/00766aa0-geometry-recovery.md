# 00766AA0 geometry recovery

GPT-6, 2026-09-27 01:55–02:23 UTC; bank only, no native credit.

The 3386-byte extent is complete: RVA 007677D7 has `ret 10h`, followed by
INT3 at 007677DA. The independently matched 00769C30 caller already pins
`Rva00766AA0Owner::forward00769C30`: primary receiver, nullable output record,
by-value AsciiString, two pointer outputs, bool AL, four stack arguments.
The semantic owner/method remains unproved and is deliberately address-derived.

The previous preferred source compiled to 6304 bytes with normalized instruction
similarity 0.287. It used X coordinates and a 50% split, had an artificial
48-byte volatile stack filler, omitted the validated mesh transform, and used
an incorrect helper output contract. The new source recovers:

* Z-coordinate extrema and a 2% end band (retail float at VA 0107C6EC).
* A root transform followed by a separately validated/copied mesh transform.
* The Drawable's object at +FC and the object's matrix at +8; the alternate
  path uses matched 0041CEC0's returned matrix and its translation.
* Mesh counts at +24/+28 and vertex ShareBuffer at +30. Name-oracle independently
  witnesses MeshGeometryClass::PolyCount at +24; the current shared header
  puts these fields four bytes later, so the bank uses a bounded RVA view.
* The two extremity passes, averaged widths, rounded transformed corners,
  and the two-polygon perpendicular-vector fallback.
* Retail's reference-count paths, including failure paths that return without
  releasing the selected object, and canonical by-value AsciiString cleanup.

The +14 render-object slot is a pointer-returning view; 0092C710's entire body
is `mov eax,ecx; ret`. The current RenderObjClass header exposes that slot as
an opaque int, so no unsupported shared signature change was made.

## Callee closure

0041CEC0 is the existing matched BfmeCalc919G cache accessor; 007629F0 is the
matched AttachmentTransform007629F0::adjust(Matrix3D&). The special helper is
the existing ILT 0002E7B7 targeting 00763AC0. Its complete 1500-byte body ends
at 00764099 with `ret 8`, followed by INT3 at 0076409C. It receives the selected
RenderObj in stack argument 1, a float output pointer in argument 2, consumes
the supplied reference and returns an allocated polygon record or null in EAX.
The independent matched 00767B30 caller already uses a typed member-pointer
union view of this same thunk. The bank reuses that mechanism with the proved
types; it adds no pin. Ghidra's 1490-byte count omits disjoint bytes and is not
the complete extent.

The remaining calls are twelve __ftol2 conversions, WWMath::Inv_Sqrt, and two
canonical string releases. A scoped strict comparison resolved all direct
targets and failed only the concrete body comparison; no unresolved-callee
error remains. Floating literal relocations correspond to 0.02f, 0.5f and 0.0f.

## Result and exhausted levers

Final source: 3386/3386 bytes, frame BC, 36 relocations covering 144 bytes.
Exactly 82 non-relocation bytes differ. The bank score is the concrete fraction
`(3386 - 144 - 82) / (3386 - 144) = 0.9747069710055521`, not the normalized
instruction score of 1.000. Twenty-eight differing bytes select scratch
registers around +15C..+1F5. Fifty-four select x87 operands, principally within
the four corner transformations; the native control-flow shape is identical.

The large improvements came from canonical geometry types, recovered behavior,
comparison polarity/order, real second-matrix storage, temporary-input
Transform_Vector calls, sharing the corner output local, and scalar fallback
stores. Normalized similarity progressed .287 → .822 → .946 → .995 → 1.000.
Concrete residue at equal length fell 380 → 321 → 144 → 82 bytes.

Failed final levers: complete visible/noinline matched adjustment helper;
Get_Translation result by const/reference/local; aliased versus distinct
Transform_Vector outputs; mulVector3 and returning-vector helpers; helper
argument order; ordinary dot-product operand order; /Ob1 and /Oi (unchanged),
/G7 and /Op (worse). No inline assembly, volatile frame padding, speculative
identity or pin was added. The old bank remains in immutable attempt history.
No nonmatching game-source file was installed.

## Exact name-guard pairing correction

The positional declaration detector paired old `BfmeVec3` with new
`Rva00766AA0RenderSlots`. They are unrelated types. The former was a local
three-float x/y/z vector and is now the canonical Vector3 from vector3.h, whose
X/Y/Z fields, arithmetic, and normalization the new bank actually uses. The
latter is the bounded six-slot render-object view needed for the independently
observed +14 pointer-returning call. No vector identity was renamed to an opaque
render-object identity. The correction is restricted to these exact snapshots.
