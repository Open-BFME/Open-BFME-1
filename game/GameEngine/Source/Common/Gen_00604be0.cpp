// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: the 22-byte adjustor unregister at 0x00604BE0, address-derived
// name. Converted out of game/gen_asm/d_00601890.asm.
//
// IDENTITY IS NOT ASSERTED. The bytes say: a __thiscall member sitting at a
// +0x0C secondary base subobject that, when the global registry pointer at
// 0x012F10D0 is non-null, calls one of that registry's methods with the
// primary base pointer (this - 12). This is the same registry global that
// GameClient/AnimationSoundClientBehaviorDestructors.cpp already reaches, and the
// callee at 0x00409040 has the same node layout as the named
// AnimationSoundClientBehaviorGlobal::unregister at 0x00409140 -- but the
// method NAME at 0x00409040 is not evidenced, so the pin below is
// address-derived and disclaims identity.
//
// Relocation note: this row needed exactly one additive targets/game/reverse/symbols.csv
// entry, `?m@Gen_00409040Registry@@QAEXPAX@Z` -> 0x00409040. The callee had
// to be spelled as a __thiscall member because retail loads ecx from the
// global, and the pre-existing `?b_00409040@@YAXXZ` pin is __cdecl.

class Gen_00409040Registry
{
public:
	void m(void *node);
};

extern Gen_00409040Registry *g_012F10D0;

class Gen_00604be0
{
public:
	void n(void);
};

void Gen_00604be0::n(void)
{
	if (g_012F10D0 != 0)
		g_012F10D0->m((char *)this - 12);
}
