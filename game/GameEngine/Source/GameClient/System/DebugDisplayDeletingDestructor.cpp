// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
//
// Open-BFME: DebugDisplay scalar-deleting destructor at retail RVA
// 0x005BD250 (30 bytes).  The exact constructor at 0x005BD1C0 installs the
// DebugDisplay vtable at 0x0110F8D4; slot zero is ILT 0x00005155, whose jump
// reaches this wrapper.  Its complete destructor is the 7-byte body at
// 0x005BD280, which reseats the DebugDisplayInterface vtable at 0x0110F898.

class DebugDisplayInterface
{
public:
	virtual ~DebugDisplayInterface() {}
};

class DebugDisplay : public DebugDisplayInterface
{
public:
	virtual ~DebugDisplay() {}
};

void forceDebugDisplayDeletingDestructor()
{
	DebugDisplay value;
}
