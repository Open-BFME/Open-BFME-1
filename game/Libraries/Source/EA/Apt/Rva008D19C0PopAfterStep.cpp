// Apt stack wrappers at 0x008D19C0 and 0x008D1A50.
// cl: /DNDEBUG /MD /EHsc
struct Rva008D19C0Value { virtual void s0(); virtual void release(); unsigned int m_bits; };
struct Rva008D19C0Stack { int m_count; int m_4; Rva008D19C0Value** m_values; };
// Local view of the pool global's layout at 0x01337810; the canonical
// declaration of that global is `struct Rva00899560Pool *g_rva01337810GcRoots`
// (defined once in game/Libraries/Source/Apt/Apt.cpp), so only the view lives
// here and every use casts.
class Rva8CD130IdleHook { public: int m_unused; int m_enabled; };
struct Rva00899560Pool;
extern Rva00899560Pool *g_rva01337810GcRoots;
// The existing MASM owners use address-derived void() symbols. Retail passes
// two cdecl stack arguments to each step and only ECX to the idle hook.
extern void d_008d0b00();
extern void d_008d0f10();
extern void d_008a30c0();
typedef void (__cdecl *Rva008D19C0Step)(Rva008D19C0Stack*, int);
typedef void (__fastcall *Rva008D19C0Idle)(Rva8CD130IdleHook*);
void aptPopAfter008D19C0(Rva008D19C0Stack* stack, int arg)
{
	(reinterpret_cast<Rva008D19C0Step>(d_008d0b00))(stack, arg);
	Rva008D19C0Value* top = stack->m_values[stack->m_count - 1];
	unsigned char flags = (unsigned char)(top->m_bits >> 30);
	if (!(flags & 1))
		top->release();
	stack->m_count--;
	if (((Rva8CD130IdleHook *)g_rva01337810GcRoots)->m_enabled && stack->m_count == 0)
		(reinterpret_cast<Rva008D19C0Idle>(d_008a30c0))((Rva8CD130IdleHook *)g_rva01337810GcRoots);
}

void aptPopAfter008D1A50(Rva008D19C0Stack* stack, int arg)
{
	(reinterpret_cast<Rva008D19C0Step>(d_008d0f10))(stack, arg);
	Rva008D19C0Value* top = stack->m_values[stack->m_count - 1];
	unsigned char flags = (unsigned char)(top->m_bits >> 30);
	if (!(flags & 1))
		top->release();
	stack->m_count--;
	if (((Rva8CD130IdleHook *)g_rva01337810GcRoots)->m_enabled && stack->m_count == 0)
		(reinterpret_cast<Rva008D19C0Idle>(d_008a30c0))((Rva8CD130IdleHook *)g_rva01337810GcRoots);
}
