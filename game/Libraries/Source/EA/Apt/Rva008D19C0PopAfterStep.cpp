// Apt stack wrappers at 0x008D19C0 and 0x008D1A50.
// cl: /DNDEBUG /MD /EHsc
struct Rva008D19C0Value { virtual void s0(); virtual void release(); unsigned int m_bits; };
struct Rva008D19C0Stack { int m_count; int m_4; Rva008D19C0Value** m_values; };
// Local view of the pool global's layout at 0x01337810; the canonical
// declaration of that global is `struct Rva00899560Pool *g_rva01337810GcRoots`
// (defined once in game/Libraries/Source/Apt/Apt.cpp), so only the view lives
// here and every use casts.
class Rva8CD130IdleHook { public: int m_unused; int m_enabled; void run(); };
struct Rva00899560Pool;
extern Rva00899560Pool *g_rva01337810GcRoots;
extern "C" void __cdecl bfmeStep1211A(Rva008D19C0Stack* stack, int arg);
extern "C" void __cdecl bfmeStep1212A(Rva008D19C0Stack* stack, int arg);
void aptPopAfter008D19C0(Rva008D19C0Stack* stack, int arg)
{
	bfmeStep1211A(stack, arg);
	Rva008D19C0Value* top = stack->m_values[stack->m_count - 1];
	unsigned char flags = (unsigned char)(top->m_bits >> 30);
	if (!(flags & 1))
		top->release();
	stack->m_count--;
	if (((Rva8CD130IdleHook *)g_rva01337810GcRoots)->m_enabled && stack->m_count == 0)
		((Rva8CD130IdleHook *)g_rva01337810GcRoots)->run();
}

void aptPopAfter008D1A50(Rva008D19C0Stack* stack, int arg)
{
	bfmeStep1212A(stack, arg);
	Rva008D19C0Value* top = stack->m_values[stack->m_count - 1];
	unsigned char flags = (unsigned char)(top->m_bits >> 30);
	if (!(flags & 1))
		top->release();
	stack->m_count--;
	if (((Rva8CD130IdleHook *)g_rva01337810GcRoots)->m_enabled && stack->m_count == 0)
		((Rva8CD130IdleHook *)g_rva01337810GcRoots)->run();
}
