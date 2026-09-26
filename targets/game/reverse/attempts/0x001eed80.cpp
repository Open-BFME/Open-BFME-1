// ?checkForAutoHeal@@YAXPAVObject@@PAX@Z
// partial score=0.8 date=2026-09-06
// Retail uses a private call convention. It passes the object in ebx and the
// helper in eax. Inline assembly preserves the call, but MSVC saves esi before
// the retail ebx load, so this body remains a near miss.

extern void d_001ee670();

namespace _STL
{
class __new_alloc
{
public:
	static void *allocate(unsigned int);
};
}

static void checkForAutoHeal(void *, void *)
{
	__asm
	{
		mov ebx, [esp + 8]
		mov esi, [esp + 0x10]
		mov eax, esi
		call d_001ee670
		test al, al
		jz checkForAutoHeal_done
		mov eax, [esi + 0x1c]
		mov esi, [eax]
		push 0x0c
		call _STL::__new_alloc::allocate
		lea ecx, [eax + 8]
		add esp, 4
		test ecx, ecx
		jz checkForAutoHeal_done
		mov [ecx], ebx
		mov ecx, [esi + 4]
		mov [eax], esi
		mov [eax + 4], ecx
		mov [ecx], eax
		mov [esi + 4], eax
		mov eax, 1
	checkForAutoHeal_done:
	}
}
