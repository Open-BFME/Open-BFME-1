// cl: /O2 /MD
// 5-byte ILT at 0x000309CC; its sole target is the W3DSmudgeManager
// ReleaseResources body at 0x00722190 (vtable slot 0x0C). Naming the virtual
// member's decorated symbol directly keeps the plain `E9 rel32` with ECX
// untouched.

extern "C" void __identifier("?ReleaseResources@W3DSmudgeManager@@UAEXXZ")();

void j_000309cc()
{
	__identifier("?ReleaseResources@W3DSmudgeManager@@UAEXXZ")();
}
