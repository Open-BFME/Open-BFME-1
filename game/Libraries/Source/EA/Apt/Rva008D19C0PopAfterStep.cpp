// ?aptPopAfter008D19C0@@YAXPAURva008D19C0Stack@@H@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
struct Rva008D19C0Value { virtual void s0(); virtual void release(); unsigned int m_bits; };
struct Rva008D19C0Stack { int m_count; int m_4; Rva008D19C0Value** m_values; };
class Rva8CD130IdleHook { public: int m_unused; int m_enabled; void run(); };
extern Rva8CD130IdleHook *g_rva8CD130IdleHook;
extern "C" void __cdecl bfmeStep1211A(Rva008D19C0Stack* stack, int arg);
void aptPopAfter008D19C0(Rva008D19C0Stack* stack, int arg)
{
	bfmeStep1211A(stack, arg);
	Rva008D19C0Value* top = stack->m_values[stack->m_count - 1];
	unsigned char flags = (unsigned char)(top->m_bits >> 30);
	if (!(flags & 1))
		top->release();
	stack->m_count--;
	if (g_rva8CD130IdleHook->m_enabled && stack->m_count == 0)
		g_rva8CD130IdleHook->run();
}
