// ?aptPopAfter008D19C0@@YAXPAURva008D19C0Stack@@H@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
struct Rva008D19C0Value { virtual void s0(); virtual void release(); unsigned int m_low : 30; unsigned int m_owned : 1; unsigned int m_high : 1; };
struct Rva008D19C0Stack { int m_count; int m_4; Rva008D19C0Value** m_values; };
struct Rva008D19C0Hook { int m_0; int m_armed; };
extern Rva008D19C0Hook* Rva008D19C0IdleHook;
void __cdecl Rva008D19C0Op008D19C0(Rva008D19C0Stack* stack, int arg);
void __cdecl Rva008D19C0Idle();
void aptPopAfter008D19C0(Rva008D19C0Stack* stack, int arg)
{
	Rva008D19C0Op008D19C0(stack, arg);
	Rva008D19C0Value* top = stack->m_values[stack->m_count - 1];
	if (!top->m_owned)
		top->release();
	stack->m_count--;
	if (Rva008D19C0IdleHook->m_armed && stack->m_count == 0)
		Rva008D19C0Idle();
}
