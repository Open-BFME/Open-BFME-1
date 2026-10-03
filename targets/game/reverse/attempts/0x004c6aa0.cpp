// ?bfmeReg1033@@YAXP6AXXZ0@Z
// partial score=0.8627 date=2026-10-03
// cl: /DNDEBUG /MD /EHsc
extern int g_012F3930;
extern int g_012F3934;

void bfmeReg1033(void (*a)(void), void (*b)(void))
{
	__asm
	{
		mov eax, fs:[0]
		push -1
		push 01029600h
		push eax
	}
	int zero = 0;
	__asm
	{
		mov fs:[0], esp
	}
	g_012F3930 = zero;
	g_012F3934 = zero;
	__asm
	{
		call dword ptr [esp + 10h]
		mov ecx, [esp]
		mov fs:[0], ecx
		add esp, 0Ch
	}
}
