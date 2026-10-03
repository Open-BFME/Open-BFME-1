# DynamicDecal positional callback, RVA 00429080

The already matched DynamicDecalFXNugget constructor428FA0 stores table
VA010F3420. Its three entries are ILTs427F52,42C854,43238F, resolving to
4293C0 (scalar destructor),429080 (this body),429050 (object callback).
The owner is witnessed by the registered DynamicDecal INI parser42BF50,
which allocates F8 and calls this constructor; constructor/symbol records
preserve this independently established identity. The method spelling and
four-argument signature are established by the matched FXNugget::doFXObj
caller427C30 invoking slot04, and the SoundFXNugget slot04 witness documented
in00427c30-complete-object-fx.md. Ghidra and retail both give575 bytes,
ending RET16 at4292BC, followed byINT3 at4292BF. No fifth ZH overrideRadius
argument is asserted.

The primary-matrix argument is read at full-frame ESP+D8 for rotation;
the old bank incorrectly read the secondary-position argument atESP+E0.
Retail copies the final12-byte coordinate as integer words into Shadow+8.
This aggregate assignment also accounts for the saved EBX/EBP registers.
Only the shader/orientation reads require volatile scheduling; marking all
opacity/time fields volatile incorrectly reordered three FPU loads.

The source includes native Lib/BaseType.h, ascii_string.h and matrix3d.h.
Ob1 inlines the native string accessor. A TU-scoped noinline decoration on
the math headers preserves the witnessed calls to RGBColor::getAsInt and
Matrix3D::Get_Z_Rotation. The latter has an independently matched8B body.
No shared header changes or surrogate string lifetime are used.

BFME-specific terrain and projected-shadow virtual calls use local
address-qualified views, with canonical global pointer spellings. Shadow's
BFME prefix and extended type-info layout differ from the reference ZH
header; retail writes the position at+8/+C/+10 and angle at+20, and passes
an A4-byte local descriptor whose type is+80 and dimensions+88/+8C.
The preserved canonical helper names are adjustVector, setOpacity, and
rva00459960; the current color helper ledger name is BfmeColourABK::bfmeSetABK.
The eight frame/opacity arguments to459960 agree with its native matched
body, not the old bank's guessed setBounds spelling.

Literal checks include the complete empty-string terminator atVA0107388B
and frame multiplier bytes8FC2F53C atVA010F224C. The scoped add_match gate verified575/575 bytes, all calls, one float
constant and seven DIR32 operands.

## Review repair of f2f04fe5887

The first landing redeclared Shadow/ShadowTypeInfo despite the covered
GameClient/Shadow.h. The corrected source includes that canonical header
and GameClient/Color.h. Rva00429080ShadowInfo is an independent BFME wire
layout, and Rva00429080ShadowView addresses only position and angle fields;
no same-named native declaration is replaced. The canonical Shadow pointer
is retained as the addDecal return type.

Calls preserve existing named ILTs j_0000dc7e and j_00005119, the exact
entries used by retail at parent offsets1B7 and22D. Their E9 bodies resolve
to Shadow::setOpacity4597A0 and Shadow::rva00459960 at459960 respectively.
The first takes one int and ends RET4, the second eight ints and ends RET32;
both require the unchanged receiver inECX. The TU-local member-pointer
bridges explicitly check their single-inheritance member-pointer width
against the function-pointer width before use. They emit direct calls with
the same ECX and stack ABI; no new pins or native inline setter bodies.

Scoped verification after canonical adoption:575/575 parent bytes, all
call references, six floating constants and seven DIR32 operands pass.
