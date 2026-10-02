// Open-BFME5 conversions.

// Retail's bytes at 0x009272E0 (44 B, tools/dis_retail.py):
//
//     push esi / mov esi,ecx / test byte [esi+0x18],4 / push edi
//     mov edi,[esp+0x0c] / je .skip
//     push ebx / mov ebx,[esi] / push edi / push edi / call 0x00927230
//     push eax / mov ecx,esi / call dword [ebx+0x10] / pop ebx
//   .skip:
//     push edi / mov ecx,esi / call 0x00927230 / pop edi / pop esi / ret 4
//
// THE CALLEE.  Both calls target 0x00927230, which the ledger defines and pins
// as `?get_vert_normals@MeshGeometryClass@@IAEPAVVector3@@_N@Z`
// (game/Libraries/Source/WWVegas/WW3D2/MeshGeometryGetVertexNormals.cpp), so
// the local view below declares that member with a `bool` parameter and the
// same `protected` access the definition uses -- `IAE` in the mangled name is
// the access code, so a `public` view would mangle to `QAE` and link nothing.
// Access to name it from `BfmeC998` comes from a friend declaration, which is
// the one way to reach a protected member of an unrelated class.
//
// That `bool` parameter costs the direct spelling five bytes per call, and
// retail has none of them.  Measured with
// `bfmeApply998((int)self->get_vert_normals(a), a)`: the compiler narrows the
// int argument before each push and emits
//
//     85 ff 0f 95 c0    test edi,edi / setnz al
//     85 ff 0f 95 c1    test edi,edi / setnz cl
//
// Retail pushes the raw `edi` with no conversion at all, so the caller and the
// callee were compiled from disagreeing declarations of the same selector --
// a normal split across a static lib boundary, and the reason the selector has
// two retail callers with different argument types (this one raw, and
// MeshGeometryReadVertexNormals.cpp at 0x009274C0 passing a real bool).
//
// Going through the union's pointer-to-member keeps the `int` type at the call
// site, so the argument is forwarded untouched, while `&get_vert_normals` in
// the union's initialiser still names the protected member and so still emits
// the ledger's exact `IAEPAVVector3@@_N@Z` reference.
//
// Note the argument split: `push edi` at +0x11 is the SECOND argument of the
// virtual `bfmeApply998`, and `push edi` at +0x12 is the callee's single
// argument.  0x00927230 reads that argument as a byte (`mov al,[esp+0x10]` at
// its +0x0E, past the 12-byte SEH prologue) and ends in `add esp,0xc / ret 4`
// at +0x8C/+0xA8 of its 171 B body, i.e. exactly one 4-byte argument.  The
// callee is therefore a one-argument thiscall returning the pointer the
// virtual consumes.
//
// WHAT IS PROVEN HERE: the ledger's own 44-byte body and its three addresses.
// The class of the `this` passed to the selector is not recovered -- the
// callee is reached through a cast view, since this caller and the callee's
// own class share no proven base.

class Vector3;
class BfmeC998;
class MeshGeometryClass
{
protected:
	Vector3 *get_vert_normals(bool alternate_format);

	// The caller class is the only thing in retail that reaches this selector
	// from outside, and its view here needs access to name it.
	friend class BfmeC998;
};

// The selector's real parameter is a bool but retail forwards a raw int to it,
// so the call has to be typed with the int while still naming that member.  A
// pointer-to-member with an `int` parameter would not name the same symbol, and
// MSVC 7.1 reserves __thiscall in a free-function-pointer typedef, so the alias
// travels in a union exactly as game/GameEngineDevice/Source/MilesAudioDevice/
// MilesAudioManagerSetHardwareAccelerated.cpp does: `asMemberBool` carries the
// real address, `asMember` the int-typed signature retail's bytes need.
union Rva00927230Getter
{
	Vector3 *(*asFunction)(MeshGeometryClass *, int);
	Vector3 *(MeshGeometryClass::*asMember)(int);
	Vector3 *(MeshGeometryClass::*asMemberBool)(bool);
};

class BfmeC998
{
public:
	virtual void bfmeVX0998();
	virtual void bfmeVX1998();
	virtual void bfmeVX2998();
	virtual void bfmeVX3998();
	virtual void bfmeApply998(int v, int a);

	void bfmeGo998C(int a);

	char m_bfmePad[0x14];
	int m_bfmeFlags;
};

void BfmeC998::bfmeGo998C(int a)
{
	Rva00927230Getter cast;
	cast.asMemberBool = &MeshGeometryClass::get_vert_normals;
	MeshGeometryClass *self = (MeshGeometryClass *)this;

	if (m_bfmeFlags & 4)
		bfmeApply998((int)(self->*cast.asMember)(a), a);

	(self->*cast.asMember)(a);
}