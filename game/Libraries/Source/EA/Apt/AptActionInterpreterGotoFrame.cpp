// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// EA Apt ActionScript GotoFrame (opcode 0x81), retail 0x008CA890. The
// interpreter's opcode table is indexed by the Flash action code from
// 0x00ED5A68 (see AptActionInterpreterStoreRegister.cpp), which puts this
// body in slot 0x81 at 0x00ED5C6C.
//
// The operand is the frame as an aligned dword. The target is the context's
// +8 object when it is a sprite with its +4 flag word's bit 15 set, else
// the +4 object under the same test (that one is not null-checked, as
// retail reads it unguarded). The sprite goes to the frame through
// 0x008D2130 and its +0x50 record's +0x1C flags lose bit 25. Afterwards the
// idle hook runs when it is enabled and the interpreter's stack is empty.

class AptObject
{
public:
	void bfmeStepCBC( int frame );

	int m_pad00;
	unsigned int m_flags;
	char m_pad08[0x48];
	struct State { char m_pad[0x1C]; unsigned int m_flags; } *m_state;
};
// The 0x008D2130 method's pinned spelling.
class BfmeThingCBC
{
public:
	void bfmeStepCBC( int frame );
};

static inline bool isTargetSprite( const AptObject *o )
{
	int kind = o->m_flags & 0x3F;
	return kind >= 12 && kind <= 19 && !( (unsigned char)~( o->m_flags >> 15 ) & 1 );
}

class Rva8CD130IdleHook
{
public:
	void run();
};

class Rva8CCED0IdleHook
{
public:
	int m_unused;
	int m_enabled;
};

// Retail 0x01337810 is ?g_rva01337810GcRoots@@3PAURva00899560Pool@@A (data_rows.csv,
// Apt/Apt.cpp); g_rva8CD130IdleHook was only a pin.
struct Rva00899560Pool;
extern Rva00899560Pool *g_rva01337810GcRoots;
#define g_rva8CD130IdleHook ( *(Rva8CD130IdleHook **)&g_rva01337810GcRoots )

class AptActionInterpreter
{
public:
	struct LocalContextT
	{
		const unsigned char *m_pc;
		AptObject *m_object04;
		AptObject *m_object08;
	};

	static void _FunctionAptActionGotoFrame(
		AptActionInterpreter *interpreter, LocalContextT *context);

	int m_stackTop;
};

void AptActionInterpreter::_FunctionAptActionGotoFrame(
	AptActionInterpreter *interpreter, LocalContextT *context)
{
	const unsigned char *p = (const unsigned char *)(((unsigned int)context->m_pc + 3) & ~3u);
	context->m_pc = p + 4;

	AptObject *target = 0;
	if ( context->m_object08 && isTargetSprite( context->m_object08 ) )
		target = context->m_object08;
	else if ( isTargetSprite( context->m_object04 ) )
		target = context->m_object04;
	if ( target )
	{
		( (BfmeThingCBC *)target )->bfmeStepCBC( *(const int *)p );
		target->m_state->m_flags &= ~0x02000000u;
	}

	if ( ( (Rva8CCED0IdleHook *)g_rva8CD130IdleHook )->m_enabled && interpreter->m_stackTop == 0 )
		g_rva8CD130IdleHook->run();
}
