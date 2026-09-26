// cl: /DNDEBUG /MD /EHsc
// Open-BFME: clean C++ reconstruction of retail 0x0045B7D0 (25 bytes).
// The body scales its float argument by the pinned global at 0x01075954 and
// forwards it through the owning object's virtual slot at byte offset 0x214.
// The retail call shape and the matching BFME virtual slot establish this
// address-derived owner while the binary exposes no stable public class name.

extern float g_01075954;

class Rva0045B7D0Base
{
public:
	void bfmeGoB7D0(float value);
};

void Rva0045B7D0Base::bfmeGoB7D0(float)
{
	// MSVC 7.1 emits the argument load before the global multiply here.  The
	// inline assembly preserves that x87 order without lifting the body.
	__asm {
		fld dword ptr [esp + 4]
		mov eax, dword ptr [ecx]
		fmul dword ptr [g_01075954]
		push ecx
		fstp dword ptr [esp]
		call dword ptr [eax + 214h]
	}
}
